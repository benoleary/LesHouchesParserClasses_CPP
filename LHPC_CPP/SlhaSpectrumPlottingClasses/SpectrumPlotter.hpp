/*
 * SpectrumPlotter.hpp
 *
 *  Created on: Feb 26, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.LHPC_CPP.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#ifndef SPECTRUMPLOTTER_HPP_
#define SPECTRUMPLOTTER_HPP_

#include <cstdlib>
#include <string>
#include <list>
#include <map>
#include "../BOLlib/Classes/VectorlikeArray.hpp"
#include "../BOLlib/Classes/StringParser.hpp"
#include "../SusyLesHouchesAccordClasses/BlockTypes.hpp"
#include "../SlhaSpectrumPlottingClasses/LineData.hpp"

namespace LHPC
{
  namespace SLHA
  {
    // this class does the job of reading in data from a SLHA MASS or FMASS
    // block & plotting it according to a LHPCPLOTTING block.
    class SpectrumPlotter
    {
    public:
      typedef BlockClass::SparseSinglyIndexed< std::string > StringBlock;
      typedef std::map< int,
                        std::string > LineMap;
      typedef std::list< SpectrumPlotting::LineData > LineList;

      SpectrumPlotter( StringBlock const& plotControlBlock,
                       StringBlock const& linePlottingBlock,
                       MassBlock const* const massPointer );
      SpectrumPlotter( StringBlock const& plotControlBlock,
                       StringBlock const& linePlottingBlock,
                       FmassBlock const* const fmassPointer );
      virtual
      ~SpectrumPlotter();

      bool
      plotSpectrum( std::string const& plotFileName );


    protected:
      static int const unitIndex;
      static int const scaleIndex;
      static int const labelSizeIndex;
      static int const gnuplotIndex;
      static int const latexIndex;
      static int const dvipsIndex;
      static int const ps2epsIndex;
      static int const rmIndex;
      static int const mvIndex;
      static std::string const unitString;
      static std::string const gnuplotDataFileName;
      static std::string const gnuplotCommandFileName;
      static std::string const gnuplotTexBaseName;
      static std::string const fullLatexBaseName;
      static double const automaticScaleFactor;
      static double const labelMinimumPosition;
      static int const maximumLabelFloatingShuffles;

      StringBlock const& plotControlBlock;
      StringBlock const& linePlottingBlock;
      MassBlock const* const massPointer;
      FmassBlock const* const fmassPointer;
      double unitFactor;
      double scaleMaximum;
      double largestMass;
      BOL::VectorlikeArray< LineList > columnSet;
      LineList* columnPointer;
      LineMap* plotLineMap;
      LineMap::const_iterator lineIterator;
      std::list< SpectrumPlotting::LineData >::iterator lowerMassIterator;
      std::list< SpectrumPlotting::LineData >::iterator upperMassIterator;
      int whichMassEigenstate;
      double massValue;
      double labelSeparation;
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
      void
      sortMasses();
      // this sorts all the masses in the columns, & then sets the scale range.
      void
      floatLabels();
      // this tries to move all the labels up or down until they are all
      // separated by ( labelSeparation * scaleMaximum ).
    };

  }

}

#endif /* SPECTRUMPLOTTER_HPP_ */
