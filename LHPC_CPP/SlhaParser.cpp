/*
 * SlhaParser.cpp
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

#include "SlhaParser.hpp"

namespace LHPC
{
  SlhaParser::SlhaParser( bool const isVerbose ) :
      isVerbose( isVerbose ),
      fileParser( "#",
                  this->isVerbose ),
      spectraToUpdate(),
      blockMap(),
      blockMapIterator(),
      mapInserter( "",
                   NULL ),
      fmassBlockPointer( NULL ),
      ownsFmassBlock( false ),
      massBlockPointer( NULL ),
      ownsMassBlock( false ),
      currentBlockPointer( NULL ),
      currentMassEigenstates(),
      massEigenstateFiller( NULL ),
      dataString( "" ),
      commentString( "" ),
      firstWordOfLine( "" ),
      wordsOfLine( 2 ),
      decayProductCodes(),
      decayRecorder(),
      recordedDecayWidth( BOL::UsefulStuff::notANumber ),
      fmassMap(),
      fmassMapIterator(),
      massMap(),
      massMapIterator()
  {
    // just an initialization list.
  }

  SlhaParser::~SlhaParser()
  {
    if( ownsMassBlock )
    {
      delete massBlockPointer;
    }
    if( ownsFmassBlock )
    {
      delete fmassBlockPointer;
    }
    blockMapIterator = blockMap.begin();
    while( blockMap.end() != blockMapIterator )
    {
      delete blockMapIterator->second;
      ++blockMapIterator;
    }
  }


  bool
  SlhaParser::readFile( std::string const& slhaFileName )
  /* this opens the file with name given by slhaFileName, parses its data
   * into strings, & passes each registered SlhaBlock & each BaseSlhaDecay
   * its appropriate string to interpret.
   */
  {
    bool successfullyRead( false );
    clearBlocks();
    // new data should overwrite the old data, not append to it.

    checkForMassBlocksForSpectrum();

    successfullyRead = fileParser.openFile( slhaFileName );
    while( fileParser.parseNextLineOfFile( dataString,
                                           commentString ) )
    {
      firstWordOfLine.assign( BOL::StringParser::substringToFirst(
                                           BOL::StringParser::substringToFirst(
                                              BOL::StringParser::trimFromFront(
                                                                    dataString,
                                          BOL::StringParser::whitespaceChars ),
                                                                         " " ),
                                                                      "\t" ) );
      // some perverts use tabs in their SLHA files.
      BOL::StringParser::transformToLowercase( firstWordOfLine );
      if( 0 == firstWordOfLine.compare( "block" ) )
      {
        prepareToReadNewBlock();
      }
      else if( 0 == firstWordOfLine.compare( "decay" ) )
      {
        prepareToReadNewDecay();
      }
      else if( NULL != currentBlockPointer )
        // otherwise, if a block is being recorded...
      {
        currentBlockPointer->recordBodyLine( dataString,
                                             commentString );
      }
      else if( !(currentMassEigenstates.empty()) )
        // otherwise, if a decay is being recorded...
      {
        recordDecayLine();
      }
      commentString.clear();
    }
    // the last block is closed after the last line has been read in:
    if( NULL != currentBlockPointer )
    {
      currentBlockPointer->finishRecordingLines();
    }

    // after reading in the file, any recorded masses are passed to
    // spectrumToUpdate if it is not NULL:
    ensureSpectraRecordMasses();
    ensureSpectraRecordChargeConjugateDecays();
    return successfullyRead;
  }

  void
  SlhaParser::checkForMassBlocksForSpectrum()
  // this ensures that if there is a spectrum to update, there are both
  // blocks for MASS & FMASS.
  {
    if( !(spectraToUpdate.empty()) )
    {
      if( NULL == fmassBlockPointer )
        // if there is at least 1 spectrum to update, but no fmass block...
      {
        ownsFmassBlock = true;
        fmassBlockPointer = new SLHA::FmassBlock( "FMASS",
                                                  ExtendedMass(),
                                                  9 );
        addBlockToMap( fmassBlockPointer );
      }
      if( NULL == massBlockPointer )
        // if there is at least 1 spectrum to update, but no mass block...
      {
        ownsMassBlock = true;
        massBlockPointer = new SLHA::MassBlock( "MASS",
                                                BOL::UsefulStuff::notANumber,
                                                9 );
        addBlockToMap( massBlockPointer );
      }
      // mass & fmass blocks for the spectrum/spectra should be made,
      // remembering to delete them in the destructor.
    }
  }

  void
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
        // if the name corresponds to a block that already exists in the map...
      {
        currentBlockPointer = blockMapIterator->second;
      }
      else if( shouldRecordBlocksNotRegistered )
        // otherwise, if it should be recorded anyway...
      {
        mapInserter.first.assign( wordsOfLine[ 1 ] );
        currentBlockPointer = new SLHA::SameNameBlockSet( mapInserter.first );
        // a new block is required.
        mapInserter.second = currentBlockPointer;
        blockMap.insert( mapInserter );
      }
      if( NULL != currentBlockPointer )
      {
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

  void
  SlhaParser::prepareToReadNewDecay()
  // this parses the block header line & sets currentMassEigenstate
  // appropriately, & records its decay width.
  {
    prepareForEitherBlockOrDecay();
    if( !(spectraToUpdate.empty())
        &&
        ( 3 == wordsOfLine.getSize() ) )
      // if there is a spectrum for recording decays, & if the line has the
      // right number of entries ("DECAY", particle code, decay width)...
    {
      for( int whichSpectrum( spectraToUpdate.size() - 1 );
           0 <= whichSpectrum;
           --whichSpectrum )
      {
        massEigenstateFiller
        = spectraToUpdate[ whichSpectrum ]->getMassEigenstate(
                          BOL::StringParser::stringToInt( wordsOfLine[ 1 ] ) );
        if( NULL != massEigenstateFiller )
        {
          currentMassEigenstates.push_back( massEigenstateFiller );
          massEigenstateFiller->setDecayWidth(
                         BOL::StringParser::stringToDouble( wordsOfLine[ 2 ] ) );
          // note that this spectrum needs to record this decay.
        }
      }
    }
  }

  void
  SlhaParser::recordDecayLine()
  // this interprets the current line as a decay for the spectrum.
  {
    wordsOfLine.clearEntries();
    BOL::StringParser::parseByChar( dataString,
                                    wordsOfLine,
                                    BOL::StringParser::whitespaceChars );
    if( !(wordsOfLine.isEmpty()) )
      // if there is a decay to record...
    {
      // first find the read the codes for the products:
      decayProductCodes.clear();
      for( int whichWord( wordsOfLine.getLastIndex() );
           1 < whichWord;
           --whichWord )
      {
        decayProductCodes.push_back( wordsOfLine[ whichWord ] );
      }
      // then for each MassEigenstate that needs to record this decay, prepare
      // decayRecorder & use it to record the decay:
      for( int whichSpectrum( currentMassEigenstates.size() - 1 );
           0 <= whichSpectrum;
           --whichSpectrum )
      {
        decayRecorder.clearPointers();
        for( int whichProduct( decayProductCodes.size() - 1 );
             0 <= whichProduct;
             --whichProduct )
        {
          decayRecorder.addPointer(
              currentMassEigenstates[ whichSpectrum ]->findPointerWithCode(
                                         decayProductCodes[ whichProduct ] ) );
        }
        decayRecorder.setPairedValueAndSortPointers(
                       BOL::StringParser::stringToDouble( wordsOfLine[ 0 ] ) );

        currentMassEigenstates[ whichSpectrum ]->recordDecay( decayRecorder );
      }
      // decays are only parsed properly to go into MassEigenstate instances.
    }
  }

  void
  SlhaParser::ensureSpectraRecordMasses()
  // this reads the masses from the FMASS & MASS blocks into the spectrum, if
  // necessary.
  {
    if( !(spectraToUpdate.empty()) )
    {
      massMap = massBlockPointer->getMap();
      if( NULL != massMap )
      {
        massMapIterator = massMap->begin();
        while( massMap->end() != massMapIterator )
        {
          for( int whichSpectrum( spectraToUpdate.size() - 1 );
               0 <= whichSpectrum;
               --whichSpectrum )
          {
            massEigenstateFiller
            = spectraToUpdate[ whichSpectrum ]->getMassEigenstate(
                                                      massMapIterator->first );
            if( NULL != massEigenstateFiller )
            {
              massEigenstateFiller->recordMass( massMapIterator->second );
              // now the charge-conjugate is considered:
              if( !(massEigenstateFiller->getChargeConjugate(
                                                     ).hasMassBeenRecorded()) )
              {
                massEigenstateFiller->getChargeConjugate().recordMass(
                                                     massMapIterator->second );
              }
            }
          }
          ++massMapIterator;
        }
      }
      fmassMap = fmassBlockPointer->getMap();
      if( NULL != fmassMap )
      {
        fmassMapIterator = fmassMap->begin();
        while( fmassMap->end() != fmassMapIterator )
        {
          for( int whichSpectrum( spectraToUpdate.size() - 1 );
               0 <= whichSpectrum;
               --whichSpectrum )
          {
            massEigenstateFiller
            = spectraToUpdate[ whichSpectrum ]->getMassEigenstate(
                                                     fmassMapIterator->first );
            if( NULL != massEigenstateFiller )
            {
              massEigenstateFiller->recordMass(
                                            fmassMapIterator->second.getMass(),
                                          fmassMapIterator->second.getScheme(),
                                         fmassMapIterator->second.getScale() );
              // now the charge-conjugate is considered:
              if( massEigenstateFiller->getChargeConjugate(
                                                ).getAllRecordedMasses().size()
                  < massEigenstateFiller->getAllRecordedMasses().size() )
              {
                massEigenstateFiller->getChargeConjugate().recordMass(
                                            fmassMapIterator->second.getMass(),
                                          fmassMapIterator->second.getScheme(),
                                         fmassMapIterator->second.getScale() );
              }
            }
          }
          ++fmassMapIterator;
        }
      }
    }
  }

  void
  SlhaParser::ensureSpectraRecordChargeConjugateDecays()
  /* this checks each particle in spectrumToUpdate for whether it is
   * self-conjugate, & if not, this checks to see if the charge-conjugate's
   * decays were already recorded, & if not, this gives the charge-conjugate
   * the charge-conjugate decays of the checked particle.
   */
  {
    for( int whichSpectrum( spectraToUpdate.size() - 1 );
         0 <= whichSpectrum;
         --whichSpectrum )
    {
      for( int
           whichParticle(
                spectraToUpdate[ whichSpectrum ]->getMassEigenstateSet().size()
                          - 1 );
           0 <= whichParticle;
           --whichParticle )
      {
        massEigenstateFiller
        = spectraToUpdate[ whichSpectrum ]->getMassEigenstateSet()[
                                                               whichParticle ];
        if( !(massEigenstateFiller->isSelfConjugate())
            &&
            !(massEigenstateFiller->getChargeConjugate(
                                                  ).haveDecaysBeenRecorded()) )
        {
          for( int whichDecay( massEigenstateFiller->getDecaySet().size()
                               - 1 );
               0 <= whichDecay;
               --whichDecay )
          {
            massEigenstateFiller->getChargeConjugate(
                                                ).recordChargeConjugateOfDecay(
                        *(massEigenstateFiller->getDecaySet()[ whichDecay ]) );
          }
          massEigenstateFiller->getChargeConjugate().setDecayWidth(
                                       massEigenstateFiller->getDecayWidth() );
        }
      }
    }
  }

}
