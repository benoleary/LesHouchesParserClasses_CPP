/*
 * LhefEvent.cpp
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

#include "LhefEvent.hpp"

namespace LHPC
{
  namespace LHEF
  {
    std::string const LhefEvent::trimmingChars( " \t\r\n" );
    BOL::VectorlikeArray< std::string > LhefEvent::eventAsLines( 2 );
    BOL::VectorlikeArray< std::string > LhefEvent::lineAsNumbersAsStrings( 6 );
    bool const LhefEvent::trueForVerbosity( true );

    LhefEvent::LhefEvent( bool const& isVerbose ) :
        numberOfParticles( (int)BOL::UsefulStuff::notANumber ),
        eventId( (int)BOL::UsefulStuff::notANumber ),
        eventWeight( BOL::UsefulStuff::notANumber ),
        eventScale( BOL::UsefulStuff::notANumber ),
        alphaQed( BOL::UsefulStuff::notANumber ),
        alphaQcd( BOL::UsefulStuff::notANumber ),
        particleLines(),
        eventNumberInFile( 1 ),
        recordingSucceeded( false ),
        headerLine( "" ),
        isVerbose( isVerbose ),
        eventAsString( "" )
    {
      // just an initialization list.
    }

    LhefEvent::LhefEvent( LhefEvent const& copySource ) :
        numberOfParticles( copySource.numberOfParticles ),
        eventId( copySource.eventId ),
        eventWeight( copySource.eventWeight ),
        eventScale( copySource.eventScale ),
        alphaQed( copySource.alphaQed ),
        alphaQcd( copySource.alphaQcd ),
        particleLines( copySource.particleLines,
                       &ParticleLine::copyParticleLine ),
        eventNumberInFile( copySource.eventNumberInFile ),
        recordingSucceeded( copySource.recordingSucceeded ),
        headerLine( "" ),
        isVerbose( trueForVerbosity ),
        eventAsString( copySource.eventAsString )
    {
      /* the copy constructors of particleLines cannot get their mother &
       * daughter pointers by themselves, so this constructor has to sort them
       * out:
       */
    }

    LhefEvent::~LhefEvent()
    {
      // does nothing.
    }


    bool
    LhefEvent::recordEvent( std::string const& eventAsString )
    /* this interprets a string as the data it is meant to correspond to, &
     * ensures that the ParticleLine instances correctly point to each other.
     * if any of the lines had the wrong number of data entries, or if the
     * header number of particles didn't correspond to the number of
     * particle lines, setAsInvalid() is called & then false is returned.
     * true is returned if all the entries were filled as expected.
     */
    {
      this->eventAsString.assign( BOL::StringParser::trimFromFront(
                                BOL::StringParser::trimFromBack( eventAsString,
                                                               trimmingChars ),
                                                             trimmingChars ) );
      ++eventNumberInFile;
      eventAsLines.clearEntries();
      BOL::StringParser::parseByChar( this->eventAsString,
                                      eventAsLines,
                                      BOL::StringParser::newlineChars );
      // now lineParser should be 1 string for the header line &
      // ( lineParser.getSize() - 1 ) strings for the particle lines.
      if( 1 >= eventAsLines.getSize() )
        // if the wrong number of data was given (header line & at least 1
        // particle line are required)...
      {
        if( isVerbose )
        {
          std::cout
          << std::endl
          << "LHPC::warning! recording event " << eventNumberInFile
          << " as invalid because only " << eventAsLines.getSize()
          << " lines were found in the event, which is not enough for a header"
          << " line + at least 1 particle line.";
          std::cout << std::endl;
        }
        setAsInvalid();
        return false;
      }
      else
      {
        // 1st the header line is set up:
        headerLine.assign( eventAsLines.getFront() );
        lineAsNumbersAsStrings.clearEntries();
        BOL::StringParser::parseByChar( headerLine,
                                        lineAsNumbersAsStrings,
                                        BOL::StringParser::whitespaceChars );

        if( 6 != lineAsNumbersAsStrings.getSize() )
          // if the wrong number of data was given (a header line & at least 1
          // particle line are required)...
        {
          if( isVerbose )
          {
            std::cout
            << std::endl
            << "LHPC::warning! recording event " << eventNumberInFile
            << " as invalid because " << lineAsNumbersAsStrings.getSize()
            << " numbers were found for the header line, instead of exactly 6"
            << " numbers, as required.";
            std::cout << std::endl;
          }
          setAsInvalid();
          return false;
        }
        else
        {
          numberOfParticles
          = BOL::StringParser::stringToInt( lineAsNumbersAsStrings[ 0 ] );
          if( numberOfParticles != ( eventAsLines.getSize() - 1 ) )
            // if the header is wrong about how many particle lines there
            // are...
          {
            if( isVerbose )
            {
              std::cout
              << std::endl
              << "LHPC::warning! recording event " << eventNumberInFile
              << " as invalid because the header line declared "
              << numberOfParticles << " particles in the event, but "
              << ( eventAsLines.getSize() - 1 ) << " lines were found for the"
              << " particles.";
              std::cout << std::endl;
            }
            setAsInvalid();
            return false;
          }
          else
          {
            eventId
            = BOL::StringParser::stringToInt( lineAsNumbersAsStrings[ 1 ] );
            eventWeight
            = BOL::StringParser::stringToDouble( lineAsNumbersAsStrings[ 2 ] );
            eventScale
            = BOL::StringParser::stringToDouble( lineAsNumbersAsStrings[ 3 ] );
            alphaQed
            = BOL::StringParser::stringToDouble( lineAsNumbersAsStrings[ 4 ] );
            alphaQcd
            = BOL::StringParser::stringToDouble( lineAsNumbersAsStrings[ 5 ] );

            // then the ParticleLines are set up:
            particleLines.setSize( numberOfParticles );
            recordingSucceeded = true;
            for( int lineCount( 1 );
                 ( recordingSucceeded
                 &&
                 ( lineCount <= numberOfParticles ) );
                 ++lineCount )
            {
              recordingSucceeded
              = particleLines[ lineCount - 1 ].recordLine( lineCount,
                                               eventAsLines[ lineCount ] );
              if( !recordingSucceeded
                  &&
                  isVerbose )
              {
                BOL::StringParser::parseByChar( eventAsLines[ lineCount ],
                                                lineAsNumbersAsStrings,
                                          BOL::StringParser::whitespaceChars );
                std::cout
                << std::endl
                << "LHPC::warning! recording event " << eventNumberInFile
                << " as invalid because particle line " << lineCount
                << " consisted of " << lineAsNumbersAsStrings.getSize()
                << " numbers rather than the required 13 numbers.";
                std::cout << std::endl;
              }
            }
            if( !recordingSucceeded )
            {
              // the warning about an invalid event is given in the loop rather
              // than here so that it can state which line was problematic.
              setAsInvalid();
              return false;
            }
            else
            {
              setUpPointersBetweenParticleLines();
              return true;
            }
            // end of if-else to finally set up the ParticleLines after
            // checking that they all recorded properly.
          }
          // end of if-else checking that the number of particles in the header
          // matches the number of lines for particles in the event.
        }  // end of if-else checking that the header is correctly formed.
      }
      // end of if-else checking that there were enough lines to form an event.
    }

    void
    LhefEvent::setUpPointersBetweenParticleLines()
    // this sets up the mother & daughter pointers for each ParticleLine in
    // particleLines.
    {
      for( int lineCount( 0 );
           lineCount < numberOfParticles;
           ++lineCount )
      {
        motherLineNumber
        = particleLines[ lineCount ].getPrimaryMotherLineNumber();
        if( motherLineNumber > 0 )
        {
          primaryMotherLinePointer
          = particleLines.getPointer( motherLineNumber - 1 );
        }
        else
        {
          primaryMotherLinePointer = NULL;
        }
        motherLineNumber
        = particleLines[ lineCount ].getSecondaryMotherLineNumber();
        if( motherLineNumber > 0 )
        {
          secondaryMotherLinePointer
          = particleLines.getPointer( motherLineNumber - 1 );
        }
        else
        {
          secondaryMotherLinePointer = NULL;
        }
        particleLines[ lineCount ].setMotherLines( primaryMotherLinePointer,
                                                  secondaryMotherLinePointer );
      }
    }

  }

}
