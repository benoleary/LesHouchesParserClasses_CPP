/*
 * FlavorObservable.cpp
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

#include "FlavorObservable.hpp"

namespace LHPC
{
  FlavorObservable::FlavorObservable() :
      valueDouble( BOL::UsefulStuff::notANumber ),
      evaluationScale( BOL::UsefulStuff::notANumber ),
      daughterParticleCodes()
  {
    // just an initialization list.
  }

  FlavorObservable::FlavorObservable( FlavorObservable const& copySource ) :
      valueDouble( copySource.valueDouble ),
      evaluationScale( copySource.evaluationScale ),
      daughterParticleCodes( copySource.daughterParticleCodes )
  {
    // just an initialization list.
  }

  FlavorObservable::~FlavorObservable()
  {
    // does nothing.
  }

}
