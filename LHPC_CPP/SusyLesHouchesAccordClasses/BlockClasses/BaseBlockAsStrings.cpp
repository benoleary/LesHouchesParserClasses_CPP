/*
 * BaseBlockAsStrings.cpp
 *
 *  Created on: Mar 3, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#include "BaseBlockAsStrings.hpp"

namespace LHPC
{
  namespace SLHA
  {
    namespace BlockClass
    {
      BaseBlockAsStrings::BaseBlockAsStrings() :
          BasicObserved(),
          blockAsStringWithHeader( "" ),
          blocksAsStringArrays()
      {
        // just an initialization list.
      }

      BaseBlockAsStrings::~BaseBlockAsStrings()
      {
        // does nothing.
      }

    }

  }

}
