/*
 * BaseSlhaBlock.cpp
 *
 *  Created on: Mar 15, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#include "BaseSlhaBlock.hpp"

namespace LHPC
{
  namespace SLHA
  {
    BaseSlhaBlock::BaseSlhaBlock( std::string const& blockName ) :
        StringBlockObserver(),
        blockName( blockName )
    {
      BOL::StringParser::transformToUppercase( this->blockName );
    }

    BaseSlhaBlock::~BaseSlhaBlock()
    {
      // does nothing.
    }

  }

}
