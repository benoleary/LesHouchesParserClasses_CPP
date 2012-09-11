/*
 * TwoDimensionalDataPlotter.cpp
 *
 *  Created on: Jan 8, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *
 *      This file is part of BOLlib, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.BOLlib.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#include "TwoDimensionalDataPlotter.hpp"

namespace BOL
{
  TwoDimensionalDataPlotter::TwoDimensionalDataPlotter(
                                    std::string const& pathToGnuplotExecutable,
                                            std::string const& plotFileName ) :
      plotFileName( plotFileName ),
      gnuplotDataFileName( "gnuplot_data.txt" ),
      gnuplotCommandFileName( "gnuplot_input.txt" ),
      patienceTicks( 10000 ),
      dataPoints( 0 ),
      outputStream(),
      gnuplotExecutor( pathToGnuplotExecutable,
                       patienceTicks )
  {
    gnuplotExecutor.setArguments( gnuplotCommandFileName );
  }

  TwoDimensionalDataPlotter::~TwoDimensionalDataPlotter()
  {
    if( outputStream.is_open() )
    {
      outputStream.close();
    }
  }


  void
  TwoDimensionalDataPlotter::plotData()
  {
    outputStream.open( gnuplotDataFileName.c_str() );
    if( outputStream.is_open() )
      // if the file was successfully opened...
    {
      for( int dataIndex( 0 );
           dataPoints.getSize() > dataIndex;
           ++dataIndex )
      {
        outputStream
        << dataPoints[ dataIndex ].first << " "
        << dataPoints[ dataIndex ].second << std::endl;
      }
      outputStream.close();

      outputStream.open( gnuplotCommandFileName.c_str() );
      if( outputStream.is_open() )
        // if the file was successfully opened...
      {
        outputStream
        << "set term postscript eps enhanced color solid" << std::endl
        << "set output \"" << plotFileName << "\"" << std::endl
        << "set style line 1 lt rgb \"red\" lw 3" << std::endl
        << "plot '" << gnuplotDataFileName
        << "' index 0 notitle with lines ls 1" << std::endl;
        outputStream.close();

        gnuplotExecutor.forkAndExecvAndWait();
      }
      else
      {
        std::cout
        << std::endl
        << "BOL::error! TwoDimensionalDataPlotter::plotData() could not open"
        << gnuplotCommandFileName;
        std::cout << std::endl;
      }
    }
    else
    {
      std::cout
      << std::endl
      << "BOL::error! TwoDimensionalDataPlotter::plotData() could not open"
      << gnuplotDataFileName;
      std::cout << std::endl;
    }
  }

  void
  TwoDimensionalDataPlotter::plotData(
               std::vector< DoublePairVectorWithString > const& dataAndColors )
  {
    std::string dataFileName;
    int const numberOfFileNumberDigits( StringParser::numberOfDigitsInInt(
                                                      dataAndColors.size() ) );

    // debugging:
    /**/std::cout << std::endl << "debugging:"
    << std::endl
    << "dataAndColors.size() = " << dataAndColors.size()
    << ", numberOfFileNumberDigits = " << numberOfFileNumberDigits;
    std::cout << std::endl;/**/

    std::vector< std::pair< std::string, std::string > > colorsWithFilenames;
    for( unsigned int whichEntry( 0 );
         dataAndColors.size() > whichEntry;
         ++whichEntry )
    {
      dataFileName.assign( gnuplotDataFileName );
      dataFileName.append( StringParser::intToString( whichEntry,
                                                      numberOfFileNumberDigits,
                                                      "" ) );
      colorsWithFilenames.push_back( std::pair< std::string, std::string >(
                                            dataAndColors[ whichEntry ].second,
                                                              dataFileName ) );

      // debugging:
      /**/std::cout << std::endl << "debugging:"
      << std::endl
      << "opening " << dataFileName
      << std::endl
      << "dataAndColors[ " << whichEntry << " ].first.size() = "
      << dataAndColors[ whichEntry ].first.size();
      std::cout << std::endl;/**/

      outputStream.open( dataFileName.c_str() );
      if( outputStream.is_open() )
        // if the file was successfully opened...
      {
        for( unsigned int dataIndex( 0 );
             dataAndColors[ whichEntry ].first.size() > dataIndex;
             ++dataIndex )
        {
          outputStream
          << dataAndColors[ whichEntry ].first[ dataIndex ].first << " "
          << dataAndColors[ whichEntry ].first[ dataIndex ].second
          << std::endl;
        }
        outputStream.close();
      }
      else
      {
        std::cout
        << std::endl
        << "BOL::error! TwoDimensionalDataPlotter::plotData() could not open"
        << dataFileName;
        std::cout << std::endl;
      }
    }

    outputStream.open( gnuplotCommandFileName.c_str() );
    if( outputStream.is_open() )
      // if the file was successfully opened...
    {
      outputStream
      << "set term postscript eps enhanced color solid" << std::endl
      << "set output \"" << plotFileName << "\"" << std::endl;
      for( unsigned int whichEntry( 0 );
           colorsWithFilenames.size() > whichEntry;
           ++whichEntry )
      {
        outputStream
        << "set style line " << ( whichEntry + 1 ) << " lt rgb \""
        << colorsWithFilenames[ whichEntry ].first << "\" lw 3"
        << std::endl;
      }
      outputStream
      << "plot ";
      for( unsigned int whichEntry( 0 );
           colorsWithFilenames.size() > whichEntry;
           ++whichEntry )
      {
        if( 0 < whichEntry )
        {
          outputStream << ", ";
        }
        outputStream
        << "'" << colorsWithFilenames[ whichEntry ].second
        << "' index 0 notitle with lines ls " << ( whichEntry + 1 );
      }
      outputStream.close();

      gnuplotExecutor.forkAndExecvAndWait();
    }
    else
    {
      std::cout
      << std::endl
      << "BOL::error! TwoDimensionalDataPlotter::plotData() could not open"
      << gnuplotCommandFileName;
      std::cout << std::endl;
    }
  }
}
