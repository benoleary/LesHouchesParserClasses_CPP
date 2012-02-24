/*
 * MassSpectrum.hpp
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

#ifndef MASSSPECTRUM_HPP_
#define MASSSPECTRUM_HPP_

#include <iostream>
#include <stdexcept>
#include "MassEigenstate.hpp"
#include "../BOLlib/Classes/StringParser.hpp"

namespace LHPC
{
  class MassSpectrum
  {
  public:
    enum defaultFlags
    {
      escapesDetector = 0,
      isJet = 1,
      isLightLepton = 2,
      sizeOfEnum = 3
    };
    MassSpectrum( bool const& isVerbose,
                  std::vector< bool >* defaultFlags = NULL );
    virtual
    ~MassSpectrum();

    MassEigenstate&
    operator[]( int const pdgCode );
    MassEigenstate const&
    operator[]( int const pdgCode ) const;
    MassEigenstate*
    getMassEigenstate( int const pdgCode );
    MassEigenstate const*
    getMassEigenstate( int const pdgCode ) const;
    std::vector< MassEigenstate* >&
    getMassEigenstateSet();
    std::vector< MassEigenstate* > const&
    getMassEigenstateSet() const;
    MassEigenstate&
    ensureMassEigenstateExists( int const pdgCode );
    MassSpectrum&
    clearMassesAndDecays();
    bool const&
    getVerbosityReference() const;


  protected:
    static std::vector< bool > defaultBoolVector;
    static std::vector< bool > defaultEscapesDetectorBoolVector;
    static std::vector< bool > defaultIsJetBoolVector;
    static std::vector< bool > defaultIsLightLeptonBoolVector;

    static MassEigenstate&
    findMassEigenstateReference( int const pdgCode,
                               MassEigenstateCodeToPointerMap const& codeMap );
    static void
    warnThatMassEigenstateWasNotFound( int const pdgCode );

    std::vector< MassEigenstate* > allMassEigenstates;
    std::vector< MassEigenstate* > unknownMassEigenstates;
    MassEigenstateCodeToPointerMap pdgCodeMap;
    bool const& isVerbose;
    MassEigenstateMapAndVectorAndBools mapAndVectorAndBools;

  };



  inline MassEigenstate&
  MassSpectrum::operator[]( int const pdgCode )
  {
    return findMassEigenstateReference( pdgCode,
                                        pdgCodeMap );
  }

  inline MassEigenstate const&
  MassSpectrum::operator[]( int const pdgCode ) const
  {
    return findMassEigenstateReference( pdgCode,
                                        pdgCodeMap );
  }

  inline MassEigenstate*
  MassSpectrum::getMassEigenstate( int const pdgCode )
  {
    return MassEigenstate::findPointerWithCode( pdgCode,
                                                pdgCodeMap );
  }

  inline MassEigenstate const*
  MassSpectrum::getMassEigenstate( int const pdgCode ) const
  {
    return MassEigenstate::findPointerWithCode( pdgCode,
                                                pdgCodeMap );
  }

  inline std::vector< MassEigenstate* >&
  MassSpectrum::getMassEigenstateSet()
  {
    return allMassEigenstates;
  }

  inline std::vector< MassEigenstate* > const&
  MassSpectrum::getMassEigenstateSet() const
  {
    return allMassEigenstates;
  }

  inline MassSpectrum&
  MassSpectrum::clearMassesAndDecays()
  {
    for( int clearingIndex( allMassEigenstates.size() - 1 );
         0 <= clearingIndex;
         --clearingIndex )
    {
      allMassEigenstates[ clearingIndex ]->clearMassesAndDecays();
    }
    return *this;
  }

  inline bool const&
  MassSpectrum::getVerbosityReference() const
  {
    return isVerbose;
  }

  inline MassEigenstate&
  MassSpectrum::findMassEigenstateReference( int const pdgCode,
                                MassEigenstateCodeToPointerMap const& codeMap )
  {
    MassEigenstate*
    massEigenstatePointer( MassEigenstate::findPointerWithCode( pdgCode,
                                                                codeMap ) );
    if( NULL != massEigenstatePointer )
    {
      return *massEigenstatePointer;
    }
    else
    {
      std::string
      errorMessage( "MassSpectrum::findMassEigenstateReference( " );
      errorMessage.append( BOL::StringParser::intToString( pdgCode,
                                                           1 ) );
      errorMessage.append( ") out of range." );
      warnThatMassEigenstateWasNotFound( pdgCode );
      throw std::out_of_range( errorMessage );
    }
  }

  inline void
  MassSpectrum::warnThatMassEigenstateWasNotFound( int const pdgCode )
  {
    std::cout
    << std::endl
    << "LhaParsing::error! MassEigenstate::findPointerWithCode could not"
    << " find the MassEigenstate with particle code " << pdgCode
    << ", so it is returning a NULL pointer. MassSpectrum is throwing an"
    << " out-of-range exception because of this.";
    std::cout << std::endl;
  }

}

#endif /* MASSSPECTRUM_HPP_ */
