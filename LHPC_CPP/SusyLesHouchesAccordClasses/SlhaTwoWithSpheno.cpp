/*
 * SlhaTwoWithSpheno.cpp
 *
 *  Created on: Feb 22, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.LHPC_CPP.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
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
    SPHENOINFO.registerWith( fileParser );
    SPHENOINPUT.registerWith( fileParser );
    SPHENOCROSSSECTIONS.registerWith( fileParser );
    SPHENOLOWENERGY.registerWith( fileParser );
  }

  SlhaTwoWithSpheno::~SlhaTwoWithSpheno()
  {
    // does nothing.
  }

}
