/*
 * UsefulStuff.cpp
 *
 *  Created on: Jan 6, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.LHPC_CPP.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#include "UsefulStuff.hpp"

namespace BOL
{
  bool UsefulStuff::randomSeedNotYetSet( true );

  double const UsefulStuff::notANumber( NAN );
  std::string const UsefulStuff::nanString( "NaN (\"Not a Number\")" );

}
