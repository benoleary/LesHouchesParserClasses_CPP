/*
 * BlockInterpretter.cpp
 *
 *  Created on: Mar 11, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#include "BlockInterpretter.hpp"

namespace LHPC
{
  namespace SLHA
  {
    BOL::StringParser BlockInterpretter::slhaDoubleMaker( 9,
                                                          ' ',
                                                          9,
                                                          3 );
    BOL::StringParser BlockInterpretter::slhaIntHelper( 1,
                                                        ' ',
                                                        1,
                                                        1,
                                                        "" );
    BOL::StringParser BlockInterpretter::particleCodeMaker( 9,
                                                            ' ',
                                                            1,
                                                            1,
                                                            "" );

    BlockInterpretter::BlockInterpretter() :
        BOL::BasicObserver(),
        stringsToObserve( NULL )
    {
      // just an initialization list.
    }

    BlockInterpretter::~BlockInterpretter()
    {
      stringsToObserve->removeObserver( this );
    }

  }

}
