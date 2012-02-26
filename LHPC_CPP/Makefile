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
SHORTDIRA=LesHouchesEventFileClasses/FilterRuleClasses
SHORTDIRB=MassEigenstateCollectionClasses/MassSpectrumClasses
SHORTDIRC=$(SHORTDIRB)/ParticleSubsetClasses
SOURCES=BOLlib/Classes/AsciiXmlParser.cpp \
 BOLlib/Classes/CommentedTextParser.cpp \
 BOLlib/Classes/StringParser.cpp \
 BOLlib/Classes/UsefulStuff.cpp \
 LesHouchesEventFileClasses/AutomaticEventFilter.cpp \
 LesHouchesEventFileClasses/FilterRule.cpp \
 LesHouchesEventFileClasses/LhefEvent.cpp \
 LesHouchesEventFileClasses/ParticleLine.cpp \
 $(SHORTDIRA)/InitialOrIntermediateOrFinalState.cpp \
 $(SHORTDIRA)/ParticleCode.cpp \
 $(SHORTDIRA)/PseudorapidityCut.cpp \
 $(SHORTDIRA)/TransverseMomentumCut.cpp \
 MassEigenstateCollectionClasses/ExtendedMass.cpp \
 MassEigenstateCollectionClasses/MassEigenstate.cpp \
 MassEigenstateCollectionClasses/MassSpectrum.cpp \
 $(SHORTDIRB)/MinimalSupersymmetricStandardModel.cpp \
 $(SHORTDIRB)/NextToMinimalSupersymmetricStandardModel.cpp \
 $(SHORTDIRB)/StandardModel.cpp \
 $(SHORTDIRC)/ChargedSleptonsOneToSix.cpp \
 $(SHORTDIRC)/CharginosOneToTwo.cpp \
 $(SHORTDIRC)/GluinoOneGeneration.cpp \
 $(SHORTDIRC)/MssmExtraEwsbSpinZeroBosonSet.cpp \
 $(SHORTDIRC)/NeutralinosOneToFive.cpp \
 $(SHORTDIRC)/NeutralinosOneToFour.cpp \
 $(SHORTDIRC)/NmssmExtraEwsbSpinZeroBosonSet.cpp \
 $(SHORTDIRC)/SneutrinosOneToThree.cpp \
 $(SHORTDIRC)/SquarksOneToSix.cpp \
 ParticleCodesAndDataClasses/NineDigitSlhaCodes.cpp \
 ParticleCodesAndDataClasses/PdgData.cpp \
 ParticleCodesAndDataClasses/SevenDigitSlhaCodes.cpp \
 SlhaSpectrumPlottingClasses/LineData.cpp \
 SlhaSpectrumPlottingClasses/MassLine.cpp \
 SlhaSpectrumPlottingClasses/SpectrumPlotter.cpp \
 SusyLesHouchesAccordClasses/SlhaBlock.cpp \
 SusyLesHouchesAccordClasses/SlhaOne.cpp \
 SusyLesHouchesAccordClasses/SlhaTwo.cpp \
 SusyLesHouchesAccordClasses/SlhaTwoWithSpheno.cpp \
 LhefParser.cpp \
 SlhaParser.cpp
OBJECTS=$(SOURCES:.cpp=.o)
LIBRARYFILE=libLHPC_CPP.a
LHEFEGCPP=LhefParserExample.cpp
LHEFEGEXE=LhefParserExample.exe
SLHAEGCPP=SlhaParserExample.cpp
SLHAEGEXE=SlhaParserExample.exe

all: $(SOURCES) $(LIBRARYFILE) $(LHEFEGEXE) $(SLHAEGEXE)

$(SOURCES):
	$(CC) $(CCOBJFLAGS) $(CCFLAGS) $< -o $@

$(LIBRARYFILE): $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $(OBJECTS)

$(LHEFEGEXE): $(LIBRARYFILE)
	$(CC) $(CCEXEFLAGS) $(CCFLAGS) -o $@ $(LHEFEGCPP) $(LDFLAGS)

$(SLHAEGEXE): $(LIBRARYFILE)
	$(CC) $(CCEXEFLAGS) $(CCFLAGS) -o $@ $(SLHAEGCPP) $(LDFLAGS)

.PHONY: clean
clean:
	\rm -f $(OBJECTS) $(LIBRARYFILE) $(LHEFEGEXE) $(SLHAEGEXE)
