/*
 * InitialOrIntermediateOrFinalState.cpp
 *
 *  Created on: Jan 30, 2012
 *      Author: oleary
 */

#include "InitialOrIntermediateOrFinalState.hpp"

namespace LHPC
{
  namespace LHEF
  {
    namespace FilterRuleClass
    {
      InitialOrIntermediateOrFinalState::InitialOrIntermediateOrFinalState(
                                               stateType const acceptableValue,
                                          bool const acceptRatherThanReject ) :
          FilterRule( acceptRatherThanReject ),
          acceptableValue( (int)acceptableValue )
      {
        // just an initialization list.
      }

      InitialOrIntermediateOrFinalState::InitialOrIntermediateOrFinalState(
                                                     int const acceptableValue,
                                          bool const acceptRatherThanReject ) :
          FilterRule( acceptRatherThanReject ),
          acceptableValue( acceptableValue )
      {
        // just an initialization list.
      }

      InitialOrIntermediateOrFinalState::~InitialOrIntermediateOrFinalState()
      {
        // does nothing.
      }

    }

  }

}
