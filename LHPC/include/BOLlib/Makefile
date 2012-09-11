#
# Makefile for Ben O'Leary's personal C++ library.
#

SHELL=/bin/sh

CC=g++
CFLAGS=-c -O3 -Wall -I./include/
LDFLAGS=
AR=ar
AFLAGS=rcs
SOURCES=source/AsciiXmlParser.cpp \
 source/BalancedPartitionCandidate.cpp \
 source/BasicObserved.cpp \
 source/BasicObserver.cpp \
 source/CommentedTextParser.cpp \
 source/InputFileToOutputFileClaimer.cpp \
 source/StringParser.cpp \
 source/TwoDimensionalDataPlotter.cpp \
 source/UsefulStuff.cpp \
 source/WaitingOnSubprocessExecutor.cpp
OBJECTS=$(SOURCES:.cpp=.o)
LIBRARYFILE=lib/libBOLlib.a

all: $(OBJECTS) $(LIBRARYFILE)

lib: $(OBJECTS) $(LIBRARYFILE)
	\rm -rf $(OBJECTS)
	
.PHONY: all lib clean

$(OBJECTS): %.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@
	
$(LIBRARYFILE): $(OBJECTS)
	$(AR) $(AFLAGS) $@ $(OBJECTS)

clean:
	\rm -rf *o $(LIBRARYFILE)