/*
 * SlhaSimplisticInterpreter.cpp
 *
 *  Created on: Sep 13, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#include "SLHA.hpp"

namespace LHPC
{
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


  std::string
  SlhaSimplisticInterpreter::operator()( std::string blockNameAndIndices )
  {
    std::string returnString( "" );
    BOL::StringParser::substituteCharacterWith( blockNameAndIndices,
                                                '[',
                                                ' ' );
    BOL::StringParser::substituteCharacterWith( blockNameAndIndices,
                                                ']',
                                                ' ' );
    BOL::StringParser::substituteCharacterWith( blockNameAndIndices,
                                                '(',
                                                ' ' );
    BOL::StringParser::substituteCharacterWith( blockNameAndIndices,
                                                ')',
                                                ' ' );
    std::string indicesString( "" );
    std::string blockName( BOL::StringParser::substringToFirst(
                                                           blockNameAndIndices,
                                                                " ",
                                                            &indicesString ) );
    std::vector< int >
    indicesVector( BOL::StringParser::stringToIntVector( indicesString ) );

    SLHA::BlockClass::BaseStringBlock const&
    blockAsStrings( (*slhaParser.getBlockAsStrings( blockName ))[ 0 ] );
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
      if( blockLine.getSize() > (int)(indicesVector.size()) )
      {
        indicesMatch = true;
        for( unsigned int whichIndex( 0 );
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
        for( int whichReturnWord( indicesVector.size() );
             blockLine.getSize() > whichReturnWord;
             ++whichReturnWord )
        {
          if( 0 < whichReturnWord )
          {
            returnString.append( "   " );
          }
          returnString.append( blockLine[ whichReturnWord ] );
        }
        break;
      }
    }
    return returnString;
  }

} /* namespace LHPC */
