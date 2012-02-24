/*
 * InitialOrIntermediateOrFinalState.hpp
 *
 *  Created on: Jan 30, 2012
 *      Author: oleary
 */

#ifndef INITIALORINTERMEDIATEORFINALSTATE_HPP_
#define INITIALORINTERMEDIATEORFINALSTATE_HPP_

#include "../FilterRule.hpp"

namespace LHPC
{
  namespace LHEF
  {
    namespace FilterRuleClass
    {
      // this class returns acceptRatherThanReject if it finds that
      // getInitialOrIntermediateOrFinalState() matches acceptableValue.
      class InitialOrIntermediateOrFinalState : public FilterRule
      {
      public:
        enum stateType
        {
          initialState = -1,
          intermediateState = 2,
          finalState = 1
        };

        InitialOrIntermediateOrFinalState( stateType const acceptableValue,
                                    bool const acceptRatherThanReject = true );
        InitialOrIntermediateOrFinalState( int const acceptableValue,
                                    bool const acceptRatherThanReject = true );
        virtual
        ~InitialOrIntermediateOrFinalState();

        virtual bool
        operator()( ParticleLine const& lineToCheck ) const;


      protected:
        int acceptableValue;
      };



      inline bool
      InitialOrIntermediateOrFinalState::operator()(
                                        ParticleLine const& lineToCheck ) const
      {
        if( acceptableValue
            == lineToCheck.getInitialOrIntermediateOrFinalState() )
        {
          return acceptRatherThanReject;
        }
        else
        {
          return !acceptRatherThanReject;
        }
      }

    }
    typedef FilterRuleClass::InitialOrIntermediateOrFinalState FilterOnState;

  }

}

#endif /* INITIALORINTERMEDIATEORFINALSTATE_HPP_ */
