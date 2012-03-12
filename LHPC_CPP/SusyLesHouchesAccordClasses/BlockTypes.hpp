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
#include "BlockClasses/JustSingleValueBlock.hpp"
#include "BlockClasses/SparseSinglyIndexedBlock.hpp"
#include "BlockClasses/DenseSinglyIndexedBlock.hpp"
#include "BlockClasses/DenseDoublyIndexedBlock.hpp"
#include "BlockClasses/DenseTriplyIndexedBlock.hpp"

// this is header file to just collect some headers together with some typedefs
// for convenience.

namespace LHPC
{
  namespace SLHA
  {
    typedef typename SparseSinglyIndexedBlock< double > MassBlock;
    typedef typename SparseSinglyIndexedBlock< ExtendedMass > FmassBlock;

  }  // end of SLHA namespace

}  // end of LHPC namespace

#endif /* BLOCKTYPES_HPP_ */
