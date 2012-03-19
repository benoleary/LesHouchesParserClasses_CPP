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
CCFLAGS= -Wall
CCOBJFLAGS= -c
CCEXEFLAGS=
LDFLAGS= -L./ -lLHPC_CPP
AR=ar
ARFLAGS=rcs
LHEFDIR=LesHouchesEventFileClasses
MECDIR=MassEigenstateCollectionClasses
MECMSCDIR=$(MECDIR)/MassSpectrumClasses
SLHADIR=SusyLesHouchesAccordClasses
SOURCES=BOLlib/Classes/AsciiXmlParser.cpp \
 BOLlib/Classes/BasicObserved.cpp \
 BOLlib/Classes/BasicObserver.cpp \
 BOLlib/Classes/CommentedTextParser.cpp \
 BOLlib/Classes/StringParser.cpp \
 BOLlib/Classes/UsefulStuff.cpp \
 LesHouchesEventFileClasses/AutomaticEventFilter.cpp \
 LesHouchesEventFileClasses/FilterRule.cpp \
 LesHouchesEventFileClasses/LhefEvent.cpp \
 LesHouchesEventFileClasses/LhefParser.cpp \
 LesHouchesEventFileClasses/ParticleLine.cpp \
 $(LHEFDIR)/FilterRuleClasses/InitialOrIntermediateOrFinalState.cpp \
 $(LHEFDIR)/FilterRuleClasses/ParticleCode.cpp \
 $(LHEFDIR)/FilterRuleClasses/PseudorapidityCut.cpp \
 $(LHEFDIR)/FilterRuleClasses/TransverseMomentumCut.cpp \
 MassEigenstateCollectionClasses/ExtendedMass.cpp \
 MassEigenstateCollectionClasses/MassEigenstate.cpp \
 MassEigenstateCollectionClasses/MassSpectrum.cpp \
 MassEigenstateCollectionClasses/SpectrumUpdater.cpp \
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
 ParticleCodesAndDataClasses/NineDigitSlhaCodes.cpp \
 ParticleCodesAndDataClasses/PdgData.cpp \
 ParticleCodesAndDataClasses/SevenDigitSlhaCodes.cpp \
 SlhaSpectrumPlottingClasses/LineData.cpp \
 SlhaSpectrumPlottingClasses/SpectrumPlotter.cpp \
 SusyLesHouchesAccordClasses/SlhaOne.cpp \
 SusyLesHouchesAccordClasses/SlhaParser.cpp \
 SusyLesHouchesAccordClasses/SlhaTwo.cpp \
 SusyLesHouchesAccordClasses/SlhaTwoWithSpheno.cpp \
 SusyLesHouchesAccordClasses/BlockClasses/BaseSlhaBlock.cpp \
 SusyLesHouchesAccordClasses/BlockClasses/BaseStringBlock.cpp \
 SusyLesHouchesAccordClasses/BlockClasses/LinesAsStringsBlock.cpp \
 SusyLesHouchesAccordClasses/BlockClasses/SameNameBlockSet.cpp \
 $(SLHADIR)/BlockClasses/InterpreterClasses/BlockInterpreter.cpp \
 $(SLHADIR)/BlockClasses/InterpreterClasses/LinesAsStrings.cpp
OBJECTS=$(SOURCES:.cpp=.o)
LIBRARYFILE=libLHPC_CPP.a
PLOTTERCPP=LhpcSpectrumPlotter.cpp
PLOTTERGEXE=LhpcSpectrumPlotter.exe
LHEFEGCPP=LhefParserExample.cpp
LHEFEGEXE=LhefParserExample.exe
SLHAEGCPP=SlhaParserExample.cpp
SLHAEGEXE=SlhaParserExample.exe

all: $(SOURCES) $(LIBRARYFILE) $(PLOTTERGEXE) $(LHEFEGEXE) $(SLHAEGEXE)

$(SOURCES):
	$(CC) $(CCOBJFLAGS) $(CCFLAGS) $< -o $@

$(LIBRARYFILE): $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $(OBJECTS)

$(PLOTTERGEXE): $(LIBRARYFILE)
	$(CC) $(CCEXEFLAGS) $(CCFLAGS) -o $@ $(PLOTTERCPP) $(LDFLAGS)

$(LHEFEGEXE): $(LIBRARYFILE)
	$(CC) $(CCEXEFLAGS) $(CCFLAGS) -o $@ $(LHEFEGCPP) $(LDFLAGS)

$(SLHAEGEXE): $(LIBRARYFILE)
	$(CC) $(CCEXEFLAGS) $(CCFLAGS) -o $@ $(SLHAEGCPP) $(LDFLAGS)

.PHONY: deleteobjects
deleteobjects:
	\rm -f $(OBJECTS)

.PHONY: clean
clean:
	\rm -f $(OBJECTS) $(LIBRARYFILE) $(PLOTTERGEXE) $(LHEFEGEXE) $(SLHAEGEXE)
