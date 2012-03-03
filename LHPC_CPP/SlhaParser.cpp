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
      spectrumToUpdate( NULL ),
      blockMap(),
      blockMapIterator(),
      mapInserter( "",
                   NULL ),
      massBlockPointer( NULL ),
      ownsMassBlock( false ),
      fmassBlockPointer( NULL ),
      ownsFmassBlock( false ),
      currentBlockPointer( NULL ),
      currentMassEigenstate( NULL ),
      dataString( "" ),
      commentString( "" ),
      firstWordOfLine( "" ),
      wordsOfLine( 2 ),
      decayRecorder(),
      massMap(),
      massMapIterator(),
      fmassMap(),
      fmassMapIterator()
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
      else if( NULL != currentMassEigenstate )
        // otherwise, if a decay is being recorded...
      {
        recordDecayLine();
      }
      commentString.clear();
    }

    // after reading in the file, any recorded masses are passed to
    // spectrumToUpdate if it is not NULL:
    ensureSpectrumRecordsMasses();
    ensureSpectrumRecordsChargeConjugateDecays();
    return successfullyRead;
  }

  void
  SlhaParser::ensureSpectrumRecordsMasses()
  // this reads the masses from the MASS & FMASS blocks into the spectrum,
  // if necessary.
  {
    if( NULL != spectrumToUpdate )
    {
      massMap = massBlockPointer->getMap();
      if( NULL != massMap )
      {
        massMapIterator = massMap->begin();
        while( massMap->end() != massMapIterator )
        {
          currentMassEigenstate
          = spectrumToUpdate->getMassEigenstate( massMapIterator->first );
          currentMassEigenstate->recordMass( massMapIterator->second );
          // now the charge-conjugate is considered:
          if( !(currentMassEigenstate->getChargeConjugate(
                                                     ).hasMassBeenRecorded()) )
          {
            currentMassEigenstate->getChargeConjugate().recordMass(
                                                     massMapIterator->second );
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
          currentMassEigenstate
          = spectrumToUpdate->getMassEigenstate( fmassMapIterator->first );
          currentMassEigenstate->recordMass(
                                            fmassMapIterator->second.getMass(),
                                          fmassMapIterator->second.getScheme(),
                                         fmassMapIterator->second.getScale() );
          // now the charge-conjugate is considered:
          if( currentMassEigenstate->getChargeConjugate().getAllRecordedMasses(
                                                                       ).size()
              < currentMassEigenstate->getAllRecordedMasses().size() )
          {
            currentMassEigenstate->getChargeConjugate().recordMass(
                                            fmassMapIterator->second.getMass(),
                                          fmassMapIterator->second.getScheme(),
                                         fmassMapIterator->second.getScale() );
          }
          ++fmassMapIterator;
        }
      }
    }
  }

  void
  SlhaParser::ensureSpectrumRecordsChargeConjugateDecays()
  /* this checks each particle in spectrumToUpdate for whether it is
   * self-conjugate, & if not, this checks to see if the charge-conjugate's
   * decays were already recorded, & if not, this gives the charge-conjugate
   * the charge-conjugate decays of the checked particle.
   */
  {
    if( NULL != spectrumToUpdate )
    {
      for( int whichParticle( spectrumToUpdate->getMassEigenstateSet().size()
                              - 1 );
           0 <= whichParticle;
           --whichParticle )
      {
        currentMassEigenstate
        = spectrumToUpdate->getMassEigenstateSet()[ whichParticle ];
        if( !(currentMassEigenstate->isSelfConjugate())
            &&
            !(currentMassEigenstate->getChargeConjugate(
                                                  ).haveDecaysBeenRecorded()) )
        {
          for( int
               whichDecay( currentMassEigenstate->getDecaySet().size() - 1 );
               0 <= whichDecay;
               --whichDecay )
          {
            currentMassEigenstate->getChargeConjugate(
                                                ).recordChargeConjugateOfDecay(
                       *(currentMassEigenstate->getDecaySet()[ whichDecay ]) );
          }
          currentMassEigenstate->getChargeConjugate().setDecayWidth(
                                      currentMassEigenstate->getDecayWidth() );
        }
      }
    }
  }

}
