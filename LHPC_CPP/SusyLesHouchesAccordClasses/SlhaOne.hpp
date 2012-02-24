/*
 * SlhaOne.hpp
 *
 *  Created on: Feb 6, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.LHPC_CPP.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#ifndef SLHAONE_HPP_
#define SLHAONE_HPP_

#include "../SlhaParser.hpp"

namespace LHPC
{
  /* this is just a collection of instances of classes derived from SlhaBlock
   * which covers all the blocks specified in SLHA1 (JHEP 0407 (2004) 036
   * [hep-ph/0311123]).
   */
  class SlhaOne
  {
  public:
    SlhaOne( SlhaParser& fileParser,
             bool const& isVerbose );
    virtual
    ~SlhaOne();

    SLHA::BlockClass::SparseSinglyIndexed< double > MODSEL;
    SLHA::BlockClass::SparseSinglyIndexed< double > SMINPUTS;
    SLHA::BlockClass::SparseSinglyIndexed< double > MINPAR;
    SLHA::BlockClass::SparseSinglyIndexed< double > EXTPAR;
    SLHA::BlockClass::SparseSinglyIndexed< double > MASS;
    SLHA::BlockClass::DenseDoublyIndexed< double > NMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > UMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > VMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > STOPMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > SBOTMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > STAUMIX;
    SLHA::BlockClass::JustSingleValue< double > ALPHA;
    SLHA::BlockClass::SparseSinglyIndexed< double > HMIX;
    SLHA::BlockClass::DenseSinglyIndexed< double > GAUGE;
    SLHA::BlockClass::SparseSinglyIndexed< double > MSOFT;
    SLHA::BlockClass::DenseDoublyIndexed< double > AU;
    SLHA::BlockClass::DenseDoublyIndexed< double > AD;
    SLHA::BlockClass::DenseDoublyIndexed< double > AE;
    SLHA::BlockClass::DenseDoublyIndexed< double > YU;
    SLHA::BlockClass::DenseDoublyIndexed< double > YD;
    SLHA::BlockClass::DenseDoublyIndexed< double > YE;
    SLHA::SlhaBlock SPINFO;


  protected:
    SlhaParser& fileParser;
    bool const& isVerbose;
  };

}

#endif /* SLHAONE_HPP_ */
