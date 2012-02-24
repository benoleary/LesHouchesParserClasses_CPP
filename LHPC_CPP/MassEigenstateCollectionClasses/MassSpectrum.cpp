/*
 * MassSpectrum.cpp
 *
 *  Created on: Jan 8, 2012
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

#include "MassSpectrum.hpp"
#include "../BOLlib/Classes/StdVectorFiller.hpp"

namespace LHPC
{
  std::vector< bool >
  MassSpectrum::defaultBoolVector( (unsigned int)(MassSpectrum::sizeOfEnum),
                                   false );
  std::vector< bool >
  MassSpectrum::defaultEscapesDetectorBoolVector(
                  BOL::StdVectorFiller< bool >( true )( false ).end( false ) );
  std::vector< bool >
  MassSpectrum::defaultIsJetBoolVector(
                  BOL::StdVectorFiller< bool >( false )( true ).end( false ) );
  std::vector< bool >
  MassSpectrum::defaultIsLightLeptonBoolVector(
                  BOL::StdVectorFiller< bool >( false )( false ).end( true ) );

  MassSpectrum::MassSpectrum( bool const& isVerbose,
                              std::vector< bool >* defaultFlags ) :
      allMassEigenstates(),
      unknownMassEigenstates(),
      pdgCodeMap(),
      isVerbose( isVerbose ),
      mapAndVectorAndBools( pdgCodeMap,
                            allMassEigenstates,
                            isVerbose )
  {
    if( NULL == defaultFlags )
    {
      defaultFlags = &defaultBoolVector;
    }
    mapAndVectorAndBools.withBools( defaultFlags );
  }

  MassSpectrum::~MassSpectrum()
  {
    for( int deletionIndex( unknownMassEigenstates.size() - 1 );
         0 <= deletionIndex;
         --deletionIndex )
    {
      delete unknownMassEigenstates[ deletionIndex ];
    }
  }


  MassEigenstate&
  MassSpectrum::ensureMassEigenstateExists( int const pdgCode )
  /* this looks for a MassEigenstate with code pdgCode, & if it doesn't find
   * one, it creates a new MassEigenstate instance with a name that is just
   * pdgCode as a string, & also its charge conjugate, & notes their pointers
   * in unknownMassEigenstates so that they can be deleted by this MassSpectrum
   * instance's destructor.
   */
  {
    MassEigenstate*
    massEigenstatePointer( MassEigenstate::findPointerWithCode( pdgCode,
                                                                pdgCodeMap ) );
    if( NULL == massEigenstatePointer )
      // if the requested MassEigenstate could not be found...
    {
      std::string codeAsName( BOL::StringParser::intToString( pdgCode,
                                                              1 ) );
      // the code is turned into a name.
      massEigenstatePointer = new MassEigenstate( pdgCode,
                          mapAndVectorAndBools.withBools( &defaultBoolVector ),
                                                  false,
                                                  codeAsName,
                                                  codeAsName );
      // the MassEigenstate is constructed with default flags.
      unknownMassEigenstates.push_back( massEigenstatePointer );
      // the pointer is noted so that it can be deleted when appropriate.
      codeAsName.assign( BOL::StringParser::intToString( -pdgCode,
                                                         1 ) );
      // the charge conjugate's name is made, & then used for the creation of
      // the charge conjugate itself, while storing its pointer for deletion:
      unknownMassEigenstates.push_back( new MassEigenstate(
                                                        *massEigenstatePointer,
                                                            codeAsName,
                                                            codeAsName ) );
    }
    return *massEigenstatePointer;
  }

}
