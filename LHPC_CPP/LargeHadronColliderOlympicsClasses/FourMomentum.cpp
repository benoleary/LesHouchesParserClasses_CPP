/*
 * FourMomentum.cpp
 *
 *  Created on: Jul 26, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#include "FourMomentum.hpp"

namespace LHPC
{
  FourMomentum::FourMomentum() :
      momentumComponents( 4,
                          BOL::UsefulStuff::notANumber )
  {
    // just an initialization list.
  }

  FourMomentum::FourMomentum( FourMomentum const& copySource ) :
    momentumComponents( 4,
                        BOL::UsefulStuff::notANumber )
{
  assignFrom( copySource );
}

  FourMomentum::FourMomentum( LHEF::ParticleLine const& copySource ) :
      momentumComponents( 4,
                          BOL::UsefulStuff::notANumber )
  {
    assignFrom( copySource );
  }

  FourMomentum::FourMomentum( LHCO::ObjectLine const& copySource ) :
      momentumComponents( 4,
                          BOL::UsefulStuff::notANumber )
  {
    assignFrom( copySource );
  }

  FourMomentum::~FourMomentum()
  {
    // does nothing.
  }

} /* namespace LHPC */
