/*
 * SlhaTwoWithSpheno.hpp
 *
 *  Created on: Feb 22, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#ifndef SLHATWOWITHSPHENO_HPP_
#define SLHATWOWITHSPHENO_HPP_

#include "SlhaTwo.hpp"

namespace LHPC
{
  /* this is just a collection of instances of classes derived from SlhaBlock
   * which covers all the blocks specified in SLHA2 (Comput. Phys. Commun. 180
   * (2009) 8 [arXiv:0801.0045 [hep-ph]]) & those used by SPheno (Comput. Phys.
   * Commun. 153 (2003) 275 [arXiv:hep-ph/0301101]).
   */
  class SlhaTwoWithSpheno : public SlhaTwo
  {
  public:
    SlhaTwoWithSpheno( SlhaParser& fileParser,
                       bool const& isVerbose );
    virtual
    ~SlhaTwoWithSpheno();

    SLHA::BlockClass::SparseSinglyIndexed< double > SPHENOINFO;
    SLHA::SlhaBlock SPHENOINPUT;
    SLHA::SlhaBlock SPHENOCROSSSECTIONS;
    SLHA::BlockClass::SparseSinglyIndexed< double > SPHENOLOWENERGY;

  //protected:
      // nothing.
  };

}

#endif /* SLHATWOWITHSPHENO_HPP_ */
