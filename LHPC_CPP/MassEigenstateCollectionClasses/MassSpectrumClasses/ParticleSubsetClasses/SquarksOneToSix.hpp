/*
 * SquarksOneToSix.hpp
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

#ifndef SQUARKSONETOSIX_HPP_
#define SQUARKSONETOSIX_HPP_

#include "../CodesAndDataForMassEigenstates.hpp"

namespace LHPC
{
  namespace MassSpectrumClass
  {
    class SquarksOneToSix : public virtual MassSpectrum
    {
    public:
      SquarksOneToSix( bool const& isVerbose,
                       std::vector< bool >* const defaultFlags = NULL );
      virtual
      ~SquarksOneToSix();

      MassEigenstate&
      getAntisdownOne();
      MassEigenstate const&
      getAntisdownOne() const;
      MassEigenstate&
      getAntisdownL(){ return getAntisdownOne(); }
      MassEigenstate const&
      getAntisdownL() const{ return getAntisdownOne(); }
      MassEigenstate&
      getSdownOne();
      MassEigenstate const&
      getSdownOne() const;
      MassEigenstate&
      getSdownL(){ return getSdownOne(); }
      MassEigenstate const&
      getSdownL() const{ return getSdownOne(); }
      MassEigenstate&
      getAntisdownTwo();
      MassEigenstate const&
      getAntisdownTwo() const;
      MassEigenstate&
      getAntisstrangeL(){ return getAntisdownTwo(); }
      MassEigenstate const&
      getAntisstrangeL() const{ return getAntisdownTwo(); }
      MassEigenstate&
      getSdownTwo();
      MassEigenstate const&
      getSdownTwo() const;
      MassEigenstate&
      getStrangeL(){ return getSdownTwo(); }
      MassEigenstate const&
      getStrangeL() const{ return getSdownTwo(); }
      MassEigenstate&
      getAntisdownThree();
      MassEigenstate const&
      getAntisdownThree() const;
      MassEigenstate&
      getAntisbottomOne(){ return getAntisdownThree(); }
      MassEigenstate const&
      getAntisbottomOne() const{ return getAntisdownThree(); }
      MassEigenstate&
      getSdownThree();
      MassEigenstate const&
      getSdownThree() const;
      MassEigenstate&
      getSbottomOne(){ return getSdownThree(); }
      MassEigenstate const&
      getSbottomOne() const{ return getSdownThree(); }
      MassEigenstate&
      getAntisdownFour();
      MassEigenstate const&
      getAntisdownFour() const;
      MassEigenstate&
      getAntisdownR(){ return getAntisdownFour(); }
      MassEigenstate const&
      getAntisdownR() const{ return getAntisdownFour(); }
      MassEigenstate&
      getSdownFour();
      MassEigenstate const&
      getSdownFour() const;
      MassEigenstate&
      getSdownR(){ return getSdownFour(); }
      MassEigenstate const&
      getSdownR() const{ return getSdownFour(); }
      MassEigenstate&
      getAntisdownFive();
      MassEigenstate const&
      getAntisdownFive() const;
      MassEigenstate&
      getAntisstrangeR(){ return getAntisdownFive(); }
      MassEigenstate const&
      getAntisstrangeR() const{ return getAntisdownFive(); }
      MassEigenstate&
      getSdownFive();
      MassEigenstate const&
      getSdownFive() const;
      MassEigenstate&
      getStrangeR(){ return getSdownFive(); }
      MassEigenstate const&
      getStrangeR() const{ return getSdownFive(); }
      MassEigenstate&
      getAntisdownSix();
      MassEigenstate const&
      getAntisdownSix() const;
      MassEigenstate&
      getAntisbottomTwo(){ return getAntisdownSix(); }
      MassEigenstate const&
      getAntisbottomTwo() const{ return getAntisdownSix(); }
      MassEigenstate&
      getSdownSix();
      MassEigenstate const&
      getSdownSix() const;
      MassEigenstate&
      getSbottomTwo(){ return getSdownSix(); }
      MassEigenstate const&
      getSbottomTwo() const{ return getSdownSix(); }
      MassEigenstate&
      getSupOne();
      MassEigenstate const&
      getSupOne() const;
      MassEigenstate&
      getSupL(){ return getSupOne(); }
      MassEigenstate const&
      getSupL() const{ return getSupOne(); }
      MassEigenstate&
      getAntisupOne();
      MassEigenstate const&
      getAntisupOne() const;
      MassEigenstate&
      getAntisupL(){ return getAntisupOne(); }
      MassEigenstate const&
      getAntisupL() const{ return getAntisupOne(); }
      MassEigenstate&
      getSupTwo();
      MassEigenstate const&
      getSupTwo() const;
      MassEigenstate&
      getScharmL(){ return getSupTwo(); }
      MassEigenstate const&
      getScharmL() const{ return getSupTwo(); }
      MassEigenstate&
      getAntisupTwo();
      MassEigenstate const&
      getAntisupTwo() const;
      MassEigenstate&
      getAntischarmL(){ return getAntisupTwo(); }
      MassEigenstate const&
      getAntischarmL() const{ return getAntisupTwo(); }
      MassEigenstate&
      getSupThree();
      MassEigenstate const&
      getSupThree() const;
      MassEigenstate&
      getStopOne(){ return getSupThree(); }
      MassEigenstate const&
      getStopOne() const{ return getSupThree(); }
      MassEigenstate&
      getAntisupThree();
      MassEigenstate const&
      getAntisupThree() const;
      MassEigenstate&
      getAntistopOne(){ return getAntisupThree(); }
      MassEigenstate const&
      getAntistopOne() const{ return getAntisupThree(); }
      MassEigenstate&
      getSupFour();
      MassEigenstate const&
      getSupFour() const;
      MassEigenstate&
      getSupR(){ return getSupFour(); }
      MassEigenstate const&
      getSupR() const{ return getSupFour(); }
      MassEigenstate&
      getAntisupFour();
      MassEigenstate const&
      getAntisupFour() const;
      MassEigenstate&
      getAntisupR(){ return getAntisupFour(); }
      MassEigenstate const&
      getAntisupR() const{ return getAntisupFour(); }
      MassEigenstate&
      getSupFive();
      MassEigenstate const&
      getSupFive() const;
      MassEigenstate&
      getScharmR(){ return getSupFive(); }
      MassEigenstate const&
      getScharmR() const{ return getSupFive(); }
      MassEigenstate&
      getAntisupFive();
      MassEigenstate const&
      getAntisupFive() const;
      MassEigenstate&
      getAntischarmR(){ return getAntisupFive(); }
      MassEigenstate const&
      getAntischarmR() const{ return getAntisupFive(); }
      MassEigenstate&
      getSupSix();
      MassEigenstate const&
      getSupSix() const;
      MassEigenstate&
      getStopTwo(){ return getSupSix(); }
      MassEigenstate const&
      getStopTwo() const{ return getSupSix(); }
      MassEigenstate&
      getAntisupSix();
      MassEigenstate const&
      getAntisupSix() const;
      MassEigenstate&
      getAntistopTwo(){ return getAntisupSix(); }
      MassEigenstate const&
      getAntistopTwo() const{ return getAntisupSix(); }
      std::vector< MassEigenstate* >&
      getDownAntisquarks();
      std::vector< MassEigenstate* > const&
      getDownAntisquarks() const;
      std::vector< MassEigenstate* >&
      getDownSquarks();
      std::vector< MassEigenstate* > const&
      getDownSquarks() const;
      std::vector< MassEigenstate* >&
      getUpSquarks();
      std::vector< MassEigenstate* > const&
      getUpSquarks() const;
      std::vector< MassEigenstate* >&
      getUpAntisquarks();
      std::vector< MassEigenstate* > const&
      getUpAntisquarks() const;
      std::vector< MassEigenstate* >&
      getSquarkPointers();
      std::vector< MassEigenstate* > const&
      getSquarkPointers() const;
      std::vector< MassEigenstate* >&
      getAntisquarkPointers();
      std::vector< MassEigenstate* > const&
      getAntisquarkPointers() const;


    protected:
      MassEigenstate antisdownOne;
      MassEigenstate sdownOne;
      MassEigenstate antisdownTwo;
      MassEigenstate sdownTwo;
      MassEigenstate antisdownThree;
      MassEigenstate sdownThree;
      MassEigenstate antisdownFour;
      MassEigenstate sdownFour;
      MassEigenstate antisdownFive;
      MassEigenstate sdownFive;
      MassEigenstate antisdownSix;
      MassEigenstate sdownSix;
      MassEigenstate supOne;
      MassEigenstate antisupOne;
      MassEigenstate supTwo;
      MassEigenstate antisupTwo;
      MassEigenstate supThree;
      MassEigenstate antisupThree;
      MassEigenstate supFour;
      MassEigenstate antisupFour;
      MassEigenstate supFive;
      MassEigenstate antisupFive;
      MassEigenstate supSix;
      MassEigenstate antisupSix;
      std::vector< MassEigenstate* > downAntisquarkPointers;
      std::vector< MassEigenstate* > downSquarkPointers;
      std::vector< MassEigenstate* > upSquarkPointers;
      std::vector< MassEigenstate* > upAntisquarkPointers;
      std::vector< MassEigenstate* > squarkPointers;
      std::vector< MassEigenstate* > antisquarkPointers;
    };



    inline MassEigenstate&
    SquarksOneToSix::getAntisdownOne()
    {
      return antisdownOne;
    }

    inline MassEigenstate const&
    SquarksOneToSix::getAntisdownOne() const
    {
      return antisdownOne;
    }

    inline MassEigenstate&
    SquarksOneToSix::getSdownOne()
    {
      return sdownOne;
    }

    inline MassEigenstate const&
    SquarksOneToSix::getSdownOne() const
    {
      return sdownOne;
    }

    inline MassEigenstate&
    SquarksOneToSix::getAntisdownTwo()
    {
      return antisdownTwo;
    }

    inline MassEigenstate const&
    SquarksOneToSix::getAntisdownTwo() const
    {
      return antisdownTwo;
    }

    inline MassEigenstate&
    SquarksOneToSix::getSdownTwo()
    {
      return sdownTwo;
    }

    inline MassEigenstate const&
    SquarksOneToSix::getSdownTwo() const
    {
      return sdownTwo;
    }

    inline MassEigenstate&
    SquarksOneToSix::getAntisdownThree()
    {
      return antisdownThree;
    }

    inline MassEigenstate const&
    SquarksOneToSix::getAntisdownThree() const
    {
      return antisdownThree;
    }

    inline MassEigenstate&
    SquarksOneToSix::getSdownThree()
    {
      return sdownThree;
    }

    inline MassEigenstate const&
    SquarksOneToSix::getSdownThree() const
    {
      return sdownThree;
    }

    inline MassEigenstate&
    SquarksOneToSix::getAntisdownFour()
    {
      return antisdownFour;
    }

    inline MassEigenstate const&
    SquarksOneToSix::getAntisdownFour() const
    {
      return antisdownFour;
    }

    inline MassEigenstate&
    SquarksOneToSix::getSdownFour()
    {
      return sdownFour;
    }

    inline MassEigenstate const&
    SquarksOneToSix::getSdownFour() const
    {
      return sdownFour;
    }

    inline MassEigenstate&
    SquarksOneToSix::getAntisdownFive()
    {
      return antisdownFive;
    }

    inline MassEigenstate const&
    SquarksOneToSix::getAntisdownFive() const
    {
      return antisdownFive;
    }

    inline MassEigenstate&
    SquarksOneToSix::getSdownFive()
    {
      return sdownFive;
    }

    inline MassEigenstate const&
    SquarksOneToSix::getSdownFive() const
    {
      return sdownFive;
    }

    inline MassEigenstate&
    SquarksOneToSix::getAntisdownSix()
    {
      return antisdownSix;
    }

    inline MassEigenstate const&
    SquarksOneToSix::getAntisdownSix() const
    {
      return antisdownSix;
    }

    inline MassEigenstate&
    SquarksOneToSix::getSdownSix()
    {
      return sdownSix;
    }

    inline MassEigenstate const&
    SquarksOneToSix::getSdownSix() const
    {
      return sdownSix;
    }

    inline MassEigenstate&
    SquarksOneToSix::getSupOne()
    {
      return supOne;
    }

    inline MassEigenstate const&
    SquarksOneToSix::getSupOne() const
    {
      return supOne;
    }

    inline MassEigenstate&
    SquarksOneToSix::getAntisupOne()
    {
      return antisupOne;
    }

    inline MassEigenstate const&
    SquarksOneToSix::getAntisupOne() const
    {
      return antisupOne;
    }

    inline MassEigenstate&
    SquarksOneToSix::getSupTwo()
    {
      return supTwo;
    }

    inline MassEigenstate const&
    SquarksOneToSix::getSupTwo() const
    {
      return supTwo;
    }

    inline MassEigenstate&
    SquarksOneToSix::getAntisupTwo()
    {
      return antisupTwo;
    }

    inline MassEigenstate const&
    SquarksOneToSix::getAntisupTwo() const
    {
      return antisupTwo;
    }

    inline MassEigenstate&
    SquarksOneToSix::getSupThree()
    {
      return supThree;
    }

    inline MassEigenstate const&
    SquarksOneToSix::getSupThree() const
    {
      return supThree;
    }

    inline MassEigenstate&
    SquarksOneToSix::getAntisupThree()
    {
      return antisupThree;
    }

    inline MassEigenstate const&
    SquarksOneToSix::getAntisupThree() const
    {
      return antisupThree;
    }

    inline MassEigenstate&
    SquarksOneToSix::getSupFour()
    {
      return supFour;
    }

    inline MassEigenstate const&
    SquarksOneToSix::getSupFour() const
    {
      return supFour;
    }

    inline MassEigenstate&
    SquarksOneToSix::getAntisupFour()
    {
      return antisupFour;
    }

    inline MassEigenstate const&
    SquarksOneToSix::getAntisupFour() const
    {
      return antisupFour;
    }

    inline MassEigenstate&
    SquarksOneToSix::getSupFive()
    {
      return supFive;
    }

    inline MassEigenstate const&
    SquarksOneToSix::getSupFive() const
    {
      return supFive;
    }

    inline MassEigenstate&
    SquarksOneToSix::getAntisupFive()
    {
      return antisupFive;
    }

    inline MassEigenstate const&
    SquarksOneToSix::getAntisupFive() const
    {
      return antisupFive;
    }

    inline MassEigenstate&
    SquarksOneToSix::getSupSix()
    {
      return supSix;
    }

    inline MassEigenstate const&
    SquarksOneToSix::getSupSix() const
    {
      return supSix;
    }

    inline MassEigenstate&
    SquarksOneToSix::getAntisupSix()
    {
      return antisupSix;
    }

    inline MassEigenstate const&
    SquarksOneToSix::getAntisupSix() const
    {
      return antisupSix;
    }

    inline std::vector< MassEigenstate* >&
    SquarksOneToSix::getDownAntisquarks()
    {
      return downAntisquarkPointers;
    }

    inline std::vector< MassEigenstate* > const&
    SquarksOneToSix::getDownAntisquarks() const
    {
      return downAntisquarkPointers;
    }

    inline std::vector< MassEigenstate* >&
    SquarksOneToSix::getDownSquarks()
    {
      return downSquarkPointers;
    }

    inline std::vector< MassEigenstate* > const&
    SquarksOneToSix::getDownSquarks() const
    {
      return downSquarkPointers;
    }

    inline std::vector< MassEigenstate* >&
    SquarksOneToSix::getUpSquarks()
    {
      return upSquarkPointers;
    }

    inline std::vector< MassEigenstate* > const&
    SquarksOneToSix::getUpSquarks() const
    {
      return upSquarkPointers;
    }

    inline std::vector< MassEigenstate* >&
    SquarksOneToSix::getUpAntisquarks()
    {
      return upAntisquarkPointers;
    }

    inline std::vector< MassEigenstate* > const&
    SquarksOneToSix::getUpAntisquarks() const
    {
      return upAntisquarkPointers;
    }

    inline std::vector< MassEigenstate* >&
    SquarksOneToSix::getSquarkPointers()
    {
      return squarkPointers;
    }

    inline std::vector< MassEigenstate* > const&
    SquarksOneToSix::getSquarkPointers() const
    {
      return squarkPointers;
    }

    inline std::vector< MassEigenstate* >&
    SquarksOneToSix::getAntisquarkPointers()
    {
      return antisquarkPointers;
    }

    inline std::vector< MassEigenstate* > const&
    SquarksOneToSix::getAntisquarkPointers() const
    {
      return antisquarkPointers;
    }

  }

}

#endif /* SQUARKSONETOSIX_HPP_ */
