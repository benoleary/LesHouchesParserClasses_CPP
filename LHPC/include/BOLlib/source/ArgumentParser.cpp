/*
 * ArgumentParser.cpp
 *
 *  Created on: Sep 13, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *
 *      This file is part of BOLlib, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.BOLlib.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#include "ArgumentParser.hpp"

namespace BOL
{
  ArgumentParser::ArgumentParser( int argumentCount,
                                  char** argumentCharArrays ) :
    argumentStrings( ( argumentCount - 1 ),
                     "" )
  {
    for( int whichArgument( 1 );
         argumentCount > whichArgument;
         ++whichArgument )
    {
      argumentStrings[ whichArgument - 1 ].assign(
                                         argumentCharArrays[ whichArgument ] );
    }
  }

  ArgumentParser::~ArgumentParser()
  {
    // does nothing.
  }

} /* namespace BOL */
