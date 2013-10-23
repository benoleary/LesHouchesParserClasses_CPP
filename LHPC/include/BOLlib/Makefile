#
# Makefile for Ben O'Leary's personal C++ library.
#

SHELL=/bin/sh

CC=g++
CFLAGS=-c -O3 -Wall -I./include/
LDFLAGS=
AR=ar
AFLAGS=rcs
SOURCES=source/ArgumentParser.cpp \
 source/AsciiXmlParser.cpp \
 source/BalancedPartitionCandidate.cpp \
 source/BasicObserved.cpp \
 source/BasicObserver.cpp \
 source/BasicTimer.cpp \
 source/CommentedTextParser.cpp \
 source/FilePlaceholderManager.cpp \
 source/InputFileToOutputFileClaimer.cpp \
 source/StringParser.cpp \
 source/TwoDimensionalDataPlotter.cpp \
 source/UsefulStuff.cpp \
 source/WaitingOnSubprocessExecutor.cpp
OBJECTS=$(SOURCES:.cpp=.o)
LIBDIR=./lib/
LIBRARYFILE=$(LIBDIR)/libBOLlib.a

all: $(OBJECTS) $(LIBRARYFILE)

library: $(OBJECTS) $(LIBRARYFILE)
	\rm -rf $(OBJECTS)
	
.PHONY: all library clean

$(OBJECTS): %.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@
	
$(LIBDIR):
	mkdir $@
	
$(LIBRARYFILE): $(LIBDIR) $(OBJECTS)
	$(AR) $(AFLAGS) $@ $(OBJECTS)

clean:
	\rm -f $(OBJECTS) $(LIBRARYFILE)

deleteobjects:
	\rm -f $(OBJECTS)