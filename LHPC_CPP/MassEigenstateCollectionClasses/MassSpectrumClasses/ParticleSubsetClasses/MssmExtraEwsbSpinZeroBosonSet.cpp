/*
 * MssmExtraEwsbSpinZeroBosonSet.cpp
 *
 *  Created on: Jan 18, 2012
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

#include "MssmExtraEwsbSpinZeroBosonSet.hpp"

namespace LHPC
{
  namespace MassSpectrumClass
  {
    MssmExtraEwsbSpinZeroBosonSet::MssmExtraEwsbSpinZeroBosonSet(
                                                         bool const& isVerbose,
                                    std::vector< bool >* const defaultFlags ) :
        MassSpectrum( isVerbose,
                      defaultFlags ),
        neutralColorlessScalarTwo( PDGIX::neutralColorlessScalarTwo,
                                   PDGVII::neutralColorlessScalarTwo,
                                   mapAndVectorAndBools,
                                   true,
                                   "h02",
                                   "$h_{2}^{0}$" ),
        neutralColorlessPseudoscalarOne(
                                        PDGIX::neutralColorlessPseudoscalarOne,
                                       PDGVII::neutralColorlessPseudoscalarOne,
                                         mapAndVectorAndBools,
                                         true,
                                         "A01",
                                         "$A_{1}^{0}$" ),
        positiveColorlessSpinZeroBosonOne(
                                      PDGIX::positiveColorlessSpinZeroBosonOne,
                                     PDGVII::positiveColorlessSpinZeroBosonOne,
                                           mapAndVectorAndBools,
                                           false,
                                           "hp1",
                                           "$h_{1}^{+}$" ),
        negativeColorlessSpinZeroBosonOne( positiveColorlessSpinZeroBosonOne,
                                           "hm1",
                                           "$h_{1}^{-}$" ),
        neutralScalarsAndPseudoscalarPointers(),
        chargedColorlessSpinZeroBosonPointers( 2,
                                        &positiveColorlessSpinZeroBosonOne ),
        ewsbSpinZeroAndOneBosonPointers(),
        neutralEwsbSpinZeroAndOneBosonPointers(),
        chargedEwsbSpinZeroAndOneBosonPointers(
                                        chargedColorlessSpinZeroBosonPointers )
    {
      MassEigenstate* vectorFiller( MassEigenstate::findPointerWithCode(
                                              PDGIX::neutralColorlessScalarOne,
                                                                pdgCodeMap ) );
      if( NULL == vectorFiller )
      {
        vectorFiller = MassEigenstate::findPointerWithCode(
                                             PDGVII::neutralColorlessScalarOne,
                                                            pdgCodeMap );
      }
      if( NULL != vectorFiller )
      {
        neutralScalarsAndPseudoscalarPointers.push_back( vectorFiller );
      }
      neutralScalarsAndPseudoscalarPointers.push_back( &neutralColorlessScalarTwo );
      neutralScalarsAndPseudoscalarPointers.push_back(
                                            &neutralColorlessPseudoscalarOne );
      chargedColorlessSpinZeroBosonPointers[ 1 ] = &negativeColorlessSpinZeroBosonOne;
      chargedEwsbSpinZeroAndOneBosonPointers[ 1 ]
      = chargedColorlessSpinZeroBosonPointers[ 1 ];
      vectorFiller = MassEigenstate::findPointerWithCode( PDGIX::wPlusBosonOne,
                                                          pdgCodeMap );
      if( NULL == vectorFiller )
      {
        vectorFiller
        = MassEigenstate::findPointerWithCode( PDGVII::wPlusBosonOne,
                                               pdgCodeMap );
      }
      if( NULL != vectorFiller )
      {
        chargedEwsbSpinZeroAndOneBosonPointers.push_back( vectorFiller );
        chargedEwsbSpinZeroAndOneBosonPointers.push_back(
                                       &(vectorFiller->getChargeConjugate()) );
      }
      neutralEwsbSpinZeroAndOneBosonPointers = neutralScalarsAndPseudoscalarPointers;
      vectorFiller = MassEigenstate::findPointerWithCode( PDGIX::zBosonOne,
                                                          pdgCodeMap );
      if( NULL == vectorFiller )
      {
        vectorFiller
        = MassEigenstate::findPointerWithCode( PDGVII::zBosonOne,
                                               pdgCodeMap );
      }
      if( NULL != vectorFiller )
      {
        neutralEwsbSpinZeroAndOneBosonPointers.push_back( vectorFiller );
      }
      ewsbSpinZeroAndOneBosonPointers = neutralEwsbSpinZeroAndOneBosonPointers;
      ewsbSpinZeroAndOneBosonPointers.insert( ewsbSpinZeroAndOneBosonPointers.end(),
                                       chargedEwsbSpinZeroAndOneBosonPointers.begin(),
                                       chargedEwsbSpinZeroAndOneBosonPointers.end() );
    }

    MssmExtraEwsbSpinZeroBosonSet::~MssmExtraEwsbSpinZeroBosonSet()
    {
      // does nothing.
    }

  }

}
