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
#include <list>
#include <map>
#include "SlhaParser.hpp"
#include "BlockClasses/SameNameBlockSet.hpp"
#include "BlockClasses/BaseStringBlock.hpp"
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
    operator()( std::string const& blockNameWithIndices ) const;
    std::list< std::pair< double, std::string > >
    getScalesPairedWithValues( std::string const& blockNameWithIndices ) const;
    std::string
    withMap( std::string blockNameWithIndices );
    double
    getDouble( std::string blockNameWithIndices );
    int
    getInt( std::string blockNameWithIndices );
    double
    getLowestScale( std::string const& blockName ) const;
    bool
    readFile( std::string const& slhaFileName );
    // this opens the file with name given by slhaFileName with slhaParser.


  protected:
    SlhaParser slhaParser;
    std::stringstream stringParser;
    std::map< std::string, std::string > keyedResults;
    std::map< std::string, std::string >::iterator mapIterator;

    std::stringstream&
    getStringParser( std::string const& newStringForParser );

    std::pair< SLHA::SameNameBlockSet const*, std::vector< int > >
    getBlockSetWithIndexVector( std::string blockNameWithIndices ) const;

    std::string
    getBlockEntry( SLHA::BlockClass::BaseStringBlock const& blockAsStrings,
                   std::vector< int > const& indicesVector ) const;
  };





  inline std::string SlhaSimplisticInterpreter::operator()(
                                std::string const& blockNameWithIndices ) const
  {
    std::pair< SLHA::SameNameBlockSet const*, std::vector< int > >
    blockSetWithIndexVector( getBlockSetWithIndexVector(
                                                      blockNameWithIndices ) );
    if( NULL == blockSetWithIndexVector.first )
    {
      return std::string( "" );
    }
    return getBlockEntry( (*(blockSetWithIndexVector.first))[ 0 ],
                          blockSetWithIndexVector.second );
  }

  inline std::list< std::pair< double, std::string > >
  SlhaSimplisticInterpreter::getScalesPairedWithValues(
                                std::string const& blockNameWithIndices ) const
  {
    std::list< std::pair< double, std::string > > returnList;
    std::pair< SLHA::SameNameBlockSet const*, std::vector< int > >
    blockSetWithIndices( getBlockSetWithIndexVector( blockNameWithIndices ) );
    if( NULL != blockSetWithIndices.first )
    {
      SLHA::SameNameBlockSet const& blockSet( *(blockSetWithIndices.first) );
      for( size_t setIndex( 1 );
           setIndex <= static_cast< size_t >(
                               blockSet.getNumberOfCopiesWithDifferentScale());
           ++setIndex )
      {
        returnList.push_back( std::make_pair( blockSet[ setIndex ].getScale(),
                                           getBlockEntry( blockSet[ setIndex ],
                                              blockSetWithIndices.second ) ) );
      }
    }
    return returnList;
  }

  inline std::string
  SlhaSimplisticInterpreter::withMap( std::string blockNameWithIndices )
  {
    mapIterator = keyedResults.find( blockNameWithIndices );
    if( keyedResults.end() == mapIterator )
    {
      mapIterator = keyedResults.insert( keyedResults.begin(),
                                         std::pair< std::string, std::string >(
                                                           blockNameWithIndices,
                                            (*this)( blockNameWithIndices ) ) );
    }
    return mapIterator->second;
  }

  inline double
  SlhaSimplisticInterpreter::getDouble( std::string blockNameWithIndices )
  {
    double returnValue( 0.0 );
    getStringParser( (*this)( blockNameWithIndices ) ) >> returnValue;
    return returnValue;
  }

  inline int
  SlhaSimplisticInterpreter::getInt( std::string blockNameWithIndices )
  {
    int returnValue( 0 );
    getStringParser( (*this)( blockNameWithIndices ) ) >> returnValue;
    return returnValue;
  }

  inline double
  SlhaSimplisticInterpreter::getLowestScale(
                                           std::string const& blockName ) const
  {
    return (*slhaParser.getBlockAsStrings( blockName ))[ 0 ].getScale();
  }

  inline bool
  SlhaSimplisticInterpreter::readFile( std::string const& slhaFileName )
  // this opens the file with name given by slhaFileName with slhaParser.
  {
    keyedResults.clear();
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

  inline std::pair< SLHA::SameNameBlockSet const*, std::vector< int > >
  SlhaSimplisticInterpreter::getBlockSetWithIndexVector(
                                       std::string blockNameWithIndices ) const
  {
    BOL::StringParser::substituteCharacterWith( blockNameWithIndices,
                                                '[',
                                                ' ' );
    BOL::StringParser::substituteCharacterWith( blockNameWithIndices,
                                                ']',
                                                ' ' );
    BOL::StringParser::substituteCharacterWith( blockNameWithIndices,
                                                '(',
                                                ' ' );
    BOL::StringParser::substituteCharacterWith( blockNameWithIndices,
                                                ')',
                                                ' ' );
    std::string indicesString( "" );
    std::string blockName( BOL::StringParser::substringToFirst(
                       BOL::StringParser::trimFromFront( blockNameWithIndices,
                                BOL::StringParser::whitespaceAndNewlineChars ),
                                                                " ",
                                                            &indicesString ) );
    return std::make_pair( slhaParser.getBlockAsStrings( blockName ),
                       BOL::StringParser::stringToIntVector( indicesString ) );
  }

} /* namespace LHPC */
#endif /* SLHASIMPLISTICINTERPRETER_HPP_ */
