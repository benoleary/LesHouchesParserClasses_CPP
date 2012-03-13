/*
 * BaseBlockAsStrings.cpp
 *
 *  Created on: Mar 3, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.LHPC_CPP.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
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
