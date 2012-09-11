#
# Makefile for C++ LesHouchesParserClasses.
#     Author: Ben O'Leary (benjamin.oleary@gmail.com)
#      Copyright 2012 Ben O'Leary
#
#      This file is part of LesHouchesParserClasses, released under the
#      GNU General Public License. Please see the accompanying
#      README.LHPC_CPP.txt file for a full list of files, brief documentation
#      on how to use these classes, and further details on the license.
#
#

SHELL=/bin/sh

CC=g++
CCOBJFLAGS=-c -Wall -O3 -I./include/
CCEXEFLAGS=-Wall -O3 -I./include/
LDFLAGS= -L./lib/ -lLHPC -L./include/BOLlib/lib/ -lBOLlib
AR=ar
ARFLAGS=rcs
LHEFDIR=source/LesHouchesEventFileClasses
MECDIR=source/MassEigenstateCollectionClasses
MECMSCDIR=$(MECDIR)/MassSpectrumClasses
SLHADIR=source/SusyLesHouchesAccordClasses
SOURCES=source/LesHouchesEventFileClasses/AutomaticEventFilter.cpp \
 source/LesHouchesEventFileClasses/FilterRule.cpp \
 source/LesHouchesEventFileClasses/LhefEvent.cpp \
 source/LesHouchesEventFileClasses/LhefParser.cpp \
 source/LesHouchesEventFileClasses/ParticleLine.cpp \
 $(LHEFDIR)/FilterRuleClasses/InitialOrIntermediateOrFinalState.cpp \
 $(LHEFDIR)/FilterRuleClasses/ParticleCode.cpp \
 $(LHEFDIR)/FilterRuleClasses/PseudorapidityCut.cpp \
 $(LHEFDIR)/FilterRuleClasses/TransverseMomentumCut.cpp \
 source/LargeHadronColliderOlympicsClasses/FourMomentum.cpp \
 source/LargeHadronColliderOlympicsClasses/LhcoEvent.cpp \
 source/LargeHadronColliderOlympicsClasses/LhcoParser.cpp \
 source/LargeHadronColliderOlympicsClasses/ObjectLine.cpp \
 source/MassEigenstateCollectionClasses/ExtendedMass.cpp \
 source/MassEigenstateCollectionClasses/MassEigenstate.cpp \
 source/MassEigenstateCollectionClasses/MassSpectrum.cpp \
 source/MassEigenstateCollectionClasses/SpectrumUpdater.cpp \
 source/MassEigenstateCollectionClasses/RunningConstant.cpp \
 source/MassEigenstateCollectionClasses/RunningConstantError.cpp \
 $(MECDIR)/MassSpectrumClasses/MinimalSupersymmetricStandardModel.cpp \
 $(MECDIR)/MassSpectrumClasses/NextToMinimalSupersymmetricStandardModel.cpp \
 $(MECDIR)/MassSpectrumClasses/StandardModel.cpp \
 $(MECMSCDIR)/ParticleSubsetClasses/ChargedSleptonsOneToSix.cpp \
 $(MECMSCDIR)/ParticleSubsetClasses/CharginosOneToTwo.cpp \
 $(MECMSCDIR)/ParticleSubsetClasses/GluinoOneGeneration.cpp \
 $(MECMSCDIR)/ParticleSubsetClasses/MssmExtraEwsbSpinZeroBosonSet.cpp \
 $(MECMSCDIR)/ParticleSubsetClasses/NeutralinosOneToFive.cpp \
 $(MECMSCDIR)/ParticleSubsetClasses/NeutralinosOneToFour.cpp \
 $(MECMSCDIR)/ParticleSubsetClasses/NmssmExtraEwsbSpinZeroBosonSet.cpp \
 $(MECMSCDIR)/ParticleSubsetClasses/SneutrinosOneToThree.cpp \
 $(MECMSCDIR)/ParticleSubsetClasses/SquarksOneToSix.cpp \
 source/ParticleCodesAndDataClasses/NineDigitSlhaCodes.cpp \
 source/ParticleCodesAndDataClasses/PdgData.cpp \
 source/ParticleCodesAndDataClasses/SevenDigitSlhaCodes.cpp \
 source/SlhaSpectrumPlottingClasses/LineData.cpp \
 source/SlhaSpectrumPlottingClasses/SpectrumPlotter.cpp \
 source/SusyLesHouchesAccordClasses/FlavorObservable.cpp \
 source/SusyLesHouchesAccordClasses/FlavorObservableError.cpp \
 source/SusyLesHouchesAccordClasses/FlhaOne.cpp \
 source/SusyLesHouchesAccordClasses/SlhaOne.cpp \
 source/SusyLesHouchesAccordClasses/SlhaParser.cpp \
 source/SusyLesHouchesAccordClasses/SlhaTwo.cpp \
 source/SusyLesHouchesAccordClasses/SlhaTwoWithSpheno.cpp \
 source/SusyLesHouchesAccordClasses/BlockClasses/BaseSlhaBlock.cpp \
 source/SusyLesHouchesAccordClasses/BlockClasses/BaseStringBlock.cpp \
 source/SusyLesHouchesAccordClasses/BlockClasses/LinesAsStringsBlock.cpp \
 source/SusyLesHouchesAccordClasses/BlockClasses/SameNameBlockSet.cpp \
 $(SLHADIR)/BlockClasses/InterpreterClasses/BlockInterpreter.cpp \
 $(SLHADIR)/BlockClasses/InterpreterClasses/LinesAsStrings.cpp
