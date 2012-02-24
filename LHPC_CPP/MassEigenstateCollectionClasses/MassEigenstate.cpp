/*
 * MassEigenstate.cpp
 *
 *  Created on: Jan 8, 2012
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

#include "MassEigenstate.hpp"

namespace LHPC
{
  std::pair< int,
             MassEigenstate* > MassEigenstate::mapFiller( 0,
                                                          NULL );

  MassEigenstate*
  MassEigenstate::findPointerWithCode( int pdgCode,
                                       MassEigenstateCodeMap const& codeMap )
  // this finds the MassEigenstate pointer which corresponds to the requested
  // code in the given map, returning NULL if there is none.
  {
    MassEigenstate* returnPointer( NULL );
    bool flipToChargeConjugate( false );
    // codeMap only knows about positive codes, but negatives codes will
    // return charge-conjugates of the MassEigenstates with the positive codes:
    if( 0 > pdgCode )
    {
      flipToChargeConjugate = true;
      pdgCode = -pdgCode;
    }
    MassEigenstateCodeMap::const_iterator
    returnFromMap( codeMap.find( pdgCode ) );
    if( codeMap.end() != returnFromMap )
      // if pdgCode was found in codeMap...
    {
      if( flipToChargeConjugate )
      {
        returnPointer = (*returnFromMap).second->chargeConjugate;
      }
      else
      {
        returnPointer = (*returnFromMap).second;
      }
    }
    return returnPointer;
  }

  MassEigenstate::MassEigenstate( int const pdgCode,
                            MassEigenstateMapVectorBools& mapAndVectorAndBools,
                                  bool const isSelfConjugate,
                                  std::string const& asciiName,
                                  std::string const& latexName ) :
      chargeConjugate( NULL ),
      isSelfConjugateFlag( isSelfConjugate ),
      identifyingPdgCodes( 1,
                           pdgCode ),
      pdgCodeMap( mapAndVectorAndBools.getMap() ),
      massRecorded( false ),
      signedDefaultMass( BOL::UsefulStuff::notANumber ),
      absoluteDefaultMass( BOL::UsefulStuff::notANumber ),
      runningMasses(),
      decaysRecorded( false ),
      decayWidth( BOL::UsefulStuff::notANumber ),
      decaySet(),
      asciiName( asciiName ),
      latexName( latexName ),
      isVerbose( mapAndVectorAndBools.getBool() ),
      flagBools( mapAndVectorAndBools.getFlags() ),
      setOfPointersOfMassEigenstateGroup( mapAndVectorAndBools.getVector() )
  {
    constructorBodyFunction();
    /* constructorBodyFunction puts pointers to this instance into pdgCodeMap
     * for each of this instance's positive codes. if this instance has
     * negative codes, they will only get into pdgCodeMap through the
     * charge-conjugate's constructor (or by manually adding them, but that's
     * not recommended).
     */
  }

  MassEigenstate::MassEigenstate( int const firstPdgCode,
                                  int const secondPdgCode,
                            MassEigenstateMapVectorBools& mapAndVectorAndBools,
                                  bool const isSelfConjugate,
                                  std::string const& asciiName,
                                  std::string const& latexName ) :
      chargeConjugate( NULL ),
      isSelfConjugateFlag( isSelfConjugate ),
      identifyingPdgCodes( 2,
                           secondPdgCode ),
      pdgCodeMap( mapAndVectorAndBools.getMap() ),
      massRecorded( false ),
      signedDefaultMass( BOL::UsefulStuff::notANumber ),
      absoluteDefaultMass( BOL::UsefulStuff::notANumber ),
      runningMasses(),
      decaysRecorded( false ),
      decayWidth( BOL::UsefulStuff::notANumber ),
      decaySet(),
      asciiName( asciiName ),
      latexName( latexName ),
      isVerbose( mapAndVectorAndBools.getBool() ),
      flagBools( mapAndVectorAndBools.getFlags() ),
      setOfPointersOfMassEigenstateGroup( mapAndVectorAndBools.getVector() )
  {
    identifyingPdgCodes.front() = firstPdgCode;
    // this, along with the initialization of identifyingPdgCodes, sorts out
    // the 2 particle codes.
    constructorBodyFunction();
    /* constructorBodyFunction puts pointers to this instance into pdgCodeMap
     * for each of this instance's positive codes. if this instance has
     * negative codes, they will only get into pdgCodeMap through the
     * charge-conjugate's constructor (or by manually adding them, but that's
     * not recommended).
     */
  }

  MassEigenstate::MassEigenstate( std::vector< int > const& pdgCodes,
                            MassEigenstateMapVectorBools& mapAndVectorAndBools,
                                  bool const isSelfConjugate,
                                  std::string const& asciiName,
                                  std::string const& latexName ) :
      chargeConjugate( NULL ),
      isSelfConjugateFlag( isSelfConjugate ),
      identifyingPdgCodes( pdgCodes.begin(),
                           pdgCodes.end() ),
      pdgCodeMap( mapAndVectorAndBools.getMap() ),
      massRecorded( false ),
      signedDefaultMass( BOL::UsefulStuff::notANumber ),
      absoluteDefaultMass( BOL::UsefulStuff::notANumber ),
      runningMasses(),
      decaysRecorded( false ),
      decayWidth( BOL::UsefulStuff::notANumber ),
      decaySet(),
      asciiName( asciiName ),
      latexName( latexName ),
      isVerbose( mapAndVectorAndBools.getBool() ),
      flagBools( mapAndVectorAndBools.getFlags() ),
      setOfPointersOfMassEigenstateGroup( mapAndVectorAndBools.getVector() )
  {
    constructorBodyFunction();
    /* constructorBodyFunction puts pointers to this instance into pdgCodeMap
     * for each of this instance's positive codes. if this instance has
     * negative codes, they will only get into pdgCodeMap through the
     * charge-conjugate's constructor (or by manually adding them, but that's
     * not recommended).
     */
  }

  MassEigenstate::MassEigenstate( MassEigenstate const& copySource,
                         MassEigenstateMapVectorBools& mapAndVectorAndBools ) :
      chargeConjugate( NULL ),
      isSelfConjugateFlag( copySource.isSelfConjugateFlag ),
      identifyingPdgCodes( copySource.identifyingPdgCodes.begin(),
                           copySource.identifyingPdgCodes.end() ),
      pdgCodeMap( mapAndVectorAndBools.getMap() ),
      massRecorded( false ),
      signedDefaultMass( BOL::UsefulStuff::notANumber ),
      absoluteDefaultMass( BOL::UsefulStuff::notANumber ),
      runningMasses(),
      decaysRecorded( false ),
      decayWidth( BOL::UsefulStuff::notANumber ),
      decaySet(),
      asciiName( copySource.asciiName ),
      latexName( copySource.latexName ),
      isVerbose( mapAndVectorAndBools.getBool() ),
      flagBools( mapAndVectorAndBools.getFlags() ),
      setOfPointersOfMassEigenstateGroup( mapAndVectorAndBools.getVector() )
  {
    constructorBodyFunction();
    /* constructorBodyFunction puts pointers to this instance into pdgCodeMap
     * for each of this instance's positive codes. if this instance has
     * negative codes, they will only get into pdgCodeMap through the
     * charge-conjugate's constructor (or by manually adding them, but that's
     * not recommended).
     */
  }

  // this last version copies as the charge conjugate of copySource:
  MassEigenstate::MassEigenstate( MassEigenstate& copySource,
                                  std::string const& asciiName,
                                  std::string const& latexName ) :
      chargeConjugate( &copySource ),
      isSelfConjugateFlag( copySource.isSelfConjugateFlag ),
      identifyingPdgCodes( copySource.identifyingPdgCodes.size(),
                           -(copySource.getCode()) ),
      pdgCodeMap( copySource.pdgCodeMap ),
      massRecorded( false ),
      signedDefaultMass( BOL::UsefulStuff::notANumber ),
      absoluteDefaultMass( BOL::UsefulStuff::notANumber ),
      runningMasses(),
      decaysRecorded( false ),
      decayWidth( BOL::UsefulStuff::notANumber ),
      decaySet(),
      asciiName( asciiName ),
      latexName( latexName ),
      isVerbose( copySource.isVerbose ),
      flagBools( copySource.flagBools ),
      setOfPointersOfMassEigenstateGroup(
                                copySource.setOfPointersOfMassEigenstateGroup )
  {
    // this for loop doesn't copy the front element because it was already
    // copied into all the entries when identifyingPdgCodes was initialized.
    for( int codeIndex( copySource.identifyingPdgCodes.size() - 1 );
         0 < codeIndex;
         --codeIndex )
    {
      identifyingPdgCodes[ codeIndex ]
      = -(copySource.identifyingPdgCodes[ codeIndex ]);
      // this gets the negatives of copySource's codes.
    }
    copySource.setChargeConjugate( this );
    constructorBodyFunction();
    /* constructorBodyFunction sorts out getting copySource's negative codes
     * into pdgCodeMap as the positive codes for this instance, with this
     * instance's pointer.
     */
  }

  MassEigenstate::~MassEigenstate()
  {
    // does nothing, since there was no dynamic allocation.
  }


  MassEigenstate&
  MassEigenstate::addCode( int extraCode )
  {
    if( isSelfConjugate() )
    {
      if( 0 > extraCode )
      {
        extraCode = -extraCode;
      }
      // self-conjugate states was forced into having only positive codes.
    }
    else if( NULL != chargeConjugate )
    {
      // the charge-conjugate should get the opposite-signed codes, &
      // pdgCodeMap should know which is mapped to by the positive code:
      chargeConjugate->identifyingPdgCodes.push_back( -extraCode );
      if( 0 > extraCode )
      {
        chargeConjugate->addToCodeMap( -extraCode );
      }
    }
    // extraCode can now be added to identifyingPdgCodes:
    identifyingPdgCodes.push_back( extraCode );
    // if the code is positive, pdgCodeMap should know that it maps to this
    // instance:
    if( 0 <= extraCode )
    {
      addToCodeMap( extraCode );
    }
    return *this;
  }

  void
  MassEigenstate::setToBeChargeConjugate(
                                        MassEigenstate* const chargeConjugate )
  {
    this->chargeConjugate = chargeConjugate;
    /* not only does the pointer to the charge conjugate need to be set, but
     * the codes need to be signed. chargeConjugate's codes are assumed to be
     * the right signs.
     */
    for( int codeIndex( identifyingPdgCodes.size() - 1 );
         0 <= codeIndex;
         --codeIndex )
    {
      MassEigenstateCodeMap::iterator codeFinder;
      if( chargeConjugate->hasCode( identifyingPdgCodes[ codeIndex ] ) )
        // if chargeConjugate should have the positive code...
      {
        // ensure that pdgCodeMap associates chargeConjugate with the positive
        // code:
        codeFinder = pdgCodeMap.find( identifyingPdgCodes[ codeIndex ] );
        if( pdgCodeMap.end() != codeFinder )
        {
          codeFinder->second = chargeConjugate;
        }
        identifyingPdgCodes[ codeIndex ] = -(identifyingPdgCodes[ codeIndex ]);
        // now this instance can set its code to be negative.
      }
    }
  }

  void
  MassEigenstate::recordMass( double const massValue,
                              int const schemeType,
                              double const evaluationScale )
  {
    runningMasses.newEnd().setValues( massValue,
                                      schemeType,
                                      evaluationScale );
    runningMassesAsVector.push_back( runningMasses.getPointer(
                                              runningMasses.getLastIndex() ) );
    // I decided to keep a separate std::vector in parallel rather than
    // constantly converting runningMasses with getAsVector(...).
    if( !massRecorded
        ||
        ( 0 == schemeType ) )
      // the pole mass becomes the default mass, unless there is no mass
      // already recorded.
    {
      signedDefaultMass = massValue;
      if( 0 > massValue )
      {
        absoluteDefaultMass = -massValue;
      }
      else
      {
        absoluteDefaultMass = massValue;
      }
      massRecorded = true;
    }
  }

  void
  MassEigenstate::constructorBodyFunction()
  {
    if( isSelfConjugate() )
    {
      chargeConjugate = this;
      for( int codeIndex( identifyingPdgCodes.size() - 1 );
           0 <= codeIndex;
           --codeIndex )
      {
        if( 0 > identifyingPdgCodes[ codeIndex ] )
        {
          identifyingPdgCodes[ codeIndex ] = -identifyingPdgCodes[ codeIndex ];
        }
        addToCodeMap( identifyingPdgCodes[ codeIndex ] );
        // self-conjugate particles are set to have only positive codes, &
        // the codes are mapped to this MassEigenstate.
      }
    }
    else
    {
      for( int codeIndex( identifyingPdgCodes.size() - 1 );
           0 <= codeIndex;
           --codeIndex )
      {
        if( 0 < identifyingPdgCodes[ codeIndex ] )
        {
          addToCodeMap( identifyingPdgCodes[ codeIndex ] );
          /* only this instance's positive codes are mapped to its pointer in
           * pdgCodeMap. if this instance has negative codes, they will only
           * get into pdgCodeMap through the charge-conjugate's constructor (or
           * by manually adding them, but that's not recommended).
           */
        }
      }
    }
    setOfPointersOfMassEigenstateGroup.push_back( this );
  }

}
