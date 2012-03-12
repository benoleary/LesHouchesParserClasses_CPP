/*
 * BlockInterpretter.hpp
 *
 *  Created on: Mar 11, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#ifndef BLOCKINTERPRETTER_HPP_
#define BLOCKINTERPRETTER_HPP_

#include "../../../BOLlib/Classes/BasicObserver.hpp"
#include "../BaseBlockAsStrings.hpp"

namespace LHPC
{
  namespace SLHA
  {
    // this abstract base class provides a base class for interpretting
    // BaseBlockAsStrings instances.
    class BlockInterpretter : public BOL::BasicObserver
    {
    public:
      static BOL::StringParser const slhaDoubleMaker;
      static BOL::StringParser const slhaIntHelper;
      static BOL::StringParser const particleCodeMaker;

      BlockInterpretter();
      virtual
      ~BlockInterpretter();

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
      // re-formatted interpretted values.


    protected:
      BlockClass::BaseBlockAsStrings* stringsToObserve;
      std::string stringInterpretation;
    };





    inline void
    BlockInterpretter::observeStrings(
                       BlockClass::BaseBlockAsStrings* const stringsToObserve )
    {
      // stop observing the old stringsToObserve, & start observing the new:
      if( NULL != this->stringsToObserve )
      {
        this->stringsToObserve->removeObserver( this );
      }
      this->stringsToObserve = stringsToObserve;
      stringsToObserve->registerObserver( this );
      updateSelf();
    }

    inline std::string const&
    BlockInterpretter::getLineWithoutComment( int const whichLine ) const
    {
      return (*stringsToObserve)[ whichLine ].first;
    }

    inline std::string
    BlockInterpretter::getLineWithComment( int const whichLine ) const
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

#endif /* BLOCKINTERPRETTER_HPP_ */