OBJECTS=$(SOURCES:.cpp=.o)
BOLLIBFILE=include/BOLlib/lib/libBOLlib.a
LIBRARYFILE=lib/libLHPC.a
PLOTTERCPP= source/LhpcSpectrumPlotter.cpp
PLOTTERGEXE=bin/LhpcSpectrumPlotter.exe
LHCOEGCPP= source/LhcoParserExample.cpp
LHCOEGEXE=bin/LhcoParserExample.exe
LHEFEGCPP= source/LhefParserExample.cpp
LHEFEGEXE=bin/LhefParserExample.exe
SLHAEGCPP= source/SlhaParserExample.cpp
SLHAEGEXE=bin/SlhaParserExample.exe
EXES=$(PLOTTERGEXE) $(LHCOEGEXE) $(LHEFEGEXE) $(SLHAEGEXE)

all: $(BOLLIBFILE) $(OBJECTS) $(LIBRARYFILE) $(EXES)

lib: $(OBJECTS) $(LIBRARYFILE)
	\rm -rf $(OBJECTS)
	
.PHONY: all lib clean

$(BOLLIBFILE):
	$(MAKE) -C ./include/BOLlib/ lib

$(OBJECTS): %.o: %.cpp $(BOLLIBFILE)
	$(CC) $(CCOBJFLAGS) $< -o $@

$(LIBRARYFILE): $(BOLLIBFILE) $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $(OBJECTS)

$(PLOTTERGEXE): $(LIBRARYFILE)
	$(CC) $(CCEXEFLAGS) -o $@ $(PLOTTERCPP) $(LDFLAGS)

$(LHCOEGEXE): $(LIBRARYFILE)
	$(CC) $(CCEXEFLAGS) -o $@ $(LHCOEGCPP) $(LDFLAGS)

$(LHEFEGEXE): $(LIBRARYFILE)
	$(CC) $(CCEXEFLAGS) -o $@ $(LHEFEGCPP) $(LDFLAGS)

$(SLHAEGEXE): $(LIBRARYFILE)
	$(CC) $(CCEXEFLAGS) -o $@ $(SLHAEGCPP) $(LDFLAGS)

clean:
	\rm -f $(OBJECTS) $(LIBRARYFILE) $(EXES)
