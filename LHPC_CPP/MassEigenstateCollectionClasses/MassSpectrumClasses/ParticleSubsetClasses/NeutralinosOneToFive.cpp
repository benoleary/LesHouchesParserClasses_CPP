/*
 * NeutralinosOneToFive.cpp
 *
 *  Created on: Jan 27, 2012
 *      Author: oleary
 */

#include "NeutralinosOneToFive.hpp"

namespace LHPC
{
  namespace MassSpectrumClass
  {
    NeutralinosOneToFive::NeutralinosOneToFive( bool const& isVerbose,
                                    std::vector< bool >* const defaultFlags ) :
        MassSpectrum( isVerbose,
                      defaultFlags ),
        NeutralinosOneToFour( isVerbose,
                              defaultFlags ),
        neutralinoFive( PDGIX::neutralinoFive,
                        PDGVII::neutralinoFive,
                        mapAndVectorAndBools,
                        true,
                        "N5",
                        "${\\tilde{{\\tilde{{\\chi}}}}}_{5}^{0}$" )
    {
      neutralinoPointers.push_back( &neutralinoFive );
    }

    NeutralinosOneToFive::~NeutralinosOneToFive()
    {
      // does nothing.
    }

  }

}
