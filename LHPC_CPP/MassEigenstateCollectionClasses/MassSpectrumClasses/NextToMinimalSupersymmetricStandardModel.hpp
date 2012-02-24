/*
 * NextToMinimalSupersymmetricStandardModel.hpp
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

#ifndef NEXTTOMINIMALSUPERSYMMETRICSTANDARDMODEL_HPP_
#define NEXTTOMINIMALSUPERSYMMETRICSTANDARDMODEL_HPP_

#include "MinimalSupersymmetricStandardModel.hpp"
#include "ParticleSubsetClasses/NmssmExtraEwsbSpinZeroBosonSet.hpp"
#include "ParticleSubsetClasses/NeutralinosOneToFive.hpp"

namespace LHPC
{
  namespace MassSpectrumClass
  {
    class NextToMinimalSupersymmetricStandardModel :
                                                   public virtual MassSpectrum,
                                                     public Mssm,
                                         public NmssmExtraEwsbSpinZeroBosonSet,
                                                    public NeutralinosOneToFive
    {
    public:
      NextToMinimalSupersymmetricStandardModel( bool const& isVerbose,
                                       bool const neutrinosAreMajorana = false,
                              std::vector< bool >* const defaultFlags = NULL );
      virtual
      ~NextToMinimalSupersymmetricStandardModel();
    };
    typedef NextToMinimalSupersymmetricStandardModel Nmssm;

  }
  typedef MassSpectrumClass::Nmssm NmssmSpectrum;

}

#endif /* NEXTTOMINIMALSUPERSYMMETRICSTANDARDMODEL_HPP_ */
