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

  FourMomentum::FourMomentum( double const initialEnergy,
                              double const initialXMomentum,
                              double const initialYMomentum,
                              double const initialZMomentum ) :
      momentumComponents( 4,
                          initialEnergy )
  {
    momentumComponents[ (int)xComponent ] = initialXMomentum;
    momentumComponents[ (int)yComponent ] = initialYMomentum;
    momentumComponents[ (int)zComponent ] = initialZMomentum;
  }

  FourMomentum::FourMomentum( FourMomentum const& copySource ) :
    momentumComponents( copySource.momentumComponents )
  {
    // just an initialization list.
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

  FourMomentum::FourMomentum(
                 std::vector< LHEF::ParticleLine const* > const& copySource ) :
      momentumComponents( 4,
                          0.0 )
  {
    for( int whichElement( copySource.size() - 1 );
         0 <= whichElement;
         --whichElement )
    {
      momentumComponents[ (int)tComponent ]
      += copySource[ whichElement ]->getEnergy();
      momentumComponents[ (int)xComponent ]
      += copySource[ whichElement ]->getXMomentum();
      momentumComponents[ (int)yComponent ]
      += copySource[ whichElement ]->getYMomentum();
      momentumComponents[ (int)zComponent ]
      += copySource[ whichElement ]->getZMomentum();
    }
  }

  FourMomentum::FourMomentum(
                   std::list< LHEF::ParticleLine const* > const& copySource ) :
      momentumComponents( 4,
                          0.0 )
  {
    for( std::list< LHEF::ParticleLine const* >::const_iterator
         whichLine( copySource.begin() );
         copySource.end() != whichLine;
         ++whichLine )
    {
      momentumComponents[ (int)tComponent ] += (*whichLine)->getEnergy();
      momentumComponents[ (int)xComponent ] += (*whichLine)->getXMomentum();
      momentumComponents[ (int)yComponent ] += (*whichLine)->getYMomentum();
      momentumComponents[ (int)zComponent ] += (*whichLine)->getZMomentum();
    }
  }

  FourMomentum::FourMomentum(
                   std::vector< LHCO::ObjectLine const* > const& copySource ) :
      momentumComponents( 4,
                          0.0 )
  {
    FourMomentum copyMomentum;
    for( int whichElement( copySource.size() - 1 );
         0 <= whichElement;
         --whichElement )
    {
      copyMomentum = *(copySource[ whichElement ]);
      momentumComponents[ (int)tComponent ] += copyMomentum.getT();
      momentumComponents[ (int)xComponent ] += copyMomentum.getX();
      momentumComponents[ (int)yComponent ] += copyMomentum.getY();
      momentumComponents[ (int)zComponent ] += copyMomentum.getZ();
    }
  }

  FourMomentum::FourMomentum(
                     std::list< LHCO::ObjectLine const* > const& copySource ) :
      momentumComponents( 4,
                          0.0 )
  {
    FourMomentum copyMomentum;
    for( std::list< LHCO::ObjectLine const* >::const_iterator
         whichLine( copySource.begin() );
         copySource.end() != whichLine;
         ++whichLine )
    {
      copyMomentum = *(*whichLine);
      momentumComponents[ (int)tComponent ] += copyMomentum.getT();
      momentumComponents[ (int)xComponent ] += copyMomentum.getX();
      momentumComponents[ (int)yComponent ] += copyMomentum.getY();
      momentumComponents[ (int)zComponent ] += copyMomentum.getZ();
    }
  }

  FourMomentum::~FourMomentum()
  {
    // does nothing.
  }

} /* namespace LHPC */
