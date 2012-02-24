/*
 * NmssmExtraEwsbSpinZeroBosonSet.cpp
 *
 *  Created on: Jan 27, 2012
 *      Author: oleary
 */

#include "NmssmExtraEwsbSpinZeroBosonSet.hpp"

namespace LHPC
{
  namespace MassSpectrumClass
  {
    NmssmExtraEwsbSpinZeroBosonSet::NmssmExtraEwsbSpinZeroBosonSet(
                                                         bool const& isVerbose,
                                    std::vector< bool >* const defaultFlags ) :
        MassSpectrum( isVerbose,
                      defaultFlags ),
        MssmExtraEwsbSpinZeroBosonSet( isVerbose,
                                       defaultFlags ),
        neutralColorlessScalarThree( PDGIX::neutralColorlessScalarThree,
                                     PDGVII::nmssmHiggsScalarThree,
                                     mapAndVectorAndBools,
                                     true,
                                     "h03",
                                     "$h_{3}^{0}$" ),
        neutralColorlessPseudoscalarTwo(
                                        PDGIX::neutralColorlessPseudoscalarTwo,
                                         PDGVII::nmssmHiggsPseudoscalarTwo,
                                         mapAndVectorAndBools,
                                         true,
                                         "A02",
                                         "$A_{2}^{0}$" )
    {
      neutralScalarsAndPseudoscalarPointers.push_back(
                                                &neutralColorlessScalarThree );
      neutralScalarsAndPseudoscalarPointers.push_back(
                                            &neutralColorlessPseudoscalarTwo );
      ewsbSpinZeroAndOneBosonPointers.push_back(
                                                &neutralColorlessScalarThree );
      ewsbSpinZeroAndOneBosonPointers.push_back(
                                            &neutralColorlessPseudoscalarTwo );
    }

    NmssmExtraEwsbSpinZeroBosonSet::~NmssmExtraEwsbSpinZeroBosonSet()
    {
      // does nothing.
    }

  }

}
