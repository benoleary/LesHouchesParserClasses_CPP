/*
 * SlhaOne.cpp
 *
 *  Created on: Feb 6, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.LHPC_CPP.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#include "SlhaOne.hpp"

namespace LHPC
{
  SlhaOne::SlhaOne( SlhaParser& fileParser,
                    bool const& isVerbose ) :
      MODSEL( "MODSEL",
              BOL::UsefulStuff::notANumber,
              isVerbose ),
      SMINPUTS( "SMINPUTS",
                BOL::UsefulStuff::notANumber,
                isVerbose ),
      MINPAR( "MINPAR",
              BOL::UsefulStuff::notANumber,
              isVerbose ),
      EXTPAR( "EXTPAR",
              BOL::UsefulStuff::notANumber,
              isVerbose ),
      MASS( "MASS",
            BOL::UsefulStuff::notANumber,
            isVerbose,
            9 ),
      NMIX( "NMIX",
            0.0,
            isVerbose ),
      UMIX( "UMIX",
            0.0,
            isVerbose ),
      VMIX( "VMIX",
            0.0,
            isVerbose ),
      STOPMIX( "STOPMIX",
               0.0,
               isVerbose ),
      SBOTMIX( "SBOTMIX",
               0.0,
               isVerbose ),
      STAUMIX( "STAUMIX",
               0.0,
               isVerbose ),
      ALPHA( "ALPHA",
             BOL::UsefulStuff::notANumber,
             isVerbose ),
      HMIX( "HMIX",
            BOL::UsefulStuff::notANumber,
            isVerbose ),
      GAUGE( "GAUGE",
             BOL::UsefulStuff::notANumber,
             isVerbose ),
      MSOFT( "MSOFT",
             BOL::UsefulStuff::notANumber,
             isVerbose ),
      AU( "AU",
          0.0,
          isVerbose ),
      AD( "AD",
          0.0,
          isVerbose ),
      AE( "AE",
          0.0,
          isVerbose ),
      YU( "YU",
          0.0,
          isVerbose ),
      YD( "YD",
          0.0,
          isVerbose ),
      YE( "YE",
          0.0,
          isVerbose ),
      SPINFO( "SPINFO",
              isVerbose ),
      fileParser( fileParser ),
      isVerbose( isVerbose )
  {
    MODSEL.registerWith( fileParser );
    SMINPUTS.registerWith( fileParser );
    MINPAR.registerWith( fileParser );
    EXTPAR.registerWith( fileParser );
    MASS.registerWith( fileParser );
    NMIX.registerWith( fileParser );
    UMIX.registerWith( fileParser );
    VMIX.registerWith( fileParser );
    STOPMIX.registerWith( fileParser );
    SBOTMIX.registerWith( fileParser );
    STAUMIX.registerWith( fileParser );
    ALPHA.registerWith( fileParser );
    HMIX.registerWith( fileParser );
    GAUGE.registerWith( fileParser );
    MSOFT.registerWith( fileParser );
    AU.registerWith( fileParser );
    AD.registerWith( fileParser );
    AE.registerWith( fileParser );
    YU.registerWith( fileParser );
    YD.registerWith( fileParser );
    YE.registerWith( fileParser );
    SPINFO.registerWith( fileParser );
  }

  SlhaOne::~SlhaOne()
  {
    // does nothing.
  }

}
