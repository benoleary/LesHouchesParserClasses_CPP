/*
 * BlockInterpretter.hpp
 *
 *  Created on: Mar 11, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#ifndef BLOCKINTERPRETTER_HPP_
#define BLOCKINTERPRETTER_HPP_

#include "../../BOLlib/Classes/BasicObserver.hpp"
#include "../../BOLlib/Classes/StringParser.hpp"
#include "BaseBlockAsStrings.hpp"

namespace LHPC
{
  namespace SLHA
  {
    // this abstract base class provides a base class for interpretting
    // BaseBlockAsStrings instances.
    class BlockInterpretter : public BOL::BasicObserver
    {
    public:
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


    protected:
      static BOL::StringParser const slhaDoubleMaker;
      static BOL::StringParser const slhaIntHelper;
      static BOL::StringParser const particleCodeMaker;

      static std::string
      spacePaddedSlhaInt( int const intToConvert,
                          int const returnStringLength );
      /* this returns a string for intToConvert that is at least
       * returnStringLength chars long, with no prefix for positive numbers &
       * '-' prefixing negative numbers, padded out with spaces before the
       * prefix.
       */

      BlockClass::BaseBlockAsStrings* stringsToObserve;
    };





    inline void
    BlockInterpretter::observeStrings(
                       BlockClass::BaseBlockAsStrings* const stringsToObserve )
    {
      // stop observing the old stringsToObserve, & start observing the new:
      this->stringsToObserve->removeObserver( this );
      this->stringsToObserve = stringsToObserve;
      stringsToObserve->registerObserver( this );
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

    inline std::string
    BlockInterpretter::spacePaddedSlhaInt( int const intToConvert,
                                           int const returnStringLength )
    /* this returns a string for intToConvert that is at least
     * returnStringLength chars long, with no prefix for positive numbers &
     * '-' prefixing negative numbers, padded out with spaces before the
     * prefix.
     */
    {
      std::string intString( slhaIntHelper.intToString( intToConvert ) );
      if( (size_t)returnStringLength > intString.size() )
      {
        intString.insert( 0,
                          ( returnStringLength - intString.size() ),
                          ' ' );
      }
      return intString;
    }

  }

}

#endif /* BLOCKINTERPRETTER_HPP_ */
