/*
 * SlhaTwoWithSpheno.cpp
 *
 *  Created on: Feb 22, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#include "SlhaTwoWithSpheno.hpp"

namespace LHPC
{
  SlhaTwoWithSpheno::SlhaTwoWithSpheno( SlhaParser& fileParser,
                                        bool const& isVerbose ) :
      SlhaTwo( fileParser,
               isVerbose ),
      SPHENOINFO( "SPHENOINFO",
                  BOL::UsefulStuff::notANumber,
                  isVerbose ),
      SPHENOINPUT( "SPHENOINPUT",
                   isVerbose ),
      SPHENOCROSSSECTIONS( "SPHENOCROSSSECTIONS",
                           isVerbose ),
      SPHENOLOWENERGY( "SPHENOLOWENERGY",
                       BOL::UsefulStuff::notANumber,
                       isVerbose )
  {
    fileParser.registerBlock( SPHENOINFO );
    fileParser.registerBlock( SPHENOINPUT );
    fileParser.registerBlock( SPHENOCROSSSECTIONS );
    fileParser.registerBlock( SPHENOLOWENERGY );
  }

  SlhaTwoWithSpheno::~SlhaTwoWithSpheno()
  {
    // does nothing.
  }

}
