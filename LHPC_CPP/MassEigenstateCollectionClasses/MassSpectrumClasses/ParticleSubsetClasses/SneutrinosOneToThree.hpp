/*
 * SneutrinosOneToThree.hpp
 *
 *  Created on: Jan 18, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses.
 *
 *      LesHouchesParserClasses is free software: you can redistribute it
 *      and/or modify it under the terms of the GNU General Public License as
 *      published by the Free Software Foundation, either version 3 of the
 *      License, or (at your option) any later version.
 *
 *      LesHouchesParserClasses is distributed in the hope that it will be
 *      useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with LesHouchesParserClasses.  If not, see
 *      <http://www.gnu.org/licenses/>.
 *
 *      The GNU General Public License should be in GNU_public_license.txt
 *      the C++ files of LesHouchesParserClasses are:
 *      LHPC_CPP/BOLlib/Classes/AsciiXmlParser.hpp
 *      LHPC_CPP/BOLlib/Classes/AsciiXmlParser.cpp
 *      LHPC_CPP/BOLlib/Classes/CommentedTextParser.hpp
 *      LHPC_CPP/BOLlib/Classes/CommentedTextParser.hpp
 *      LHPC_CPP/BOLlib/Classes/StdVectorFiller.hpp
 *      LHPC_CPP/BOLlib/Classes/StringParser.hpp
 *      LHPC_CPP/BOLlib/Classes/StringParser.cpp
 *      LHPC_CPP/BOLlib/Classes/UsefulStuff.hpp
 *      LHPC_CPP/BOLlib/Classes/UsefulStuff.cpp
 *      LHPC_CPP/BOLlib/Classes/VectorlikeArray.hpp
 *      LHPC_CPP/LesHouchesEventFileClasses/AutomaticEventFilter.hpp
 *      LHPC_CPP/LesHouchesEventFileClasses/AutomaticEventFilter.cpp
 *      LHPC_CPP/LesHouchesEventFileClasses/FilterRule.hpp
 *      LHPC_CPP/LesHouchesEventFileClasses/FilterRule.cpp
 *      LHPC_CPP/LesHouchesEventFileClasses/LhefEvent.hpp
 *      LHPC_CPP/LesHouchesEventFileClasses/LhefEvent.cpp
 *      LHPC_CPP/LesHouchesEventFileClasses/ParticleLine.hpp
 *      LHPC_CPP/LesHouchesEventFileClasses/ParticleLine.cpp
 *      6 files in LHPC_CPP/LesHouchesEventFileClasses/FilterRuleClasses/:
 *      - ParticleCode.hpp
 *      - ParticleCode.cpp
 *      - PseudorapidityCut.hpp
 *      - PseudorapidityCut.cpp
 *      - TransverseMomentumCut.hpp
 *      - TransverseMomentumCut.cpp
 *      LHPC_CPP/MassEigenstateCollectionClasses/ExtendedMass.hpp
 *      LHPC_CPP/MassEigenstateCollectionClasses/ExtendedMass.cpp
 *      LHPC_CPP/MassEigenstateCollectionClasses/MapAndVectorAndBools.hpp
 *      LHPC_CPP/MassEigenstateCollectionClasses/MassSpectrum.hpp
 *      LHPC_CPP/MassEigenstateCollectionClasses/MassSpectrum.cpp
 *      6 files and a subdirectory in
 *      LHPC_CPP/MassEigenstateCollectionClasses/MassSpectrumClasses/:
 *      - CodesAndDataForMassEigenstates.hpp
 *      - ParticleCode.hpp
 *      - ParticleCode.cpp
 *      - MinimalSupersymmetricStandardModel.hpp
 *      - MinimalSupersymmetricStandardModel.cpp
 *      - PseudorapidityCut.hpp
 *      - PseudorapidityCut.cpp
 *      - NextToMinimalSupersymmetricStandardModel.hpp
 *      - NextToMinimalSupersymmetricStandardModel.cpp
 *      - StandardModel.hpp
 *      - StandardModel.cpp
 *      - ParticleSpectrumSubsetClasses/ with 14 files:
 *        - ChargedSleptonsOneToSix.hpp
 *        - ChargedSleptonsOneToSix.cpp
 *        - CharginosOneToTwo.hpp
 *        - CharginosOneToTwo.cpp
 *        - GluinoOneGeneration.hpp
 *        - GluinoOneGeneration.cpp
 *        - MssmExtraEwsbSpinZeroBosonSet.hpp
 *        - MssmExtraEwsbSpinZeroBosonSet.cpp
 *        - NeutralinosOneToFour.hpp
 *        - NeutralinosOneToFour.cpp
 *        - SneutrinosOneToThree.hpp
 *        - SneutrinosOneToThree.cpp
 *        - SquarksOneToSix.hpp
 *        - SquarksOneToSix.cpp
 *      LHPC_CPP/ParticleCodesAndData/NineDigitSlhaCodes.hpp
 *      LHPC_CPP/ParticleCodesAndData/NineDigitSlhaCodes.cpp
 *      LHPC_CPP/ParticleCodesAndData/PdgData.hpp
 *      LHPC_CPP/ParticleCodesAndData/PdgData.cpp
 *      LHPC_CPP/ParticleCodesAndData/SevenDigitSlhaCodes.hpp
 *      LHPC_CPP/ParticleCodesAndData/SevenDigitSlhaCodes.cpp
 *      LHPC_CPP/LhefParser.hpp
 *      LHPC_CPP/LhefParser.cpp
 *      LHPC_CPP/SlhaParser.hpp
 *      LHPC_CPP/SlhaParser.cpp
 *      and README.LHPC_CPP.txt which describes the package.
 */

