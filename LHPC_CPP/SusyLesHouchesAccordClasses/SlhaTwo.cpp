/*
 * SlhaTwo.cpp
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

#include "SlhaTwo.hpp"

namespace LHPC
{
  SlhaTwo::SlhaTwo( SlhaParser& fileParser,
                    bool const& isVerbose ) :
      SlhaOne( fileParser,
               isVerbose ),
      QEXTPAR( "QEXTPAR",
               BOL::UsefulStuff::notANumber,
               isVerbose ),
      IMMINPAR( "IMMINPAR",
                BOL::UsefulStuff::notANumber,
                isVerbose ),
      IMEXTPAR( "IMEXTPAR",
                BOL::UsefulStuff::notANumber,
                isVerbose ),
      IMNMIX( "IMNMIX",
              0.0,
              isVerbose ),
      IMUMIX( "IMUMIX",
              0.0,
              isVerbose ),
      IMVMIX( "IMVMIX",
              0.0,
              isVerbose ),
      IMSTOPMIX( "IMSTOPMIX",
                 0.0,
                 isVerbose ),
      IMSBOTMIX( "IMSBOTMIX",
                 0.0,
                 isVerbose ),
      IMSTAUMIX( "IMSTAUMIX",
                 0.0,
                 isVerbose ),
      IMALPHA( "IMALPHA",
               BOL::UsefulStuff::notANumber,
               isVerbose ),
      IMHMIX( "IMHMIX",
              BOL::UsefulStuff::notANumber,
              isVerbose ),
      IMGAUGE( "IMGAUGE",
                0.0,
                isVerbose ),
      IMMSOFT( "IMMSOFT",
               BOL::UsefulStuff::notANumber,
               isVerbose ),
      IMAU( "IMAU",
            0.0,
            isVerbose ),
      IMAD( "IMAD",
            0.0,
            isVerbose ),
      IMAE( "IMAE",
            0.0,
            isVerbose ),
      IMYU( "IMYU",
            0.0,
            isVerbose ),
      IMYD( "IMYD",
            0.0,
            isVerbose ),
      IMYE( "IMYE",
            0.0,
            isVerbose ),
      CVHMIX( "CVHMIX",
              0.0,
              isVerbose ),
      IMCVHMIX( "IMCVHMIX",
                0.0,
                isVerbose ),
      VCKMIN( "VCKMIN",
              0.0,
              isVerbose ),
      IMVCKMIN( "IMVCKMIN",
                0.0,
                isVerbose ),
      VCKM( "VCKM",
            0.0,
            isVerbose ),
      IMVCKM( "IMVCKM",
              0.0,
              isVerbose ),
      UPMNSIN( "UPMNSIN",
               0.0,
               isVerbose ),
      IMUPMNSIN( "IMUPMNSIN",
                 0.0,
                 isVerbose ),
      UPMNS( "UPMNS",
             0.0,
             isVerbose ),
      IMUPMNS( "IMUPMNS",
               0.0,
               isVerbose ),
      MSQ2IN( "MSQ2IN",
              0.0,
              isVerbose ),
      IMMSQ2IN( "IMMSQ2IN",
                0.0,
                isVerbose ),
      MSQ2( "MSQ2",
            0.0,
            isVerbose ),
      IMMSQ2( "IMMSQ2",
              0.0,
              isVerbose ),
      MSU2IN( "MSU2IN",
              0.0,
              isVerbose ),
      IMMSU2IN( "IMMSU2IN",
                0.0,
                isVerbose ),
      MSU2( "MSU2",
            0.0,
            isVerbose ),
      IMMSU2( "IMMSU2",
              0.0,
              isVerbose ),
      MSD2IN( "MSD2IN",
              0.0,
              isVerbose ),
      IMMSD2IN( "IMMSD2IN",
                0.0,
                isVerbose ),
      MSD2( "MSD2",
            0.0,
            isVerbose ),
      IMMSD2( "IMMSD2",
              0.0,
              isVerbose ),
      MSL2IN( "MSL2IN",
              0.0,
              isVerbose ),
      IMMSL2IN( "IMMSL2IN",
                0.0,
                isVerbose ),
      MSL2( "MSL2",
            0.0,
            isVerbose ),
      IMMSL2( "IMMSL2",
              0.0,
              isVerbose ),
      MSE2IN( "MSE2IN",
              0.0,
              isVerbose ),
      IMMSE2IN( "IMMSE2IN",
                0.0,
                isVerbose ),
      MSE2( "MSE2",
            0.0,
            isVerbose ),
      IMMSE2( "IMMSE2",
              0.0,
              isVerbose ),
      MSN2IN( "MSN2IN",
              0.0,
              isVerbose ),
      IMMSN2IN( "IMMSN2IN",
                0.0,
                isVerbose ),
      MSN2( "MSN2",
            0.0,
            isVerbose ),
      IMMSN2( "IMMSN2",
              0.0,
              isVerbose ),
      TUIN( "TUIN",
            0.0,
            isVerbose ),
      IMTUIN( "IMTUIN",
              0.0,
              isVerbose ),
      TU( "TU",
          0.0,
          isVerbose ),
      IMTU( "IMTU",
            0.0,
            isVerbose ),
      TDIN( "TDIN",
            0.0,
            isVerbose ),
      IMTDIN( "IMTDIN",
              0.0,
              isVerbose ),
      TD( "TD",
          0.0,
          isVerbose ),
      IMTD( "IMTD",
            0.0,
            isVerbose ),
      TEIN( "TEIN",
            0.0,
            isVerbose ),
      IMTEIN( "IMTEIN",
              0.0,
              isVerbose ),
      TE( "TE",
          0.0,
          isVerbose ),
      IMTE( "IMTE",
            0.0,
            isVerbose ),
      TNIN( "TNIN",
            0.0,
            isVerbose ),
      IMTNIN( "IMTNIN",
              0.0,
              isVerbose ),
      TN( "TN",
          0.0,
          isVerbose ),
      IMTN( "IMTN",
            0.0,
            isVerbose ),
      YN( "YN",
          0.0,
          isVerbose ),
      USQMIX( "USQMIX",
              0.0,
              isVerbose ),
      IMUSQMIX( "IMUSQMIX",
                0.0,
                isVerbose ),
      DSQMIX( "DSQMIX",
              0.0,
              isVerbose ),
      IMDSQMIX( "IMDSQMIX",
                0.0,
                isVerbose ),
      SELMIX( "SELMIX",
              0.0,
              isVerbose ),
      IMSELMIX( "IMSELMIX",
                0.0,
                isVerbose ),
      SNUMIX( "SNUMIX",
              0.0,
              isVerbose ),
      IMSNUMIX( "IMSNUMIX",
                0.0,
                isVerbose ),
      SNSMIX( "SNSMIX",
              0.0,
              isVerbose ),
      IMSNSMIX( "IMSNSMIX",
                0.0,
                isVerbose ),
      SNAMIX( "SNAMIX",
              0.0,
              isVerbose ),
      IMSNAMIX( "IMSNAMIX",
                0.0,
                isVerbose ),
      RVLAMLLEIN( "RVLAMLLEIN",
                  0.0,
                  isVerbose ),
      IMRVLAMLLEIN( "IMRVLAMLLEIN",
                    0.0,
                    isVerbose ),
      RVLAMLLE( "RVLAMLLE",
                0.0,
                isVerbose ),
      IMRVLAMLLE( "IMRVLAMLLE",
                  0.0,
                  isVerbose ),
      RVLAMLQDIN( "RVLAMLQDIN",
                  0.0,
                  isVerbose ),
      IMRVLAMLQDIN( "IMRVLAMLQDIN",
                    0.0,
                    isVerbose ),
      RVLAMLQD( "RVLAMLQD",
                0.0,
                isVerbose ),
      IMRVLAMLQD( "IMRVLAMLQD",
                  0.0,
                  isVerbose ),
      RVLAMUDDIN( "RVLAMUDDIN",
                  0.0,
                  isVerbose ),
      IMRVLAMUDDIN( "IMRVLAMUDDIN",
                    0.0,
                    isVerbose ),
      RVLAMUDD( "RVLAMUDD",
                0.0,
                isVerbose ),
      IMRVLAMUDD( "IMRVLAMUDD",
                  0.0,
                  isVerbose ),
      RVTLLEIN( "RVTLLEIN",
                0.0,
                isVerbose ),
      IMRVTLLEIN( "IMRVTLLEIN",
                  0.0,
                  isVerbose ),
      RVTLLE( "RVTLLE",
              0.0,
              isVerbose ),
      IMRVTLLE( "IMRVTLLE",
                0.0,
                isVerbose ),
      RVTLQDIN( "RVTLQDIN",
                0.0,
                isVerbose ),
      IMRVTLQDIN( "IMRVTLQDIN",
                  0.0,
                  isVerbose ),
      RVTLQD( "RVTLQD",
              0.0,
              isVerbose ),
      IMRVTLQD( "IMRVTLQD",
                0.0,
                isVerbose ),
      RVTUDDIN( "RVTUDDIN",
                0.0,
                isVerbose ),
      IMRVTUDDIN( "IMRVTUDDIN",
                  0.0,
                  isVerbose ),
      RVTUDD( "RVTUDD",
              0.0,
              isVerbose ),
      IMRVTUDD( "IMRVTUDD",
                0.0,
                isVerbose ),
      RVKAPPAIN( "RVKAPPAIN",
                 0.0,
                 isVerbose ),
      IMRVKAPPAIN( "IMRVKAPPAIN",
                   0.0,
                   isVerbose ),
      RVKAPPA( "RVKAPPA",
               0.0,
               isVerbose ),
      IMRVKAPPA( "IMRVKAPPA",
                 0.0,
                 isVerbose ),
      RVDIN( "RVDIN",
             0.0,
             isVerbose ),
      IMRVDIN( "IMRVDIN",
               0.0,
               isVerbose ),
      RVD( "RVD",
           0.0,
           isVerbose ),
      IMRVD( "IMRVD",
             0.0,
             isVerbose ),
      RVM2LH1( "RVM2LH1",
               0.0,
               isVerbose ),
      IMRVM2LH1( "IMRVM2LH1",
                 0.0,
                 isVerbose ),
      RVSNVEVIN( "RVSNVEVIN",
                 0.0,
                 isVerbose ),
      IMRVSNVEVIN( "IMRVSNVEVIN",
                   0.0,
                   isVerbose ),
      RVSNVEV( "RVSNVEV",
               0.0,
               isVerbose ),
      IMRVSNVEV( "IMRVSNVEV",
                 0.0,
                 isVerbose ),
      RVNMIX( "RVNMIX",
              0.0,
              isVerbose ),
      IMRVNMIX( "IMRVNMIX",
                0.0,
                isVerbose ),
      RVUMIX( "RVUMIX",
              0.0,
              isVerbose ),
      IMRVUMIX( "IMRVUMIX",
                0.0,
                isVerbose ),
      RVVMIX( "RVVMIX",
              0.0,
              isVerbose ),
      IMRVVMIX( "IMRVVMIX",
                0.0,
                isVerbose ),
      RVHMIX( "RVHMIX",
              0.0,
              isVerbose ),
      IMRVHMIX( "IMRVHMIX",
                0.0,
                isVerbose ),
      RVAMIX( "RVAMIX",
              0.0,
              isVerbose ),
      IMRVAMIX( "IMRVAMIX",
                0.0,
                isVerbose ),
      RVLMIX( "RVLMIX",
              0.0,
              isVerbose ),
      IMRVLMIX( "IMRVLMIX",
                0.0,
                isVerbose ),
      NMSSMRUN( "NMSSMRUN",
                BOL::UsefulStuff::notANumber,
                isVerbose ),
      NMHMIX( "NMHMIX",
              0.0,
              isVerbose ),
      IMNMHMIX( "IMNMHMIX",
                0.0,
                isVerbose ),
      NMAMIX( "NMAMIX",
              0.0,
              isVerbose ),
      IMNMAMIX( "IMNMAMIX",
                0.0,
                isVerbose ),
      NMNMIX( "NMNMIX",
              0.0,
              isVerbose ),
      IMNMNMIX( "IMNMNMIX",
            0.0,
            isVerbose )
  {
    QEXTPAR.registerWith( fileParser );
    IMMINPAR.registerWith( fileParser );
    IMEXTPAR.registerWith( fileParser );
    IMNMIX.registerWith( fileParser );
    IMUMIX.registerWith( fileParser );
    IMVMIX.registerWith( fileParser );
    IMSTOPMIX.registerWith( fileParser );
    IMSBOTMIX.registerWith( fileParser );
    IMSTAUMIX.registerWith( fileParser );
    IMALPHA.registerWith( fileParser );
    IMHMIX.registerWith( fileParser );
    IMGAUGE.registerWith( fileParser );
    IMMSOFT.registerWith( fileParser );
    IMAU.registerWith( fileParser );
    IMAD.registerWith( fileParser );
    IMAE.registerWith( fileParser );
    IMYU.registerWith( fileParser );
    IMYD.registerWith( fileParser );
    IMYE.registerWith( fileParser );
    CVHMIX.registerWith( fileParser );
    IMCVHMIX.registerWith( fileParser );
    VCKMIN.registerWith( fileParser );
    IMVCKMIN.registerWith( fileParser );
    VCKM.registerWith( fileParser );
    IMVCKM.registerWith( fileParser );
    UPMNSIN.registerWith( fileParser );
    IMUPMNSIN.registerWith( fileParser );
    UPMNS.registerWith( fileParser );
    IMUPMNS.registerWith( fileParser );
    MSQ2IN.registerWith( fileParser );
    IMMSQ2IN.registerWith( fileParser );
    MSQ2.registerWith( fileParser );
    IMMSQ2.registerWith( fileParser );
    MSU2IN.registerWith( fileParser );
    IMMSU2IN.registerWith( fileParser );
    MSU2.registerWith( fileParser );
    IMMSU2.registerWith( fileParser );
    MSD2IN.registerWith( fileParser );
    IMMSD2IN.registerWith( fileParser );
    MSD2.registerWith( fileParser );
    IMMSD2.registerWith( fileParser );
    MSL2IN.registerWith( fileParser );
    IMMSL2IN.registerWith( fileParser );
    MSL2.registerWith( fileParser );
    IMMSL2.registerWith( fileParser );
    MSE2IN.registerWith( fileParser );
    IMMSE2IN.registerWith( fileParser );
    MSE2.registerWith( fileParser );
    IMMSE2.registerWith( fileParser );
    MSN2IN.registerWith( fileParser );
    IMMSN2IN.registerWith( fileParser );
    MSN2.registerWith( fileParser );
    IMMSN2.registerWith( fileParser );
    TUIN.registerWith( fileParser );
    IMTUIN.registerWith( fileParser );
    TU.registerWith( fileParser );
    IMTU.registerWith( fileParser );
    TDIN.registerWith( fileParser );
    IMTDIN.registerWith( fileParser );
    TD.registerWith( fileParser );
    IMTD.registerWith( fileParser );
    TEIN.registerWith( fileParser );
    IMTEIN.registerWith( fileParser );
    TE.registerWith( fileParser );
    IMTE.registerWith( fileParser );
    TNIN.registerWith( fileParser );
    IMTNIN.registerWith( fileParser );
    TN.registerWith( fileParser );
    IMTN.registerWith( fileParser );
    YN.registerWith( fileParser );
    USQMIX.registerWith( fileParser );
    IMUSQMIX.registerWith( fileParser );
    DSQMIX.registerWith( fileParser );
    IMDSQMIX.registerWith( fileParser );
    SELMIX.registerWith( fileParser );
    IMSELMIX.registerWith( fileParser );
    SNUMIX.registerWith( fileParser );
    IMSNUMIX.registerWith( fileParser );
    SNSMIX.registerWith( fileParser );
    IMSNSMIX.registerWith( fileParser );
    SNAMIX.registerWith( fileParser );
    IMSNAMIX.registerWith( fileParser );
    RVLAMLLEIN.registerWith( fileParser );
    IMRVLAMLLEIN.registerWith( fileParser );
    RVLAMLLE.registerWith( fileParser );
    IMRVLAMLLE.registerWith( fileParser );
    RVLAMLQDIN.registerWith( fileParser );
    IMRVLAMLQDIN.registerWith( fileParser );
    RVLAMLQD.registerWith( fileParser );
    IMRVLAMLQD.registerWith( fileParser );
    RVLAMUDDIN.registerWith( fileParser );
    IMRVLAMUDDIN.registerWith( fileParser );
    RVLAMUDD.registerWith( fileParser );
    IMRVLAMUDD.registerWith( fileParser );
    RVTLLEIN.registerWith( fileParser );
    IMRVTLLEIN.registerWith( fileParser );
    RVTLLE.registerWith( fileParser );
    IMRVTLLE.registerWith( fileParser );
    RVTLQDIN.registerWith( fileParser );
    IMRVTLQDIN.registerWith( fileParser );
    RVTLQD.registerWith( fileParser );
    IMRVTLQD.registerWith( fileParser );
    RVTUDDIN.registerWith( fileParser );
    IMRVTUDDIN.registerWith( fileParser );
    RVTUDD.registerWith( fileParser );
    IMRVTUDD.registerWith( fileParser );
    RVKAPPAIN.registerWith( fileParser );
    IMRVKAPPAIN.registerWith( fileParser );
    RVKAPPA.registerWith( fileParser );
    IMRVKAPPA.registerWith( fileParser );
    RVDIN.registerWith( fileParser );
    IMRVDIN.registerWith( fileParser );
    RVD.registerWith( fileParser );
    IMRVD.registerWith( fileParser );
    RVM2LH1.registerWith( fileParser );
    IMRVM2LH1.registerWith( fileParser );
    RVSNVEVIN.registerWith( fileParser );
    IMRVSNVEVIN.registerWith( fileParser );
    RVSNVEV.registerWith( fileParser );
    IMRVSNVEV.registerWith( fileParser );
    RVNMIX.registerWith( fileParser );
    IMRVNMIX.registerWith( fileParser );
    RVUMIX.registerWith( fileParser );
    IMRVUMIX.registerWith( fileParser );
    RVVMIX.registerWith( fileParser );
    IMRVVMIX.registerWith( fileParser );
    RVHMIX.registerWith( fileParser );
    IMRVHMIX.registerWith( fileParser );
    RVAMIX.registerWith( fileParser );
    IMRVAMIX.registerWith( fileParser );
    RVLMIX.registerWith( fileParser );
    IMRVLMIX.registerWith( fileParser );
    NMSSMRUN.registerWith( fileParser );
    NMHMIX.registerWith( fileParser );
    IMNMHMIX.registerWith( fileParser );
    NMAMIX.registerWith( fileParser );
    IMNMAMIX.registerWith( fileParser );
    NMNMIX.registerWith( fileParser );
    IMNMNMIX.registerWith( fileParser );
  }

  SlhaTwo::~SlhaTwo()
  {
    // does nothing.
  }

}
