/*
 * ArgumentParser.hpp
 *
 *  Created on: Sep 13, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *
 *      This file is part of BOLlib, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.BOLlib.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#ifndef ARGUMENTPARSER_HPP_
#define ARGUMENTPARSER_HPP_

#include <string>
#include <vector>

namespace BOL
{
  // this is a class to search the command line arguments for given strings.
  class ArgumentParser
  {
  public:
    ArgumentParser( int argumentCount,
                    char** argumentCharArrays );
    ~ArgumentParser();

    std::string
    getArgument( std::string const& argumentName ) const;
    // this looks for argumentName as a substring (from the starting char) of
    // any of the elements of argumentStrings, & returns the rest of the 1st
    // matching string (or an empty string if no match was found).


  protected:
    std::vector< std::string > argumentStrings;
  };





  inline std::string
  ArgumentParser::getArgument( std::string const& argumentName ) const
  // this looks for argumentName as a substring (from the starting char) of
  // any of the elements of argumentStrings, & returns the rest of the 1st
  // matching string (or an empty string if no match was found).
  {
    std::string returnString( "" );
    for( std::vector< std::string >::const_iterator
         whichArgument( argumentStrings.begin() );
         argumentStrings.end() > whichArgument;
         ++whichArgument )
    {
      if( 0 == whichArgument->compare( 0,
                                       argumentName.size(),
                                       argumentName ) )
      {
        returnString.assign( *whichArgument,
                             argumentName.size(),
                             ( whichArgument->size() - argumentName.size() ) );
        break;
      }
    }
    return returnString;
  }

} /* namespace BOL */
#endif /* ARGUMENTPARSER_HPP_ */
