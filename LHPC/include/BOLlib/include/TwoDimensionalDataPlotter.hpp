/*
 * TwoDimensionalDataPlotter.hpp
 *
 *  Created on: Jan 8, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *
 *      This file is part of BOLlib, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.BOLlib.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#ifndef TWODIMENSIONALDATAPLOTTER_HPP_
#define TWODIMENSIONALDATAPLOTTER_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include "VectorlikeArray.hpp"
#include "WaitingOnSubprocessExecutor.hpp"

namespace BOL
{
  // this class is used to make plots of data using Gnuplot.
  class TwoDimensionalDataPlotter
  {
  public:
    typedef std::pair< double, double > DoublePair;
    typedef std::vector< DoublePair > DoublePairVector;
    typedef
    std::pair< DoublePairVector, std::string > DoublePairVectorWithString;

    TwoDimensionalDataPlotter( std::string const& pathToGnuplotExecutable,
                               std::string const& plotFileName);
    ~TwoDimensionalDataPlotter();

    void
    addPoint( double const xValue,
              double const yValue );
    void
    plotData();
    void
    plotData( std::vector< DoublePairVectorWithString > const& dataAndColors );
    void
    clearEntries( std::string plotFileName );


  protected:
    std::string plotFileName;
    std::string const gnuplotDataFileName;
    std::string const gnuplotCommandFileName;
    int const patienceTicks;
    VectorlikeArray< std::pair< double, double > > dataPoints;
    std::ofstream outputStream;
    WaitingOnSubprocessExecutor gnuplotExecutor;
  };



  inline void
  TwoDimensionalDataPlotter::addPoint( double const xValue,
                                       double const yValue )
  {
    dataPoints.newEnd().first = xValue;
    dataPoints.getBack().second = yValue;
  }

  inline void
  TwoDimensionalDataPlotter::clearEntries( std::string plotFileName )
  {
    this->plotFileName.assign( plotFileName );
    dataPoints.setSize( 0 );
  }

}

#endif /* TWODIMENSIONALDATAPLOTTER_HPP_ */
