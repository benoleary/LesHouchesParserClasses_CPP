/*
 * SpectrumPlotter.hpp
 *
 *  Created on: Feb 26, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#ifndef SPECTRUMPLOTTER_HPP_
#define SPECTRUMPLOTTER_HPP_

#include <cstdlib>
#include <string>
#include <list>
#include <map>
#include "../BOLlib/Classes/VectorlikeArray.hpp"
#include "../SusyLesHouchesAccordClasses/BlockTypes.hpp"
#include "../SlhaSpectrumPlottingClasses/LineData.hpp"
#include "../SlhaSpectrumPlottingClasses/MassLine.hpp"

namespace LHPC
{
  namespace SLHA
  {
    // this class does the job of reading in data from a SLHA MASS or FMASS
    // block & plotting it according to a LHPCPLOTTING block.
    class SpectrumPlotter
    {
    public:
      typedef BlockClass::SparseSinglyIndexed< std::string > ControlBlock;
      typedef
      BlockClass::SparseSinglyIndexed< SpectrumPlotting::LineData >
      LineBlock;
      typedef std::map< int,
                        SpectrumPlotting::LineData > LineMap;
      typedef std::list< SpectrumPlotting::MassLine > LineList;

      SpectrumPlotter( ControlBlock const& plotControlBlock,
                       LineBlock const& linePlottingBlock,
                       MassBlock const* const massPointer );
      SpectrumPlotter( ControlBlock const& plotControlBlock,
                       LineBlock const& linePlottingBlock,
                       FmassBlock const* const fmassPointer );
      virtual
      ~SpectrumPlotter();

      bool
      plotSpectrum( std::string const& plotFileName );


    protected:
      static int const scaleIndex;
      static int const labelSizeIndex;
      static int const gnuplotIndex;
      static int const latexIndex;
      static int const dvipsIndex;
      static int const ps2epsIndex;
      static int const rmIndex;
      static int const mvIndex;
      static std::string const gnuplotDataFileName;
      static std::string const gnuplotCommandFileName;
      static std::string const gnuplotTexBaseName;
      static std::string const fullLatexBaseName;

      ControlBlock const& plotControlBlock;
      LineBlock const& linePlottingBlock;
      MassBlock const* const massPointer;
      FmassBlock const* const fmassPointer;
      double scaleMaximum;
      double largestMass;
      BOL::VectorlikeArray< LineList > columnSet;
      LineList* columnPointer;
      LineMap::const_iterator plotLineMap;
      LineMap::const_iterator lineIterator;
      int whichMassEigenstate;
      double massValue;
      bool lastOperationSuccessful;
      int systemCallReturn;
      std::string gnuplotCommand;
      std::string latexCommand;
      std::string dvipsCommand;
      std::string ps2epsCommand;
      bool epsiInstead;
      std::string mainCleanupCommand;
      std::string moveCommand;

      void
      loadCommands( std::string const& plotFileName );
      void
      loadLines();
      void
      sortAndFloatLinesAndLabels();
      bool
      writeGnuplotFiles();
    };

  }

}

#endif /* SPECTRUMPLOTTER_HPP_ */
