/*
 * BasicParser.cpp
 *
 *  Created on: Mar 12, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.LHPC_CPP.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#include "BasicParser.hpp"

namespace LHPC
{
  namespace SLHA
  {
    std::string const BasicParser::blockIdentifierString( "BLOCK" );
    std::string const BasicParser::decayIdentifierString( "DECAY" );


    BasicParser::BasicParser( bool const shouldRecordBlocksNotRegistered,
                              bool const isVerbose ) :
          isVerbose( isVerbose ),
          shouldRecordBlocksNotRegistered( shouldRecordBlocksNotRegistered ),
          fileParser( "#",
                      this->isVerbose ),
          blockMap(),
          blockMapIterator(),
          mapInserter( "",
                       NULL ),
          currentBlockPointer( NULL ),
          dataString( "" ),
          commentString( "" ),
          firstWordOfLine( "" ),
          wordsOfLine( 2 )
      {
        // just an initialization list.
      }

    BasicParser::~BasicParser()
    {
      // does nothing.
    }

  }

}