#ifndef SNEUTRINOSONETOTHREE_HPP_
#define SNEUTRINOSONETOTHREE_HPP_

#include "../CodesAndDataForMassEigenstates.hpp"

namespace LHPC
{
  namespace MassSpectrumClass
  {
    class SneutrinosOneToThree : public virtual MassSpectrum
    {
    public:
      SneutrinosOneToThree( bool const& isVerbose,
                            std::vector< bool >* const defaultFlags = NULL );
      virtual
      ~SneutrinosOneToThree();

      MassEigenstate&
      getAntisneutrinoOne();
      MassEigenstate const&
      getAntisneutrinoOne() const;
      MassEigenstate&
      getElectronAntisneutrinoL(){ return getAntisneutrinoOne(); }
      MassEigenstate const&
      getElectronAntisneutrinoL() const{ return getAntisneutrinoOne(); }
      MassEigenstate&
      getSneutrinoOne();
      MassEigenstate const&
      getSneutrinoOne() const;
      MassEigenstate&
      getElectronSneutrinoL(){ return getSneutrinoOne(); }
      MassEigenstate const&
      getElectronSneutrinoL() const{ return getSneutrinoOne(); }
      MassEigenstate&
      getAntisneutrinoTwo();
      MassEigenstate const&
      getAntisneutrinoTwo() const;
      MassEigenstate&
      getMuonAntisneutrinoL(){ return getAntisneutrinoTwo(); }
      MassEigenstate const&
      getMuonAntisneutrinoL() const{ return getAntisneutrinoTwo(); }
      MassEigenstate&
      getSneutrinoTwo();
      MassEigenstate const&
      getSneutrinoTwo() const;
      MassEigenstate&
      getMuonSneutrinoL(){ return getSneutrinoTwo(); }
      MassEigenstate const&
      getMuonSneutrinoL() const{ return getSneutrinoTwo(); }
      MassEigenstate&
      getAntisneutrinoThree();
      MassEigenstate const&
      getAntisneutrinoThree() const;
      MassEigenstate&
      getTauAntisneutrinoL(){ return getAntisneutrinoThree(); }
      MassEigenstate const&
      getTauAntisneutrinoL() const{ return getAntisneutrinoThree(); }
      MassEigenstate&
      getSneutrinoThree();
      MassEigenstate const&
      getSneutrinoThree() const;
      MassEigenstate&
      getTauSneutrinoL(){ return getSneutrinoThree(); }
      MassEigenstate const&
      getTauSneutrinoL() const{ return getSneutrinoThree(); }
      std::vector< MassEigenstate* >&
      getAntisneutrinos();
      std::vector< MassEigenstate* > const&
      getAntisneutrinos() const;
      std::vector< MassEigenstate* >&
      getSneutrinos();
      std::vector< MassEigenstate* > const&
      getSneutrinos() const;


    protected:
      MassEigenstate antisneutrinoOne;
      MassEigenstate sneutrinoOne;
      MassEigenstate antisneutrinoTwo;
      MassEigenstate sneutrinoTwo;
      MassEigenstate antisneutrinoThree;
      MassEigenstate sneutrinoThree;
      std::vector< MassEigenstate* > antisneutrinoPointers;
      std::vector< MassEigenstate* > sneutrinoPointers;
    };



    inline MassEigenstate&
    SneutrinosOneToThree::getAntisneutrinoOne()
    {
      return antisneutrinoOne;
    }

    inline MassEigenstate const&
    SneutrinosOneToThree::getAntisneutrinoOne() const
    {
      return antisneutrinoOne;
    }

    inline MassEigenstate&
    SneutrinosOneToThree::getSneutrinoOne()
    {
      return sneutrinoOne;
    }

    inline MassEigenstate const&
    SneutrinosOneToThree::getSneutrinoOne() const
    {
      return sneutrinoOne;
    }

    inline MassEigenstate&
    SneutrinosOneToThree::getAntisneutrinoTwo()
    {
      return antisneutrinoTwo;
    }

    inline MassEigenstate const&
    SneutrinosOneToThree::getAntisneutrinoTwo() const
    {
      return antisneutrinoTwo;
    }

    inline MassEigenstate&
    SneutrinosOneToThree::getSneutrinoTwo()
    {
      return sneutrinoTwo;
    }

    inline MassEigenstate const&
    SneutrinosOneToThree::getSneutrinoTwo() const
    {
      return sneutrinoTwo;
    }

    inline MassEigenstate&
    SneutrinosOneToThree::getAntisneutrinoThree()
    {
      return antisneutrinoThree;
    }

    inline MassEigenstate const&
    SneutrinosOneToThree::getAntisneutrinoThree() const
    {
      return antisneutrinoThree;
    }

    inline MassEigenstate&
    SneutrinosOneToThree::getSneutrinoThree()
    {
      return sneutrinoThree;
    }

    inline MassEigenstate const&
    SneutrinosOneToThree::getSneutrinoThree() const
    {
      return sneutrinoThree;
    }
    inline std::vector< MassEigenstate* >&
    SneutrinosOneToThree::getAntisneutrinos()
    {
      return antisneutrinoPointers;
    }

    inline std::vector< MassEigenstate* > const&
    SneutrinosOneToThree::getAntisneutrinos() const
    {
      return antisneutrinoPointers;
    }

    inline std::vector< MassEigenstate* >&
    SneutrinosOneToThree::getSneutrinos()
    {
      return sneutrinoPointers;
    }

    inline std::vector< MassEigenstate* > const&
    SneutrinosOneToThree::getSneutrinos() const
    {
      return sneutrinoPointers;
    }

  }

}

#endif /* SNEUTRINOSONETOTHREE_HPP_ */
