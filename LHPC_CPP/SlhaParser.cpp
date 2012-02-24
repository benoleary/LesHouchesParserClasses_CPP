/*
 * SlhaParser.cpp
 *
 *  Created on: Jan 11, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses.
 *
 *      LesHouchesParserClasses is free software: you can redistribute it
 *      and/or modify it under the terms of the GNU General Public License as
 *      published by the Free Software Foundation, either version 3 of the
 *      License, or (at your option) any later version.
 *
 *      LesHouchesParserClasses is distributed in the hope that it will be
 *      useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with LesHouchesParserClasses.  If not, see
 *      <http://www.gnu.org/licenses/>.
 *
 *      The GNU General Public License should be in GNU_public_license.txt
 *      the C++ files of LesHouchesParserClasses are:
 *      LHPC_CPP/BOLlib/Classes/AsciiXmlParser.hpp
 *      LHPC_CPP/BOLlib/Classes/AsciiXmlParser.cpp
 *      LHPC_CPP/BOLlib/Classes/CommentedTextParser.hpp
 *      LHPC_CPP/BOLlib/Classes/CommentedTextParser.hpp
 *      LHPC_CPP/BOLlib/Classes/StdVectorFiller.hpp
 *      LHPC_CPP/BOLlib/Classes/StringParser.hpp
 *      LHPC_CPP/BOLlib/Classes/StringParser.cpp
 *      LHPC_CPP/BOLlib/Classes/UsefulStuff.hpp
 *      LHPC_CPP/BOLlib/Classes/UsefulStuff.cpp
 *      LHPC_CPP/BOLlib/Classes/VectorlikeArray.hpp
 *      LHPC_CPP/LesHouchesEventFileClasses/AutomaticEventFilter.hpp
 *      LHPC_CPP/LesHouchesEventFileClasses/AutomaticEventFilter.cpp
 *      LHPC_CPP/LesHouchesEventFileClasses/FilterRule.hpp
 *      LHPC_CPP/LesHouchesEventFileClasses/FilterRule.cpp
 *      LHPC_CPP/LesHouchesEventFileClasses/LhefEvent.hpp
 *      LHPC_CPP/LesHouchesEventFileClasses/LhefEvent.cpp
 *      LHPC_CPP/LesHouchesEventFileClasses/ParticleLine.hpp
 *      LHPC_CPP/LesHouchesEventFileClasses/ParticleLine.cpp
 *      6 files in LHPC_CPP/LesHouchesEventFileClasses/FilterRuleClasses/:
 *      - ParticleCode.hpp
 *      - ParticleCode.cpp
 *      - PseudorapidityCut.hpp
 *      - PseudorapidityCut.cpp
 *      - TransverseMomentumCut.hpp
 *      - TransverseMomentumCut.cpp
 *      LHPC_CPP/MassEigenstateCollectionClasses/ExtendedMass.hpp
 *      LHPC_CPP/MassEigenstateCollectionClasses/ExtendedMass.cpp
 *      LHPC_CPP/MassEigenstateCollectionClasses/MapAndVectorAndBools.hpp
 *      LHPC_CPP/MassEigenstateCollectionClasses/MassSpectrum.hpp
 *      LHPC_CPP/MassEigenstateCollectionClasses/MassSpectrum.cpp
 *      6 files and a subdirectory in
 *      LHPC_CPP/MassEigenstateCollectionClasses/MassSpectrumClasses/:
 *      - CodesAndDataForMassEigenstates.hpp
 *      - ParticleCode.hpp
 *      - ParticleCode.cpp
 *      - MinimalSupersymmetricStandardModel.hpp
 *      - MinimalSupersymmetricStandardModel.cpp
 *      - PseudorapidityCut.hpp
 *      - PseudorapidityCut.cpp
 *      - NextToMinimalSupersymmetricStandardModel.hpp
 *      - NextToMinimalSupersymmetricStandardModel.cpp
 *      - StandardModel.hpp
 *      - StandardModel.cpp
 *      - ParticleSpectrumSubsetClasses/ with 14 files:
 *        - ChargedSleptonsOneToSix.hpp
 *        - ChargedSleptonsOneToSix.cpp
 *        - CharginosOneToTwo.hpp
 *        - CharginosOneToTwo.cpp
 *        - GluinoOneGeneration.hpp
 *        - GluinoOneGeneration.cpp
 *        - MssmExtraEwsbSpinZeroBosonSet.hpp
 *        - MssmExtraEwsbSpinZeroBosonSet.cpp
 *        - NeutralinosOneToFour.hpp
 *        - NeutralinosOneToFour.cpp
 *        - SneutrinosOneToThree.hpp
 *        - SneutrinosOneToThree.cpp
 *        - SquarksOneToSix.hpp
 *        - SquarksOneToSix.cpp
 *      LHPC_CPP/ParticleCodesAndData/NineDigitSlhaCodes.hpp
 *      LHPC_CPP/ParticleCodesAndData/NineDigitSlhaCodes.cpp
 *      LHPC_CPP/ParticleCodesAndData/PdgData.hpp
 *      LHPC_CPP/ParticleCodesAndData/PdgData.cpp
 *      LHPC_CPP/ParticleCodesAndData/SevenDigitSlhaCodes.hpp
 *      LHPC_CPP/ParticleCodesAndData/SevenDigitSlhaCodes.cpp
 *      LHPC_CPP/LhefParser.hpp
 *      LHPC_CPP/LhefParser.cpp
 *      LHPC_CPP/SlhaParser.hpp
 *      LHPC_CPP/SlhaParser.cpp
 *      and README.LHPC_CPP.txt which describes the package.
 */

#include "SlhaParser.hpp"

namespace LHPC
{
  SlhaParser::StringAndBlockPair SlhaParser::mapInserter( "",
                                                          NULL );

  SlhaParser::SlhaParser( bool const isVerbose ) :
      isVerbose( isVerbose ),
      fileParser( "#",
                  this->isVerbose ),
      spectrumToUpdate( NULL ),
      blockMap(),
      blockMapIterator(),
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
