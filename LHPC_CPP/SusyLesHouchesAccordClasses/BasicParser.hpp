/*
 * BasicParser.hpp
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

#ifndef BASICPARSER_HPP_
#define BASICPARSER_HPP_

#include <string>
#include <map>
#include "../BOLlib/Classes/CommentedTextParser.hpp"
#include "../BOLlib/Classes/VectorlikeArray.hpp"
#include "BlockClasses/InterpreterClasses/BlockInterpreterFactory.hpp"
#include "BlockClasses/SameNameBlockSet.hpp"

namespace LHPC
{
  namespace SLHA
  {
    // this is an abstract base class to allow the SlhaParser class to know
    // about block types without going in circles of inclusion.
    class BasicParser
    {
    public:
      static std::string const blockIdentifierString;
      static std::string const decayIdentifierString;

      BasicParser( bool const shouldRecordBlocksNotRegistered = true,
                   bool const isVerbose = true);
      virtual
      ~BasicParser();

      virtual SameNameBlockSet*
      registerBlock(
              InterpreterClass::BlockInterpreterFactory& blockToUpdate ) = 0;
      // this registers blockToUpdate so that its data get updated every time a
      // new block of the appropriate name is read.


    protected:
      bool const isVerbose;
      bool const shouldRecordBlocksNotRegistered;
      BOL::CommentedTextParser fileParser;
      std::map< std::string, SameNameBlockSet* > blockMap;
      std::map< std::string, SameNameBlockSet* >::iterator
      blockMapIterator;
      std::pair< std::string, SameNameBlockSet* > mapInserter;
      SameNameBlockSet* currentBlockPointer;
      std::string dataString;
      std::string commentString;
      std::string firstWordOfLine;
      BOL::VectorlikeArray< std::string > wordsOfLine;
    };

  }

}

#endif /* BASICPARSER_HPP_ */
