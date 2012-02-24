/*
 * ParticleLine.cpp
 *
 *  Created on: Jan 25, 2012
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

#include "ParticleLine.hpp"

namespace LHPC
{
  namespace LHEF
  {
    BOL::VectorlikeArray< std::string > ParticleLine::lineParser;

    ParticleLine::ParticleLine() :
        particleCode( (int)BOL::UsefulStuff::notANumber ),
        initialOrIntermediateOrFinalState( (int)BOL::UsefulStuff::notANumber ),
        primaryMotherLineNumber( (int)BOL::UsefulStuff::notANumber ),
        secondaryMotherLineNumber( (int)BOL::UsefulStuff::notANumber ),
        colorCode( (int)BOL::UsefulStuff::notANumber ),
        anticolorCode( (int)BOL::UsefulStuff::notANumber ),
        xMomentum( BOL::UsefulStuff::notANumber ),
        yMomentum( BOL::UsefulStuff::notANumber ),
        zMomentum( BOL::UsefulStuff::notANumber ),
        tMomentum( BOL::UsefulStuff::notANumber ),
        restMass( BOL::UsefulStuff::notANumber ),
        properLifetime( BOL::UsefulStuff::notANumber ),
        twiceSpin( (int)BOL::UsefulStuff::notANumber ),
        ownLineNumber( (int)BOL::UsefulStuff::notANumber ),
        primaryMotherLinePointer( NULL ),
        secondaryMotherLinePointer( NULL ),
        daughterLines()
    {
      // just an initialization list.
    }

    ParticleLine::ParticleLine( ParticleLine const& copySource ) :
        particleCode( copySource.particleCode ),
        initialOrIntermediateOrFinalState(
                                copySource.initialOrIntermediateOrFinalState ),
        primaryMotherLineNumber( copySource.primaryMotherLineNumber ),
        secondaryMotherLineNumber( copySource.secondaryMotherLineNumber ),
        colorCode( copySource.colorCode ),
        anticolorCode( copySource.anticolorCode ),
        xMomentum( copySource.xMomentum ),
        yMomentum( copySource.yMomentum ),
        zMomentum( copySource.zMomentum ),
        tMomentum( copySource.tMomentum),
        restMass( copySource.restMass ),
        properLifetime( copySource.properLifetime ),
        twiceSpin( copySource.twiceSpin ),
        ownLineNumber( (int)BOL::UsefulStuff::notANumber ),
        primaryMotherLinePointer( NULL ),
        secondaryMotherLinePointer( NULL ),
        daughterLines()
    {
      /* just an initialization list. unfortunately there's no easy way to copy
       * the mother & daughter pointers. however, that should be taken care of
       * by the copy constructor of the LhefEvent that is copying its
       * ParticleLines.
       */
    }

    ParticleLine::~ParticleLine()
    {
      // does nothing.
    }


    double
    ParticleLine::IPUP( int const whichComponent ) const
    {
      if( 1 == whichComponent )
      {
        return getXMomentum();
      }
      else if( 2 == whichComponent )
      {
        return getYMomentum();
      }
      else if( 3 == whichComponent )
      {
        return getZMomentum();
      }
      else if( 4 == whichComponent )
      {
        return getEnergy();
      }
      else if( 5 == whichComponent )
      {
        return getMass();
      }
      else
      {
        return BOL::UsefulStuff::notANumber;
      }
    }

    bool
    ParticleLine::recordLine( int const ownLineNumber,
                              std::string const& lineAsString )
    /* this interprets a string as the data it is meant to correspond to. it
     * returns false if the wrong number of data were given, & in that case
     * it sets all its entries to BOL::UsefulStuff::reallyWrongValue. it
     * returns true if all the entries were filled as expected. this function
     * also clears daughterLines.
     */
    {
      this->ownLineNumber = ownLineNumber;
      daughterLines.clear();
      primaryMotherLinePointer = NULL;
      secondaryMotherLinePointer = NULL;
      lineParser.clearEntries();
      BOL::StringParser::parseByChar( lineAsString,
                                      lineParser,
                                      BOL::StringParser::whitespaceChars );
      if( 13 != lineParser.getSize() )
        // if the wrong number of data was given...
      {
        particleCode = (int)BOL::UsefulStuff::notANumber;
        initialOrIntermediateOrFinalState = (int)BOL::UsefulStuff::notANumber;
        primaryMotherLineNumber = (int)BOL::UsefulStuff::notANumber;
        secondaryMotherLineNumber = (int)BOL::UsefulStuff::notANumber;
        colorCode = (int)BOL::UsefulStuff::notANumber;
        anticolorCode = (int)BOL::UsefulStuff::notANumber;
        xMomentum = BOL::UsefulStuff::notANumber;
        yMomentum = BOL::UsefulStuff::notANumber;
        zMomentum = BOL::UsefulStuff::notANumber;
        tMomentum = BOL::UsefulStuff::notANumber;
        restMass = BOL::UsefulStuff::notANumber;
        properLifetime = BOL::UsefulStuff::notANumber;
        twiceSpin = (int)BOL::UsefulStuff::notANumber;
        return false;
      }
      else
      {
        particleCode = BOL::StringParser::stringToInt( lineParser[ 0 ] );
        initialOrIntermediateOrFinalState
        = BOL::StringParser::stringToInt( lineParser[ 1 ] );
        primaryMotherLineNumber
        = BOL::StringParser::stringToInt( lineParser[ 2 ] );
        secondaryMotherLineNumber
        = BOL::StringParser::stringToInt( lineParser[ 3 ] );
        colorCode = BOL::StringParser::stringToInt( lineParser[ 4 ] );
        anticolorCode = BOL::StringParser::stringToInt( lineParser[ 5 ] );
        xMomentum = BOL::StringParser::stringToDouble( lineParser[ 6 ] );
        yMomentum = BOL::StringParser::stringToDouble( lineParser[ 7 ] );
        zMomentum = BOL::StringParser::stringToDouble( lineParser[ 8 ] );
        tMomentum = BOL::StringParser::stringToDouble( lineParser[ 9 ] );
        restMass = BOL::StringParser::stringToDouble( lineParser[ 10 ] );
        properLifetime = BOL::StringParser::stringToDouble( lineParser[ 11 ] );
        twiceSpin = BOL::StringParser::stringToInt( lineParser[ 12 ] );
        return true;
      }
    }

  }

}
