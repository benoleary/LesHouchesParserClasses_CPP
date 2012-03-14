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

#include "../../../BOLlib/Classes/BasicObserver.hpp"
#include "../../../BOLlib/Classes/StringParser.hpp"
#include "../BaseBlockAsStrings.hpp"

namespace LHPC
{
  namespace SLHA
  {
    // this abstract base class provides a base class for interpreting
    // BaseBlockAsStrings instances.
    class BlockInterpreter : public BOL::BasicObserver
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
      observeStrings( BlockClass::BaseBlockAsStrings* const stringsToObserve );
      std::string const&
      getLineWithoutComment( int const whichLine ) const;
      std::string
      getLineWithComment( int const whichLine ) const;
      /* information in comments can be decoded by someone else's code, because
       * putting important information in comments is an entirely unacceptably
       * stupid idea, in my humble opinion.
       */
      virtual std::string const&
      interpretAsString() = 0;
      // derived classes should return their block as a single string of
      // re-formatted interpreted values.


    protected:
      BlockClass::BaseBlockAsStrings* stringsToObserve;
      std::string stringInterpretation;
    };





    inline void
    BlockInterpreter::observeStrings(
                       BlockClass::BaseBlockAsStrings* const stringsToObserve )
    {
      // stop observing the old stringsToObserve, & start observing the new:
      if( NULL != this->stringsToObserve )
      {
        this->stringsToObserve->removeObserver( this );
      }
      this->stringsToObserve = stringsToObserve;
      stringsToObserve->registerObserver( this );
      this->respondToObservedSignal();
    }

    inline std::string const&
    BlockInterpreter::getLineWithoutComment( int const whichLine ) const
    {
      return (*stringsToObserve)[ whichLine ].first;
    }

    inline std::string
    BlockInterpreter::getLineWithComment( int const whichLine ) const
    /* information in comments can be decoded by someone else's code, because
     * putting important information in comments is an entirely unacceptably
     * stupid idea, in my humble opinion.
     */
    {
      std::string returnString( (*stringsToObserve)[ whichLine ].first );
      returnString.append( (*stringsToObserve)[ whichLine ].second );
      return returnString;
    }

  }

}

#endif /* BLOCKINTERPRETER_HPP_ */
