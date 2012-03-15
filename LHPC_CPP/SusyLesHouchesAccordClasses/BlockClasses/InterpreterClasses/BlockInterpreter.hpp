/*
 * BlockInterpreter.hpp
 *
 *  Created on: Mar 11, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.LHPC_CPP.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#ifndef BLOCKINTERPRETER_HPP_
#define BLOCKINTERPRETER_HPP_

#include "../../../BOLlib/Classes/StringParser.hpp"
#include "../BaseStringBlock.hpp"

namespace LHPC
{
  namespace SLHA
  {
    // this abstract base class provides a base class for interpreting
    // BaseStringBlock instances.
    class BlockInterpreter
    {
    public:
      static BOL::StringParser const slhaDoubleMaker;
      static BOL::StringParser const slhaIntHelper;
      static BOL::StringParser const particleCodeMaker;
      static bool const defaultVerbosity;

      BlockInterpreter();
      virtual
      ~BlockInterpreter();

      void
      interpretStringBlock(
                       BlockClass::BaseStringBlock const& stringsToInterpret );
      std::string const&
      getLineWithoutComment( int const whichLine ) const;
      std::string
      getLineWithComment( int const whichLine ) const;
      /* information in comments can be decoded by someone else's code, because
       * putting important information in comments is an entirely unacceptably
       * stupid idea, in my humble opinion.
       */
      virtual std::string const&
      getAsString() = 0;
      // derived classes should return their block as a single string of
      // re-formatted interpreted values.
      virtual void
      clearEntries() = 0;
      // derived classes should clear their interpreted values.


    protected:
      BlockClass::BaseStringBlock* currentStringBlock;
      std::string stringInterpretation;

      virtual void
      interpretCurrentStringBlock() = 0;
    };





    inline void
    BlockInterpreter::interpretStringBlock(
                        BlockClass::BaseStringBlock const& stringsToInterpret )
    {
      clearEntries();
      this->stringsToInterpret = &stringsToInterpret;
      interpretCurrentStringBlock();
    }

    inline std::string const&
    BlockInterpreter::getLineWithoutComment( int const whichLine ) const
    {
      return (*stringsToInterpret)[ whichLine ].first;
    }

    inline std::string
    BlockInterpreter::getLineWithComment( int const whichLine ) const
    /* information in comments can be decoded by someone else's code, because
     * putting important information in comments is an entirely unacceptably
     * stupid idea, in my humble opinion.
     */
    {
      std::string returnString( (*stringsToInterpret)[ whichLine ].first );
      returnString.append( (*stringsToInterpret)[ whichLine ].second );
      return returnString;
    }

  }

}

#endif /* BLOCKINTERPRETER_HPP_ */
