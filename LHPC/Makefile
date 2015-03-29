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

CC=g++ -g
CCOBJFLAGS=-c -Wall -O3 -I./include/
CCEXEFLAGS=-Wall -O3 -I./include/
AR=ar
ARFLAGS=rcs
AREXTRACTIONFLAGS=xv
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
 $(LHEFDIR)/PreselectorClasses/EitherSignElectronPreselector.cpp \
 $(LHEFDIR)/PreselectorClasses/EitherSignMuonPreselector.cpp \
 $(LHEFDIR)/PreselectorClasses/JetPreselector.cpp \
 $(LHEFDIR)/PreselectorClasses/LightLeptonPreselector.cpp \
 $(LHEFDIR)/PreselectorClasses/StandardPreselector.cpp \
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
 source/SlhaSpectrumPlottingClasses/SlhaValueColoredSegments.cpp \
 source/SlhaSpectrumPlottingClasses/SlhaValueLineColoring.cpp \
 source/SlhaSpectrumPlottingClasses/SlhaValuePlotLine.cpp \
 source/SlhaSpectrumPlottingClasses/SlhaValuePlotter.cpp \
 source/SlhaSpectrumPlottingClasses/SlhaValueSingleColor.cpp \
 source/SlhaSpectrumPlottingClasses/SpectrumPlotter.cpp \
 source/SusyLesHouchesAccordClasses/FlavorObservable.cpp \
 source/SusyLesHouchesAccordClasses/FlavorObservableError.cpp \
 source/SusyLesHouchesAccordClasses/FlhaOne.cpp \
 source/SusyLesHouchesAccordClasses/SlhaOne.cpp \
 source/SusyLesHouchesAccordClasses/SlhaParser.cpp \
 source/SusyLesHouchesAccordClasses/SlhaSimplisticInterpreter.cpp \
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
LIBNAME=LHPC
LIBDIR=./lib/
LDFLAGS= -L$(LIBDIR) -l$(LIBNAME)
LIBRARYFILE=$(LIBDIR)/lib$(LIBNAME).a
BINDIR=./bin/
SLHAVALUEPLOTTERCPP= source/LhpcSlhaValuePlotter.cpp
SLHAVALUEPLOTTEREXE=$(BINDIR)/LhpcSlhaValuePlotter.exe
SLHASPECTRUMPLOTTERCPP= source/LhpcSpectrumPlotter.cpp
SLHASPECTRUMPLOTTEREXE=$(BINDIR)/LhpcSpectrumPlotter.exe
LHCOEGCPP= source/LhcoParserExample.cpp
LHCOEGEXE=$(BINDIR)/LhcoParserExample.exe
LHEFEGCPP= source/LhefParserExample.cpp
LHEFEGEXE=$(BINDIR)/LhefParserExample.exe
SLHAEGCPP= source/SlhaParserExample.cpp
SLHAEGEXE=$(BINDIR)/SlhaParserExample.exe
EXES=$(SLHAVALUEPLOTTEREXE) \
 $(SLHASPECTRUMPLOTTEREXE) \
 $(LHCOEGEXE) \
 $(LHEFEGEXE) \
 $(SLHAEGEXE)

all: $(BOLLIBFILE) $(OBJECTS) $(LIBRARYFILE) $(EXES)

library: $(OBJECTS) $(LIBRARYFILE)
	\rm -rf $(OBJECTS)
	
.PHONY: all library clean deleteobjects

$(BOLLIBFILE):
	$(MAKE) -C ./include/BOLlib/ library

$(OBJECTS): %.o: %.cpp $(BOLLIBFILE)
	$(CC) $(CCOBJFLAGS) $< -o $@
	
$(LIBDIR):
	mkdir $@

$(LIBRARYFILE): $(LIBDIR) $(BOLLIBFILE) $(OBJECTS)
	$(AR) $(AREXTRACTIONFLAGS) $(BOLLIBFILE)
	$(AR) $(ARFLAGS) $@ $(OBJECTS) *.o
	-\rm *.o __.SYMDEF
	
$(BINDIR):
	mkdir $@

$(SLHAVALUEPLOTTEREXE): $(BINDIR) $(LIBRARYFILE)
	$(CC) $(CCEXEFLAGS) -o $@ $(SLHAVALUEPLOTTERCPP) $(LDFLAGS)

$(SLHASPECTRUMPLOTTEREXE): $(BINDIR) $(LIBRARYFILE)
	$(CC) $(CCEXEFLAGS) -o $@ $(SLHASPECTRUMPLOTTERCPP) $(LDFLAGS)

$(LHCOEGEXE): $(BINDIR) $(LIBRARYFILE)
	$(CC) $(CCEXEFLAGS) -o $@ $(LHCOEGCPP) $(LDFLAGS)

$(LHEFEGEXE): $(BINDIR) $(LIBRARYFILE)
	$(CC) $(CCEXEFLAGS) -o $@ $(LHEFEGCPP) $(LDFLAGS)

$(SLHAEGEXE): $(BINDIR) $(LIBRARYFILE)
	$(CC) $(CCEXEFLAGS) -o $@ $(SLHAEGCPP) $(LDFLAGS)

clean:
	$(MAKE) -C ./include/BOLlib/ clean
	\rm -f $(OBJECTS) $(LIBRARYFILE) $(EXES)

deleteobjects:
	$(MAKE) -C ./include/BOLlib/ deleteobjects
	\rm -f $(OBJECTS)
	
