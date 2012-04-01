/*
 * FlavorObservable.hpp
 *
 *  Created on: Apr 1, 2012 (really!)
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.LHPC_CPP.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#ifndef FLAVOROBSERVABLE_HPP_
#define FLAVOROBSERVABLE_HPP_

#include <string>
#include "../BOLlib/Classes/UsefulStuff.hpp"
#include "../BOLlib/Classes/StringParser.hpp"

namespace LHPC
{
  // this is a class to hold the information about the mass of a particle in
  // the FLHA format.
  class FlavorObservable
  {
  public:
    FlavorObservable();
    FlavorObservable( FlavorObservable const& copySource );
    ~FlavorObservable();

    double
    getValue() const;
    double
    getScale() const;
    int
    getNumberOfDaughterParticles() const;
    std::list< int >&
    getDaughterParticleList();
    std::list< int > const&
    getDaughterParticleList() const;
    void
    setValues( double const valueDouble,
               double const evaluationScale,
               std::list< int > const& daughterParticleCodes );
    void
    setFromString( std::string const& valuesString );
    std::string
    getAsString() const;


  protected:
    double valueDouble;
    double evaluationScale;
    std::list< int > daughterParticleCodes;
  };





  inline double
  FlavorObservable::getValue() const
  {
    return valueDouble;
  }

  inline double
  FlavorObservable::getScale() const
  {
    return evaluationScale;
  }

  inline int
  FlavorObservable::getNumberOfDaughterParticles() const
  {
    return (int)(daughterParticleCodes.size());
  }

  inline std::list< int >&
  FlavorObservable::getDaughterParticleList()
  {
    return daughterParticleCodes;
  }

  inline std::list< int > const&
  FlavorObservable::getDaughterParticleList() const
  {
    return daughterParticleCodes;
  }

  inline void
  FlavorObservable::setValues( double const valueDouble,
                               double const evaluationScale,
                               std::list< int > const& daughterParticleCodes )
  {
    this->valueDouble = valueDouble;
    this->evaluationScale = evaluationScale;
    this->daughterParticleCodes = daughterParticleCodes;
  }

  inline void
  FlavorObservable::setFromString( std::string const& valuesString )
  {
    std::string firstRemainder;
    std::string secondRemainder;
    valueDouble
    = BOL::StringParser::stringToDouble( BOL::StringParser::firstWordOf(
                                                                  valuesString,
                                                               &firstRemainder,
                              BOL::StringParser::whitespaceAndNewlineChars ) );
    evaluationScale
    = BOL::StringParser::stringToDouble( BOL::StringParser::firstWordOf(
                                                                firstRemainder,
                                                              &secondRemainder,
                              BOL::StringParser::whitespaceAndNewlineChars ) );
    int numberOfDaughterParticles( BOL::StringParser::stringToInt(
                                                BOL::StringParser::firstWordOf(
                                                               secondRemainder,
                                                               &firstRemainder,
                            BOL::StringParser::whitespaceAndNewlineChars ) ) );
    secondRemainder.assign( BOL::StringParser::trimFromFrontAndBack(
                                                                firstRemainder,
                              BOL::StringParser::whitespaceAndNewlineChars ) );
    while( !(secondRemainder.empty()) )
    {
      daughterParticleCodes.push_back( BOL::StringParser::stringToInt(
                                                BOL::StringParser::firstWordOf(
                                                               secondRemainder,
                                                               &firstRemainder,
                            BOL::StringParser::whitespaceAndNewlineChars ) ) );
      secondRemainder.assign( BOL::StringParser::trimFromFrontAndBack(
                                                                firstRemainder,
                              BOL::StringParser::whitespaceAndNewlineChars ) );
    }
    if( ( 0 < numberOfDaughterParticles )
        &&
        ( (size_t)numberOfDaughterParticles != daughterParticleCodes.size() ) )
    {
      std::cout
      << std::endl
      << "LHPC::warning! An FOBS line declared a different number of daughter"
      << " particles ( " << numberOfDaughterParticles << " ) to the actual"
      << " number of daughter particle codes it had ( "
      << daughterParticleCodes.size()
      << " )! The declared number is being ignored in favor of the number of"
      << " codes read in.";
      std::cout << std::endl;
    }
  }

  inline std::string
  FlavorObservable::getAsString() const
  {
    std::string returnString( BOL::StringParser::doubleToString( valueDouble,
                                                                 9,
                                                                 3 ) );
    returnString.append( "   " );
    returnString.append( BOL::StringParser::doubleToString( evaluationScale,
                                                            9,
                                                            3 ) );
    for( std::list< int >::const_iterator
         daughterIterator( daughterParticleCodes.begin() );
         daughterParticleCodes.end() != daughterIterator;
         ++daughterIterator )
    {
      returnString.append( "   " );
      returnString.append( BOL::StringParser::intToString( *daughterIterator,
                                                           9,
                                                           "",
                                                           "-",
                                                           ' ' ) );
    }
    return returnString;
  }

}

#endif /* FLAVOROBSERVABLE_HPP_ */
