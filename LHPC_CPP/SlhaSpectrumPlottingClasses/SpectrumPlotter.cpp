/*
 * SpectrumPlotter.cpp
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

#include "SpectrumPlotter.hpp"

namespace LHPC
{
  namespace SLHA
  {
    int const SpectrumPlotter::scaleIndex( 1 );
    int const SpectrumPlotter::labelSizeIndex( 2 );
    int const SpectrumPlotter::gnuplotIndex( 3 );
    int const SpectrumPlotter::latexIndex( 4 );
    int const SpectrumPlotter::dvipsIndex( 5 );
    int const SpectrumPlotter::ps2epsIndex( 6 );
    int const SpectrumPlotter::rmIndex( 7 );
    int const SpectrumPlotter::mvIndex( 8 );
    std::string const SpectrumPlotter::gnuplotDataFileName(
                                          "LHPC_SpectrumPlotter_gnuplot.dat" );
    std::string const SpectrumPlotter::gnuplotCommandFileName(
                                        "LHPC_SpectrumPlotter_gnuplot.input" );
    std::string const
    SpectrumPlotter::gnuplotTexBaseName( "LHPC_SpectrumPlotter_gnuplot_TeX" );
    std::string const
    SpectrumPlotter::fullLatexBaseName( "LHPC_SpectrumPlotter_LaTeX" );
    double const automaticScaleFactor( 1.1 );


    SpectrumPlotter::SpectrumPlotter( StringBlock const& plotControlBlock,
                                      StringBlock const& linePlottingBlock,
                                      MassBlock const* const massPointer ) :
        plotControlBlock( plotControlBlock ),
        linePlottingBlock( linePlottingBlock ),
        massPointer( massPointer ),
        fmassPointer( NULL ),
        scaleMaximum( -1.0 ),
        columnSet(),
        lastOperationSuccessful( false ),
        systemCallReturn( -1 ),
        gnuplotCommand( "" ),
        latexCommand( "" ),
        dvipsCommand( "" ),
        ps2epsCommand( "" ),
        epsiInstead( false ),
        mainCleanupCommand( "" ),
        moveCommand( "" )
    {
      // just an initialization list.
    }

    SpectrumPlotter::SpectrumPlotter( StringBlock const& plotControlBlock,
                                      StringBlock const& linePlottingBlock,
                                      FmassBlock const* const fmassPointer ) :
        plotControlBlock( plotControlBlock ),
        linePlottingBlock( linePlottingBlock ),
        massPointer( NULL ),
        fmassPointer( fmassPointer ),
        scaleMaximum( -1.0 ),
        columnSet(),
        lastOperationSuccessful( false ),
        systemCallReturn( -1 ),
        gnuplotCommand( "" ),
        latexCommand( "" ),
        dvipsCommand( "" ),
        ps2epsCommand( "" ),
        epsiInstead( false ),
        mainCleanupCommand( "" ),
        moveCommand( "" )
    {
      // just an initialization list.
    }

    SpectrumPlotter::~SpectrumPlotter()
    {
      // does nothing.
    }


    bool
    SpectrumPlotter::plotSpectrum( std::string const& plotFileName,
                                   bool const shouldCleanUp )
    {
      loadCommands( plotFileName );
      loadLines();
      sortAndFloatLinesAndLabels();
      lastOperationSuccessful = writeGnuplotFiles();
      if( lastOperationSuccessful )
      {
        systemCallReturn = system( gnuplotCommand.c_str() );
        // "gnuplot LHPC_SpectrumPlotter_gnuplot.input"
      }
      if( -1 != systemCallReturn )
      {
        systemCallReturn = system( latexCommand.c_str() );
        // "latex LHPC_SpectrumPlotter_LaTeX.tex"
      }
      if( -1 != systemCallReturn )
      {
        systemCallReturn = system( dvipsCommand.c_str() );
        // "dvips LHPC_SpectrumPlotter_LaTeX.dvi"
      }
      if( -1 != systemCallReturn )
      {
        systemCallReturn = system( ps2epsCommand.c_str() );
        // "ps2eps LHPC_SpectrumPlotter_LaTeX.ps"
      }
      if( ( -1 != systemCallReturn )
          &&
          shouldCleanUp )
      {
        systemCallReturn = system( mainCleanupCommand.c_str() );
        /* "rm LHPC_SpectrumPlotter_gnuplot.dat \
         * LHPC_SpectrumPlotter_gnuplot.input \
         * LHPC_SpectrumPlotter_gnuplot_TeX.eps \
         * LHPC_SpectrumPlotter_gnuplot_TeX.tex \
         * LHPC_SpectrumPlotter_LaTeX.aux \
         * LHPC_SpectrumPlotter_LaTeX.dvi \
         * LHPC_SpectrumPlotter_LaTeX.log \
         * LHPC_SpectrumPlotter_LaTeX.ps \
         * LHPC_SpectrumPlotter_LaTeX.tex"
         */
      }
      if( -1 != systemCallReturn )
      {
        systemCallReturn = system( moveCommand.c_str() );
        // "mv LHPC_SpectrumPlotter_LaTeX.eps plotFileName"
      }
      if( -1 != systemCallReturn )
      {
        return true;
      }
      else
      {
        return false;
      }
    }

    void
    SpectrumPlotter::loadCommands( std::string const& plotFileName )
    {
      if( plotControlBlock.hasEntry( scaleIndex ) )
      {
        scaleMaximum
        = BOL::StringParser::stringToDouble( plotControlBlock[ scaleIndex ] );
      }
      else
      {
        scaleMaximum = -1.0;
      }
      if( plotControlBlock.hasEntry( labelSizeIndex ) )
      {
        labelSeparation = BOL::StringParser::stringToDouble( plotControlBlock[
                                                            labelSizeIndex ] );
      }
      else
      {
        labelSeparation = 5.0;
      }
      if( plotControlBlock.hasEntry( gnuplotIndex ) )
      {
        gnuplotCommand.assign( plotControlBlock[ gnuplotIndex ] );
      }
      else
      {
        gnuplotCommand.assign( "" );
      }
      gnuplotCommand.assign( plotControlBlock[ gnuplotIndex ] );
      gnuplotCommand.append( " " );
      gnuplotCommand.append( gnuplotCommandFileName );
      // "gnuplot LHPC_SpectrumPlotter_gnuplot.input"
      latexCommand.assign( plotControlBlock[ latexIndex ] );
      latexCommand.append( " " );
      latexCommand.append( fullLatexBaseName );
      latexCommand.append( ".tex" );
      // "latex LHPC_SpectrumPlotter_LaTeX.tex"
      dvipsCommand.assign( plotControlBlock[ dvipsIndex ] );
      dvipsCommand.append( " " );
      dvipsCommand.append( fullLatexBaseName );
      dvipsCommand.append( ".dvi" );
      // "dvips LHPC_SpectrumPlotter_LaTeX.dvi"
      ps2epsCommand.assign( plotControlBlock[ ps2epsIndex ] );
      if( 0 == ps2epsCommand.compare( ( ps2epsCommand.size() - 7 ),
                                      7,
                                      "ps2epsi" ) )
      {
        epsiInstead = true;
      }
      ps2epsCommand.append( " " );
      ps2epsCommand.append( fullLatexBaseName );
      ps2epsCommand.append( ".ps" );
      // "ps2eps LHPC_SpectrumPlotter_LaTeX.ps"
      mainCleanupCommand.assign( plotControlBlock[ rmIndex ] );
      mainCleanupCommand.append( " " );
      mainCleanupCommand.append( gnuplotDataFileName );
      mainCleanupCommand.append( " " );
      mainCleanupCommand.append( gnuplotCommandFileName );
      mainCleanupCommand.append( " " );
      mainCleanupCommand.append( gnuplotTexBaseName );
      mainCleanupCommand.append( ".eps " );
      mainCleanupCommand.append( gnuplotTexBaseName );
      mainCleanupCommand.append( ".tex " );
      mainCleanupCommand.append( fullLatexBaseName );
      mainCleanupCommand.append( ".aux " );
      mainCleanupCommand.append( fullLatexBaseName );
      mainCleanupCommand.append( ".dvi " );
      mainCleanupCommand.append( fullLatexBaseName );
      mainCleanupCommand.append( ".log " );
      mainCleanupCommand.append( fullLatexBaseName );
      mainCleanupCommand.append( ".ps " );
      mainCleanupCommand.append( fullLatexBaseName );
      mainCleanupCommand.append( ".tex" );
      /* "rm LHPC_SpectrumPlotter_gnuplot.dat \
       * LHPC_SpectrumPlotter_gnuplot.input \
       * LHPC_SpectrumPlotter_gnuplot_TeX.eps \
       * LHPC_SpectrumPlotter_gnuplot_TeX.tex \
       * LHPC_SpectrumPlotter_LaTeX.aux \
       * LHPC_SpectrumPlotter_LaTeX.dvi \
       * LHPC_SpectrumPlotter_LaTeX.log \
       * LHPC_SpectrumPlotter_LaTeX.ps \
       * LHPC_SpectrumPlotter_LaTeX.tex"
       */
      moveCommand.assign( plotControlBlock[ mvIndex ] );
      moveCommand.append( fullLatexBaseName );
      moveCommand.append( ".eps" );
      if( epsiInstead )
      {
        moveCommand.append( "i" );
      }
      moveCommand.append( " " );
      moveCommand.append( plotFileName );
      // "mv LHPC_SpectrumPlotter_LaTeX.eps plotFileName"
    }

    void
    SpectrumPlotter::loadLines()
    {
      plotLineMap = linePlottingBlock.getMap();
      lineIterator = plotLineMap->begin();
      while( plotLineMap->end() != lineIterator )
        // for each mass eigenstate specified to be plotted...
      {
        whichMassEigenstate = lineIterator->second.getCode();
        lastOperationSuccessful = false;
        // whether there is a mass for the line needs to be checked:
        if( ( NULL != massPointer )
            &&
            ( massPointer->hasEntry( whichMassEigenstate ) ) )
        {
          massValue = massPointer[ whichMassEigenstate ];
          lastOperationSuccessful = true;
        }
        else if( ( NULL != fmassPointer )
                 &&
                 ( fmassPointer->hasEntry( whichMassEigenstate ) ) )
        {
          massValue = fmassPointer[ whichMassEigenstate ].getMass();
          lastOperationSuccessful = true;
        }
        if( lastOperationSuccessful )
          // if there was a mass recorded for this mass eigenstate...
        {
          if( lineIterator->second.getColumn() >= columnSet.getSize() )
          {
            columnSet.setSize( lineIterator->second.getColumn() + 1 );
          }
          // now columnSet is large enough for the line to be put into its
          // appropriate column:
          columnSet[ lineIterator->second.getColumn() ].push_back(
                                            new MassLine( lineIterator->second,
                                                          massValue ) );
        }
        ++lineIterator;
      }
    }

    void
    SpectrumPlotter::sortAndFloatLinesAndLabels()
    {
      sortMasses();


      largestMass = 0.0;
      for( int whichColumn( columnSet.getLastIndex() );
           0 < whichColumn;
           --whichColumn )
      {
        columnPointer = columnSet.getPointer( whichColumn );
        if( !(columnPointer->empty()) )
        {
          columnPointer->sort( &(SpectrumPlotting::MassLine::lowToHigh) );
          largestMass = columnPointer->back().getMass();
        }
      }
    }

    bool
    SpectrumPlotter::writeGnuplotFiles();
    void
    SpectrumPlotter::sortMasses()
    // this sorts all the masses in the columns, & then sets the scale range.
    {
      largestMass = 0.0;
      for( int whichColumn( columnSet.getLastIndex() );
           0 < whichColumn;
           --whichColumn )
      {
        columnPointer = columnSet.getPointer( whichColumn );
        if( !(columnPointer->empty()) )
        {
          columnPointer->sort( &(SpectrumPlotting::MassLine::lowToHigh) );
          largestMass = columnPointer->back().getMass();
        }
      }
      if( 0.0 >= scaleMaximum )
        // if the scale is to be automatically decided by the largest mass...
      {
        scaleMaximum = ( largestMass * automaticScaleFactor );
      }
    }


  }

}
