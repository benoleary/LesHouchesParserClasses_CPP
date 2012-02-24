/*
 * LhefEvent.hpp
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

#ifndef LHEFEVENT_HPP_
#define LHEFEVENT_HPP_

#include <iostream>
#include "ParticleLine.hpp"
#include "../BOLlib/Classes/VectorlikeArray.hpp"

namespace LHPC
{
  namespace LHEF
  {
    // this class is for holding several ParticleLine instances together with
    // some ints and doubles to describe a complete LHEF-format event.
    class LhefEvent
    {
    public:
      LhefEvent( bool const& isVerbose );
      LhefEvent( LhefEvent const& copySource );
      ~LhefEvent();

      int
      getNumberOfParticles() const;
      int
      NUP() const{ return getNumberOfParticles(); }
      int
      getEventId() const;
      int
      IDPRUP() const{ return getEventId(); }
      double
      getEventWeight() const;
      double
      XWGTUP() const{ return getEventWeight(); }
      double
      getEventScale() const;
      double
      SCALUP() const{ return getEventScale(); }
      double
      getAlphaQed() const;
      double
      AQEDUP() const{ return getAlphaQed(); }
      double
      getAlphaQcd() const;
      double
      AQCDUP() const{ return getAlphaQcd(); }
      ParticleLine const&
      getLine( int const whichLine ) const;
      ParticleLine const&
      operator[]( int const whichLine ) const{ return getLine( whichLine ); }
      int
      getEventNumberInFile() const;
      std::string const&
      getAsString() const;
      std::string const
      getAsStringWithTags() const;

      // stuff for setting up the lhefEvent:
      bool
      recordEvent( std::string const& eventAsString );
      /* this interprets a string as the data it is meant to correspond to, &
       * ensures that the ParticleLine instances correctly point to each other.
       * if any of the lines had the wrong number of data entries, or if the
       * header number of particles didn't correspond to the number of
       * particle lines, setAsInvalid() is called & then false is returned.
       * true is returned if all the entries were filled as expected.
       */


    protected:
      static std::string const trimmingChars;
      static BOL::VectorlikeArray< std::string > eventAsLines;
      static BOL::VectorlikeArray< std::string > lineAsNumbersAsStrings;
      // these are for parsing the data lines.
      static bool const trueForVerbosity;

      // in the order in which they appear in LHE format:
      // 1st line of the event:
      int numberOfParticles;
      // NUP, the number of particles listed in the event.
      int eventId;
      // IDPRUP, which is not actually defined in hep-ph/0609017...
      double eventWeight;
      // XWGTUP, the weight of the event.
      double eventScale;
      // SCALUP, the energy scale of the event, in GeV.
      double alphaQed;
      // AQEDUP, the value of the electromagnetic alpha at eventScale.
      double alphaQcd;
      // AQCDUP, the value of the color force alpha at eventScale.

      // then numberOfParticles lines, each of which are stored in a
      // ParticleLine:
      BOL::VectorlikeArray< ParticleLine > particleLines;

      int eventNumberInFile;
      // this isn't specified as part of the LHEF format, but it's probably
      // useful.

      // stuff for setting up the LhefEvent:
      bool recordingSucceeded;
      std::string headerLine;
      int motherLineNumber;
      ParticleLine* primaryMotherLinePointer;
      ParticleLine* secondaryMotherLinePointer;
      bool const& isVerbose;
      std::string eventAsString;

      void
      setAsInvalid();
      // this sets every entry in the header line to
      // BOL::UsefulStuff::notANumber & clears particleLines.
      void
      setUpPointersBetweenParticleLines();
      // this sets up the mother & daughter pointers for each ParticleLine in
      // particleLines.
    };





    inline int
    LhefEvent::getNumberOfParticles() const
    {
      return numberOfParticles;
    }

    inline int
    LhefEvent::getEventId() const
    {
      return eventId;
    }

    inline double
    LhefEvent::getEventWeight() const
    {
      return eventId;
    }

    inline double
    LhefEvent::getEventScale() const
    {
      return eventScale;
    }

    inline double
    LhefEvent::getAlphaQed() const
    {
      return alphaQed;
    }

    inline double
    LhefEvent::getAlphaQcd() const
    {
      return alphaQcd;
    }

    inline ParticleLine const&
    LhefEvent::getLine( int const whichLine ) const
    {
      return particleLines[ whichLine - 1 ];
    }

    inline int
    LhefEvent::getEventNumberInFile() const
    {
      return eventNumberInFile;
    }

    inline std::string const&
    LhefEvent::getAsString() const
    {
      return eventAsString;
    }

    inline std::string const
    LhefEvent::getAsStringWithTags() const
    {
      std::string returnString( "<event>\n" );
      returnString.append( eventAsString );
      returnString.append( "\n</event>" );
      return returnString;
    }

    inline void
    LhefEvent::setAsInvalid()
    // this sets every entry in the header line to
    // BOL::UsefulStuff::notANumber & clears particleLines.
    {
      particleLines.clearEntries();
      numberOfParticles = (int)BOL::UsefulStuff::notANumber;
      eventId = (int)BOL::UsefulStuff::notANumber;
      eventWeight = BOL::UsefulStuff::notANumber;
      eventScale = BOL::UsefulStuff::notANumber;
      alphaQed = BOL::UsefulStuff::notANumber;
      alphaQcd = BOL::UsefulStuff::notANumber;

      std::cout
      << std::endl
      << "LHPC::warning! the following string could not be parsed as a valid"
      << " LHEF event:";
      std::cout << std::endl << eventAsString;
      std::cout << std::endl;
    }

  }

}

#endif /* LHEFEVENT_HPP_ */
