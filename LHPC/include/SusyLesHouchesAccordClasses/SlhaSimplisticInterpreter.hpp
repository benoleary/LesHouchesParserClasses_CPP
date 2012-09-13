/*
 * SlhaSimplisticInterpreter.hpp
 *
 *  Created on: Sep 13, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#ifndef SLHASIMPLISTICINTERPRETER_HPP_
#define SLHASIMPLISTICINTERPRETER_HPP_

#include <string>
#include <sstream>
#include <vector>
#include "SlhaParser.hpp"
#include "BOLlib/include/BOLlib.hpp"

namespace LHPC
{
  /* this is a class for an object that reads in an SLHA file & then returns
   * strings interpreting given keys as block names with sets of index
   * integers. it also includes functionality to interpret the string as a
   * double or an int.
   */
  class SlhaSimplisticInterpreter
  {
  public:
    SlhaSimplisticInterpreter( std::string const& slhaFilename );
    ~SlhaSimplisticInterpreter();

    std::string
    operator()( std::string blockNameAndIndices );
    double
    getDouble( std::string blockNameAndIndices );
    int
    getInt( std::string blockNameAndIndices );
    bool
    readFile( std::string const& slhaFileName );
    // this opens the file with name given by slhaFileName with slhaParser.


  protected:
    SlhaParser slhaParser;
    std::stringstream stringParser;

    std::stringstream&
    getStringParser( std::string const& newStringForParser );
  };





  inline double
  SlhaSimplisticInterpreter::getDouble( std::string blockNameAndIndices )
  {
    double returnValue( 0.0 );
    getStringParser( (*this)( blockNameAndIndices ) ) >> returnValue;
    return returnValue;
  }

  inline int
  SlhaSimplisticInterpreter::getInt( std::string blockNameAndIndices )
  {
    int returnValue( 0 );
    getStringParser( (*this)( blockNameAndIndices ) ) >> returnValue;
    return returnValue;
  }

  inline bool
  SlhaSimplisticInterpreter::readFile( std::string const& slhaFileName )
  // this opens the file with name given by slhaFileName with slhaParser.
  {
    return slhaParser.readFile( slhaFileName );
  }

  inline std::stringstream&
  SlhaSimplisticInterpreter::getStringParser(
                                        std::string const& newStringForParser )
  {
    stringParser.clear();
    stringParser.str( newStringForParser );
    return stringParser;
  }


} /* namespace LHPC */
#endif /* SLHASIMPLISTICINTERPRETER_HPP_ */
