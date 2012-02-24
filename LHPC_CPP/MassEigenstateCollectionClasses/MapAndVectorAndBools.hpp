/*
 * MapAndVectorAndBools.hpp
 *
 *  Created on: Jan 19, 2012
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

#ifndef MAPANDVECTORANDBOOLS_HPP_
#define MAPANDVECTORANDBOOLS_HPP_

#include <map>
#include <vector>

namespace LHPC
{
  /* this is a class to hold a std::map of ints and pointers (intended to be
   * MassEigenstate pointers) along with a std::vector of that type of pointer,
   * and also a pointer to a std::vector< bool > (intended to hold whatever
   * flags the MassEigenstate instances are meant to have) and a const
   * reference to a bool (intended for a verbosity flag).
   */
  template< class PointerClass >
  class MapAndVectorAndBools
  {
  public:
    typedef typename std::map< int,
                               PointerClass > PointerMap;
    typedef typename std::vector< PointerClass > PointerVector;

    MapAndVectorAndBools( PointerMap& codeMap,
                          PointerVector& pointerGroup,
                          bool const& boolReference );
    virtual
    ~MapAndVectorAndBools();

    MapAndVectorAndBools< PointerClass >&
    withBools( std::vector< bool > const* const boolVector );
    // this sets this->boolVector to the given pointer & returns *this.
    PointerMap&
    getMap();
    PointerVector&
    getVector();
    bool const&
    getBool();
    std::vector< bool > const*
    getFlags();


  protected:
    PointerMap& codeMap;
    PointerVector& pointerGroup;
    bool const& boolReference;
    std::vector< bool > const* boolVector;
  };



  template< class PointerClass >
  inline
  MapAndVectorAndBools< PointerClass >::MapAndVectorAndBools(
                                                           PointerMap& codeMap,
                                                   PointerVector& pointerGroup,
                                                  bool const& boolReference ) :
      codeMap( codeMap ),
      pointerGroup( pointerGroup ),
      boolReference( boolReference ),
      boolVector( NULL )
  {
    // just an initialization list.
  }

  template< class PointerClass >
  inline
  MapAndVectorAndBools< PointerClass >::~MapAndVectorAndBools()
  {
    // does nothing.
  }


  template< class PointerClass >
  inline MapAndVectorAndBools< PointerClass >&
  MapAndVectorAndBools< PointerClass >::withBools(
                                  std::vector< bool > const* const boolVector )
  // this sets this->boolVector to the given pointer & returns *this.
  {
    this->boolVector = boolVector;
    return *this;
  }

  template< class PointerClass >
  inline std::map< int,
                   PointerClass >&
  MapAndVectorAndBools< PointerClass >::getMap()
  {
    return codeMap;
  }

  template< class PointerClass >
  inline std::vector< PointerClass >&
  MapAndVectorAndBools< PointerClass >::getVector()
  {
    return pointerGroup;
  }

  template< class PointerClass >
  inline bool const&
  MapAndVectorAndBools< PointerClass >::getBool()
  {
    return boolReference;
  }

  template< class PointerClass >
  inline std::vector< bool > const*
  MapAndVectorAndBools< PointerClass >::getFlags()
  {
    return boolVector;
  }

}

#endif /* MAPANDVECTORANDBOOLS_HPP_ */
