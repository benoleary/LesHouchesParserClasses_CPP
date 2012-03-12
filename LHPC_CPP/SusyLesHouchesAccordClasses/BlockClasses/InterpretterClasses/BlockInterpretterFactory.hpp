/*
 * BlockInterpretterFactory.hpp
 *
 *  Created on: Mar 11, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#ifndef BLOCKINTERPRETTERFACTORY_HPP_
#define BLOCKINTERPRETTERFACTORY_HPP_

#include "../BaseBlockAsStrings.hpp"

namespace LHPC
{
  namespace SLHA
  {
    namespace InterpretterClass
    {
      // this abstract base class allows SameNameBlockSet to register its
      // BaseBlockAsStrings instances with derived classes.
      class BlockInterpretterFactory
      {
      public:
        BlockInterpretterFactory();
        virtual
        ~BlockInterpretterFactory();

        virtual void
        clearEntries() = 0;
        virtual void
        addAndUpdateInterpretter(
                         BlockClass::BaseBlockAsStrings* observedStrings ) = 0;
      };

    }

  }

}

#endif /* BLOCKINTERPRETTERFACTORY_HPP_ */
