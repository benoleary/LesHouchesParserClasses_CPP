/*
 * NeutralinosOneToFive.hpp
 *
 *  Created on: Jan 27, 2012
 *      Author: oleary
 */

#ifndef NEUTRALINOSONETOFIVE_HPP_
#define NEUTRALINOSONETOFIVE_HPP_

#include "../CodesAndDataForMassEigenstates.hpp"
#include "NeutralinosOneToFour.hpp"

namespace LHPC
{
  namespace MassSpectrumClass
  {
    class NeutralinosOneToFive : public virtual MassSpectrum,
                                 public NeutralinosOneToFour
    {
    public:
      NeutralinosOneToFive( bool const& isVerbose,
                            std::vector< bool >* const defaultFlags = NULL );
      virtual
      ~NeutralinosOneToFive();

      MassEigenstate&
      getNeutralinoFive();
      MassEigenstate const&
      getNeutralinoFive() const;


    protected:
      MassEigenstate neutralinoFive;
    };



    inline MassEigenstate&
    NeutralinosOneToFive::getNeutralinoFive()
    {
      return neutralinoFive;
    }

    inline MassEigenstate const&
    NeutralinosOneToFive::getNeutralinoFive() const
    {
      return neutralinoFive;
    }

  }

}

#endif /* NEUTRALINOSONETOFIVE_HPP_ */
