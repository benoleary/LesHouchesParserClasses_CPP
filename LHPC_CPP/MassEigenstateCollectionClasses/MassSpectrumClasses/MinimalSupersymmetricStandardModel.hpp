/*
 * MinimalSupersymmetricStandardModel.hpp
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

#ifndef MINIMALSUPERSYMMETRICSTANDARDMODEL_HPP_
#define MINIMALSUPERSYMMETRICSTANDARDMODEL_HPP_

#include "StandardModel.hpp"
#include "ParticleSubsetClasses/MssmExtraEwsbSpinZeroBosonSet.hpp"
#include "ParticleSubsetClasses/ChargedSleptonsOneToSix.hpp"
#include "ParticleSubsetClasses/SneutrinosOneToThree.hpp"
#include "ParticleSubsetClasses/SquarksOneToSix.hpp"
#include "ParticleSubsetClasses/NeutralinosOneToFour.hpp"
#include "ParticleSubsetClasses/CharginosOneToTwo.hpp"
#include "ParticleSubsetClasses/GluinoOneGeneration.hpp"

namespace LHPC
{
  namespace MassSpectrumClass
  {
    class MinimalSupersymmetricStandardModel : public virtual MassSpectrum,
                                               public StandardModel,
                                          public MssmExtraEwsbSpinZeroBosonSet,
                                               public ChargedSleptonsOneToSix,
                                               public SneutrinosOneToThree,
                                               public SquarksOneToSix,
                                               public NeutralinosOneToFour,
                                               public CharginosOneToTwo,
                                               public GluinoOneGeneration
    {
    public:
      MinimalSupersymmetricStandardModel( bool const& isVerbose,
                                       bool const neutrinosAreMajorana = false,
                                          bool const flavorConserving = false,
                              std::vector< bool >* const defaultFlags = NULL );
      virtual
      ~MinimalSupersymmetricStandardModel();
    };
    typedef MinimalSupersymmetricStandardModel MSSM;

  }
  typedef MassSpectrumClass::MinimalSupersymmetricStandardModel MssmSpectrum;

}

#endif /* MINIMALSUPERSYMMETRICSTANDARDMODEL_HPP_ */
