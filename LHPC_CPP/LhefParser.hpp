/*
 * LhefParser.hpp
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

#ifndef LHEFPARSER_HPP_
#define LHEFPARSER_HPP_

#include "BOLlib/Classes/AsciiXmlParser.hpp"
#include "BOLlib/Classes/VectorlikeArray.hpp"
#include "LesHouchesEventFileClasses/LhefEvent.hpp"
#include "LesHouchesEventFileClasses/AutomaticEventFilter.hpp"
#include "LesHouchesEventFileClasses/FilterRuleClasses/InitialOrIntermediateOrFinalState.hpp"
#include "LesHouchesEventFileClasses/FilterRuleClasses/ParticleCode.hpp"
#include "LesHouchesEventFileClasses/FilterRuleClasses/PseudorapidityCut.hpp"
#include "LesHouchesEventFileClasses/FilterRuleClasses/TransverseMomentumCut.hpp"
#include "ParticleCodesAndData/NineDigitSlhaCodes.hpp"
#include "ParticleCodesAndData/SevenDigitSlhaCodes.hpp"

namespace LHPC
{
  // this is a class for reading in a LHEF format file & parsing the events
  // from it.
  class LhefParser
  {
  public:
    LhefParser( std::string const& eventFileName,
                bool const isVerbose = true );
    ~LhefParser();

    bool
    readNextEvent();
    // this reads in the next event in the event file, & returns true if
    // successful.
    LHEF::LhefEvent const&
    getEvent() const;
    // this returns the last parsed event.
    LhefParser&
    registerFilter( LHEF::AutomaticEventFilter& filterToUpdate );
    // this adds a pointer to filterToUpdate to automaticFilters so that its
    // updateForNewEvent(...) gets called at the end of readNextEvent().
    bool
    openFile( std::string const& eventFileName );
    // this opens the file with the given name as the source of its events &
    // returns true, unless the file could not be opened.
    bool
    eventReadSuccessfully();
    // this returns true if the last event that was read was also successfully
    // interpretted.


  protected:
    bool isVerbose;
    BOL::AsciiXmlParser fileParser;
    LHEF::LhefEvent currentEvent;
    std::vector< LHEF::AutomaticEventFilter* > automaticFilters;
    bool fileIsOpen;
    std::string eventAsString;
    bool eventIsValid;
  };





  inline bool
  LhefParser::readNextEvent()
  // this reads in the next event in the event file, & returns true if
  // successful.
  {
    if( fileIsOpen )
    {
      eventAsString.assign( fileParser.findNextElement() );
      fileIsOpen = fileParser.wasSuccessful();
      if( fileIsOpen )
      {
        eventIsValid = currentEvent.recordEvent( eventAsString );
        for( int filterIndex( automaticFilters.size() - 1 );
             0 <= filterIndex;
             --filterIndex )
        {
          automaticFilters[ filterIndex ]->updateForNewEvent( currentEvent );
        }
      }
      else
      {
        fileParser.closeFile();
      }
    }
    return fileIsOpen;
  }

  inline LHEF::LhefEvent const&
  LhefParser::getEvent() const
  // this returns the last parsed event.
  {
    return currentEvent;
  }

  inline LhefParser&
  LhefParser::registerFilter( LHEF::AutomaticEventFilter& filterToUpdate )
  // this adds a pointer to filterToUpdate to automaticFilters so that its
  // updateForNewEvent(...) gets called at the end of readNextEvent().
  {
    automaticFilters.push_back( &filterToUpdate );
    return *this;
  }

  inline bool
  LhefParser::openFile( std::string const& eventFileName )
  // this opens the file with the given name as the source of its events &
  // returns true, unless the file could not be opened.
  {
    fileParser.openFile( eventFileName );
    fileIsOpen = fileParser.wasSuccessful();
    return fileIsOpen;
  }

  inline bool
  LhefParser::eventReadSuccessfully()
  // this returns true if the last event that was read was also successfully
  // interpretted.
  {
    return eventIsValid;
  }

}

#endif /* LHEFPARSER_HPP_ */
