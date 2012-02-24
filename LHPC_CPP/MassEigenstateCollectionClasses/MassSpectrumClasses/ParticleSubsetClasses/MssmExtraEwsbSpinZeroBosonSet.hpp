/*
 * MssmExtraEwsbSpinZeroBosonSet.hpp
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

#ifndef MSSMEXTRAEWSBSPINZEROBOSONSET_HPP_
#define MSSMEXTRAEWSBSPINZEROBOSONSET_HPP_

#include "../CodesAndDataForMassEigenstates.hpp"

namespace LHPC
{
  namespace MassSpectrumClass
  {
    class MssmExtraEwsbSpinZeroBosonSet : public virtual MassSpectrum
    {
    public:
      MssmExtraEwsbSpinZeroBosonSet( bool const& isVerbose,
                              std::vector< bool >* const defaultFlags = NULL );
      virtual
      ~MssmExtraEwsbSpinZeroBosonSet();

      MassEigenstate&
      getNeutralColorlessScalarTwo();
      MassEigenstate const&
      getNeutralColorlessScalarTwo() const;
      MassEigenstate&
      getHiggsScalarTwo(){ return getNeutralColorlessScalarTwo(); }
      MassEigenstate const&
      getHiggsScalarTwo() const{ return getNeutralColorlessScalarTwo(); }
      virtual MassEigenstate&
      getHeavyHiggs(){ return getNeutralColorlessScalarTwo(); }
      virtual MassEigenstate const&
      getHeavyHiggs() const{ return getNeutralColorlessScalarTwo(); }
      MassEigenstate&
      getNeutralColorlessPseudoscalarOne();
      MassEigenstate const&
      getNeutralColorlessPseudoscalarOne() const;
      MassEigenstate&
      getHiggsPseudoscalarOne(){ return getNeutralColorlessPseudoscalarOne(); }
      MassEigenstate const&
      getHiggsPseudoscalarOne() const{ return
                                       getNeutralColorlessPseudoscalarOne(); }
      MassEigenstate&
      getHiggsPseudoscalar(){ return getNeutralColorlessPseudoscalarOne(); }
      MassEigenstate const&
      getHiggsPseudoscalar() const{ return
                                    getNeutralColorlessPseudoscalarOne(); }
      MassEigenstate&
      getPositiveColorlessSpinZeroBosonOne();
      MassEigenstate const&
      getPositiveColorlessSpinZeroBosonOne() const;
      MassEigenstate&
      getPositiveHiggsOne(){ return getPositiveColorlessSpinZeroBosonOne(); }
      MassEigenstate const&
      getPositiveHiggsOne() const{ return
                                   getPositiveColorlessSpinZeroBosonOne(); }
      MassEigenstate&
      getPositiveHiggs(){ return getPositiveColorlessSpinZeroBosonOne(); }
      MassEigenstate const&
      getPositiveHiggs() const{ return
                                getPositiveColorlessSpinZeroBosonOne(); }
      MassEigenstate&
      getNegativeColorlessSpinZeroBosonOne();
      MassEigenstate const&
      getNegativeColorlessSpinZeroBosonOne() const;
      MassEigenstate&
      getNegativeHiggsOne(){ return getNegativeColorlessSpinZeroBosonOne(); }
      MassEigenstate const&
      getNegativeHiggsOne() const{ return
                                   getNegativeColorlessSpinZeroBosonOne(); }
      MassEigenstate&
      getNegativeHiggs(){ return getNegativeColorlessSpinZeroBosonOne(); }
      MassEigenstate const&
      getNegativeHiggs() const{ return
                                getNegativeColorlessSpinZeroBosonOne(); }
      std::vector< MassEigenstate* >&
      getNeutralScalarsAndPseudoscalars();
      std::vector< MassEigenstate* > const&
      getNeutralScalarsAndPseudoscalars() const;
      std::vector< MassEigenstate* >&
      getChargedColorlessSpinZeroBosons();
      std::vector< MassEigenstate* > const&
      getChargedColorlessSpinZeroBosons() const;
      std::vector< MassEigenstate* >&
      getEwsbSpinZeroAndOneBosons();
      std::vector< MassEigenstate* > const&
      getEwsbSpinZeroAndOneBosons() const;
      std::vector< MassEigenstate* >&
      getNeutralEwsbSpinZeroAndOneBosons();
      std::vector< MassEigenstate* > const&
      getNeutralEwsbSpinZeroAndOneBosons() const;
      std::vector< MassEigenstate* >&
      getChargedEwsbSpinZeroAndOneBosons();
      std::vector< MassEigenstate* > const&
      getChargedEwsbSpinZeroAndOneBosons() const;


    protected:
      MassEigenstate neutralColorlessScalarTwo;
      MassEigenstate neutralColorlessPseudoscalarOne;
      MassEigenstate positiveColorlessSpinZeroBosonOne;
      MassEigenstate negativeColorlessSpinZeroBosonOne;
      std::vector< MassEigenstate* > neutralScalarsAndPseudoscalarPointers;
      std::vector< MassEigenstate* > chargedColorlessSpinZeroBosonPointers;
      std::vector< MassEigenstate* > ewsbSpinZeroAndOneBosonPointers;
      std::vector< MassEigenstate* > neutralEwsbSpinZeroAndOneBosonPointers;
      std::vector< MassEigenstate* > chargedEwsbSpinZeroAndOneBosonPointers;
    };



    inline MassEigenstate&
    MssmExtraEwsbSpinZeroBosonSet::getNeutralColorlessScalarTwo()
    {
      return neutralColorlessScalarTwo;
    }

    inline MassEigenstate const&
    MssmExtraEwsbSpinZeroBosonSet::getNeutralColorlessScalarTwo() const
    {
      return neutralColorlessScalarTwo;
    }

    inline MassEigenstate&
    MssmExtraEwsbSpinZeroBosonSet::getNeutralColorlessPseudoscalarOne()
    {
      return neutralColorlessPseudoscalarOne;
    }

    inline MassEigenstate const&
    MssmExtraEwsbSpinZeroBosonSet::getNeutralColorlessPseudoscalarOne() const
    {
      return neutralColorlessPseudoscalarOne;
    }

    inline MassEigenstate&
    MssmExtraEwsbSpinZeroBosonSet::getPositiveColorlessSpinZeroBosonOne()
    {
      return positiveColorlessSpinZeroBosonOne;
    }

    inline MassEigenstate const&
    MssmExtraEwsbSpinZeroBosonSet::getPositiveColorlessSpinZeroBosonOne() const
    {
      return positiveColorlessSpinZeroBosonOne;
    }

    inline MassEigenstate&
    MssmExtraEwsbSpinZeroBosonSet::getNegativeColorlessSpinZeroBosonOne()
    {
      return negativeColorlessSpinZeroBosonOne;
    }

    inline MassEigenstate const&
    MssmExtraEwsbSpinZeroBosonSet::getNegativeColorlessSpinZeroBosonOne() const
    {
      return negativeColorlessSpinZeroBosonOne;
    }

    inline std::vector< MassEigenstate* >&
    MssmExtraEwsbSpinZeroBosonSet::getNeutralScalarsAndPseudoscalars()
    {
      return neutralScalarsAndPseudoscalarPointers;
    }

    inline std::vector< MassEigenstate* > const&
    MssmExtraEwsbSpinZeroBosonSet::getNeutralScalarsAndPseudoscalars() const
    {
      return neutralScalarsAndPseudoscalarPointers;
    }

    inline std::vector< MassEigenstate* >&
    MssmExtraEwsbSpinZeroBosonSet::getChargedColorlessSpinZeroBosons()
    {
      return chargedColorlessSpinZeroBosonPointers;
    }

    inline std::vector< MassEigenstate* > const&
    MssmExtraEwsbSpinZeroBosonSet::getChargedColorlessSpinZeroBosons() const
    {
      return chargedColorlessSpinZeroBosonPointers;
    }

    inline std::vector< MassEigenstate* >&
    MssmExtraEwsbSpinZeroBosonSet::getEwsbSpinZeroAndOneBosons()
    {
      return ewsbSpinZeroAndOneBosonPointers;
    }

    inline std::vector< MassEigenstate* > const&
    MssmExtraEwsbSpinZeroBosonSet::getEwsbSpinZeroAndOneBosons() const
    {
      return ewsbSpinZeroAndOneBosonPointers;
    }

    inline std::vector< MassEigenstate* >&
    MssmExtraEwsbSpinZeroBosonSet::getNeutralEwsbSpinZeroAndOneBosons()
    {
      return neutralEwsbSpinZeroAndOneBosonPointers;
    }

    inline std::vector< MassEigenstate* > const&
    MssmExtraEwsbSpinZeroBosonSet::getNeutralEwsbSpinZeroAndOneBosons() const
    {
      return neutralEwsbSpinZeroAndOneBosonPointers;
    }

    inline std::vector< MassEigenstate* >&
    MssmExtraEwsbSpinZeroBosonSet::getChargedEwsbSpinZeroAndOneBosons()
    {
      return chargedEwsbSpinZeroAndOneBosonPointers;
    }

    inline std::vector< MassEigenstate* > const&
    MssmExtraEwsbSpinZeroBosonSet::getChargedEwsbSpinZeroAndOneBosons() const
    {
      return chargedEwsbSpinZeroAndOneBosonPointers;
    }

  }

}

#endif /* MSSMEXTRAEWSBSPINZEROBOSONSET_HPP_ */
