/*
 * LhpcSpectrumPlotter.cpp
 *
 *  Created on: Feb 29, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.LHPC_CPP.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#include <string>
#include "SlhaSpectrumPlottingClasses/SpectrumPlotter.hpp"
#include "SLHA.hpp"
#include "BOLlib/Classes/UsefulStuff.hpp"

int main( int argumentCount,
          char* argumentCharArray[] )
{
  if( ( 2 != argumentCount )
      &&
      ( 3 != argumentCount )
      &&
      ( 4 != argumentCount ) )
  {
    std::cout
    << std::endl
    << "this spectrum-plotting program requires the names of 1, 2 or 3"
    << " files in the SLHA format. in particular, it requires that it can find"
    << " blocks called LHPCSPECTRUMPLOTCONTROL and LHPCSPECTRUMPLOTPARTICLES,"
    << " (which are not specified by the SLHA papers, but are permitted by the"
    << " format and are required for this program)."
    << std::endl
    << "if only 1 filename is  provided, it is  assumed that this single file"
    << " has the MASS (or FMASS, which is taken over MASS),"
    << " LHPCSPECTRUMPLOTCONTROL and LHPCSPECTRUMPLOTPARTICLES blocks, and the"
    << " output file name will be the same as the input file name, appended"
    << " with \".eps\" (so if \"exampleSpectrum.dat\" was given as the single"
    << " argument, \"exampleSpectrum.dat.eps\" will be the name of the output"
    << " file)."
    << std::endl
    << "if 2 filenames are provided, it is assumed that the 1st file has only"
    << " the MASS or FMASS blocks, while the 2nd has the"
    << " LHPCSPECTRUMPLOTCONTROL and LHPCSPECTRUMPLOTPARTICLES blocks, and the"
    << " output file name will be the same as the 1st input file name,"
    << " appended with \".eps\" (so if \"exampleSpectrum.dat\" and"
    << " \"exampleControl.dat\" were given as the 2 arguments,"
    <<  " \"exampleSpectrum.dat.eps\" will be the name of the output file)."
    << std::endl
    << "if 3 filenames are provided, it is assumed that the 1st file has only"
    << " the MASS or FMASS blocks, while the 2nd has the"
    << " LHPCSPECTRUMPLOTCONTROL and LHPCSPECTRUMPLOTPARTICLES blocks, and the"
    << " 3rd argument will be used as the output file name.";
    std::cout << std::endl;
  }
  else
  {
    bool const isVerbose( true );
    LHPC::SlhaParser spectrumParser( isVerbose );

    // both FMASS & MASS are searched for:
    LHPC::SLHA::SpectrumPlotter::FmassBlock fmassBlock( "FMASS",
                                                        LHPC::ExtendedMass(),
                                                        isVerbose );
    spectrumParser.registerBlock( fmassBlock );
    LHPC::SLHA::SpectrumPlotter::MassBlock massBlock( "MASS",
                                                  BOL::UsefulStuff::notANumber,
                                                      isVerbose );
    spectrumParser.registerBlock( massBlock );

    // the spectrum-plotter-specific blocks are also searched for in the
    // spectrum file:
    LHPC::SLHA::SparseSinglyIndexedBlock< std::string >
    controlBlock( "LHPCSPECTRUMPLOTCONTROL",
                  "error",
                  isVerbose );
    spectrumParser.registerBlock( controlBlock );
    LHPC::SLHA::SparseSinglyIndexedBlock< std::string >
    linesBlock( "LHPCSPECTRUMPLOTPARTICLES",
                "error",
                isVerbose );
    spectrumParser.registerBlock( linesBlock );

    // the spectrum file is now read:
    spectrumParser.readFile( argumentCharArray[ 1 ] );

    std::string outputFilename( argumentCharArray[ 1 ] );
    outputFilename.append( ".eps" );

    if( 2 < argumentCount )
      // if the extra control file is specified...
    {
      // the control blocks are registered with a different parser, which
      // reads in the extra file & over-writes the control blocks:
      LHPC::SlhaParser controlParser( isVerbose );
      controlParser.registerBlock( controlBlock );
      controlParser.registerBlock( linesBlock );
      controlParser.readFile( argumentCharArray[ 2 ] );

      if( 4 == argumentCount )
      {
        outputFilename.assign( argumentCharArray[ 3 ] );
      }
    }

    LHPC::SLHA::SpectrumPlotter massSpectrumPlotter( controlBlock,
                                                     linesBlock,
                                                     &fmassBlock,
                                                     &massBlock );
    massSpectrumPlotter.plotSpectrum( outputFilename );
  }  // end of if correct number of arguments was given.

  // this was a triumph! I'm making a note here:
  return EXIT_SUCCESS;
}


