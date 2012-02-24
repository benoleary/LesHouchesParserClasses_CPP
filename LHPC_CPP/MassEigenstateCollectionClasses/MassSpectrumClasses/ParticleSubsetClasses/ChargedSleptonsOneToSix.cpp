/*
 * ChargedSleptonsOneToSix.cpp
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

#include "ChargedSleptonsOneToSix.hpp"

namespace LHPC
{
  namespace MassSpectrumClass
  {
    ChargedSleptonsOneToSix::ChargedSleptonsOneToSix( bool const& isVerbose,
                                    std::vector< bool >* const defaultFlags ) :
        MassSpectrum( isVerbose,
                      defaultFlags ),
        spositronOne( PDGIX::spositronOne,
                      -PDGVII::selectronOne,
                      mapAndVectorAndBools,
                      false,
                      "se1c",
                      "${\\tilde{e}}_{1}^{\\ast}$" ),
        antispositronOne( spositronOne,
                          "se1",
                          "${\\tilde{e}}_{1}$" ),
        spositronTwo( PDGIX::spositronTwo,
                      -PDGVII::selectronTwo,
                      mapAndVectorAndBools,
                      false,
                      "se2c",
                      "${\\tilde{e}}_{2}^{\\ast}$" ),
        antispositronTwo( spositronTwo,
                          "se2",
                          "${\\tilde{e}}_{2}$" ),
        spositronThree( PDGIX::spositronThree,
                        -PDGVII::selectronThree,
                        mapAndVectorAndBools,
                        false,
                        "se3c",
                        "${\\tilde{e}}_{3}^{\\ast}$" ),
        antispositronThree( spositronThree,
                            "se3",
                            "${\\tilde{e}}_{3}$" ),
        spositronFour( PDGIX::spositronFour,
                       -PDGVII::selectronFour,
                       mapAndVectorAndBools,
                       false,
                       "se4c",
                       "${\\tilde{e}}_{4}^{\\ast}$" ),
        antispositronFour( spositronFour,
                           "se4",
                           "${\\tilde{e}}_{4}$" ),
        spositronFive( PDGIX::spositronFive,
                       -PDGVII::selectronFive,
                       mapAndVectorAndBools,
                       false,
                       "se5c",
                       "${\\tilde{e}}_{5}^{\\ast}$" ),
        antispositronFive( spositronFive,
                           "se5",
                           "${\\tilde{e}}_{5}$" ),
        spositronSix( PDGIX::spositronSix,
                      -PDGVII::selectronSix,
                      mapAndVectorAndBools,
                      false,
                      "se6c",
                      "${\\tilde{e}}_{6}^{\\ast}$" ),
        antispositronSix( spositronSix,
                          "se6",
                          "${\\tilde{e}}_{6}$" ),
        positiveSleptonPointers( 6,
                                 &spositronOne ),
        negativeSleptonPointers( 6,
                                 &antispositronOne )
    {
      positiveSleptonPointers[ 1 ] = &spositronTwo;
      positiveSleptonPointers[ 2 ] = &spositronThree;
      positiveSleptonPointers[ 3 ] = &spositronFour;
      positiveSleptonPointers[ 4 ] = &spositronFive;
      positiveSleptonPointers[ 5 ] = &spositronSix;
      negativeSleptonPointers[ 1 ] = &antispositronTwo;
      negativeSleptonPointers[ 2 ] = &antispositronThree;
      negativeSleptonPointers[ 3 ] = &antispositronFour;
      negativeSleptonPointers[ 4 ] = &antispositronFive;
      negativeSleptonPointers[ 5 ] = &antispositronSix;
    }

    ChargedSleptonsOneToSix::~ChargedSleptonsOneToSix()
    {
      // does nothing.
    }

  }

}
