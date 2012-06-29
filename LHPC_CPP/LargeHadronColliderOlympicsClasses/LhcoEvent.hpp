/*
 * LhcoEvent.hpp
 *
 *  Created on: Jun 29, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#ifndef LHCOEVENT_HPP_
#define LHCOEVENT_HPP_

#include <list>
#include "ObjectLine.hpp"


namespace LHPC
{
  namespace LHCO
  {
    class LhcoEvent
    {
    public:
      LhcoEvent( bool const& isVerbose );
      LhcoEvent( LhcoEvent const& copySource );
      ~LhcoEvent();

      int
      getNumberOfObjects() const;
      int
      getEventNumber() const;
      int
      getTriggerWord() const;
      ObjectLine const&
      getLine( int const whichLine ) const;
      ObjectLine const&
      operator[]( int const whichLine ) const{ return getLine( whichLine ); }
      std::list< ObjectLine const* > const&
      getPhotons() const;
      std::list< ObjectLine const* > const&
      getElectrons() const;
      std::list< ObjectLine const* > const&
      getMuons() const;
      std::list< ObjectLine const* > const&
      getTaus() const;
      std::list< ObjectLine const* > const&
      getJets() const;
      ObjectLine const*
      getMissingEnergy() const;
      std::list< ObjectLine const* > const&
      getObjectsOfType( int const whichType ) const;
      std::string const&
      getAsString() const;

      // stuff for setting up the LhcoEvent:
      int
      recordLine( std::string const& lineAsString );
      // this parses the 1st word of lineAsString and returns it, first adding
      // a new ObjectLine if appropriate, noting its pointer in the appropriate
      // std::list. if lineAsString is the start of a new event (as the line
      // begins with 0, which is also what this function will return), it
      // prepares nextEventNumber & nextTriggerWord based on this line.
      void
      prepareForNextEvent();
      // this clears objectLines, copies nextEventNumber & nextTriggerWord
      // into eventNumber & triggerWord, & prepares eventAsString.


    protected:
      static std::string const trimmingChars;
      static bool const trueForVerbosity;
      static std::string const eventCommentLine;
      static int const charactersForEventNumber;

      int numberOfObjects;
      // the number of objects listed in the event.
      int eventNumber;
      // the number of the event, given in line 0.
      int triggerWord;
      // the number encoding information about the trigger, given in line 0.
      int nextEventNumber;
      // eventNumber for the next event.
      int nextTriggerWord;
      // triggerWord for the next event.

      BOL::VectorlikeArray< ObjectLine > objectLines;

      std::list< ObjectLine const* > photonLines;
      std::list< ObjectLine const* > electronLines;
      std::list< ObjectLine const* > muonLines;
      std::list< ObjectLine const* > tauLines;
      std::list< ObjectLine const* > jetLines;
      ObjectLine const* missingEnergyLinePointer;
      std::list< ObjectLine const* > missingEnergyLines;
      std::list< ObjectLine const* > emptyList;

      bool const& isVerbose;
      std::string eventAsString;
      ObjectLine interpretingObjectLine;
      // this is for parsing the data line:
      BOL::VectorlikeArray< std::string > lineParser;
    };





    inline int
    LhcoEvent::getNumberOfObjects() const
    {
      return numberOfObjects;
    }

    inline int
    LhcoEvent::getEventNumber() const
    {
      return eventNumber;
    }

    inline int
    LhcoEvent::getTriggerWord() const
    {
      return triggerWord;
    }

    inline ObjectLine const&
    LhcoEvent::getLine( int const whichLine ) const
    {
      return objectLines[ ( whichLine - 1 ) ];
    }

    inline std::list< ObjectLine const* > const&
    LhcoEvent::getPhotons() const
    {
      return photonLines;
    }

    inline std::list< ObjectLine const* > const&
    LhcoEvent::getElectrons() const
    {
      return electronLines;
    }

    inline std::list< ObjectLine const* > const&
    LhcoEvent::getMuons() const
    {
      return muonLines;
    }

    inline std::list< ObjectLine const* > const&
    LhcoEvent::getTaus() const
    {
      return tauLines;
    }

    inline std::list< ObjectLine const* > const&
    LhcoEvent::getJets() const
    {
      return jetLines;
    }

    inline ObjectLine const*
    LhcoEvent::getMissingEnergy() const
    {
      return missingEnergyLinePointer;
    }

    inline std::list< ObjectLine const* > const&
    LhcoEvent::getObjectsOfType( int const whichType ) const
    {
      if( 1 == whichType )
      {
        return getPhotons();
      }
      else if( 2 == whichType )
      {
        return getElectrons();
      }
      else if( 3 == whichType )
      {
        return getMuons();
      }
      else if( 4 == whichType )
      {
        return getJets();
      }
      else if( 6 == whichType )
      {
        return getMissingEnergy();
      }
      else
      {
        return emptyList;
      }
    }

    inline std::string const&
    LhcoEvent::getAsString() const
    {
      return eventAsString;
    }

    inline void
    LhcoEvent::prepareForNextEvent()
    // this clears objectLines, copies nextEventNumber & nextTriggerWord
    // into eventNumber & triggerWord, & prepares eventAsString.
    {
      objectLines.clearEntries();
      eventNumber = nextEventNumber;
      triggerWord = nextTriggerWord;
      eventAsString.assign( eventCommentLine );
      eventAsString.append( "0 " );
      eventAsString.append( BOL::StringParser::intToSpacePaddedString(
                                                               nextEventNumber,
                                                  charactersForEventNumber ) );
      eventAsString.append( " " );
      eventAsString.append( BOL::StringParser::intToSpacePaddedString(
                                                               nextTriggerWord,
                                                  charactersForTriggerWord ) );
    }

  }

}

#endif /* LHCOEVENT_HPP_ */
