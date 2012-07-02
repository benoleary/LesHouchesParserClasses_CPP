/*
 * LhefParser.hpp
 *
 *  Created on: Jan 11, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.LHPC_CPP.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#ifndef LHEFPARSER_HPP_
#define LHEFPARSER_HPP_

#include "../BOLlib/Classes/AsciiXmlParser.hpp"
#include "../BOLlib/Classes/VectorlikeArray.hpp"
#include "LhefEvent.hpp"
#include "AutomaticEventFilter.hpp"
#include "DefaultFilterRules.hpp"
#include "../ParticleCodesAndDataClasses/NineDigitSlhaCodes.hpp"
#include "../ParticleCodesAndDataClasses/SevenDigitSlhaCodes.hpp"

namespace LHPC
{
  // this is a class for reading in a LHEF format file & parsing the events
  // from it.
  class LhefParser
  {
  public:
    LhefParser( std::string const eventFileName = "",
                bool const isVerbose = true );
    ~LhefParser();

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
    // interpreted.
    bool
    readNextEvent();
    // this reads in the next event in the event file, & returns true if
    // successful.
    LHEF::LhefEvent const&
    getEvent() const;
    // this returns the last parsed event.


  protected:
    bool isVerbose;
    BOL::AsciiXmlParser fileParser;
    LHEF::LhefEvent currentEvent;
    std::vector< LHEF::AutomaticEventFilter* > automaticFilters;
    bool fileIsOpen;
    std::string eventAsString;
    bool eventIsValid;
  };





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
  // interpreted.
  {
    return eventIsValid;
  }

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

}

#endif /* LHEFPARSER_HPP_ */
