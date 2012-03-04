/*
 * SingleScaleBlockInterpretter.hpp
 *
 *  Created on: Mar 4, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#ifndef SINGLESCALEBLOCKINTERPRETTER_HPP_
#define SINGLESCALEBLOCKINTERPRETTER_HPP_

namespace LHPC
{
  namespace SLHA
  {
    // this interprets
    class SingleScaleBlockInterpretter
    {
    public:
      SingleScaleBlockInterpretter();
      virtual
      ~SingleScaleBlockInterpretter();

      // REGISTERING THE SET TO A NEW SameNameBlockSet SHOULD CLEAR THE ENTRIES
      // & FORGET THE PREVIOUS SameNameBlockSet.
    };

  }

}

#endif /* SINGLESCALEBLOCKINTERPRETTER_HPP_ */
