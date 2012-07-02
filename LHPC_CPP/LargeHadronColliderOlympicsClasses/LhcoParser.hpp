/*
 * LhcoParser.hpp
 *
 *  Created on: Jun 29, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#ifndef LHCOPARSER_HPP_
#define LHCOPARSER_HPP_

#include "../BOLlib/Classes/CommentedTextParser.hpp"
#include "../BOLlib/Classes/VectorlikeArray.hpp"
#include "LhcoEvent.hpp"

namespace LHPC
{
  // this is a class for reading in a LHCO format file & parsing the events
  // from it.
  class LhcoParser
  {
  public:
    LhcoParser( std::string const eventFileName = "",
                bool const isVerbose = true );
    ~LhcoParser();

    bool
    openFile( std::string const& eventFileName );
    // this opens the file with the given name as the source of its events &
    // returns true, unless the file could not be opened.
    bool
    readNextEvent();
    // this reads in the next event in the event file, & returns true if
    // successful.
    LHCO::LhcoEvent const&
    getEvent() const;
    // this returns the last parsed event.


  protected:
    bool isVerbose;
    BOL::CommentedTextParser fileParser;
    LHCO::LhcoEvent currentEvent;
    bool fileIsOpen;
    std::string currentLine;
    int lineNumber;

    bool
    lookForFirstEvent();
    // this reads in to the 1st non-commented line that begins with '0' with
    // optional whitespace before it & at least 1 whitespace-type character
    // following it. it returns true if it found such a line, which it also
    // assigns to currentLine.
  };





  inline bool
  LhcoParser::openFile( std::string const& eventFileName )
  // this opens the file with the given name as the source of its events &
  // returns true, unless the file could not be opened. it also reads in up to
  // the 1st event (preparing currentEvent with the 1st "line 0" of an event).
  {
    fileIsOpen = fileParser.openFile( eventFileName );
    if( fileIsOpen )
    {
      fileIsOpen = lookForFirstEvent();
      if( fileIsOpen )
      {
        lineNumber = currentEvent.recordLine( currentLine );
      }
    }
    return fileIsOpen;
  }

  inline LHCO::LhcoEvent const&
  LhcoParser::getEvent() const
  // this returns the last parsed event.
  {
    return currentEvent;
  }

  inline bool
  LhcoParser::lookForFirstEvent()
  // this reads in to the 1st non-commented line that begins with '0' with
  // optional whitespace before it & at least 1 whitespace-type character
  // following it. it returns true if it found such a line, which it also
  // assigns to currentLine.
  {
    if( fileIsOpen )
    {
      bool notYetFoundFirstLineOfAnEvent( true );
      while( fileIsOpen
             &&
             notYetFoundFirstLineOfAnEvent )
      {
        fileIsOpen
        = fileParser.readNextNonEmptyLineOfFileWithoutComment( currentLine );
        if( fileIsOpen )
        {
          notYetFoundFirstLineOfAnEvent
          = ( 0.0 != BOL::StringParser::stringToDouble( currentLine ) );
          // stringToDouble(...) takes the 1st number found in the string.
        }
      }
      // this loop ends as soon as a line starting with 0 was found, or if the
      // end of the file was reached.
    }
    return fileIsOpen;
  }

}

#endif /* LHCOPARSER_HPP_ */
