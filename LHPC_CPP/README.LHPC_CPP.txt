/*
 * README.LHPC_CPP.txt
 *
 *  Created on: Jan 27, 2012
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
 *      The GNU General Public License should be in
 *      LHPC_CPP/GNU_public_license.txt
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
 *      7 files in and a subdirectory in LHPC_CPP/LesHouchesEventFileClasses/:
 *      - AutomaticEventFilter.hpp
 *      - AutomaticEventFilter.cpp
 *      - FilterRule.hpp
 *      - FilterRule.cpp
 *      - LhefEvent.hpp
 *      - LhefEvent.cpp
 *      - ParticleLine.hpp
 *      - ParticleLine.cpp
 *      - InterfaceToClhepLorentzVectorClass.hpp
 *      - FilterRuleClasses/ with 6 files:
 *        - InitialOrIntermediateOrFinalState.hpp
 *        - InitialOrIntermediateOrFinalState.cpp
 *        - ParticleCode.hpp
 *        - ParticleCode.cpp
 *        - PseudorapidityCut.hpp
 *        - PseudorapidityCut.cpp
 *        - TransverseMomentumCut.hpp
 *        - TransverseMomentumCut.cpp
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
 *      - ParticleSpectrumSubsetClasses/ with 18 files:
 *        - ChargedSleptonsOneToSix.hpp
 *        - ChargedSleptonsOneToSix.cpp
 *        - CharginosOneToTwo.hpp
 *        - CharginosOneToTwo.cpp
 *        - GluinoOneGeneration.hpp
 *        - GluinoOneGeneration.cpp
 *        - MssmExtraEwsbSpinZeroBosonSet.hpp
 *        - MssmExtraEwsbSpinZeroBosonSet.cpp
 *        - NeutralinosOneToFive.hpp
 *        - NeutralinosOneToFive.cpp
 *        - NeutralinosOneToFour.hpp
 *        - NeutralinosOneToFour.cpp
 *        - NmssmExtraEwsbSpinZeroBosonSet.hpp
 *        - NmssmExtraEwsbSpinZeroBosonSet.cpp
 *        - SneutrinosOneToThree.hpp
 *        - SneutrinosOneToThree.cpp
 *        - SquarksOneToSix.hpp
 *        - SquarksOneToSix.cpp
 *      LHPC_CPP/ParticleCodesAndDataClasses/NineDigitSlhaCodes.hpp
 *      LHPC_CPP/ParticleCodesAndDataClasses/NineDigitSlhaCodes.cpp
 *      LHPC_CPP/ParticleCodesAndDataClasses/PdgData.hpp
 *      LHPC_CPP/ParticleCodesAndDataClasses/PdgData.cpp
 *      LHPC_CPP/ParticleCodesAndDataClasses/SevenDigitSlhaCodes.hpp
 *      LHPC_CPP/ParticleCodesAndDataClasses/SevenDigitSlhaCodes.cpp
 *      LHPC_CPP/SlhaSpectrumPlottingClasses/LineData.hpp
 *      LHPC_CPP/SlhaSpectrumPlottingClasses/LineData.cpp
 *      LHPC_CPP/SlhaSpectrumPlottingClasses/SpectrumDrawer.hpp
 *      LHPC_CPP/SlhaSpectrumPlottingClasses/SpectrumDrawer.cpp
 *      LHPC_CPP/SusyLesHouchesAccordClasses/BlockTypes.hpp
 *      LHPC_CPP/SusyLesHouchesAccordClasses/SlhaBlock.hpp
 *      LHPC_CPP/SusyLesHouchesAccordClasses/SlhaBlock.cpp
 *      LHPC_CPP/SusyLesHouchesAccordClasses/SlhaOne.hpp
 *      LHPC_CPP/SusyLesHouchesAccordClasses/SlhaOne.cpp
 *      LHPC_CPP/SusyLesHouchesAccordClasses/SlhaTwo.hpp
 *      LHPC_CPP/SusyLesHouchesAccordClasses/SlhaTwo.cpp
 *      LHPC_CPP/SusyLesHouchesAccordClasses/SlhaTwoWithSpheno.hpp
 *      LHPC_CPP/SusyLesHouchesAccordClasses/SlhaTwoWithSpheno.cpp
 *      6 files in LHPC_CPP/SusyLesHouchesAccordClasses/BlockClasses/:
 *      - DenseDoublyIndexed.hpp
 *      - DenseSinglyIndexed.hpp
 *      - DenseTriplyIndexed.hpp
 *      - JustSingleValue.hpp
 *      - SparseSinglyIndexed.hpp
 *      - StandardBlockTemplate.hpp
 *      LHPC_CPP/LhefParser.hpp
 *      LHPC_CPP/LhefParser.cpp
 *      LHPC_CPP/LhefParserExample.cpp
 *      LHPC_CPP/SlhaParser.hpp
 *      LHPC_CPP/SlhaParser.cpp
 *      LHPC_CPP/SlhaParserExample.cpp
 *      LHPC_CPP/Makefile
 *      and README.LHPC_CPP.txt which describes the package (copied as
 *      README.txt).
 */
 
