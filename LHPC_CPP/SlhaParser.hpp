/*
 * SlhaParser.hpp
 *
 *  Created on: Jan 11, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.LHPC_CPP.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#ifndef SLHAPARSER_HPP_
#define SLHAPARSER_HPP_

#include <string>
#include <map>
#include "BOLlib/Classes/CommentedTextParser.hpp"
#include "BOLlib/Classes/VectorlikeArray.hpp"
#include "MassEigenstateCollectionClasses/MassSpectrum.hpp"
#include "SusyLesHouchesAccordClasses/BlockTypes.hpp"

namespace LHPC
{
  // this is a class for reading in a SLHA format file & parsing the data from
  // it.
  class SlhaParser
  {
  public:
    SlhaParser( bool const isVerbose = true );
    ~SlhaParser();

    void
    registerSpectrum( MassSpectrum& spectrumToUpdate );
    // this adds a pointer to spectrumToUpdate to spectraToUpdate so that its
    // data get updated during each readFile().
    void
    registerBlock( SLHA::SlhaBlock& blockToUpdate );
    // this registers blockToUpdate so that its data get updated every time a
    // new block of the appropriate name is read.
    void
    registerBlock( SLHA::FmassBlock& blockToUpdate );
    // this is a special case to try to catch if an FMASS block is given, so
    // that the spectrum (if any) can read from it rather than needing its own.
    void
    registerBlock( SLHA::MassBlock& blockToUpdate );
    // this is a special case to try to catch if a MASS block is given, so that
    // the spectrum (if any) can read from it rather than needing its own.
    bool
    readFile( std::string const& slhaFileName );
    /* this opens the file with name given by slhaFileName, parses its data
     * into strings, & passes each registered SlhaBlock & each BaseSlhaDecay
     * its appropriate string to interpret.
     */


  protected:
    typedef std::map< std::string,
                      SLHA::SlhaBlock* > StringToBlockMap;
    typedef std::pair< std::string,
                       SLHA::SlhaBlock* > StringAndBlockPair;
    typedef std::map< int,
                      double > IntToDoubleMap;
    typedef std::map< int,
                      ExtendedMass > IntToExtendedMassMap;

    bool const isVerbose;
    BOL::CommentedTextParser fileParser;
    MassSpectrum* spectrumToUpdate;
    StringToBlockMap blockMap;
    StringToBlockMap::iterator blockMapIterator;
    StringAndBlockPair mapInserter;
    SLHA::MassBlock* massBlockPointer;
    bool ownsMassBlock;
    SLHA::FmassBlock* fmassBlockPointer;
    bool ownsFmassBlock;
    SLHA::SlhaBlock* currentBlockPointer;
    MassEigenstate* currentMassEigenstate;
    std::string dataString;
    std::string commentString;
    std::string firstWordOfLine;
    BOL::VectorlikeArray< std::string > wordsOfLine;
    MassEigenstate::MassEigenstatesPairedWithBr decayRecorder;
    double recordedDecayWidth;
    IntToDoubleMap const* massMap;
    IntToDoubleMap::const_iterator massMapIterator;
    IntToExtendedMassMap const* fmassMap;
    IntToExtendedMassMap::const_iterator fmassMapIterator;

    void
    addBlockToMap( SLHA::SlhaBlock* const blockToUpdate );
    // this adds blockToUpdate to blockMap, so that its data get updated during
    // each readFile().
    void
    clearBlocks();
    // this goes through all the blocks in blockMap & calls their
    // clearEntries() member functions.
    void
    checkForMassBlocksForSpectrum();
    // this ensures that if there is a spectrum to update, there are both
    // blocks for MASS & FMASS.
    void
    prepareToReadNewBlock();
    // this parses the block header line & sets currentBlockPointer
    // appropriately, & calls checkForBlockScaleOrDecayWidth().
    void
    prepareToReadNewDecay();
    // this parses the decay header line & sets currentBlockPointer
    // appropriately, & calls checkForBlockScaleOrDecayWidth().
    void
    recordDecayLine();
    // this interprets the current line as a decay for the spectrum.
    void
    ensureSpectrumRecordsMasses();
    // this reads the masses from the MASS & FMASS blocks into the spectrum,
    // if necessary.
    void
    ensureSpectrumRecordsChargeConjugateDecays();
    /* this checks each particle in spectrumToUpdate for whether it is
     * self-conjugate, & if not, this checks to see if the charge-conjugate's
     * decays were already recorded, & if not, this gives the charge-conjugate
     * the charge-conjugate decays of the checked particle.
     */
    void
    prepareForEitherBlockOrDecay();
    // this sets up the common parsing of the line being read.
  };





  inline SlhaParser&
  SlhaParser::registerSpectrum( MassSpectrum& spectrumToUpdate )
  // this adds a pointer to spectrumToUpdate to spectraToUpdate so that its
  // data get updated during each readFile().
  {
    this->spectrumToUpdate = &spectrumToUpdate;
    return *this;
  }

  inline void
  SlhaParser::registerBlock( SLHA::SlhaBlock& blockToUpdate )
  // this registers blockToUpdate so that its data get updated every time a
  // new block of the appropriate name is read.
  {
    addBlockToMap( &blockToUpdate );
  }

  inline void
  SlhaParser::registerBlock( SLHA::FmassBlock& blockToUpdate )
  // this is a special case to try to catch if an FMASS block is given, so
  // that the spectrum (if any) can read from it rather than needing its own.
  {
    addBlockToMap( &blockToUpdate );
    if( blockToUpdate.nameMatches( "FMASS" ) )
    {
      fmassBlockPointer = &blockToUpdate;
    }
  }

  inline void
  SlhaParser::registerBlock( SLHA::MassBlock& blockToUpdate )
  // this is a special case to try to catch if a MASS block is given, so that
  // the spectrum (if any) can read from it rather than needing its own.
  {
    addBlockToMap( &blockToUpdate );
    if( blockToUpdate.nameMatches( "MASS" ) )
    {
      massBlockPointer = &blockToUpdate;
    }
  }

  inline void
  SlhaParser::addBlockToMap( SLHA::SlhaBlock* const blockToUpdate )
  // this adds blockToUpdate to blockMap, so that its data get updated during
  // each readFile().
  {
    blockMapIterator = blockMap.find( blockToUpdate->getName() );
    if( blockMap.end() == blockMapIterator )
    {
      mapInserter.first.assign( blockToUpdate->getName() );
      mapInserter.second = blockToUpdate;
      blockMap.insert( mapInserter );
    }
    else
    {
      std::string errorMessage( "LHPC::SlhaParser::error! \"BLOCK " );
      errorMessage.append( blockToUpdate->getName() );
      errorMessage.append(
                   "\" is already registered with this SlhaParser instance." );
      throw std::range_error( errorMessage );
    }
  }

  inline void
  SlhaParser::clearBlocks()
  // this goes through all the blocks in blockMap & calls their clearEntries()
  // member functions.
  {
    blockMapIterator = blockMap.begin();
    if( NULL != spectrumToUpdate )
    {
      spectrumToUpdate->clearMassesAndDecays();
    }
    while( blockMap.end() != blockMapIterator )
    {
      blockMapIterator->second->clearEntries();
      ++blockMapIterator;
    }
  }

  inline void
  SlhaParser::checkForMassBlocksForSpectrum()
  // this ensures that if there is a spectrum to update, there are both
  // blocks for MASS & FMASS.
  {
    if( NULL != spectrumToUpdate )
    {
      if( NULL == massBlockPointer )
        // if there is a spectrum to update, but no mass block...
      {
        ownsMassBlock = true;
        massBlockPointer = new SLHA::MassBlock( "MASS",
                                                BOL::UsefulStuff::notANumber,
                                                9 );
        addBlockToMap( massBlockPointer );
      }
      if( NULL == fmassBlockPointer )
        // if there is a spectrum to update, but no fmass block...
      {
        ownsFmassBlock = true;
        fmassBlockPointer = new SLHA::FmassBlock( "FMASS",
                                                  ExtendedMass(),
                                                  9 );
        addBlockToMap( fmassBlockPointer );
      }
      // mass & fmass blocks for the spectrum/spectra should be made,
      // remembering to delete them in the destructor.
    }
  }

  inline void
  SlhaParser::prepareToReadNewBlock()
  // this parses the block header line & sets currentBlockPointer
  // appropriately, & calls checkForBlockScaleOrDecayWidth().
  {
    prepareForEitherBlockOrDecay();
    if( 2 <= wordsOfLine.getSize() )
      // if the line at least has a string for the block name...
    {
      BOL::StringParser::transformToUppercase( wordsOfLine[ 1 ] );
      blockMapIterator = blockMap.find( wordsOfLine[ 1 ] );
      if( blockMap.end() != blockMapIterator )
        // if the name corresponds to a block that should be recorded...
      {
        currentBlockPointer = blockMapIterator->second;
        if( 3 <= wordsOfLine.getSize() )
        {
          currentBlockPointer->recordScale(
                  BOL::StringParser::stringToDouble( wordsOfLine.getBack() ) );
        }
        else
        {
          currentBlockPointer->recordScale( 0.0 );
        }
      }
    }
  }

  inline void
  SlhaParser::prepareToReadNewDecay()
  // this parses the block header line & sets currentMassEigenstate
  // appropriately, & records its decay width.
  {
    prepareForEitherBlockOrDecay();
    if( ( NULL != spectrumToUpdate )
        &&
        ( 3 == wordsOfLine.getSize() ) )
      // if there is a spectrum for recording decays, & if the line has the
      // right number of entries ("DECAY", particle code, decay width)...
    {
      currentMassEigenstate = spectrumToUpdate->getMassEigenstate(
                          BOL::StringParser::stringToInt( wordsOfLine[ 1 ] ) );
      currentMassEigenstate->setDecayWidth(
                       BOL::StringParser::stringToDouble( wordsOfLine[ 2 ] ) );
    }
  }

  inline void
  SlhaParser::recordDecayLine()
  // this interprets the current line as a decay for the spectrum.
  {
    wordsOfLine.clearEntries();
    BOL::StringParser::parseByChar( dataString,
                                    wordsOfLine,
                                    BOL::StringParser::whitespaceChars );
    if( !(wordsOfLine.isEmpty()) )
    {
      decayRecorder.clearPointers();
      for( int whichWord( wordsOfLine.getLastIndex() );
           1 < whichWord;
           --whichWord )
      {
        decayRecorder.addPointer( spectrumToUpdate->getMassEigenstate(
                BOL::StringParser::stringToInt( wordsOfLine[ whichWord ] ) ) );
      }
      decayRecorder.setPairedValueAndSortPointers(
                       BOL::StringParser::stringToDouble( wordsOfLine[ 0 ] ) );
      currentMassEigenstate->recordDecay( decayRecorder );
      // decays are only parsed properly to go into MassEigenstate instances.
    }
  }

  inline void
  SlhaParser::prepareForEitherBlockOrDecay()
  // this sets up the common parsing of the line being read.
  {
    currentBlockPointer = NULL;
    currentMassEigenstate = NULL;
    // first it is assumed that the block is not one that is looked for.
    wordsOfLine.clearEntries();
    BOL::StringParser::parseByChar( dataString,
                                    wordsOfLine,
                                    BOL::StringParser::whitespaceChars );
  }

}

#endif /* SLHAPARSER_HPP_ */
