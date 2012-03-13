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
#include "../BOLlib/Classes/CommentedTextParser.hpp"
#include "../BOLlib/Classes/VectorlikeArray.hpp"
#include "../MassEigenstateCollectionClasses/MassSpectrum.hpp"
#include "../MassEigenstateCollectionClasses/ExtendedMass.hpp"
#include "BasicParser.hpp"
#include "BlockTypes.hpp"

namespace LHPC
{
  // this is a class for reading in a SLHA format file & parsing the data from
  // it.
  class SlhaParser : public SLHA::BasicParser
  {
  public:
    SlhaParser( bool const shouldRecordBlocksNotRegistered = true,
                bool const isVerbose = true);
    virtual
    ~SlhaParser();

    virtual SLHA::SameNameBlockSet*
    registerBlock(
          SLHA::InterpreterClass::BlockInterpreterFactory& blockToUpdate );
    // this registers blockToUpdate so that its data get updated every time a
    // new block of the appropriate name is read.
    void
    registerSpectrum( MassSpectrum& spectrumToUpdate );
    // this adds a pointer to spectrumToUpdate to spectraToUpdate so that its
    // data get updated during each readFile().
    bool
    readFile( std::string const& slhaFileName );
    /* this opens the file with name given by slhaFileName, parses its data
     * into strings, & passes each registered SlhaBlock & each BaseSlhaDecay
     * its appropriate string to interpret.
     */
    SLHA::SameNameBlockSet*
    getBlockAsStrings( std::string blockName );
    SLHA::SameNameBlockSet const*
    getBlockAsStrings( std::string blockName ) const;


  protected:
    std::vector< MassSpectrum* > spectraToUpdate;
    SLHA::InterpreterClass::BlockInterpreterFactory* fmassBlockPointer;
    bool ownsFmassBlock;
    std::map< int, ExtendedMass > const* fmassMap;
    std::map< int, ExtendedMass >::const_iterator fmassMapIterator;
    SLHA::InterpreterClass::BlockInterpreterFactory* massBlockPointer;
    bool ownsMassBlock;
    std::map< int, double > const* massMap;
    std::map< int, double >::const_iterator massMapIterator;
    std::vector< MassEigenstate* > currentMassEigenstates;
    MassEigenstate* massEigenstateFiller;
    std::vector< int > decayProductCodes;
    MassEigenstate::MassEigenstatesPairedWithBr decayRecorder;
    double recordedDecayWidth;

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
    ensureSpectraRecordMasses();
    // this reads the masses from the FMASS & MASS blocks into the spectrum, if
    // necessary.
    void
    ensureSpectraRecordChargeConjugateDecays();
    /* this checks each particle in spectrumToUpdate for whether it is
     * self-conjugate, & if not, this checks to see if the charge-conjugate's
     * decays were already recorded, & if not, this gives the charge-conjugate
     * the charge-conjugate decays of the checked particle.
     */
    void
    prepareForEitherBlockOrDecay();
    // this sets up the common parsing of the line being read.
  };





  inline void
  SlhaParser::registerSpectrum( MassSpectrum& spectrumToUpdate )
  // this adds a pointer to spectrumToUpdate to spectraToUpdate so that its
  // data get updated during each readFile().
  {
    spectraToUpdate.push_back( &spectrumToUpdate );
  }

  inline SLHA::SameNameBlockSet*
  SlhaParser::registerBlock(
             SLHA::InterpreterClass::BlockInterpreterFactory& blockToUpdate )
  // this registers blockToUpdate so that its data get updated every time a
  // new block of the appropriate name is read.
  {
    SLHA::SameNameBlockSet* returnPointer( NULL );
    blockMapIterator = blockMap.find( blockToUpdate.getName() );
    if( blockMap.end() == blockMapIterator )
    {
      mapInserter.first.assign( blockToUpdate.getName() );
      returnPointer = new SLHA::SameNameBlockSet( mapInserter.first );
      mapInserter.second = returnPointer;
      blockMap.insert( mapInserter );
    }
    else
    {
      returnPointer = blockMapIterator->second;
    }
    if( blockToUpdate.nameMatches( "FMASS" ) )
    {
      fmassBlockPointer = &blockToUpdate;
    }
    if( blockToUpdate.nameMatches( "MASS" ) )
    {
      massBlockPointer = &blockToUpdate;
    }
    returnPointer->registerBlock( blockToUpdate );
    return returnPointer;
  }

  inline SLHA::SameNameBlockSet*
  SlhaParser::getBlockAsStrings( std::string blockName )
  {
    BOL::StringParser::transformToUppercase( blockName );
    blockMapIterator = blockMap.find( blockName );
    if( blockMap.end() == blockMapIterator )
    {
      return NULL;
    }
    else
    {
      return blockMapIterator->second;
    }
  }

  inline SLHA::SameNameBlockSet const*
  SlhaParser::getBlockAsStrings( std::string blockName ) const
  {
    BOL::StringParser::transformToUppercase( blockName );
    std::map< std::string, SLHA::SameNameBlockSet* >::const_iterator
    constBlockMapIterator( blockMap.find( blockName ) );
    if( blockMap.end() == constBlockMapIterator )
    {
      return NULL;
    }
    else
    {
      return constBlockMapIterator->second;
    }
  }

  inline void
  SlhaParser::clearBlocks()
  // this goes through all the blocks in blockMap & calls their clearEntries()
  // member functions.
  {
    for( int whichSpectrum( spectraToUpdate.size() - 1 );
         0 <= whichSpectrum;
         --whichSpectrum )
    {
      spectraToUpdate[ whichSpectrum ]->clearMassesAndDecays();
    }
    blockMapIterator = blockMap.begin();
    while( blockMap.end() != blockMapIterator )
    {
      blockMapIterator->second->clearEntries();
      ++blockMapIterator;
    }
  }

  inline void
  SlhaParser::prepareForEitherBlockOrDecay()
  // this sets up the common parsing of the line being read.
  {
    if( NULL != currentBlockPointer )
    {
      currentBlockPointer->finishRecordingLines();
    }
    currentBlockPointer = NULL;
    currentMassEigenstates.clear();
    // first it is assumed that the block is not one that is looked for, or
    // that none of the spectra need to record this decay.
    wordsOfLine.clearEntries();
    BOL::StringParser::parseByChar( dataString,
                                    wordsOfLine,
                                    BOL::StringParser::whitespaceChars );
  }

}

#endif /* SLHAPARSER_HPP_ */
