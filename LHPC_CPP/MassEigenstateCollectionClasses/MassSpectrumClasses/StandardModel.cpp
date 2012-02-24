/*
 * StandardModel.cpp
 *
 *  Created on: Jan 8, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.LHPC_CPP.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#include "StandardModel.hpp"

namespace LHPC
{
  namespace MassSpectrumClass
  {
    StandardModel::StandardModel( bool const& isVerbose,
                                  bool const neutrinosAreMajorana,
                                  std::vector< bool >* const defaultFlags ) :
        MassSpectrum( isVerbose,
                      defaultFlags ),
        neutralColorlessScalarOne( PDGIX::neutralColorlessScalarOne,
                                   PDGVII::neutralColorlessScalarOne,
                                   mapAndVectorAndBools,
                                   true,
                                   "h01",
                                   "$h_{1}^{0}$" ),
        positronOne( PDGIX::positronOne,
                     -PDGVII::electronOne,
                     mapAndVectorAndBools,
                     false,
                     "e1bar",
                     "${\\bar{e}}_{1}$" ),
        antipositronOne( positronOne,
                         "e1",
                         "$e_{1}$" ),
        positronTwo( PDGIX::positronTwo,
                     -PDGVII::electronTwo,
                     mapAndVectorAndBools,
                     false,
                     "e2bar",
                     "${\\bar{e}}_{2}$" ),
        antipositronTwo( positronTwo,
                         "e2",
                         "$e_{2}$" ),
        positronThree( PDGIX::positronThree,
                       -PDGVII::electronThree,
                       mapAndVectorAndBools,
                       false,
                       "e3bar",
                       "${\\bar{e}}_{3}$" ),
        antipositronThree( positronThree,
                           "e3",
                           "$e_{3}$" ),
        antineutrinoOne( PDGIX::antineutrinoOne,
                         -PDGVII::neutrinoOne,
                         mapAndVectorAndBools,
                         false,
                         "v1bar",
                         "${\\bar{{\\nu}}}_{1}$" ),
        neutrinoOne( antineutrinoOne,
                     "v1",
                     "${\\nu}_{1}$" ),
        antineutrinoTwo( PDGIX::antineutrinoTwo,
                         -PDGVII::neutrinoTwo,
                         mapAndVectorAndBools,
                         false,
                         "v2bar",
                         "${\\bar{{\\nu}}}_{2}$" ),
        neutrinoTwo( antineutrinoTwo,
                     "v2",
                     "${\\nu}_{2}$" ),
        antineutrinoThree( PDGIX::antineutrinoThree,
                           -PDGVII::neutrinoThree,
                           mapAndVectorAndBools,
                           false,
                           "v3bar",
                           "${\\bar{{\\nu}}}_{3}$" ),
        neutrinoThree( antineutrinoThree,
                       "v3",
                       "${\\nu}_{3}$" ),
        antidownOne( PDGIX::antidownOne,
                     -PDGVII::downOne,
                     mapAndVectorAndBools,
                     false,
                     "d1bar",
                     "${\\bar{d}}_{1}$" ),
        downOne( antidownOne,
                 "d1",
                 "$d_{1}$" ),
        antidownTwo( PDGIX::antidownTwo,
                     -PDGVII::downTwo,
                     mapAndVectorAndBools,
                     false,
                     "d2bar",
                     "${\\bar{d}}_{2}$" ),
        downTwo( antidownTwo,
                 "d2",
                 "$d_{2}$" ),
        antidownThree( PDGIX::antidownThree,
                       -PDGVII::downThree,
                       mapAndVectorAndBools,
                       false,
                       "d3bar",
                       "${\\bar{d}}_{3}$" ),
        downThree( antidownThree,
                   "d3",
                   "$d_{3}$" ),
        upOne( PDGIX::upOne,
               PDGVII::upOne,
               mapAndVectorAndBools,
               false,
               "u1",
               "$u_{1}$" ),
        antiupOne( upOne,
                   "u1bar",
                   "${\\bar{u}}_{1}$" ),
        upTwo( PDGIX::upTwo,
               PDGVII::upTwo,
               mapAndVectorAndBools,
               false,
               "u2",
               "$u_{2}$" ),
        antiupTwo( upTwo,
                   "u2bar",
                   "${\\bar{u}}_{2}$" ),
        upThree( PDGIX::upThree,
                 PDGVII::upThree,
                 mapAndVectorAndBools,
                 false,
                 "u3",
                 "$u_{3}$" ),
        antiupThree( upThree,
                     "u3bar",
                     "${\\bar{u}}_{3}$" ),
        photonBoson( PDGIX::photonBoson,
                     PDGVII::photonBoson,
                     mapAndVectorAndBools,
                     true,
                     "A",
                     "${\\gamma}$" ),
        zBosonOne( PDGIX::zBosonOne,
                   PDGVII::zBosonOne,
                   mapAndVectorAndBools,
                   true,
                   "Z",
                   "$Z$" ),
        wPlusBosonOne( PDGIX::wPlusBosonOne,
                       PDGVII::wPlusBosonOne,
                       mapAndVectorAndBools,
                       false,
                       "Wp",
                       "$W^{+}$" ),
        wMinusBosonOne( wPlusBosonOne,
                        "Wm",
                        "$W^{-}$" ),
        gluonBoson( PDGIX::gluonBoson,
                    PDGVII::gluonBoson,
                    mapAndVectorAndBools,
                    true,
                    "g",
                    "$g$" ),
        positiveLeptonPointers( 3,
                                &positronOne ),
        negativeLeptonPointers( 3,
                                &antipositronOne ),
        antineutrinoPointers( 3,
                              &antineutrinoOne ),
        neutrinoPointers( 3,
                          &neutrinoOne ),
        downAntiquarkPointers( 3,
                               &antidownOne ),
        downQuarkPointers( 3,
                           &downOne ),
        upQuarkPointers( 3,
                         &upOne ),
        upAntiquarkPointers( 3,
                             &antiupOne )
    {
      positiveLeptonPointers[ 1 ] = &positronTwo;
      positiveLeptonPointers[ 2 ] = &positronThree;
      negativeLeptonPointers[ 1 ] = &antipositronTwo;
      negativeLeptonPointers[ 2 ] = &antipositronThree;
      antineutrinoPointers[ 1 ] = &antineutrinoTwo;
      antineutrinoPointers[ 2 ] = &antineutrinoThree;
      neutrinoPointers[ 1 ] = &neutrinoTwo;
      neutrinoPointers[ 2 ] = &neutrinoThree;
      downAntiquarkPointers[ 1 ] = &antidownTwo;
      downAntiquarkPointers[ 2 ] = &antidownThree;
      downQuarkPointers[ 1 ] = &downTwo;
      downQuarkPointers[ 2 ] = &downThree;
      upQuarkPointers[ 1 ] = &upTwo;
      upQuarkPointers[ 2 ] = &upThree;
      upAntiquarkPointers[ 1 ] = &antiupTwo;
      upAntiquarkPointers[ 2 ] = &antiupThree;
      if( neutrinosAreMajorana )
      {
        setNeutrinosToMajorana();
      }
      if( &defaultBoolVector == mapAndVectorAndBools.getFlags() )
      {
        positronOne.setFlags( &defaultIsLightLeptonBoolVector );
        antipositronOne.setFlags( &defaultIsLightLeptonBoolVector );
        positronTwo.setFlags( &defaultIsLightLeptonBoolVector );
        antipositronTwo.setFlags( &defaultIsLightLeptonBoolVector );
        for( int whichParticle( 2 );
             0 <= whichParticle;
             --whichParticle )
          // the number of generations is hard-coded in for the Standard Model.
        {
          antineutrinoPointers[ whichParticle ]->setFlags(
                                           &defaultEscapesDetectorBoolVector );
          neutrinoPointers[ whichParticle ]->setFlags(
                                           &defaultEscapesDetectorBoolVector );
          downAntiquarkPointers[ whichParticle ]->setFlags(
                                                     &defaultIsJetBoolVector );
          downQuarkPointers[ whichParticle ]->setFlags(
                                                     &defaultIsJetBoolVector );
          upQuarkPointers[ whichParticle ]->setFlags(
                                                     &defaultIsJetBoolVector );
          upAntiquarkPointers[ whichParticle ]->setFlags(
                                                     &defaultIsJetBoolVector );
        }
        gluonBoson.setFlags( &defaultIsJetBoolVector );
      }
    }

    StandardModel::~StandardModel()
    {
      // does nothing.
    }

  }

}
