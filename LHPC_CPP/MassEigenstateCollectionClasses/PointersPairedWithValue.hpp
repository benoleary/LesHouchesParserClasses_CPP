/*
 * PointersPairedWithValue.hpp
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

#ifndef POINTERSPAIREDWITHVALUE_HPP_
#define POINTERSPAIREDWITHVALUE_HPP_

#include <list>
#include <algorithm>
#include "../BOLlib/Classes/UsefulStuff.hpp"

namespace LHPC
{
  /* this is a class to hold pointers (intended to be MassEigenstate pointers)
   * paired with values (intended to be branching ratios as double), with
   * functions for matching.
   */
  template< class PointerClass,
            class ValueClass >
  class PointersPairedWithValue
  {
  public:
    PointersPairedWithValue();
    ~PointersPairedWithValue();

    std::list< PointerClass >&
    getPointerList();
    std::list< PointerClass > const&
    getPointerList() const;
    int
    getListSize() const;
    void
    addPointer( PointerClass const pointerToAdd );
    ValueClass
    getPairedValue() const;
    void
    clearPointers();
    void
    setPairedValueAndSortPointers( ValueClass const pairedValue );
    bool
    matchesExactly( PointerClass const firstPointer,
                    PointerClass const secondPointer ) const;
    bool
    matchesExactly( std::list< PointerClass > const& sortedList ) const;
    bool
    matchesExactly( int const firstCode,
                    int const secondCode,
                    bool (*comparisonFunction)( PointerClass const,
                                                int const ) ) const;
    bool
    containsAllAsSubset( std::list< PointerClass > const& sortedList ) const;
    bool
    containsAnyAsSubset( std::list< PointerClass > const& sortedList ) const;


  protected:
    std::list< PointerClass > pointerList;
    ValueClass pairedValue;
  };





  template< class PointerClass,
            class ValueClass >
  inline
  PointersPairedWithValue< PointerClass,
                           ValueClass >::PointersPairedWithValue() :
      pointerList(),
      pairedValue( BOL::UsefulStuff::notANumber )
  {
    // just an initialization list.
  }

  template< class PointerClass,
            class ValueClass >
  inline
  PointersPairedWithValue< PointerClass,
                           ValueClass >::~PointersPairedWithValue()
  {
    // does nothing.
  }


  template< class PointerClass,
            class ValueClass >
  inline std::list< PointerClass >&
  PointersPairedWithValue< PointerClass,
                           ValueClass >::getPointerList()
  {
    return pointerList;
  }

  template< class PointerClass,
            class ValueClass >
  inline std::list< PointerClass > const&
  PointersPairedWithValue< PointerClass,
                           ValueClass >::getPointerList() const
  {
    return pointerList;
  }

  template< class PointerClass,
            class ValueClass >
  inline int
  PointersPairedWithValue< PointerClass,
                           ValueClass >::getListSize() const
  {
    return (int)(pointerList.size());
  }

  template< class PointerClass,
            class ValueClass >
  inline void
  PointersPairedWithValue< PointerClass,
                           ValueClass >::addPointer(
                                              PointerClass const pointerToAdd )
  {
    pointerList.push_back( pointerToAdd );
  }

  template< class PointerClass,
            class ValueClass >
  inline ValueClass
  PointersPairedWithValue< PointerClass,
                           ValueClass >::getPairedValue() const
  {
    return pairedValue;
  }

  template< class PointerClass,
            class ValueClass >
  inline void
  PointersPairedWithValue< PointerClass,
                           ValueClass >::clearPointers()
  {
    pointerList.clear();
  }

  template< class PointerClass,
            class ValueClass >
  inline void
  PointersPairedWithValue< PointerClass,
                           ValueClass >::setPairedValueAndSortPointers(
                                                 ValueClass const pairedValue )
  {
    this->pairedValue = pairedValue;
    pointerList.sort();
  }

  template< class PointerClass,
            class ValueClass >
  inline bool
  PointersPairedWithValue< PointerClass,
                           ValueClass >::matchesExactly(
                                               PointerClass const firstPointer,
                                       PointerClass const secondPointer ) const
  {
    if( ( 2 == pointerList.size() )
        &&
        ( ( ( firstPointer == pointerList.front() )
            &&
            ( secondPointer == pointerList.back() ) )
          ||
          ( ( secondPointer == pointerList.front() )
            &&
            ( firstPointer == pointerList.back() ) ) ) )
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  template< class PointerClass,
            class ValueClass >
  inline bool
  PointersPairedWithValue< PointerClass,
                           ValueClass >::matchesExactly(
                            std::list< PointerClass > const& sortedList ) const
  {
    if( sortedList.size() == pointerList.size() )
    {
      return std::equal( sortedList.begin(),
                         sortedList.end(),
                         pointerList.begin() );
    }
    else
    {
      return false;
    }
  }

  template< class PointerClass,
            class ValueClass >
  inline bool
  PointersPairedWithValue< PointerClass,
                           ValueClass >::matchesExactly( int const firstCode,
                                                         int const secondCode,
                                bool (*comparisonFunction)( PointerClass const,
                                                            int const ) ) const
  {
    if( ( 2 == pointerList.size() )
        &&
        ( ( (*comparisonFunction)( pointerList.front(),
                                   firstCode )
            &&
            (*comparisonFunction)( pointerList.back(),
                                   secondCode ) )
          ||
          ( (*comparisonFunction)( pointerList.back(),
                                   firstCode )
            &&
            (*comparisonFunction)( pointerList.front(),
                                   secondCode ) ) ) )
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  template< class PointerClass,
            class ValueClass >
  inline bool
  PointersPairedWithValue< PointerClass,
                           ValueClass >::containsAllAsSubset(
                            std::list< PointerClass > const& sortedList ) const
  {
    bool returnBool( false );
    if( pointerList.size() >= sortedList.size() )
    {
      int allowedMismatches( pointerList.size() - sortedList.size() );
      // the difference in list sizes is the most comparisons that can fail.
      typename std::list< PointerClass >::const_iterator
      fromThisSet( pointerList.begin() );
      typename std::list< PointerClass >::const_iterator
      toBeCompared( sortedList.begin() );
      while( ( allowedMismatches >= 0 )
             &&
             ( fromThisSet != pointerList.end() ) )
      {
        if( *fromThisSet < *toBeCompared )
        {
          --allowedMismatches;
          // note that a comparison failed.
        }
        else
        {
          if( *fromThisSet == *toBeCompared )
          {
            // move on to the next sought pointer, as this one was just found:
            ++toBeCompared;
          }
          else
          {
            allowedMismatches = -1;
            /* otherwise, since the 2 lists are ordered & sortedList is smaller
             * than pointerList, if *thisSetPointer > *comparisonPointer then
             * there's no way that all of sortedList can be in pointerList.
             */
          }
        }
        ++fromThisSet;
      }
      if( allowedMismatches >= 0 )
      {
        returnBool = true;
      }
    }
    return returnBool;
  }

  template< class PointerClass,
            class ValueClass >
  inline bool
  PointersPairedWithValue< PointerClass,
                           ValueClass >::containsAnyAsSubset(
                            std::list< PointerClass > const& sortedList ) const
  {
    bool returnBool( false );
    typename std::list< PointerClass >::const_iterator
    fromThisSet( pointerList.begin() );
    typename std::list< PointerClass >::const_iterator
    toBeCompared( sortedList.begin() );
    /* both lists are sorted, so we walk each iterator along until it catches
     * up with the other: either it overtakes, & we switch to iterating the
     * other, or they are equal, in which case we should stop looking, and
     * return true.
     */
    while( !returnBool
           &&
           ( fromThisSet != pointerList.end() )
           &&
           ( toBeCompared != sortedList.end() ) )
    {
      if( *fromThisSet < *toBeCompared )
      {
        ++fromThisSet;
      }
      else if( *fromThisSet == *toBeCompared )
      {
        returnBool = true;
      }
      else
      {
        ++toBeCompared;
      }
    }
    return returnBool;
  }

}

#endif /* POINTERSPAIREDWITHVALUE_HPP_ */
