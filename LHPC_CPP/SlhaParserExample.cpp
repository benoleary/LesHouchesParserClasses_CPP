/*
 * SlhaParserExample.cpp
 *
 *  Created on: Feb 22, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.LHPC_CPP.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#include "SLHA.hpp"

int main( int argumentCount,
          char* argumentCharArray[] )
{
  if( 3 != argumentCount )
  {
    std::cout
    << std::endl
    << "this testing program requires the name of 2 SLHA files to read in!";
    std::cout << std::endl;
  }
  else
  {
    std::string firstFileName( argumentCharArray[ 1 ] );
    std::string secondFileName( argumentCharArray[ 2 ] );
    bool const isVerbose( true );

    /* first, a demonstration where one picks the blocks to read: here MINPAR
     * & NMIX were chosen. the user has to know what format they are, so that
     * the parser knows how to interpret the data. MODSEL is a set of doubles
     * ordered with a single index, & all indices from 1 to [maximum index]
     * must be present, so SparseSinglyIndexedBlock< double > would be
     * appropriate, except most of the time the values are integers (& nobody
     * ever seems to use MODSEL 12, which specifies the largest Q scale, which
     * itself almost always is just the value for the EWSB scale. hence,
     * SparseSinglyIndexedBlock< int > is chosen for demonstration. MINPAR is a
     * set of doubles ordered with a single index, & all indices from 1 to
     * [maximum index] must be present, so DenseSinglyIndexedBlock< double > is
     * appropriate. likewise, NMIX is a set of doubles ordered by 2 indices, &
     * no indices should be skipped so DenseDoublyIndexedBlock< double > is
     * appropriate.
     */
    LHPC::SLHA::SparseSinglyIndexedBlock< int > modselBlock( "MODSEL",
                                                             -1,
                                                             isVerbose );
    LHPC::SLHA::DenseSinglyIndexedBlock< double > minparBlock( "MINPAR",
                                                               0.0,
                                                               isVerbose );
    LHPC::SLHA::DenseDoublyIndexedBlock< double > nmixBlock( "NMIX",
                                                             0.0,
                                                             isVerbose );

    // a parser is also needed, to do the actual reading of the file & passing
    // of strings to the blocks:
    LHPC::SlhaParser testParser( isVerbose );
    // true as the argument so that warnings are printed.

    // the blocks have to be registered with the parser:
    testParser.registerBlock( modselBlock );
    testParser.registerBlock( minparBlock );
    testParser.registerBlock( nmixBlock );

    // one can also register a spectrum of particles, which automatically
    // groups masses & decays together for each mass eigenstate:
    LHPC::MassSpectrumClass::MSSM testSpectrum( isVerbose );

    // the spectrum has to be registered with the parser:
    testParser.registerSpectrum( testSpectrum );


    // this line now does all the work!
    testParser.readFile( firstFileName );


    // this is just printing out some of what was read, demonstrating various
    // ways of accessing the data from the blocks & spectrum:
    std::cout
    << std::endl
    << "testParser.readFile( \"" << firstFileName << "\" ) successful.";
    std::cout << std::endl;
    std::cout
    << std::endl
    << "MODSEL( 1 ) = " << modselBlock( 1 );
    // operator() takes the lowest-scale copy of the block & finds the index
    // there.
    std::cout
    << std::endl
    << "MODSEL[ 0 ][ 2 ] = " << modselBlock[ 0 ][ 2 ];
    /* block operator[ whichCopy ] returns the whichCopy-th copy of the block
     * with the same name but different scale value, then
     * operator[ soughtIndex ] on the returned block interpreter finds the
     * value for index soughtIndex.
     */
    std::cout
    << std::endl
    << "MODSEL( 100 ) = " << modselBlock( 100 );
    std::cout
    << std::endl
    << "MODSEL( -1 ) = " << modselBlock( -1 );
    std::cout
    << std::endl
    << "MINPAR( 1 ) = " << minparBlock( 1 );
    std::cout
    << std::endl
    << "MINPAR[ 0 ][ 2 ] = " << minparBlock[ 0 ][ 2 ];
    std::cout
    << std::endl
    << "MODSEL between dashed lines: " << std::endl
    << "-------------------------" << std::endl
    << modselBlock.interpretAsString( true ) << std::endl
    << "-------------------------" << std::endl;
    std::cout
    << std::endl
    << "MINPAR between dashed lines: " << std::endl
    << "-------------------------" << std::endl
    << minparBlock.interpretAsString( false ) << std::endl
    << "-------------------------" << std::endl;
    std::cout
    << std::endl
    << "NMIX( 1, 3 ) = " << nmixBlock( 1, 3 );
    std::cout
    << std::endl
    << "NMIX between dashed lines: " << std::endl
    << "-------------------------" << std::endl
    << nmixBlock.interpretAsString() << std::endl
    << "-------------------------" << std::endl;

    LHPC::MassEigenstate&
    spositronL( testSpectrum.getSpositronL() );
    /* instead of using the direct access function getSpositronL(), one could
     * find it with testSpectrum.getMassEigenstate( -1000011 ) by knowing the
     * spositron's 7-digit PDG code (one could also use
     * -LHPC::PDGVII::selectronL (from
     * SevenDigitSlhaCodes.hpp) to substitute for the explicit number), though
     * one should note that the direct access function returns a reference
     * while the searching function returns a pointer, since it might be asked
     * for a particle it doesn't have, in which case it returns a NULL pointer.
     */
    std::cout
    << std::endl
    << "spositron_L: "
    << spositronL.getAsciiName()
    << " / " << spositronL.getLatexName()
    << ", self-conjugate (0 = false, 1 = true): "
    << spositronL.isSelfConjugate()
    << ", absolute mass: " << spositronL.getAbsoluteMass()
    << ", default code: " << spositronL.getCode()
    << ", decay width: " << spositronL.getDecayWidth();
    std::cout << std::endl;
    std::cout
    << std::endl
    << "spositron_L decays(" << spositronL.getDecaySet().size()
    << " lines):";
    std::cout << std::endl;
    std::list< LHPC::MassEigenstate const* > const* decayList( NULL );
    for( size_t whichDecay( 0 );
         spositronL.getDecaySet().size() > whichDecay;
         ++whichDecay )
    {
      std::cout << "BR "
      << spositronL.getDecay( whichDecay ).getPairedValue()
      << " to ";
      decayList
      = &(spositronL.getDecay( whichDecay ).getPointerList());
      for( std::list< LHPC::MassEigenstate const* >::const_iterator
           particleIterator( decayList->begin() );
           decayList->end() != particleIterator;
           ++particleIterator )
      {
        if( decayList->begin() == particleIterator )
        {
          std::cout << " ";
        }
        else
        {
          std::cout << " + ";
        }
        std::cout << (*particleIterator)->getAsciiName();
      }
      std::cout << std::endl;
    }

    LHPC::MassEigenstate&
    selectronL( spositronL.getChargeConjugate() );
    std::cout
    << std::endl
    << "selectron_L: "
    << selectronL.getAsciiName()
    << " / " << selectronL.getLatexName()
    << ", self-conjugate: " << selectronL.isSelfConjugate()
    << ", absolute mass: " << selectronL.getAbsoluteMass()
    << ", default code: " << selectronL.getCode()
    << ", decay width: " << selectronL.getDecayWidth();
    std::cout << std::endl;

    std::cout
    << std::endl
    << "selectron_L decays (" << selectronL.getDecaySet().size()
    << " lines):";
    std::cout << std::endl;
    for( size_t whichDecay( 0 );
         selectronL.getDecaySet().size() > whichDecay;
         ++whichDecay )
    {
      std::cout << "BR "
      << selectronL.getDecay( whichDecay ).getPairedValue()
      << " to ";
      decayList
      = &(selectronL.getDecay( whichDecay ).getPointerList());
      for( std::list< LHPC::MassEigenstate const* >::const_iterator
           particleIterator( decayList->begin() );
           decayList->end() != particleIterator;
           ++particleIterator )
      {
        if( decayList->begin() == particleIterator )
        {
          std::cout << " ";
        }
        else
        {
          std::cout << " + ";
        }
        std::cout << (*particleIterator)->getAsciiName();
      }
      std::cout << std::endl;
    }

    LHPC::MassEigenstate& gluinoFermion( testSpectrum.getGluino() );
    double largestBr( 0.0 );
    std::list< LHPC::MassEigenstate const* > const* subdecayList( NULL );
    for( size_t whichDecay( 0 );
         gluinoFermion.getDecaySet().size() > whichDecay;
         ++whichDecay )
    {
      if( gluinoFermion.getDecay( whichDecay ).getPairedValue()
          > largestBr )
      {
        decayList
        = &(gluinoFermion.getDecay( whichDecay ).getPointerList());
        largestBr
        = gluinoFermion.getDecay( whichDecay ).getPairedValue();
      }
    }
    std::cout
    << std::endl
    << "largest gluino BR = " << largestBr;
    if( !(gluinoFermion.getDecaySet().empty()) )
    {
      std::cout << " to ";
      for( std::list< LHPC::MassEigenstate const* >::const_iterator
           particleIterator( decayList->begin() );
           decayList->end() != particleIterator;
           ++particleIterator )
      {
        if( decayList->begin() == particleIterator )
        {
          std::cout << std::endl << " ";
        }
        else
        {
          std::cout << std::endl << " + ";
        }
        largestBr = 0.0;
        for( size_t whichDecay( 0 );
             (*particleIterator)->getDecaySet().size() > whichDecay;
             ++whichDecay )
        {
          if( (*particleIterator)->getDecay( whichDecay ).getPairedValue()
              > largestBr )
          {
            subdecayList
            = &((*particleIterator)->getDecay( whichDecay ).getPointerList());
            largestBr
            = (*particleIterator)->getDecay( whichDecay ).getPairedValue();
          }
        }
        std::cout
        << (*particleIterator)->getAsciiName();
        if( (*particleIterator)->getDecaySet().empty() )
        {
          std::cout<< " (no decays)";
        }
        else
        {
          std::cout
          << " (with its own largest BR = " << largestBr
          << " to ";
          for( std::list< LHPC::MassEigenstate const* >::const_iterator
               productIterator( subdecayList->begin() );
               subdecayList->end() != productIterator;
               ++productIterator )
          {
            if( subdecayList->begin() == productIterator )
            {
              std::cout << " ";
            }
            else
            {
              std::cout << " + ";
            }
            std::cout << (*productIterator)->getAsciiName();
          }
          std::cout << ")";
        }
      }
    }
    if( 2<= gluinoFermion.getDecaySet().size() )
    {
      std::cout
      << std::endl
      << "1st 2 gluino decays from file:"
      << std::endl << " to ";
      decayList
      = &(gluinoFermion.getDecay( 0 ).getPointerList());
      for( std::list< LHPC::MassEigenstate const* >::const_iterator
           particleIterator( decayList->begin() );
           decayList->end() != particleIterator;
           ++particleIterator )
      {
        if( decayList->begin() == particleIterator )
        {
          std::cout << std::endl << " ";
        }
        else
        {
          std::cout << std::endl << " + ";
        }
        largestBr = 0.0;
        for( size_t whichDecay( 0 );
             (*particleIterator)->getDecaySet().size() > whichDecay;
             ++whichDecay )
        {
          if( (*particleIterator)->getDecay( whichDecay ).getPairedValue()
              > largestBr )
          {
            subdecayList
            = &((*particleIterator)->getDecay( whichDecay ).getPointerList());
            largestBr
            = (*particleIterator)->getDecay( whichDecay ).getPairedValue();
          }
        }
        std::cout
        << (*particleIterator)->getAsciiName();
        if( (*particleIterator)->getDecaySet().empty() )
        {
          std::cout<< " (no decays)";
        }
        else
        {
          std::cout
          << " (with its own largest BR = " << largestBr
          << " to ";
          for( std::list< LHPC::MassEigenstate const* >::const_iterator
               productIterator( subdecayList->begin() );
               subdecayList->end() != productIterator;
               ++productIterator )
          {
            if( subdecayList->begin() == productIterator )
            {
              std::cout << " ";
            }
            else
            {
              std::cout << " + ";
            }
            std::cout << (*productIterator)->getAsciiName();
          }
          std::cout << ")";
        }
      }
      std::cout << std::endl << " and to ";
      decayList
      = &(gluinoFermion.getDecay( 1 ).getPointerList());
      for( std::list< LHPC::MassEigenstate const* >::const_iterator
           particleIterator( decayList->begin() );
           decayList->end() != particleIterator;
           ++particleIterator )
      {
        if( decayList->begin() == particleIterator )
        {
          std::cout << std::endl << " ";
        }
        else
        {
          std::cout << std::endl << " + ";
        }
        largestBr = 0.0;
        for( size_t whichDecay( 0 );
             (*particleIterator)->getDecaySet().size() > whichDecay;
             ++whichDecay )
        {
          if( (*particleIterator)->getDecay( whichDecay ).getPairedValue()
              > largestBr )
          {
            subdecayList
            = &((*particleIterator)->getDecay( whichDecay ).getPointerList());
            largestBr
            = (*particleIterator)->getDecay( whichDecay ).getPairedValue();
          }
        }
        std::cout
        << (*particleIterator)->getAsciiName();
        if( (*particleIterator)->getDecaySet().empty() )
        {
          std::cout<< " (no decays)";
        }
        else
        {
          std::cout
          << " (with its own largest BR = " << largestBr
          << " to ";
          for( std::list< LHPC::MassEigenstate const* >::const_iterator
               productIterator( subdecayList->begin() );
               subdecayList->end() != productIterator;
               ++productIterator )
          {
            if( subdecayList->begin() == productIterator )
            {
              std::cout << " ";
            }
            else
            {
              std::cout << " + ";
            }
            std::cout << (*productIterator)->getAsciiName();
          }
          std::cout << ")";
        }
      }
    }


    // now the 2nd file is read in:
    testParser.readFile( secondFileName );

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout
    << std::endl
    << "testParser.readFile( \"" << secondFileName << "\" ) successful.";
    std::cout << std::endl;
    std::cout
    << std::endl
    << "MODSEL( 1 ) = " << modselBlock( 1 );
    std::cout
    << std::endl
    << "MODSEL[ 1 ][ 2 ] = " << modselBlock[ 1 ][ 2 ];
    std::cout
    << std::endl
    << "MODSEL( 100 ) = " << modselBlock( 100 );
    std::cout
    << std::endl
    << "MODSEL( -1 ) = " << modselBlock( -1 );
    std::cout
    << std::endl
    << "MINPAR( 1 ) = " << minparBlock( 1 );
    std::cout
    << std::endl
    << "MINPAR[ 1 ][ 2 ] = " << minparBlock[ 1 ][ 2 ];
    // both operator[] & operator() do the same thing for DenseSinglyIndexed
    // blocks.
    std::cout
    << std::endl
    << "MODSEL between dashed lines: " << std::endl
    << "-------------------------" << std::endl
    << modselBlock.interpretAsString() << std::endl
    << "-------------------------" << std::endl;
    std::cout
    << std::endl
    << "MINPAR between dashed lines: " << std::endl
    << "-------------------------" << std::endl
    << minparBlock.interpretAsString() << std::endl
    << "-------------------------" << std::endl;
    std::cout
    << std::endl
    << "NMIX( 1, 3 ) = " << nmixBlock( 1, 3 );
    std::cout
    << std::endl
    << "NMIX between dashed lines: " << std::endl
    << "-------------------------" << std::endl
    << nmixBlock.interpretAsString() << std::endl
    << "-------------------------" << std::endl;

    std::cout
    << std::endl
    << "spositron_L: "
    << spositronL.getAsciiName()
    << " / " << spositronL.getLatexName()
    << ", self-conjugate (0 = false, 1 = true): "
    << spositronL.isSelfConjugate()
    << ", absolute mass: " << spositronL.getAbsoluteMass()
    << ", default code: " << spositronL.getCode()
    << ", decay width: " << spositronL.getDecayWidth();
    std::cout << std::endl;
    std::cout
    << std::endl
    << "spositron_L decays(" << spositronL.getDecaySet().size()
    << " lines):";
    std::cout << std::endl;
    for( size_t whichDecay( 0 );
         spositronL.getDecaySet().size() > whichDecay;
         ++whichDecay )
    {
      std::cout << "BR "
      << spositronL.getDecay( whichDecay ).getPairedValue()
      << " to ";
      decayList
      = &(spositronL.getDecay( whichDecay ).getPointerList());
      for( std::list< LHPC::MassEigenstate const* >::const_iterator
           particleIterator( decayList->begin() );
           decayList->end() != particleIterator;
           ++particleIterator )
      {
        if( decayList->begin() == particleIterator )
        {
          std::cout << " ";
        }
        else
        {
          std::cout << " + ";
        }
        std::cout << (*particleIterator)->getAsciiName();
      }
      std::cout << std::endl;
    }

    std::cout
    << std::endl
    << "selectron_L: "
    << selectronL.getAsciiName()
    << " / " << selectronL.getLatexName()
    << ", self-conjugate: " << selectronL.isSelfConjugate()
    << ", absolute mass: " << selectronL.getAbsoluteMass()
    << ", default code: " << selectronL.getCode()
    << ", decay width: " << selectronL.getDecayWidth();
    std::cout << std::endl;

    std::cout
    << std::endl
    << "selectron_L decays (" << selectronL.getDecaySet().size()
    << " lines):";
    std::cout << std::endl;
    for( size_t whichDecay( 0 );
         selectronL.getDecaySet().size() > whichDecay;
         ++whichDecay )
    {
      std::cout << "BR "
      << selectronL.getDecay( whichDecay ).getPairedValue()
      << " to ";
      decayList
      = &(selectronL.getDecay( whichDecay ).getPointerList());
      for( std::list< LHPC::MassEigenstate const* >::const_iterator
           particleIterator( decayList->begin() );
           decayList->end() != particleIterator;
           ++particleIterator )
      {
        if( decayList->begin() == particleIterator )
        {
          std::cout << " ";
        }
        else
        {
          std::cout << " + ";
        }
        std::cout << (*particleIterator)->getAsciiName();
      }
      std::cout << std::endl;
    }

    largestBr = 0.0;
    for( size_t whichDecay( 0 );
         gluinoFermion.getDecaySet().size() > whichDecay;
         ++whichDecay )
    {
      if( gluinoFermion.getDecay( whichDecay ).getPairedValue()
          > largestBr )
      {
        decayList
        = &(gluinoFermion.getDecay( whichDecay ).getPointerList());
        largestBr
        = gluinoFermion.getDecay( whichDecay ).getPairedValue();
      }
    }
    std::cout
    << std::endl
    << "largest gluino BR = " << largestBr;
    if( !(gluinoFermion.getDecaySet().empty()) )
    {
      std::cout << " to ";
      for( std::list< LHPC::MassEigenstate const* >::const_iterator
           particleIterator( decayList->begin() );
           decayList->end() != particleIterator;
           ++particleIterator )
      {
        if( decayList->begin() == particleIterator )
        {
          std::cout << std::endl << " ";
        }
        else
        {
          std::cout << std::endl << " + ";
        }
        largestBr = 0.0;
        for( size_t whichDecay( 0 );
             (*particleIterator)->getDecaySet().size() > whichDecay;
             ++whichDecay )
        {
          if( (*particleIterator)->getDecay( whichDecay ).getPairedValue()
              > largestBr )
          {
            subdecayList
            = &((*particleIterator)->getDecay( whichDecay ).getPointerList());
            largestBr
            = (*particleIterator)->getDecay( whichDecay ).getPairedValue();
          }
        }
        std::cout
        << (*particleIterator)->getAsciiName();
        if( (*particleIterator)->getDecaySet().empty() )
        {
          std::cout<< " (no decays)";
        }
        else
        {
          std::cout
          << " (with its own largest BR = " << largestBr
          << " to ";
          for( std::list< LHPC::MassEigenstate const* >::const_iterator
               productIterator( subdecayList->begin() );
               subdecayList->end() != productIterator;
               ++productIterator )
          {
            if( subdecayList->begin() == productIterator )
            {
              std::cout << " ";
            }
            else
            {
              std::cout << " + ";
            }
            std::cout << (*productIterator)->getAsciiName();
          }
          std::cout << ")";
        }
      }
    }
    if( 2<= gluinoFermion.getDecaySet().size() )
    {
      std::cout
      << std::endl
      << "1st 2 gluino decays from file:"
      << std::endl << " to ";
      decayList
      = &(gluinoFermion.getDecay( 0 ).getPointerList());
      for( std::list< LHPC::MassEigenstate const* >::const_iterator
           particleIterator( decayList->begin() );
           decayList->end() != particleIterator;
           ++particleIterator )
      {
        if( decayList->begin() == particleIterator )
        {
          std::cout << std::endl << " ";
        }
        else
        {
          std::cout << std::endl << " + ";
        }
        largestBr = 0.0;
        for( size_t whichDecay( 0 );
             (*particleIterator)->getDecaySet().size() > whichDecay;
             ++whichDecay )
        {
          if( (*particleIterator)->getDecay( whichDecay ).getPairedValue()
              > largestBr )
          {
            subdecayList
            = &((*particleIterator)->getDecay( whichDecay ).getPointerList());
            largestBr
            = (*particleIterator)->getDecay( whichDecay ).getPairedValue();
          }
        }
        std::cout
        << (*particleIterator)->getAsciiName();
        if( (*particleIterator)->getDecaySet().empty() )
        {
          std::cout<< " (no decays)";
        }
        else
        {
          std::cout
          << " (with its own largest BR = " << largestBr
          << " to ";
          for( std::list< LHPC::MassEigenstate const* >::const_iterator
               productIterator( subdecayList->begin() );
               subdecayList->end() != productIterator;
               ++productIterator )
          {
            if( subdecayList->begin() == productIterator )
            {
              std::cout << " ";
            }
            else
            {
              std::cout << " + ";
            }
            std::cout << (*productIterator)->getAsciiName();
          }
          std::cout << ")";
        }
      }
      std::cout << std::endl << " and to ";
      decayList
      = &(gluinoFermion.getDecay( 1 ).getPointerList());
      for( std::list< LHPC::MassEigenstate const* >::const_iterator
           particleIterator( decayList->begin() );
           decayList->end() != particleIterator;
           ++particleIterator )
      {
        if( decayList->begin() == particleIterator )
        {
          std::cout << std::endl << " ";
        }
        else
        {
          std::cout << std::endl << " + ";
        }
        largestBr = 0.0;
        for( size_t whichDecay( 0 );
             (*particleIterator)->getDecaySet().size() > whichDecay;
             ++whichDecay )
        {
          if( (*particleIterator)->getDecay( whichDecay ).getPairedValue()
              > largestBr )
          {
            subdecayList
            = &((*particleIterator)->getDecay( whichDecay ).getPointerList());
            largestBr
            = (*particleIterator)->getDecay( whichDecay ).getPairedValue();
          }
        }
        std::cout
        << (*particleIterator)->getAsciiName();
        if( (*particleIterator)->getDecaySet().empty() )
        {
          std::cout<< " (no decays)";
        }
        else
        {
          std::cout
          << " (with its own largest BR = " << largestBr
          << " to ";
          for( std::list< LHPC::MassEigenstate const* >::const_iterator
               productIterator( subdecayList->begin() );
               subdecayList->end() != productIterator;
               ++productIterator )
          {
            if( subdecayList->begin() == productIterator )
            {
              std::cout << " ";
            }
            else
            {
              std::cout << " + ";
            }
            std::cout << (*productIterator)->getAsciiName();
          }
          std::cout << ")";
        }
      }
    }


    // now a demonstration where one uses a set of pre-bundled blocks:

    // a parser is needed for the block bundle:
    LHPC::SlhaParser testParserForBlockSet( isVerbose );

    // for demonstration, this has all the blocks specified in SLHA1 & SLHA2, &
    // also includes some SPheno-specific blocks:
    LHPC::SlhaTwoWithSpheno testBlockSet( testParserForBlockSet,
                                          isVerbose );

    // again, this line does all the work!
    testParserForBlockSet.readFile( firstFileName );

    // this is for showing that the const versions of the block member
    // functions work:
    LHPC::SLHA::DenseDoublyIndexedBlock< double > const&
    constNmix( testBlockSet.NMIX );

    std::cout
    << std::endl
    << "SMINPUTS( 2 ) = " << testBlockSet.SMINPUTS( 2 );
    std::cout << std::endl;
    std::cout
    << std::endl
    << "MASS( 1000024 ) = " << testBlockSet.MASS( 1000024 );
    std::cout << std::endl;
    std::cout
    << std::endl
    << "NMIX( 1, 3 ) = " << testBlockSet.NMIX( 1, 3 );
    std::cout
    << std::endl
    << "const NMIX( 1, 3 ) = " << constNmix( 1, 3 );
    std::cout << std::endl;
    std::cout
    << std::endl
    << "NMIX between dashed lines: " << std::endl
    << "-------------------------" << std::endl
    << testBlockSet.NMIX.interpretAsString() << std::endl
    << "-------------------------" << std::endl;
    std::cout << std::endl;
    std::cout
    << std::endl
    << "AU between dashed lines: " << std::endl
    << "-------------------------" << std::endl
    << testBlockSet.AU.interpretAsString() << std::endl
    << "-------------------------" << std::endl;
    std::cout << std::endl;
    std::cout
    << std::endl
    << "ALPHA between dashed lines: " << std::endl
    << "-------------------------" << std::endl
    << testBlockSet.ALPHA.interpretAsString() << std::endl
    << "-------------------------" << std::endl;
    std::cout << std::endl;
    std::cout
    << std::endl
    << "STOPMIX between dashed lines: " << std::endl
    << "-------------------------" << std::endl
    << testBlockSet.STOPMIX.interpretAsString() << std::endl
    << "-------------------------" << std::endl;
    std::cout << std::endl;
    std::cout
    << std::endl
    << "HMIX between dashed lines: " << std::endl
    << "-------------------------" << std::endl
    << testBlockSet.HMIX.interpretAsString() << std::endl
    << "-------------------------" << std::endl;
    std::cout << std::endl;
    std::cout
    << std::endl
    << "MSOFT between dashed lines: " << std::endl
    << "-------------------------" << std::endl
    << testBlockSet.MSOFT.interpretAsString() << std::endl
    << "-------------------------" << std::endl;
    std::cout << std::endl;


    std::cout
    << std::endl
    << "reading in 2nd file!";
    std::cout << std::endl;

    // again, this line does all the work!
    testParserForBlockSet.readFile( secondFileName );

    std::cout
    << std::endl
    << "SMINPUTS( 2 ) = " << testBlockSet.SMINPUTS( 2 );
    std::cout << std::endl;
    std::cout
    << std::endl
    << "MASS( 1000024 ) = " << testBlockSet.MASS( 1000024 );
    std::cout << std::endl;
    std::cout
    << std::endl
    << "NMIX( 1, 3 ) = " << testBlockSet.NMIX( 1, 3 );
    std::cout
    << std::endl
    << "const NMIX( 1, 3 ) = " << constNmix( 1, 3 );
    std::cout << std::endl;
    std::cout
    << std::endl
    << "NMIX between dashed lines: " << std::endl
    << "-------------------------" << std::endl
    << testBlockSet.NMIX.interpretAsString( false ) << std::endl
    << "-------------------------" << std::endl;
    std::cout << std::endl;
    std::cout
    << std::endl
    << "AU between dashed lines: " << std::endl
    << "-------------------------" << std::endl
    << testBlockSet.AU.interpretAsString( false ) << std::endl
    << "-------------------------" << std::endl;
    std::cout << std::endl;
    std::cout
    << std::endl
    << "ALPHA between dashed lines: " << std::endl
    << "-------------------------" << std::endl
    << testBlockSet.ALPHA.interpretAsString( false ) << std::endl
    << "-------------------------" << std::endl;
    std::cout << std::endl;
    std::cout
    << std::endl
    << "STOPMIX between dashed lines: " << std::endl
    << "-------------------------" << std::endl
    << testBlockSet.STOPMIX.interpretAsString( false ) << std::endl
    << "-------------------------" << std::endl;
    std::cout << std::endl;
    std::cout
    << std::endl
    << "HMIX between dashed lines: " << std::endl
    << "-------------------------" << std::endl
    << testBlockSet.HMIX.interpretAsString( false ) << std::endl
    << "-------------------------" << std::endl;
    std::cout << std::endl;
    std::cout
    << std::endl
    << "MSOFT between dashed lines: " << std::endl
    << "-------------------------" << std::endl
    << testBlockSet.MSOFT.interpretAsString( false ) << std::endl
    << "-------------------------" << std::endl;
    std::cout << std::endl;

    std::cout
    << std::endl
    << "ended successfully, I hope.";
    std::cout << std::endl;
  }  // end of if correct number of arguments was given.

  // this was a triumph! I'm making a note here:
  return EXIT_SUCCESS;
}
