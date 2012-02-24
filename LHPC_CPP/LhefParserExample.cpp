/*
 * LesHouchesParserClasses_tester.cpp
 *
 *  Created on: Jan 26, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.LHPC_CPP.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#include "LhefParser.hpp"
#include "LesHouchesEventFileClasses/FilterRuleClasses/InitialOrIntermediateOrFinalState.hpp"
#include "LesHouchesEventFileClasses/FilterRuleClasses/ParticleCode.hpp"
#include "LesHouchesEventFileClasses/FilterRuleClasses/TransverseMomentumCut.hpp"
#include "ParticleCodesAndData/SevenDigitSlhaCodes.hpp"

class exampleRule : public LHPC::LHEF::FilterRule
{
public:
  exampleRule();
  virtual
  ~exampleRule();

  virtual bool
  operator()( LHPC::LHEF::ParticleLine const& lineToCheck ) const;

//protected:
  // nothing.
};

exampleRule::exampleRule() :
    LHPC::LHEF::FilterRule( true )
// FilterRule needs to know if it returns true or false if the test by
// operator() is successful.
{
  // just an initialization list.
}

exampleRule::~exampleRule()
{
  // does nothing.
}

bool
exampleRule::operator()( LHPC::LHEF::ParticleLine const& lineToCheck ) const
{
  double sillyDouble( lineToCheck.getEnergy() );
  if( 0.0 != sillyDouble )
  {
    // make sure that sillyDouble is positive:
    if( 0.0 > sillyDouble )
    {
      sillyDouble = -sillyDouble;
    }
    // keep multiplying sillyDouble by 10 until it's bigger than 1:
    while( 1.0 > sillyDouble );
    {
      sillyDouble = ( 10.0 * sillyDouble );
    }
    // keep dividing sillyDouble by 10 until it's less than 10:
    while( 1.0 < sillyDouble );
    {
      sillyDouble = ( 0.1 * sillyDouble );
    }
    // now sillyDouble is between 1.0 & 9.9999...
    if( 5.0 < sillyDouble )
    {
      return acceptRatherThanReject;
    }
    else
    {
      return !acceptRatherThanReject;
    }
  }
  else
  {
    return acceptRatherThanReject;
  }
}

//.not_compiled_by_default
int main( int argumentCount,
          char* argumentCharArray[] )
{
  if( 2 != argumentCount )
  {
    std::cout
    << std::endl
    << "this testing program requires the name of the LHEF file to read in!";
    std::cout << std::endl;
  }
  else
  {
    std::string eventFileName( argumentCharArray[ 1 ] );
    LHPC::LhefParser testParser( eventFileName,
                                 true );
    // true as the 2nd argument so that warnings about invalid events are
    // printed.
    LHPC::LHEF::LhefEvent const& currentEvent( testParser.getEvent() );
    bool eventSuccessfullyRead( testParser.readNextEvent() );
    if( eventSuccessfullyRead )
    {
      double energySum( 0 );
      for( int whichLine( 1 );
           currentEvent.getNumberOfParticles() >= whichLine;
           ++whichLine )
      {
        energySum += currentEvent[ whichLine ].getEnergy();
      }
      std::cout
      << std::endl
      << "the sum of energies of the particles in the 1st event (including"
      << " initial state & intermediate particles) is " << energySum;
      std::cout << std::endl;

      // now we set up some filter rules.

      /* I set up typedefs (like aliases) for the descriptive FilterRuleClass
       * names because with their namespace etc., they get a bit long:
       * FilterOnState is equivalent to
       * FilterRuleClass::InitialOrIntermediateOrFinalState,
       * FilterOnParticleCode
       * is equivalent to
       * FilterRuleClass::ParticleCode,
       * FilterOnPseudorapidity
       * is equivalent to
       * FilterRuleClass::PseudorapidityCut,
       * FilterOnTransverseMomentum
       * is equivalent to
       * FilterRuleClass::TransverseMomentumCut.
       */

      // 1st, some transverse momentum cuts:
      LHPC::LHEF::FilterOnTransverseMomentum acceptPtOverThreeHundred( 300.0,
                                                                       true );
      // this will only take particle lines with transverse momentum *greater*
      // than 300.0 GeV.
      LHPC::LHEF::FilterOnTransverseMomentum rejecttPtOverOneThousand( 1000.0,
                                                                       false );
      // this will only take particle lines with transverse momentum *less*
      // than 1000.0 GeV.
      LHPC::LHEF::FilterOnTransverseMomentum acceptPtOverFifty( 50.0,
                                                                true );

      // next, selecting on whether the particle is initial-state,
      // intermediate, or final-state:
      LHPC::LHEF::FilterOnState takeOnlyInitialStates( -1,
                                                       true );
      // LHPC::LHEF::FilterOnState::initialState is equivalent to -1 here.
      LHPC::LHEF::FilterRuleClass::InitialOrIntermediateOrFinalState
      takeOnlyIntermediateStates( LHPC::LHEF::FilterOnState::intermediateState,
                                  true );
      // LHPC::LHEF::FilterOnState::intermediateState is equivalent to 2 here.
      LHPC::LHEF::FilterOnState
      takeOnlyFinalStates( LHPC::LHEF::FilterOnState::finalState,
                           true );
      // LHPC::LHEF::FilterOnState::finalState is equivalent to 1 here.

      // next, selecting on which type of particle the line is describing,
      // based on its PDG particle code. the code lists need to be prepared:
      std::vector< int > jetCodes;
      // lots of different ways of adding the codes:
      jetCodes.push_back( 1 );  // downs
      jetCodes.push_back( -1 );  // antidowns
      jetCodes.push_back( LHPC::PDGVII::upQuark );  // ups
      jetCodes.push_back( -LHPC::PDGVII::upQuark );  // antiups
      jetCodes.push_back( LHPC::PDGVII::strangeQuark );  // stranges
      jetCodes.push_back( LHPC::PDGVII::strangeAntiquark );  // antistranges
      jetCodes.push_back( LHPC::PDGVII::upTwo );  // charms
      jetCodes.push_back( LHPC::PDGVII::antiupTwo );  // anticharms
      jetCodes.push_back( LHPC::PDGVII::downThree );  // bottoms
      jetCodes.push_back( -LHPC::PDGVII::downThree );  // antibottoms
      // another way of setting up a std::vector< int > is to construct it with
      // a size & then set the elements directly:
      std::vector< int > charginoCodes( 2 );
      charginoCodes[ 0 ] = 1000024;
      charginoCodes[ 1 ] = LHPC::SevenDigitSlhaCodes::negativeCharginoOne;
      // making use of a convoluted solution for setting up a constant
      // std::vector with heterogeneous elements:
      std::vector< int > const
      detectorEscaperCodes(
      BOL::StdVectorFiller< int >( LHPC::PDGVII::neutrinoOne
                                )( LHPC::PDGVII::antineutrinoOne
                                )( LHPC::PDGVII::neutrinoTwo
                                )( LHPC::PDGVII::antineutrinoTwo
                                )( LHPC::PDGVII::neutrinoThree
                                )( LHPC::PDGVII::antineutrinoThree
                            ).end( LHPC::PDGVII::neutralinoOne ) );
      /* (BOL::StdVectorFiller sets up a temporary non-const vector, taking
       * the 1st element as its constructor's argument, pushes
       * back subsequent elements with operator(), & finally pushes back the
       * last element & passes a reference to this vector
       * to the const vector's constructor with end( lastElement ) so that the
       * const vector is constructed with a copy constructor on the temporary
       * vector.
       */
      // now that the code lists have been set up, the filter rules can be
      // set up:
      LHPC::LHEF::FilterRuleClass::ParticleCode takeOnlyJets( jetCodes,
                                                              true );
      LHPC::LHEF::FilterOnParticleCode takeOnlyCharginos( charginoCodes,
                                                          true );
      LHPC::LHEF::FilterOnParticleCode takeOnlyInvisible( detectorEscaperCodes,
                                                          true );
      LHPC::LHEF::FilterOnParticleCode
      ignoreZBosons( LHPC::SevenDigitSlhaCodes::zBoson,
                     false );

      // at this point, the filters can be set up with various filter rule
      // combinations:
      LHPC::LHEF::AutomaticEventFilter anyCharginoFilter;
      anyCharginoFilter.addFilterRule( takeOnlyCharginos );
      testParser.registerFilter( anyCharginoFilter );
      std::list< LHPC::LHEF::ParticleLine const* >&
      anyCharginoLines( anyCharginoFilter.getFilteredLines() );

      LHPC::LHEF::AutomaticEventFilter onlyHardCharginoFilter;
      onlyHardCharginoFilter.addFilterRule( takeOnlyCharginos );
      onlyHardCharginoFilter.addFilterRule( acceptPtOverThreeHundred );
      testParser.registerFilter( onlyHardCharginoFilter );
      std::list< LHPC::LHEF::ParticleLine const* >&
      onlyHardCharginoLines( onlyHardCharginoFilter.getFilteredLines() );

      LHPC::LHEF::AutomaticEventFilter onlyFinalStateJetsFilter;
      onlyFinalStateJetsFilter.addFilterRule( takeOnlyJets );
      onlyFinalStateJetsFilter.addFilterRule( takeOnlyFinalStates );
      testParser.registerFilter( onlyFinalStateJetsFilter );

      LHPC::LHEF::AutomaticEventFilter onlyHardFinalStateJetsFilter;
      onlyHardFinalStateJetsFilter.addFilterRule( takeOnlyJets );
      onlyHardFinalStateJetsFilter.addFilterRule( takeOnlyFinalStates );
      onlyHardFinalStateJetsFilter.addFilterRule( acceptPtOverFifty );
      testParser.registerFilter( onlyHardFinalStateJetsFilter );
      std::list< LHPC::LHEF::ParticleLine const* >&
      onlyHardFinalStateJetLines(
                             onlyHardFinalStateJetsFilter.getFilteredLines() );

      LHPC::LHEF::AutomaticEventFilter detectorEscapersFilter;
      detectorEscapersFilter.addFilterRule( takeOnlyInvisible );
      detectorEscapersFilter.addFilterRule( takeOnlyFinalStates );
      testParser.registerFilter( detectorEscapersFilter );
      std::list< LHPC::LHEF::ParticleLine const* >&
      invisibleLines( detectorEscapersFilter.getFilteredLines() );
      LHPC::LHEF::ParticleLine sumOfInvisibleLine;

      int numberOfEventsToRead( 10 );
      std::vector< LHPC::LHEF::LhefEvent* > storedEvents;
      while( ( 0 < numberOfEventsToRead )
             &&
             testParser.readNextEvent() )
      {
        std::cout
        << std::endl
        << "number of charginos in this event = " << anyCharginoLines.size();
        std::cout
        << std::endl
        << "number of charginos with pT > 300.0 in this event = "
        << onlyHardCharginoLines.size();
        std::cout
        << std::endl
        << "number of final-state jets with pT > 50.0 in this event = "
        << onlyHardFinalStateJetsFilter.getFilteredLines().size();
        std::cout
        << std::endl
        << "effective mass (scalar sum of pT) of hard jets of this event = "
        << LHPC::LHEF::ParticleLine::scalarSumOfTransverseMomentum(
                                                  onlyHardFinalStateJetLines );
        std::cout
        << std::endl
        << "total pT (vector sum) of hard jets of this event = "
        << LHPC::LHEF::ParticleLine::transverseMomentumOfVectorSum(
                                                  onlyHardFinalStateJetLines );
        std::cout << std::endl;
        if( !(onlyHardFinalStateJetLines.empty()) )
        {
          onlyHardFinalStateJetLines.sort(
                    &LHPC::LHEF::ParticleLine::isLowToHighTransverseMomentum );
          std::cout
          << std::endl
          << "line for jet with greatest pT is line number "
          << onlyHardFinalStateJetLines.back()->getOwnLineNumber()
          << ", with pT = "
          << onlyHardFinalStateJetLines.back()->getTransverseMomentum();
        }
        std::cout
        << std::endl
        << "number of invisible particles escaping the detector in this event"
        << " = " << invisibleLines.size();
        std::cout << ", total missing transverse momentum = "
        << LHPC::LHEF::ParticleLine::sumMomentaAsLine( sumOfInvisibleLine,
                                                       invisibleLines
                                                      ).getTransverseMomentum()
        /* convoluted example to show that
         * LHPC::LHEF::ParticleLine::sumMomentaAsLine returns a reference
         * to the ParticleLine that it uses to store the sum of the momenta.
         */
        << " (actual total energy carried by sum of invisible particles = "
        << sumOfInvisibleLine.getEnergy() << ")";
        // sumOfInvisibleLine still has the momemtum sum from
        // LHPC::LHEF::ParticleLine::sumMomentaAsLine.
        std::cout << std::endl;
        std::cout << std::endl;

        storedEvents.push_back( new LHPC::LHEF::LhefEvent( currentEvent ) );
        // recording the event for later by making a copy.
        --numberOfEventsToRead;
      }
      int eventsInFile( 11 - numberOfEventsToRead );
      // there was the initial event that was read in too...
      while( testParser.readNextEvent() )
      {
        ++eventsInFile;
      }
      std::cout
      << std::endl
      << "number of events in this file = " << eventsInFile;
      std::cout << std::endl << std::endl;

      // because we created new LhefEvent instances with "new" above, we should
      // delete them once we're done with them:
      for( int deletionIndex( storedEvents.size() - 1 );
           0 <= deletionIndex;
           --deletionIndex )
      {
        delete storedEvents.at( deletionIndex );
      }
    }  // end of if 1st event was successfully read.
  }  // end of if correct number of arguments was given.

  // this was a triumph! I'm making a note here:
  return EXIT_SUCCESS;
}
