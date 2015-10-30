/*
 * SlhaSimplisticInterpreter.cpp
 *
 *  Created on: Sep 13, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#include "SLHA.hpp"

namespace LHPC
{
  SlhaSimplisticInterpreter::SlhaSimplisticInterpreter() :
      slhaParser( true,
                  false ),
      stringParser()
  {
    // This constructor is just an initialization list.
  }

  SlhaSimplisticInterpreter::SlhaSimplisticInterpreter(
                                            std::string const& slhaFilename ) :
      slhaParser( true,
                  false ),
      stringParser()
  {
    slhaParser.readFile( slhaFilename );
  }

  SlhaSimplisticInterpreter::~SlhaSimplisticInterpreter()
  {
    // does nothing.
  }


  std::string SlhaSimplisticInterpreter::getBlockEntry(
                       SLHA::BlockClass::BaseStringBlock const& blockAsStrings,
                                std::vector< int > const& indicesVector ) const
  {
    std::string returnString( "" );
    BOL::VectorlikeArray< std::string > blockLine;
    for( int whichLine( blockAsStrings.getNumberOfBodyLines() );
         0 < whichLine;
         --whichLine )
    {
      blockLine.clearEntries();
      BOL::StringParser::parseByChar( blockAsStrings[ whichLine ].first,
                                      blockLine,
                                      BOL::StringParser::whitespaceChars );
      bool indicesMatch( false );
      if( blockLine.getSize() > static_cast< int >( indicesVector.size() ) )
      {
        indicesMatch = true;
        for( size_t whichIndex( 0 );
             indicesVector.size() > whichIndex;
             ++whichIndex )
        {
          if( indicesVector[ whichIndex ]
              != BOL::StringParser::stringToInt( blockLine[ whichIndex ] ) )
          {
            indicesMatch = false;
            break;
          }
        }
      }
      if( indicesMatch )
      {
        for( int whichReturnWord( static_cast< int >( indicesVector.size() ) );
             blockLine.getSize() > whichReturnWord;
             ++whichReturnWord )
        {
          returnString.append( blockLine[ whichReturnWord ] );
          if( blockLine.getLastIndex() > whichReturnWord )
          {
            returnString.append( "   " );
          }
        }
        break;
      }
    }
    return returnString;
  }

} /* namespace LHPC */
