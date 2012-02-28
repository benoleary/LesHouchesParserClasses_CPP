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
    int const SpectrumPlotter::unitIndex( 1 );
    int const SpectrumPlotter::scaleIndex( 2 );
    int const SpectrumPlotter::labelSizeIndex( 3 );
    int const SpectrumPlotter::gnuplotIndex( 4 );
    int const SpectrumPlotter::latexIndex( 5 );
    int const SpectrumPlotter::dvipsIndex( 6 );
    int const SpectrumPlotter::ps2epsIndex( 7 );
    int const SpectrumPlotter::rmIndex( 8 );
    int const SpectrumPlotter::mvIndex( 9 );
    std::string SpectrumPlotter::unitString( "GeV" );
    std::string const SpectrumPlotter::gnuplotDataFileName(
                                          "LHPC_SpectrumPlotter_gnuplot.dat" );
    std::string const SpectrumPlotter::gnuplotCommandFileName(
                                        "LHPC_SpectrumPlotter_gnuplot.input" );
    std::string const
    SpectrumPlotter::gnuplotTexBaseName( "LHPC_SpectrumPlotter_gnuplot_TeX" );
    std::string const
    SpectrumPlotter::fullLatexBaseName( "LHPC_SpectrumPlotter_LaTeX" );
    double const SpectrumPlotter::automaticScaleFactor( 1.1 );
    double const SpectrumPlotter::labelMinimumPosition( 0.05 );
    double const SpectrumPlotter::labelSeparationShuffleFactor( 0.51 );
    double const SpectrumPlotter::labelWidth( 30.0 );
    double const SpectrumPlotter::joinerWidth( 20.0 );
    double const SpectrumPlotter::flatBitWidth( 100.0 );
    double const SpectrumPlotter::columnPairOffset( 10.0 );
    double const
    SpectrumPlotter::fullColumnWidth( labelWidth + joinerWidth
                                      + flatBitWidth + columnPairOffset
                                      + joinerWidth + labelWidth );
    int const SpectrumPlotter::maximumLabelFloatingShuffles( 100 );


    SpectrumPlotter::SpectrumPlotter( StringBlock const& plotControlBlock,
                                      StringBlock const& linePlottingBlock,
                                      MassBlock const* const massPointer ) :
        plotControlBlock( plotControlBlock ),
        linePlottingBlock( linePlottingBlock ),
        massPointer( massPointer ),
        fmassPointer( NULL ),
        unitFactor( 1.0 ),
        scaleMaximum( -1.0 ),
        largestMass( 0.0 ),
        columnSet(),
        columnPointer( NULL ),
        plotLineMap( NULL ),
        lineIterator(),
        linePointer( NULL ),
        lowerMassIterator(),
        upperMassIterator(),
        notYetFinishedShuffling( false ),
        remainingShuffles( maximumLabelFloatingShuffles ),
        whichMassEigenstate( 0 ),
        massValue( 0.0 ),
        labelSeparation( labelMinimumPosition ),
        labelAverage( 0.0 ),
        lastOperationSuccessful( false ),
        systemCallReturn( -1 ),
        gnuplotCommand( "" ),
        latexCommand( "" ),
        dvipsCommand( "" ),
        ps2epsCommand( "" ),
        epsiInstead( false ),
        mainCleanupCommand( "" ),
        moveCommand( "" ),
        leftColumnRatherThanRight( false ),
        leftLineXValue( 0.0 ),
        middleLineXValue( 0.0 ),
        rightLineXValue( 0.0 ),
        gnuplotLineIndex( 0 )
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
        unitFactor( 1.0 ),
        scaleMaximum( -1.0 ),
        largestMass( 0.0 ),
        columnSet(),
        columnPointer( NULL ),
        plotLineMap( NULL ),
        lineIterator(),
        linePointer( NULL ),
        lowerMassIterator(),
        upperMassIterator(),
        notYetFinishedShuffling( false ),
        remainingShuffles( maximumLabelFloatingShuffles ),
        whichMassEigenstate( 0 ),
        massValue( 0.0 ),
        labelSeparation( labelMinimumPosition ),
        labelAverage( 0.0 ),
        lastOperationSuccessful( false ),
        systemCallReturn( -1 ),
        gnuplotCommand( "" ),
        latexCommand( "" ),
        dvipsCommand( "" ),
        ps2epsCommand( "" ),
        epsiInstead( false ),
        mainCleanupCommand( "" ),
        moveCommand( "" ),
        leftColumnRatherThanRight( false ),
        leftLineXValue( 0.0 ),
        middleLineXValue( 0.0 ),
        rightLineXValue( 0.0 ),
        gnuplotLineIndex( 0 )
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
      if( plotControlBlock.hasEntry( unitIndex ) )
      {
        unitString.assign( plotControlBlock[ unitIndex ] );
        BOL::StringParser::transformToUppercase( unitString );
        if( unitString.compare( "GEV" ) )
        {
          unitFactor = 1.0;
        }
        else if( unitString.compare( "TEV" ) )
        {
          unitFactor = 1000.0;
        }
        else if( unitString.compare( "MEV" ) )
        {
          unitFactor = 0.001;
        }
        else if( unitString.compare( "KEV" ) )
        {
          unitFactor = 0.000001;
        }
        else if( unitString.compare( "EV" ) )
        {
          unitFactor = 0.000000001;
        }
        else
        {
          unitFactor = 1.0;
          std::cout
          << std::endl
          << "LHPC::warning! SpectrumPlotter did not understand \""
          << plotControlBlock[ unitIndex ] << "\" as a unit (acceptable units"
          << " are \"GeV\", \"TeV\", \"MeV\", \"keV\", and \"eV\"), and is"
          << " defaulting to GeV.";
          std::cout << std::endl;
        }
      }
      else
      {
        unitFactor = 1.0;
      }
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
        labelSeparation
        = ( 0.01 * BOL::StringParser::stringToDouble( plotControlBlock[
                                                          labelSizeIndex ] ) );
        // the label separation is given as a percentage in the control block.
      }
      else
      {
        labelSeparation = 0.05;
      }
      if( plotControlBlock.hasEntry( gnuplotIndex ) )
      {
        gnuplotCommand.assign( plotControlBlock[ gnuplotIndex ] );
      }
      else
      {
        gnuplotCommand.assign( "/usr/bin/gnuplot" );
      }
      gnuplotCommand.append( " " );
      gnuplotCommand.append( gnuplotCommandFileName );
      // "gnuplot LHPC_SpectrumPlotter_gnuplot.input"
      if( plotControlBlock.hasEntry( latexIndex ) )
      {
        latexCommand.assign( plotControlBlock[ latexIndex ] );
      }
      else
      {
        latexCommand.assign( "/usr/bin/latex" );
      }
      latexCommand.append( " " );
      latexCommand.append( fullLatexBaseName );
      latexCommand.append( ".tex" );
      // "latex LHPC_SpectrumPlotter_LaTeX.tex"
      if( plotControlBlock.hasEntry( dvipsIndex ) )
      {
        dvipsCommand.assign( plotControlBlock[ dvipsIndex ] );
      }
      else
      {
        dvipsCommand.assign( "/usr/bin/dvips" );
      }
      dvipsCommand.append( " " );
      dvipsCommand.append( fullLatexBaseName );
      dvipsCommand.append( ".dvi" );
      // "dvips LHPC_SpectrumPlotter_LaTeX.dvi"
      if( plotControlBlock.hasEntry( ps2epsIndex ) )
      {
        ps2epsCommand.assign( plotControlBlock[ ps2epsIndex ] );
      }
      else
      {
        ps2epsCommand.assign( "/usr/bin/ps2eps" );
      }
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
      if( plotControlBlock.hasEntry( rmIndex ) )
      {
        mainCleanupCommand.assign( plotControlBlock[ rmIndex ] );
      }
      else
      {
        mainCleanupCommand.assign( "/bin/rm" );
      }
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
      if( plotControlBlock.hasEntry( mvIndex ) )
      {
        moveCommand.assign( plotControlBlock[ mvIndex ] );
      }
      else
      {
        mainCleanupCommand.assign( "/bin/mv" );
      }
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
        whichMassEigenstate = lineIterator->first;
        lastOperationSuccessful = false;
        // whether there is a mass for the line needs to be checked:
        if( ( NULL != massPointer )
            &&
            ( massPointer->hasEntry( whichMassEigenstate ) ) )
        {
          massValue = ( unitFactor * (*massPointer)[ whichMassEigenstate ] );
          lastOperationSuccessful = true;
        }
        else if( ( NULL != fmassPointer )
                 &&
                 ( fmassPointer->hasEntry( whichMassEigenstate ) ) )
        {
          massValue = ( unitFactor
                        * (*fmassPointer)[ whichMassEigenstate ].getMass() );
          lastOperationSuccessful = true;
        }
        if( lastOperationSuccessful )
          // if there was a mass recorded for this mass eigenstate...
        {
          linePointer = new SpectrumPlotting::LineData( lineIterator->second,
                                                        massValue );
          if( linePointer->getColumn() >= columnSet.getSize() )
          {
            columnSet.setSize( linePointer->getColumn() + 1 );
          }
          // now columnSet is large enough for the line to be put into its
          // appropriate column:
          columnSet[ linePointer->getColumn() ].push_back( *linePointer );
        }
        ++lineIterator;
      }
    }

    void
    SpectrumPlotter::sortAndFloatLinesAndLabels()
    {
      sortMasses();
      floatLabels();
    }

    bool
    SpectrumPlotter::writeGnuplotFiles()
    {
      std::ofstream gnuplotDataFile( gnuplotDataFileName.c_str() );
      std::ofstream gnuplotCommandFile( gnuplotCommandFileName.c_str() );
      if( gnuplotDataFile.is_open()
          &&
          gnuplotCommandFile.is_open() )
      {
        bool returnBool( true );
        gnuplotCommandFile
        << "set term epslatex color solid"
        << std::endl << "set output \"" << gnuplotTexBaseName << ".eps\""
        << std::endl << "set format x \"\""
        << std::endl;

        gnuplotLineIndex = 0;
        for( int whichColumn( columnSet.getLastIndex() );
             0 < whichColumn;
             --whichColumn )
        {
          if( 1 == ( whichColumn % 2 ) )
            // if the column gets its labels to its left...
          {
            leftColumnRatherThanRight = true;
          }
          else
          {
            leftColumnRatherThanRight = false;
          }

          leftLineXValue
          = ( ( ((double)( whichColumn / 2 )) * fullColumnWidth )
              + labelWidth );
          if( leftColumnRatherThanRight )
          {
            middleLineXValue = ( leftLineXValue + joinerWidth );
            rightLineXValue = ( middleLineXValue + flatBitWidth );
          }
          else
          {
            leftLineXValue += ( joinerWidth + columnPairOffset );
            middleLineXValue = ( leftLineXValue + flatBitWidth );
            rightLineXValue = ( middleLineXValue + joinerWidth );
          }

          for( std::list< SpectrumPlotting::LineData >::iterator
               lineIterator( columnPointer->begin() );
               columnPointer->end() != lineIterator;
               ++lineIterator )
          {
            if( leftColumnRatherThanRight )
            {
              gnuplotDataFile
              << leftLineXValue << " " << lineIterator->getLabelPosition()
              << std::endl
              << middleLineXValue << " " << lineIterator->getMass()
              << std::endl
              << rightLineXValue << " " << lineIterator->getMass()
              << std::endl;
            }
            else
            {
              gnuplotDataFile
              << leftLineXValue << " " << lineIterator->getMass()
              << std::endl
              << middleLineXValue << " " << lineIterator->getMass()
              << std::endl
              << rightLineXValue << " " << lineIterator->getLabelPosition()
              << std::endl;
            }

            // gnuplot treats double blank lines as meaning that the data
            // above has a separate "index":
            gnuplotDataFile << std::endl << std::endl;

            gnuplotCommandFile
            << "set style line " << (++gnuplotLineIndex) << " lt rgb \""
            << lineIterator->getColor() << "\" lw 3"
            << std::endl;
            // gnuplotLineIndex is incremented to give each line its own unique
            // linestyle.
          }  // end of loop over lines within the column.
        }  // end of loop over columns.

        gnuplotDataFile.close();

        // finally construct the plot command:
        gnuplotCommandFile
        << "plot [0:"
        << ( (double)( ( columnSet.getLastIndex() / 2 )
                       + ( columnSet.getLastIndex() % 2 ) ) * fullColumnWidth )
        // this should correctly count the number of column pairs, even if the
        // last pair is only one column.
        << "] [0:" << scaleMaximum << "] '" << gnuplotDataFileName
        << "' index 0 notitle with lines ls 1";
        for( int whichLine( 1 );
             gnuplotLineIndex > whichLine;
             ++whichLine )
        {
          gnuplotCommandFile
          << ", '" << gnuplotDataFileName
          << "' index " << whichLine
          << " notitle with lines ls " << ( whichLine + 1 );
        }
        gnuplotCommandFile << std::endl;
        gnuplotCommandFile.close();

        std::ofstream fullLatexFile( fullLatexBaseName.c_str() );
        if( fullLatexFile.is_open() )
        {
          fullLatexFile
          << "\\documentclass{article}" << std::endl
          << "\\usepackage{graphics}" << std::endl
          << "\\newlength\\labelmover" << std::endl
          << "\\begin{document}" << std::endl
          << "\\pagestyle{empty}" << std::endl
          << "\\begin{center}" << std::endl
          << "\\input{./" << gnuplotTexBaseName << ".tex}" << std::endl
          << "\\end{center}" << std::endl
          << "\\end{document}" << std::endl;
          fullLatexFile.close();
        }
        else
        {
          returnBool = false;
        }
        return returnBool;
      }
      else
      {
        return false;
      }
    }

    void
    SpectrumPlotter::sortMasses()
    // this sorts all the masses in the columns, & then sets the scale range,
    // then deals with any labels above the final scaleMaximum.
    {
      largestMass = 0.0;
      for( int whichColumn( columnSet.getLastIndex() );
           0 < whichColumn;
           --whichColumn )
      {
        columnPointer = columnSet.getPointer( whichColumn );
        if( !(columnPointer->empty()) )
        {
          columnPointer->sort( &(SpectrumPlotting::LineData::lowToHigh) );
          largestMass = columnPointer->back().getMass();
        }
      }
      if( 0.0 >= scaleMaximum )
        // if the scale is to be automatically decided by the largest mass...
      {
        scaleMaximum = ( largestMass * automaticScaleFactor );
      }

      // now labels above scaleMaximum get the mass appended in brackets, get
      // moved to just beneath scaleMaximum, & get flagged as center-justified.
      for( int whichColumn( columnSet.getLastIndex() );
           0 < whichColumn;
           --whichColumn )
      {
        columnPointer = columnSet.getPointer( whichColumn );
        for( std::list< SpectrumPlotting::LineData >::iterator
             lineIterator( columnPointer->begin() );
             columnPointer->end() != lineIterator;
             ++lineIterator )
        {
          if( lineIterator->getMass() > scaleMaximum )
          {
            lineIterator->relabelForOverlargeMass( scaleMaximum );
          }
        }
      }
    }

    void
    SpectrumPlotter::floatLabels()
    // this tries to move all the labels up or down until they are all
    // separated by ( labelSeparation * scaleMaximum ).
    {
      for( int whichColumn( columnSet.getLastIndex() );
           0 < whichColumn;
           --whichColumn )
      {
        columnPointer = columnSet.getPointer( whichColumn );
        if( 1 < columnPointer->size() )
          // the labels only need to be checked for overlap if there are at
          // least 2 lines in the column.
        {
          remainingShuffles = maximumLabelFloatingShuffles;
          // each column is allowed to try floating the labels apart
          // maximumLabelFloatingShuffles times.
          while( notYetFinishedShuffling
                &&
                ( 0 < remainingShuffles ) )
          {
            notYetFinishedShuffling = false;
            // each iteration starts by assuming that it just finds that all
            // the labels are sufficiently separate, with no floating needed.
            --remainingShuffles;
            lowerMassIterator = columnPointer->begin();
            // if the lowest label is too low, it is bumped up to its lowest
            // allowed position:
            if( labelMinimumPosition > lowerMassIterator->getLabelPosition() )
            {
              notYetFinishedShuffling = true;
              // moving the lowest label means that the column has to be
              // checked again for overlapping labels.
              lowerMassIterator->setLabelPosition( labelMinimumPosition );
            }
            upperMassIterator = lowerMassIterator;
            ++upperMassIterator;
            while( upperMassIterator != columnPointer->end() )
              // lowerMassIterator is always 1 step behind upperMassIterator.
            {
              if( labelSeparation < ( upperMassIterator->getLabelPosition()
                                    - lowerMassIterator->getLabelPosition() ) )
                // if a pair of overlapping labels is found...
              {
                notYetFinishedShuffling = true;
                /* ... first notYetFinishedShuffling is set to true since this
                 * iteration did not merely confirm that the labels are in
                 * order & well separated. then the labels are floated away
                 * from each other around their average position. since the
                 * conditional does not check for the absolute separation, if
                 * labels ever get twisted past each other, the conditional
                 * will find them, & since the lines are sorted according to
                 * their mass value rather than their current label position,
                 * the labels get separated in the right direction.
                 */
                labelAverage
                = ( 0.5 * ( upperMassIterator->getLabelPosition()
                            + lowerMassIterator->getLabelPosition() ) );
                lowerMassIterator->setLabelPosition( labelAverage
                                                 - labelSeparationShuffleFactor
                                                   * labelSeparation );
                upperMassIterator->setLabelPosition( labelAverage
                                                 + labelSeparationShuffleFactor
                                                   * labelSeparation );
              }
              ++lowerMassIterator;
              ++upperMassIterator;
            }
            /* now upperMassIterator is at columnPointer->end(), so
             * lowerMassIterator is at the highest label, which is ensured to
             * be lower than its highest value:
             */
            if( scaleMaximum < lowerMassIterator->getLabelPosition() )
            {
              notYetFinishedShuffling = true;
              // moving the highest label means that the column has to be
              // checked again for overlapping labels.
              lowerMassIterator->setLabelPosition( scaleMaximum );
            }
          }  // end of loop over shuffles.
        }  // end of if the column had 2 or more lines.
      }  // end of loop over columns.
    }

  }

}
