/*
 * LhpcSlhaValuePlotter.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.LHPC_CPP.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#include "SlhaSpectrumPlottingClasses/SlhaValuePlotter.hpp"

int main( int argumentCount,
          char* argumentCharArray[] )
{
  if( 4 != argumentCount )
  {
    std::cout
    << std::endl
    << "This SLHA-value-plotting program requires the names of 3 files:"
    << std::endl
    << " 1st, a file in the XML format, which has the elements defining how to"
    << " plot the values;"
    << std::endl
    << " 2nd, a file in the SLHA format, which has the BLOCKs with the values"
    << " to be plotted; and"
    << std::endl
    << " 3rd, the output file name to use.";
    std::cout << std::endl;
  }
  else
  {
    LHPC::SLHA::SlhaValuePlotter slhaPlotter( argumentCharArray[ 1 ] );
    slhaPlotter.plotValues( argumentCharArray[ 2 ],
                            argumentCharArray[ 3 ],
                            true );

  }

  // This was a triumph! I'm making a note here:
  return EXIT_SUCCESS;
}




