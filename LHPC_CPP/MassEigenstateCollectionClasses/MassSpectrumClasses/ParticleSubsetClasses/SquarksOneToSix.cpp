/*
 * SquarksOneToSix.cpp
 *
 *  Created on: Jan 18, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.LHPC_CPP.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#include "SquarksOneToSix.hpp"

namespace LHPC
{
  namespace MassSpectrumClass
  {
    SquarksOneToSix::SquarksOneToSix( bool const& isVerbose,
                                    std::vector< bool >* const defaultFlags ) :
        MassSpectrum( isVerbose,
                        defaultFlags ),
        antisdownOne( PDGIX::antisdownOne,
                      -PDGVII::sdownOne,
                      mapAndVectorAndBools,
                      false,
                      "sd1c",
                      "${\\tilde{d}}_{1}^{\\ast}$" ),
        sdownOne( antisdownOne,
                  "sd1",
                  "${\\tilde{d}}_{1}$" ),
        antisdownTwo( PDGIX::antisdownTwo,
                      -PDGVII::sdownTwo,
                      mapAndVectorAndBools,
                      false,
                      "sd2c",
                      "${\\tilde{d}}_{2}^{\\ast}$" ),
        sdownTwo( antisdownTwo,
                  "sd2",
                  "${\\tilde{d}}_{2}$" ),
        antisdownThree( PDGIX::antisdownThree,
                        -PDGVII::sdownThree,
                        mapAndVectorAndBools,
                        false,
                        "sd3c",
                        "${\\tilde{d}}_{3}^{\\ast}$" ),
        sdownThree( antisdownThree,
                    "sd1",
                    "${\\tilde{d}}_{1}$" ),
        antisdownFour( PDGIX::antisdownFour,
                       -PDGVII::sdownFour,
                       mapAndVectorAndBools,
                       false,
                       "sd4c",
                       "${\\tilde{d}}_{4}^{\\ast}$" ),
        sdownFour( antisdownFour,
                   "sd4",
                   "${\\tilde{d}}_{4}$" ),
        antisdownFive( PDGIX::antisdownFive,
                       -PDGVII::sdownFive,
                       mapAndVectorAndBools,
                       false,
                       "sd5c",
                       "${\\tilde{d}}_{5}^{\\ast}$" ),
        sdownFive( antisdownFive,
                   "sd5",
                   "${\\tilde{d}}_{5}$" ),
        antisdownSix( PDGIX::antisdownSix,
                      -PDGVII::sdownSix,
                      mapAndVectorAndBools,
                      false,
                      "sd6c",
                      "${\\tilde{d}}_{6}^{\\ast}$" ),
        sdownSix( antisdownSix,
                  "sd6",
                  "${\\tilde{d}}_{6}$" ),
        supOne( PDGIX::supOne,
                PDGVII::supOne,
                mapAndVectorAndBools,
                false,
                "su1",
                "${\\tilde{u}}_{1}$" ),
        antisupOne( supOne,
                    "su1c",
                    "${\\tilde{u}}_{1}^{\\ast}$" ),
        supTwo( PDGIX::supTwo,
                PDGVII::supTwo,
                mapAndVectorAndBools,
                false,
                "su2",
                "${\\tilde{u}}_{2}$" ),
        antisupTwo( supTwo,
                    "su2c",
                    "${\\tilde{u}}_{2}^{\\ast}$" ),
        supThree( PDGIX::supThree,
                  PDGVII::supThree,
                  mapAndVectorAndBools,
                  false,
                  "su3",
                  "${\\tilde{u}}_{3}$" ),
        antisupThree( supThree,
                      "su3c",
                      "${\\tilde{u}}_{3}^{\\ast}$" ),
        supFour( PDGIX::supFour,
                 PDGVII::supFour,
                 mapAndVectorAndBools,
                 false,
                 "su4",
                 "${\\tilde{u}}_{4}$" ),
        antisupFour( supFour,
                     "su4c",
                     "${\\tilde{u}}_{4}^{\\ast}$" ),
        supFive( PDGIX::supFive,
                 PDGVII::supFive,
                 mapAndVectorAndBools,
                 false,
                 "su5",
                 "${\\tilde{u}}_{5}$" ),
        antisupFive( supFive,
                     "su5c",
                     "${\\tilde{u}}_{5}^{\\ast}$" ),
        supSix( PDGIX::supSix,
                PDGVII::supSix,
                mapAndVectorAndBools,
                false,
                "su6",
                "${\\tilde{u}}_{6}$" ),
        antisupSix( supSix,
                    "su6c",
                    "${\\tilde{u}}_{6}^{\\ast}$" ),
        downAntisquarkPointers( 6,
                                &antisdownOne ),
        downSquarkPointers( 6,
                            &sdownOne ),
        upSquarkPointers( 6,
                          &supOne ),
        upAntisquarkPointers( 6,
                              &antisupOne ),
        squarkPointers(),
        antisquarkPointers()
    {
      downAntisquarkPointers[ 1 ] = &antisdownTwo;
      downAntisquarkPointers[ 2 ] = &antisdownThree;
      downAntisquarkPointers[ 3 ] = &antisdownFour;
      downAntisquarkPointers[ 4 ] = &antisdownFive;
      downAntisquarkPointers[ 5 ] = &antisdownSix;
      downSquarkPointers[ 1 ] = &sdownTwo;
      downSquarkPointers[ 2 ] = &sdownThree;
      downSquarkPointers[ 3 ] = &sdownFour;
      downSquarkPointers[ 4 ] = &sdownFive;
      downSquarkPointers[ 5 ] = &sdownSix;
      upSquarkPointers[ 1 ] = &supTwo;
      upSquarkPointers[ 2 ] = &supThree;
      upSquarkPointers[ 3 ] = &supFour;
      upSquarkPointers[ 4 ] = &supFive;
      upSquarkPointers[ 5 ] = &supSix;
      upAntisquarkPointers[ 1 ] = &antisupTwo;
      upAntisquarkPointers[ 2 ] = &antisupThree;
      upAntisquarkPointers[ 3 ] = &antisupFour;
      upAntisquarkPointers[ 4 ] = &antisupFive;
      upAntisquarkPointers[ 5 ] = &antisupSix;
      squarkPointers = downSquarkPointers;
      squarkPointers.insert( squarkPointers.end(),
                             upSquarkPointers.begin(),
                             upSquarkPointers.end() );
      antisquarkPointers = downAntisquarkPointers;
      antisquarkPointers.insert( antisquarkPointers.end(),
                                 upAntisquarkPointers.begin(),
                                 upAntisquarkPointers.end() );
    }

    SquarksOneToSix::~SquarksOneToSix()
    {
      // does nothing.
    }

  }

}
