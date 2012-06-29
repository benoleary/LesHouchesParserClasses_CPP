/*
 * LhcoEvent.cpp
 *
 *  Created on: Jun 29, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#include "LhcoEvent.hpp"

namespace LHPC
{
  namespace LHCO
  {
    std::string const LhcoEvent::trimmingChars( " \t\r\n" );
    bool const LhcoEvent::trueForVerbosity( true );
    std::string const LhcoEvent::eventCommentLine(
     "#   typ     eta    phi       pt  jmass  ntrk  btag   had/em  dummy dummy"
                                                                             );
    int const LhcoEvent::charactersForEventNumber( 14 );
    int const LhcoEvent::charactersForTriggerWord( 6 );

    LhcoEvent::LhcoEvent( bool const& isVerbose ) :
        numberOfObjects( 0 ),
        eventNumber( 0 ),
        triggerWord( 0 ),
        objectLines(),
        photonLines(),
        electronLines(),
        muonLines(),
        tauLines(),
        jetLines(),
        missingEnergyLinePointer( NULL ),
        missingEnergyLines(),
        emptyList(),
        isVerbose( isVerbose ),
        eventAsString( "" ),
        interpretingObjectLine()
    {
      // just an initialization list.
    }

    LhcoEvent::LhcoEvent( LhcoEvent const& copySource ) :
        numberOfObjects( copySource.numberOfObjects ),
        eventNumber( copySource.eventNumber ),
        triggerWord( copySource.triggerWord ),
        objectLines( copySource.objectLines,
                     &ObjectLine::copyObjectLine ),
        photonLines(),
        electronLines(),
        muonLines(),
        tauLines(),
        jetLines(),
        missingEnergyLinePointer( NULL ),
        missingEnergyLines(),
        emptyList(),
        isVerbose( trueForVerbosity ),
        eventAsString( "" ),
        interpretingObjectLine()
    {
      for( int whichLine( 0 );
           objectLines.getLastIndex() >= whichLine;
           ++whichLine )
      {
        if( 0 == objectLines[ whichLine ].getObjectType() )
        {
          photonLines.push_back( objectLines.getPointer( whichLine ) );
        }
        else if( 1 == objectLines[ whichLine ].getObjectType() )
        {
          electronLines.push_back( objectLines.getPointer( whichLine ) );
        }
        else if( 2 == objectLines[ whichLine ].getObjectType() )
        {
          muonLines.push_back( objectLines.getPointer( whichLine ) );
        }
        else if( 3 == objectLines[ whichLine ].getObjectType() )
        {
          tauLines.push_back( objectLines.getPointer( whichLine ) );
        }
        else if( 4 == objectLines[ whichLine ].getObjectType() )
        {
          jetLines.push_back( objectLines.getPointer( whichLine ) );
        }
        else if( 6 == objectLines[ whichLine ].getObjectType() )
        {
          missingEnergyLinePointer = objectLines.getPointer( whichLine );
          missingEnergyLines.push_back( missingEnergyLinePointer );
        }
      }
    }

    LhcoEvent::~LhcoEvent()
    {
      // does nothing.
    }


    int
    LhcoEvent::recordLine( std::string const& lineAsString )
    // this parses the 1st word of lineAsString and returns it, first adding
    // a new ObjectLine if appropriate, noting its pointer in the appropriate
    // std::list. if lineAsString is the start of a new event (as the line
    // begins with 0, which is also what this function will return), it
    // prepares nextEventNumber & nextTriggerWord based on this line.
    {
      eventAsString.append( "\n" );
      eventAsString.append( lineAsString );

      lineParser.clearEntries();
      BOL::StringParser::parseByChar( lineAsString,
                                      lineParser,
                                      BOL::StringParser::whitespaceChars );

      if( 2 >= lineParser.getSize() )
        // if the wrong number of data was given (at least 2 numbers are
        // required)...
      {
        if( isVerbose )
        {
          std::cout
          << std::endl
          << "LHPC::warning! \"" << lineAsString
          << "\" is not a valid LHCO line!";
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

    lineParser.clearEntries();
    BOL::StringParser::parseByChar( lineAsString,
                                    lineParser,
                                    BOL::StringParser::whitespaceChars );
    if( 9 > lineParser.getSize() )
      // if too few numbers were given...
    {
      lineNumber = (int)BOL::UsefulStuff::notANumber;
      objectType = (int)BOL::UsefulStuff::notANumber;
      valueVector.assign( 11,
                          BOL::UsefulStuff::notANumber );
      return false;
    }
    else
    {
      valueVector.assign( lineParser.getSize(),
                          BOL::UsefulStuff::notANumber );
      lineNumber = BOL::StringParser::stringToInt( lineParser[ 0 ] );
      valueVector[ 0 ] = (double)lineNumber;
      objectType = BOL::StringParser::stringToInt( lineParser[ 1 ] );
      valueVector[ 1 ] = (double)objectType;
      for( int whichElement( 2 );
           lineParser.getLastIndex() >= whichElement;
           ++whichElement )
      {
        valueVector[ whichElement ]
        = BOL::StringParser::stringToDouble( lineParser[ whichElement ] );
      }
      return true;
    }
  }

}
