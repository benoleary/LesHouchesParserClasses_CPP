/*
 * LhefParser.cpp
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

#include "LhefParser.hpp"

namespace LHPC
{
  LhefParser::LhefParser( std::string const eventFileName,
                          bool const isVerbose ) :
      isVerbose( isVerbose ),
      fileParser( "event",
                  this->isVerbose ),
      currentEvent( this->isVerbose ),
      automaticFilters(),
      fileIsOpen( false ),
      eventAsString( "" ),
      eventIsValid( false )
  {
    if( !(eventFileName.empty()) )
    {
      openFile( eventFileName );
    }
  }

  LhefParser::~LhefParser()
  {
    // does nothing.
  }

}
