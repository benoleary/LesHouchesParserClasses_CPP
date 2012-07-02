/*
 * LhcoParserExample.cpp
 *
 *  Created on: Jul 2, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.LHPC_CPP.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#include "LHCO.hpp"


int main( int argumentCount,
          char* argumentCharArray[] )
{
  if( 2 != argumentCount )
  {
    std::cout
    << std::endl
    << "this testing program requires the name of the LHCO file to read in!";
    std::cout << std::endl;
  }
  else
  {
    std::string eventFileName( argumentCharArray[ 1 ] );
    LHPC::LhcoParser testParser( eventFileName,
                                 true );
    // true as the 2nd argument so that warnings about invalid events are
    // printed.
    LHPC::LHCO::LhcoEvent const& currentEvent( testParser.getEvent() );
    bool eventSuccessfullyRead( testParser.readNextEvent() );
    if( eventSuccessfullyRead )
    {
      double energySum( 0 );
      for( int whichLine( 1 );
           currentEvent.getNumberOfObjects() >= whichLine;
           ++whichLine )
      {
        energySum += currentEvent[ whichLine ].getTransverseMomentum();
      }
      std::cout
      << std::endl
      << "the scalar sum of transverse of the particles in the 1st event is "
      << energySum;
      std::cout << std::endl;

      int numberOfEventsToRead( 10 );
      std::vector< LHPC::LHCO::LhcoEvent* > storedEvents;
      while( ( 0 < numberOfEventsToRead )
             &&
             testParser.readNextEvent() )
      {
        std::cout
        << std::endl
        << "number of electrons+positrons in this event = "
        << currentEvent.getObjectsOfType( LHPC::LHCO::LhcoEvent::electronObject
                                                                      ).size();
        double scalarSumOfJetTransverseMomenta( 0.0 );
        for( std::list< LHPC::LHCO::ObjectLine const* >::const_iterator
             jetIterator( currentEvent.getJets().begin() );
             currentEvent.getJets().end() != jetIterator;
             ++jetIterator )
        {
          scalarSumOfJetTransverseMomenta
          += (*jetIterator)->getTransverseMomentum();
        }
        std::cout
        << std::endl
        << "scalar sum of jet transverse momenta in this event = "
        << scalarSumOfJetTransverseMomenta;
        std::cout << std::endl;
        std::cout << std::endl;

        storedEvents.push_back( new LHPC::LHCO::LhcoEvent( currentEvent ) );
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

      // because we created new LhcoEvent instances with "new" above, we should
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


