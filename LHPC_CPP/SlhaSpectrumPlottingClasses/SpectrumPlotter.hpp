/*
 * SpectrumPlotter.hpp
 *
 *  Created on: Feb 26, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#ifndef SPECTRUMPLOTTER_HPP_
#define SPECTRUMPLOTTER_HPP_

#include "../SusyLesHouchesAccordClasses/BlockTypes.hpp"

namespace LHPC
{
  namespace SLHA
  {
    // this class does the job of reading in data from a SLHA MASS or FMASS
    // block & plotting it according to a LHPCPLOTTING block.
    class SpectrumPlotter
    {
    public:
      SpectrumPlotter( MassBlock const* const massPointer );
      SpectrumPlotter( FmassBlock const* const fmassPointer );
      virtual
      ~SpectrumPlotter();


    protected:
      MassBlock const* const massPointer;
      FmassBlock const* const fmassPointer;
    };

  }

}

#endif /* SPECTRUMPLOTTER_HPP_ */
