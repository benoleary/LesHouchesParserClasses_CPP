/*
 * SlhaTwo.hpp
 *
 *  Created on: Feb 22, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#ifndef SLHATWO_HPP_
#define SLHATWO_HPP_

#include "SlhaOne.hpp"

namespace LHPC
{
  /* this is just a collection of instances of classes derived from SlhaBlock
   * which covers all the blocks specified in SLHA2 (Comput. Phys. Commun. 180
   * (2009) 8 [arXiv:0801.0045 [hep-ph]]).
   */
  class SlhaTwo : public SlhaOne
  {
  public:
    SlhaTwo( SlhaParser& fileParser,
             bool const& isVerbose );
    virtual
    ~SlhaTwo();

    SLHA::BlockClass::SparseSinglyIndexed< double > QEXTPAR;
    SLHA::BlockClass::SparseSinglyIndexed< double > IMMINPAR;
    SLHA::BlockClass::SparseSinglyIndexed< double > IMEXTPAR;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMNMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMUMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMVMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMSTOPMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMSBOTMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMSTAUMIX;
    SLHA::BlockClass::JustSingleValue< double > IMALPHA;
    SLHA::BlockClass::SparseSinglyIndexed< double > IMHMIX;
    SLHA::BlockClass::DenseSinglyIndexed< double > IMGAUGE;
    SLHA::BlockClass::SparseSinglyIndexed< double > IMMSOFT;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMAU;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMAD;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMAE;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMYU;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMYD;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMYE;
    SLHA::BlockClass::DenseDoublyIndexed< double > CVHMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMCVHMIX;
    SLHA::BlockClass::DenseSinglyIndexed< double > VCKMIN;
    SLHA::BlockClass::DenseSinglyIndexed< double > IMVCKMIN;
    SLHA::BlockClass::DenseSinglyIndexed< double > VCKM;
    SLHA::BlockClass::DenseSinglyIndexed< double > IMVCKM;
    SLHA::BlockClass::DenseSinglyIndexed< double > UPMNSIN;
    SLHA::BlockClass::DenseSinglyIndexed< double > IMUPMNSIN;
    SLHA::BlockClass::DenseSinglyIndexed< double > UPMNS;
    SLHA::BlockClass::DenseSinglyIndexed< double > IMUPMNS;
    SLHA::BlockClass::DenseDoublyIndexed< double > MSQ2IN;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMMSQ2IN;
    SLHA::BlockClass::DenseDoublyIndexed< double > MSQ2;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMMSQ2;
    SLHA::BlockClass::DenseDoublyIndexed< double > MSU2IN;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMMSU2IN;
    SLHA::BlockClass::DenseDoublyIndexed< double > MSU2;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMMSU2;
    SLHA::BlockClass::DenseDoublyIndexed< double > MSD2IN;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMMSD2IN;
    SLHA::BlockClass::DenseDoublyIndexed< double > MSD2;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMMSD2;
    SLHA::BlockClass::DenseDoublyIndexed< double > MSL2IN;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMMSL2IN;
    SLHA::BlockClass::DenseDoublyIndexed< double > MSL2;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMMSL2;
    SLHA::BlockClass::DenseDoublyIndexed< double > MSE2IN;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMMSE2IN;
    SLHA::BlockClass::DenseDoublyIndexed< double > MSE2;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMMSE2;
    SLHA::BlockClass::DenseDoublyIndexed< double > MSN2IN;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMMSN2IN;
    SLHA::BlockClass::DenseDoublyIndexed< double > MSN2;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMMSN2;
    SLHA::BlockClass::DenseDoublyIndexed< double > TUIN;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMTUIN;
    SLHA::BlockClass::DenseDoublyIndexed< double > TU;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMTU;
    SLHA::BlockClass::DenseDoublyIndexed< double > TDIN;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMTDIN;
    SLHA::BlockClass::DenseDoublyIndexed< double > TD;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMTD;
    SLHA::BlockClass::DenseDoublyIndexed< double > TEIN;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMTEIN;
    SLHA::BlockClass::DenseDoublyIndexed< double > TE;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMTE;
    SLHA::BlockClass::DenseDoublyIndexed< double > TNIN;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMTNIN;
    SLHA::BlockClass::DenseDoublyIndexed< double > TN;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMTN;
    SLHA::BlockClass::DenseDoublyIndexed< double > YN;
    SLHA::BlockClass::DenseDoublyIndexed< double > USQMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMUSQMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > DSQMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMDSQMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > SELMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMSELMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > SNUMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMSNUMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > SNSMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMSNSMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > SNAMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMSNAMIX;
    SLHA::BlockClass::DenseTriplyIndexed< double > RVLAMLLEIN;
    SLHA::BlockClass::DenseTriplyIndexed< double > IMRVLAMLLEIN;
    SLHA::BlockClass::DenseTriplyIndexed< double > RVLAMLLE;
    SLHA::BlockClass::DenseTriplyIndexed< double > IMRVLAMLLE;
    SLHA::BlockClass::DenseTriplyIndexed< double > RVLAMLQDIN;
    SLHA::BlockClass::DenseTriplyIndexed< double > IMRVLAMLQDIN;
    SLHA::BlockClass::DenseTriplyIndexed< double > RVLAMLQD;
    SLHA::BlockClass::DenseTriplyIndexed< double > IMRVLAMLQD;
    SLHA::BlockClass::DenseTriplyIndexed< double > RVLAMUDDIN;
    SLHA::BlockClass::DenseTriplyIndexed< double > IMRVLAMUDDIN;
    SLHA::BlockClass::DenseTriplyIndexed< double > RVLAMUDD;
    SLHA::BlockClass::DenseTriplyIndexed< double > IMRVLAMUDD;
    SLHA::BlockClass::DenseTriplyIndexed< double > RVTLLEIN;
    SLHA::BlockClass::DenseTriplyIndexed< double > IMRVTLLEIN;
    SLHA::BlockClass::DenseTriplyIndexed< double > RVTLLE;
    SLHA::BlockClass::DenseTriplyIndexed< double > IMRVTLLE;
    SLHA::BlockClass::DenseTriplyIndexed< double > RVTLQDIN;
    SLHA::BlockClass::DenseTriplyIndexed< double > IMRVTLQDIN;
    SLHA::BlockClass::DenseTriplyIndexed< double > RVTLQD;
    SLHA::BlockClass::DenseTriplyIndexed< double > IMRVTLQD;
    SLHA::BlockClass::DenseTriplyIndexed< double > RVTUDDIN;
    SLHA::BlockClass::DenseTriplyIndexed< double > IMRVTUDDIN;
    SLHA::BlockClass::DenseTriplyIndexed< double > RVTUDD;
    SLHA::BlockClass::DenseTriplyIndexed< double > IMRVTUDD;
    SLHA::BlockClass::DenseSinglyIndexed< double > RVKAPPAIN;
    SLHA::BlockClass::DenseSinglyIndexed< double > IMRVKAPPAIN;
    SLHA::BlockClass::DenseSinglyIndexed< double > RVKAPPA;
    SLHA::BlockClass::DenseSinglyIndexed< double > IMRVKAPPA;
    SLHA::BlockClass::DenseSinglyIndexed< double > RVDIN;
    SLHA::BlockClass::DenseSinglyIndexed< double > IMRVDIN;
    SLHA::BlockClass::DenseSinglyIndexed< double > RVD;
    SLHA::BlockClass::DenseSinglyIndexed< double > IMRVD;
    SLHA::BlockClass::DenseSinglyIndexed< double > RVM2LH1;
    SLHA::BlockClass::DenseSinglyIndexed< double > IMRVM2LH1;
    SLHA::BlockClass::DenseSinglyIndexed< double > RVSNVEVIN;
    SLHA::BlockClass::DenseSinglyIndexed< double > IMRVSNVEVIN;
    SLHA::BlockClass::DenseSinglyIndexed< double > RVSNVEV;
    SLHA::BlockClass::DenseSinglyIndexed< double > IMRVSNVEV;
    SLHA::BlockClass::DenseDoublyIndexed< double > RVNMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMRVNMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > RVUMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMRVUMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > RVVMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMRVVMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > RVHMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMRVHMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > RVAMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMRVAMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > RVLMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMRVLMIX;
    SLHA::BlockClass::SparseSinglyIndexed< double > NMSSMRUN;
    SLHA::BlockClass::DenseDoublyIndexed< double > NMHMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMNMHMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > NMAMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMNMAMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > NMNMIX;
    SLHA::BlockClass::DenseDoublyIndexed< double > IMNMNMIX;

  //protected:
    // nothing.
  };

}

#endif /* SLHATWO_HPP_ */
