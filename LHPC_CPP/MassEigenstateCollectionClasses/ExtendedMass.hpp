/*
 * ExtendedMass.hpp
 *
 *  Created on: Jan 8, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.LHPC_CPP.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#ifndef EXTENDEDMASS_HPP_
#define EXTENDEDMASS_HPP_

#include "../BOLlib/Classes/UsefulStuff.hpp"

namespace LHPC
{
  // this is a class to hold the information about the mass of a particle in
  // the FLHA format.
  class ExtendedMass
  {
  public:
    ExtendedMass();
    ExtendedMass( ExtendedMass const& copySource );
    ~ExtendedMass();

    double
    getMass() const;
    int
    getScheme() const;
    double
    getScale() const;
    void
    setValues( double const massValue,
               int const schemeType,
               double const evaluationScale );


  protected:
    double massValue;
    int schemeType;
    double evaluationScale;
  };



  inline double
  ExtendedMass::getMass() const
  {
    return massValue;
  }

  inline int
  ExtendedMass::getScheme() const
  {
    return schemeType;
  }

  inline double
  ExtendedMass::getScale() const
  {
    return evaluationScale;
  }

  inline void
  ExtendedMass::setValues( double const massValue,
                           int const schemeType,
                           double const evaluationScale )
  {
    this->massValue = massValue;
    this->schemeType = schemeType;
    this->evaluationScale = evaluationScale;
  }

}

#endif /* EXTENDEDMASS_HPP_ */
