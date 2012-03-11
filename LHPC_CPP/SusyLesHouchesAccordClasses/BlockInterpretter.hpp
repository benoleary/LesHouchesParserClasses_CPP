/*
 * BlockInterpretter.hpp
 *
 *  Created on: Mar 11, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#ifndef BLOCKINTERPRETTER_HPP_
#define BLOCKINTERPRETTER_HPP_

namespace LHPC
{
  namespace SLHA
  {
    // this class does something!
    class BlockInterpretter
    {
    public:
      BlockInterpretter();
      virtual
      ~BlockInterpretter();


      /* this returns the lines without comments. if there is important
       * information encoded in the comments, the whole block in its original
       * form can be requested, & decoded by someone else's code, because
       * putting important information in comments is an entirely unacceptably
       * stupid idea, in my humble opinion.
       */

      std::string const&
      spacePaddedSlhaInt( int const intToConvert,
                          int const returnStringLength );
      /* this returns a string for intToConvert that is at least
       * returnStringLength chars long, with no prefix for positive numbers &
       * '-' prefixing negative numbers, padded out with spaces before the
       * prefix.
       */
    };
    inline std::string const&
    SlhaBlock::spacePaddedSlhaInt( int const intToConvert,
                                   int const returnStringLength )
    /* this returns a string for intToConvert that is at least
     * returnStringLength chars long, with no prefix for positive numbers &
     * '-' prefixing negative numbers, padded out with spaces before the
     * prefix.
     */
    {
      intString.assign( slhaIntHelper.intToString( intToConvert ) );
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
