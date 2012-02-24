/*
 * AutomaticEventFilter.hpp
 *
 *  Created on: Jan 26, 2012
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

#ifndef AUTOMATICEVENTFILTER_HPP_
#define AUTOMATICEVENTFILTER_HPP_

#include <list>
#include "LhefEvent.hpp"
#include "ParticleLine.hpp"
#include "FilterRule.hpp"

namespace LHPC
{
  namespace LHEF
  {
    // this class is for automatically filtering ParticleLines from a LhefEvent
    // according to specified selections or vetoes.
    class AutomaticEventFilter
    {
    public:
      AutomaticEventFilter();
      ~AutomaticEventFilter();

      AutomaticEventFilter&
      addFilterRule( FilterRule const& ruleToAdd );
      // the filters get applied to the events in the order in which they are
      // added with this function.
      std::list< ParticleLine const* >&
      getFilteredLines();

      // functions for automatic updating:
      void
      updateForNewEvent( LhefEvent const& eventSource );
      /* this clears filteredLines then goes through eventSource & records in
       * filteredLines all pointers to ParticleLines that pass the filters.
       * this is automatically called by the LhefParser that created this
       * instance when it reads in a new LHEF event, so it shouldn't have to be
       * called by anything else.
       */

    protected:
      std::list< ParticleLine const* > filteredLines;
      std::vector< FilterRule const* > filterRules;
      int numberOfRules;
      int rulesToPass;

      bool
      passesAllFilters( ParticleLine const& lineToCheck );
    };





    inline AutomaticEventFilter&
    AutomaticEventFilter::addFilterRule( FilterRule const& ruleToAdd )
    // the filters get applied to the events in the order in which they are
    // added with this function.
    {
      filterRules.push_back( &ruleToAdd );
      ++numberOfRules;
      return *this;
    }

    inline std::list< ParticleLine const* >&
    AutomaticEventFilter::getFilteredLines()
    {
      return filteredLines;
    }

    inline void
    AutomaticEventFilter::updateForNewEvent( LhefEvent const& eventSource )
    /* this clears filteredLines then goes through eventSource & records in
     * filteredLines all pointers to ParticleLines that pass the filters.
     * this is automatically called by the LhefParser that created this
     * instance when it reads in a new LHEF event, so it shouldn't have to be
     * called by anything else.
     */
    {
      filteredLines.clear();
      for( int whichLine( eventSource.getNumberOfParticles() );
           0 < whichLine;
           --whichLine )
      {
        if( passesAllFilters( eventSource[ whichLine ] ) )
        {
          filteredLines.push_back( &(eventSource[ whichLine ]) );
        }
      }
    }

    inline bool
    AutomaticEventFilter::passesAllFilters( ParticleLine const& lineToCheck )
    /* this clears filteredLines then goes through eventSource & records in
     * filteredLines all pointers to ParticleLines that pass the filters.
     * this is automatically called by the LhefParser that created this
     * instance when it reads in a new LHEF event, so it shouldn't have to be
     * called by anything else.
     */
    {
      rulesToPass = numberOfRules;
      while( ( 0 < rulesToPass )
             &&
             ( (*filterRules[ numberOfRules - rulesToPass ])( lineToCheck ) ) )
      {
        --rulesToPass;
      }
      if( 0 == rulesToPass )
      {
        return true;
      }
      else
      {
        return false;
      }
    }

  }

}

#endif /* AUTOMATICEVENTFILTER_HPP_ */
