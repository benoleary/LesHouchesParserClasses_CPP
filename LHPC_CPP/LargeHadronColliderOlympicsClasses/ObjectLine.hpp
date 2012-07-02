/*
 * ObjectLine.hpp
 *
 *  Created on: Jun 25, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.LHPC_CPP.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#ifndef OBJECTLINE_HPP_
#define OBJECTLINE_HPP_

#include "../BOLlib/Classes/UsefulStuff.hpp"
#include "../BOLlib/Classes/VectorlikeArray.hpp"
#include "../BOLlib/Classes/StringParser.hpp"

namespace LHPC
{
  namespace LHCO
  {
    // this is a class to hold the data in a single line of an event in the
    // Large Hadron Collider Olympics format.
    class ObjectLine
    {
    public:
      static ObjectLine*
      copyObjectLine( ObjectLine const& copySource );

      ObjectLine();
      ObjectLine( ObjectLine const& copySource );
      ~ObjectLine();

      double
      operator[]( int const whichElement );
      // this returns the element of the line treating all the values as
      // doubles. it starts from 0, rather than 1 (so entry [ 2 ] is the
      // pseudorapidity, for example).
      int
      getLineNumber() const;
      int
      hash() const { return getLineNumber(); }
      int
      getObjectType() const;
      int
      typ() const { return getObjectType(); }
      double
      getPseudorapidity() const;
      double
      eta() const { return getPseudorapidity(); }
      double
      getAzimuthalAngle() const;
      double
      phi() const { return getAzimuthalAngle(); }
      double
      getTransverseMomentum() const;
      double
      pt() const { return getTransverseMomentum(); }
      double
      getInvariantMass() const;
      double
      jmass() const { return getInvariantMass(); }
      double
      getNumberOfTracks() const;
      double
      ntrk() const { return getNumberOfTracks(); }
      double
      getTagNumber() const;
      double
      btag() const { return getTagNumber(); }
      double
      getHadronicToElectromagneticEnergyRatio() const;
      double
      hadem() const { return getHadronicToElectromagneticEnergyRatio(); }
      double
      getColumnTen() const;
      double
      getColumnEleven() const;
      ObjectLine const*
      recordLine( int const lineNumber,
                  BOL::VectorlikeArray< std::string > const& lineAsStrings );


    protected:
      static int const minimumNumberOfEntries;
      // this is the minimum number of numbers expected for a valid line.

      int lineNumber;
      // the number of the line for the object within the list of the event.
      int objectType;
      // the type of object:
      // 0: photon
      // 1: electron
      // 2: muon
      // 3: hadronically-decaying tau lepton
      // 4: jet
      // 5: not defined
      // 6: missing transverse energy
      std::vector< double > valueVector;
      // the entries in the vector are, in order:
      // lineNumber, as a double,
      // objectType, as a double,
      // the pseudorapidity,
      // the azimuthal angle,
      // the transverse momentum,
      // the invariant mass,
      // the number of tracks,
      // the number for the b-tag, which has a special meaning for muons,
      // the ratio of hadronic to electromagnetic energies.
      // any further numbers have not been defined by 2012-06-29,
      // but the standard includes 2 dummy numbers. this class only requires
      // the minimum of 9 numbers, assumes that it will read 11 numbers (but
      // fills the 10th & 11th entries with NaN), yet can cope with longer
      // lines (assuming that all space-separated strings represent doubles).
    };





    inline ObjectLine*
    ObjectLine::copyObjectLine( ObjectLine const& copySource )
    {
      return new ObjectLine( copySource );
    }

    inline double
    ObjectLine::operator[]( int const whichElement )
    {
      return valueVector[ whichElement ];
    }

    inline int
    ObjectLine::getLineNumber() const
    {
      return lineNumber;
    }

    inline int
    ObjectLine::getObjectType() const
    {
      return objectType;
    }

    inline double
    ObjectLine::getPseudorapidity() const
    {
      return valueVector[ 2 ];
    }

    inline double
    ObjectLine::getAzimuthalAngle() const
    {
      return valueVector[ 3 ];
    }

    inline double
    ObjectLine::getTransverseMomentum() const
    {
      return valueVector[ 4 ];
    }

    inline double
    ObjectLine::getInvariantMass() const
    {
      return valueVector[ 5 ];
    }

    inline double
    ObjectLine::getNumberOfTracks() const
    {
      return valueVector[ 6 ];
    }

    inline double
    ObjectLine::getTagNumber() const
    {
      return valueVector[ 7 ];
    }

    inline double
    ObjectLine::getHadronicToElectromagneticEnergyRatio() const
    {
      return valueVector[ 8 ];
    }

    inline double
    ObjectLine::getColumnTen() const
    {
      return valueVector[ 9 ];
    }

    inline double
    ObjectLine::getColumnEleven() const
    {
      return valueVector[ 10 ];
    }

  }

}

#endif /* OBJECTLINE_HPP_ */
