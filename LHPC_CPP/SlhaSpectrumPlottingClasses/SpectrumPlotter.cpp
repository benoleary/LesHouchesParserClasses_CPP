/*
 * SpectrumPlotter.cpp
 *
 *  Created on: Feb 26, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#include "SpectrumPlotter.hpp"

namespace LHPC
{
  namespace SLHA
  {
    SpectrumPlotter::SpectrumPlotter( MassBlock const* const massPointer ) :
        massPointer( massPointer ),
        fmassPointer( NULL )
    {
      // TODO Auto-generated constructor stub
    }

    SpectrumPlotter::SpectrumPlotter( FmassBlock const* const fmassPointer ) :
        massPointer( NULL ),
        fmassPointer( fmassPointer )
    {
      // TODO Auto-generated constructor stub

    }

    SpectrumPlotter::~SpectrumPlotter()
    {
      // TODO Auto-generated destructor stub
    }

  }

}