/* CHANGELOG:
 * 29th February 2012: version 0.1 released!
 * (LHEF & SLHA parsers seem to work, spectrum plotter seems to work; after
 * some beta testing, this version will be tweaked & released as 1.0.0)
 */

/* LesHouchesParserClasses (LHPC) is a set of classes for interpretting Les
 * Houches Event File (LHEF) format files and SUSY Les Houches Accord (SLHA)
 * files. it also parses Flavor Les Houches Accord (FLHA) files, though with
 * less functionality. this LHPC_CPP set of files is the version written in
 * C++.
 * there are 2 main parts to LHPC: the LHEF parser & associated structures;
 * & the SLHA parser & associated structures. there is also code to
 * automatically plot SLHA spectra using the SLHA parser, though this requires
 * the use of external programs: gnuplot, latex, dvips, & ps2eps (or ps2epsi).
 *
 * SLHA spectrum plotter: running make will produce LhpcSpectrumPlotter.exe,
 * which can be run without any arguments to show further information on how to
 * use it.
 *
 * LHPC::LhefParser, the class for reading in events from a file in the LHEF
 * format:
 * the essential functionality of this class is already covered by the classes
 * in the LesHouches directory of an installation of the publically-available
 * code ThePEG (typically part of an installation of Herwig++). the LhefParser
 * class was written independently of the code in ThePEG, & provides an extra
 * layer of interpretation beyond just filling the HEPRUP & HEPEUP groupings
 * of the old Les Houches Accord format.
 * the intended use of LhefParser is that an instance of the class is
 * constructed with the name of the LHEF-format file that it should open, then
 * readNextEvent() is called for as long as necessary. readNextEvent() returns
 * false when the file can no longer be read, which in normal circumstances is
 * when the end of the file has been reached, though reading stops as soon as
 * an event is found which is not in the valid format, either by invalid XML,
 * or by having the wrong number of data entries on any line, or by
 * disagreement between the number of lines describing particles given in the
 * 1st line of the event & the actual number of lines describing particles
 * between "<event>" & "</event>".
 * at this basic level, the LhefParser holds a single event at a time, as a
 * LHPC::LHEF::LhefEvent, which holds the HEPRUP information (the information
 * from the 1st line of the event) directly & the HEPEUP information as a set
 * of LHPC::LHEF::ParticleLine instances, which each hold the information of a
 * single line describing a particle and its momentum from the event.
 * one can read LhefEvent.hpp & ParticleLine.hpp for the full information on
 * these classes, but I expect that, for an example LhefEvent called
 * exampleEvent, exampleEvent.getEventWeight() (or exampleEvent.XWGTUP()
 * equivalently) to get the event's weight, exampleEvent.getNumberOfParticles()
 * (or exampleEvent.NUP() equivalently) to get the number of particle lines of
 * the event, & exampleEvent[ whichLine ] (or exampleEvent.getLine( whichLine )
 * equivalently) to get the line number whichLine (the first line is 1, not 0)
 * would be the most used functions. I expect that, for each example
 * ParticleLine called exampleLine,
 * exampleLine.getXMomentum()/.getYMomentum()/.getZMomentum()/.getEnergy(), or
 * equivalently exampleLine.IPUP( 1 )/.IPUP( 2 )/.IPUP( 3 )/.IPUP( 4 ), to get
 * the particle's momentum, & exampleLine.getPrimaryMotherLineNumber, or
 * equivalently exampleLine.MOTHUP( 1 ), to get the primary mother particle
 * line number to find the source of this particle would be the most used
 * functions.
 * the further functionality mentioned above is pretty much two aspects: the
 * minor convenience of the ParticleLines having direct pointers to their
 * mother & daughter lines, and automatic collection of ParticleLine subsets
 * of the event prepared by the LHPC::LHEF::AutomaticEventFilter class. the
 * intended use of this class is as an aid to analyze an event (e.g. for
 * whether to accept it or reject it): each time a new event is read in, each
 * AutomaticEventFilter instance makes a
 * std::list< LHPC::LHEF::ParticleLine const* > of pointers to the
 * ParticleLines which pass its own FilterRule criteria (note that this does
 * not _remove_ any lines from the LhefEvent, the list is prepared in
 * addition). this could be used for example by setting up a filter to collect
 * all the lines corresponding to final-state muons or antimuons with
 * transverse momentum greater than e.g. 10 GeV, & then one can quickly find
 * how many of these occur in the last read event by asking for the size of the
 * list that the filter prepared, so that the event can be accepted or rejected
 * based on the number of muons which would pass that transverse momentum cut,
 * for instance. note that the filters do not accept or reject *events*, they
 * merely collect *lines* that are accepted or rejected by their FilterRules.
 * instances of the AutomaticEventFilter class hold a set of
 * LHPC::LHEF::FilterRule instances which are used to select which lines of the
 * last event read in. to be added to the list, the ParticleLine must pass
 * *all* the FilterRules that an AutomaticEventFilter has. more complicated
 * rules than the provided "select on transverse momentum", "select on
 * pseudorapidity", "select on PDG particle code", & "select on whether
 * initial-state, intermediate, or final-state" rules provided can be written
 * as classes derived from the FilterRule abstract base class. I hope that the
 * examples in LhefParserExample.cpp.not_compiled_by_default are clear enough.
 * the ParticleLine class provides some static functions to provide sums of
 * momenta as lines & transverse momentum sums of these lists of lines.
 * 
 * 
 * LHPC::SlhaParser, the class for reading in data from a file in the SLHA
 * format:
 * SLHA1 refers to JHEP 0407 (2004) 036 [hep-ph/0311123], and
 * SLHA2 to Comput. Phys. Commun. 180 (2009) 8 [arXiv:0801.0045 [hep-ph]].
 * the intended use of SlhaParser is that an instance of the class is
 * constructed, & then instances of derived classes of the SlhaBlock class are
 * constructed & then registered with the parser with the
 * registerBlock( LHPC::SLHA::SlhaBlock const& ) function. there are bundles of
 * blocks that automatically register their blocks with the SlhaParser given
 * to the bundle's constructor, which cover the blocks described in SLHA1 &
 * SLHA2. an instance of LHPC::SlhaOne has all the blocks in SLHA1, & an
 * instance of SlhaTwo has all the blocks mentioned in SLHA1 & in SLHA2. the
 * entries in the blocks are then filled when readFile( std::string const& ) is
 * called. the entries are accessed with operator() (various derived classes
 * use different numbers of arguments for this), or the block as a set of lines
 * (each line held as a separate std::string) can be obtained by
 * getLines( double const ), which looks for the copy of the block with scale
 * ("Q") closest to the given argument, or as a single std::string with
 * interpretAsString( double const ). I had intended to provide flexible
 * searching of the blocks as strings to accommodate non-standard blocks, but
 * this is still on the to-do list.
 * decays are only recorded if a MassSpectrum instance has been registered with
 * the SlhaParser. a registered MassSpectrum instance has its MassEigenstate
 * data members filled with masses recorded from the MASS or FMASS blocks that
 * are read from the SLHA file, & with decays filled from the decays of the
 * file. the particle codes of the decays are interpretted so that accessing
 * the decays gets references to other MassEigenstates, to simplify following
 * cascade decays.
 * I intend to include the functionality to be able to load in the central
 * values of the masses and decays of W bosons, Z bosons, & top quarks from
 * data from the Particle Data Group (PDG), but that's still on the to-do list.
 * 
 * 
 * examples:
 * examples of the intended use of the LhefParser & SlhaParser classes &
 * assorted data-organizing classes are found in LHPC_CPP/LhefParserExample.cpp
 * & LHPC_CPP/SlhaParserExample.cpp respectively. these are compiled by
 * default by the Makefile, producing LhefParserExample.exe &
 * SlhaParserExample.exe which can be used with the example LHEF & SLHA files
 * in the testing subdirectory.
 */
 
 
 
 