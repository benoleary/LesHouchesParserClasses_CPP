/*
 * BlockTypes.hpp
 *
 *  Created on: Feb 26, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#ifndef BLOCKTYPES_HPP_
#define BLOCKTYPES_HPP_

#include "../MassEigenstateCollectionClasses/ExtendedMass.hpp"
#include "BlockClasses/SameNameBlockSet.hpp"
#include "SlhaBlock.hpp"
#include "BlockClasses/JustSingleValue.hpp"
#include "BlockClasses/SparseSinglyIndexed.hpp"
#include "BlockClasses/DenseSinglyIndexed.hpp"
#include "BlockClasses/DenseDoublyIndexed.hpp"
#include "BlockClasses/DenseTriplyIndexed.hpp"

// this is header file to just collect some headers together with some typedefs
// for convenience.

namespace LHPC
{
  namespace SLHA
  {
    typedef BlockClass::SparseSinglyIndexed< double > MassBlock;
    typedef BlockClass::SparseSinglyIndexed< ExtendedMass > FmassBlock;

  }  // end of SLHA namespace

}  // end of LHPC namespace

#endif /* BLOCKTYPES_HPP_ */
