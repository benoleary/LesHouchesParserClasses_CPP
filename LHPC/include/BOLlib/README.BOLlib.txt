/*****************************************************************************\
 * README.BOLlib.txt                                                         *
 *                                                                           *
 *  Created on: Sep 10, 2012                                                 *
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)                      *
 *      Copyright 2012 Ben O'Leary                                           *
 *                                                                           *
 *      This file is part of BOLlib.                                         *
 *                                                                           *
 *      BOLlib is free software: you can redistribute it and/or modify it    *
 *      under the terms of the GNU General Public License as published by    *
 *      the Free Software Foundation, either version 3 of the License, or    *
 *      (at your option) any later version.                                  *
 *                                                                           *
 *      BOLlib is distributed in the hope that it will be useful, but        *
 *      WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    *
 *      General Public License for more details.                             *
 *                                                                           *
 *      You should have received a copy of the GNU General Public License    *
 *      (in GNU_public_license.txt ) along with BOLlib.  If not, see         *
 *      <http://www.gnu.org/licenses/>.                                      *
 *      A full list of the files of BOLlib is at the end of this file.       *
\*****************************************************************************/

 Now that the legalese preamble is out of the way, the description of the code
 and how to use it can begin!

 BOLlib is a set of classes written in C++ for the private use of Ben O'Leary,
 but made publically available in case it would be useful for others, in
 particular also to be distributed as part of LesHouchesParserClasses.

 Unfortunately I am too lazy to write full documentation for these classes. I
 hope that the comments and the function names are sufficiently descriptive
 to allow others to use the classes.

CHANGELOG:
 * 4th March 2014: version 0.4.7
 - added StringParser::stringIsDouble( std::string const& stringToInterpret,
                                       double& doubleToSet )
   to check if a string represents a floating-point number in scientific E
   notation.
 - added StringParser::lowercaseAlphabetChars,
   StringParser::uppercaseAlphabetChars, & StringParser::digitChars as public
   static strings.

 * 23rd October 2013: version 0.4.6
 - CommentedTextParser::openFile(...) now definitely sets linesOfFileRemain to
   false if it could not open the file.
 - added FilePlaceholderManager class to do the job of
   InputFileToOutputFileClaimer better. I'd remove InputFileToOutputFileClaimer
   out of embarrassment, but I'd rather not break backwards compatibility.
 - added BasicTimer class for basic timing stuff.

 * 3rd April 2013: version 0.4.5
 - CommentedTextParser::parseNextLineOfFile(...) now trims uncommented lines
   of any trailing newline characters.

 * 25th March 2013: version 0.4.4
 - added explicit #include <unistd.h> to WaitingOnSubprocessExecutor.hpp so
   that it no longer relies on some other header including it.
 - added UsefulStuff::runSystemCommand( std::string const& systemCommand ) to
   simplify running system( char[] ), throwing an exception if system( ... )
   returned -1.

 * 8th March 2013: version 0.4.3
 - fixed bug where quote marks (' & ") within comments were not being correctly
   ignored.

 * 15th February 2013: version 0.4.2
 - added default value of StringParser::whitespaceAndNewlineChars as
   StringParser::charsToTrim for StringParser::trimFromFrontAndBack.

 * 23rd October 2012: version 0.4.1
 - minor signature change to AsciiXmlParser::loadString: from taking a
   std::string const& reference to a std::string const copy (fixing some bugs
   caused by overly leet re-use of the same AsciiXmlParser to parse its own
   parsed content).

 * 16th October 2012: version 0.4.0
 - major changes to AsciiXmlParser (breaking compatibility with 0.3 & older):
   -- now ignores XML comments properly.
   -- now ignores XML prolog properly.
   -- now records XML processing instructions & CDATA sections properly.
   -- now just reads the direct child elements of the loaded string or of the
      root element of the loaded file. child elements of these elements can be
      parsed by giving their strings to another AsciiXmlParser (or the original
      parser, if discarding the rest of the text isn't a problem).
 - ArgumentParser changed to be compatible with new AsciiXmlParser.

 * 8th October 2012: version 0.3.1
 - added
   CommentedTextParser::readJustNextValidLine( std::string& stringToFill )
   as an alias for
   CommentedTextParser::readNextNonEmptyLineOfFileWithoutComment(
                                                    std::string& stringToFill )
 - tidied extra whitespace in README.BOLlib.txt file.

 * 5th October 2012: version 0.3.0
 - changed AsciiXmlParser::getCurrentElementAttributes() to return a
   std::map< std::string, std::string > const& reference.
 - fixed make clean in makefile to properly clean up, & added
   make deleteobjects to allow the deletion of .o files without deleting the
   library file.

 * 4th October 2012: version 0.2.2
 - tried to make StringParser as thread-safe as possible by removing all
   non-const static data members.

 * 19th September 2012: version 0.2.1
 - fixed bug in AsciiXmlParser where searching for the default tag subsequent
   to looking for a non-default tag would fail unless the last non-default tag
   was the same length as the default tag.

 * 19th September 2012: version 0.2.0
 - fixed bug in AsciiXmlParser where searching for tags subsequent to the 1st
   would fail unless they were the same length as the 1st tag.
 - fixed StringParser::stringToIntVector( std::string stringToInterpret ) to
   return an empty std::vector< int > if stringToInterpret has no indices.
 - enhanced functionality of ArgumentParser class, so that it now searches for
   tags in command-line arguments and then in an input XML file and then
   resorts to defaults.
 * 10th September 2012: version 0.1.0
 - first release!

The C++ files of LesHouchesParserClasses are:
 include/ArgumentParser.hpp
 include/AsciiXmlParser.hpp
 include/BalancedPartitionCandidate.hpp
 include/BasicObserved.hpp
 include/BasicObserver.hpp
 include/BasicTimer.hpp
 include/BOLlib.hpp
 include/CommentedTextParser.hpp
 include/FilePlaceholderManager.hpp
 include/InputFileToOutputFileClaimer.hpp
 include/PushedToObserver.hpp
 include/PushingObserved.hpp
 include/StdVectorFiller.hpp
 include/StringParser.hpp
 include/TwoDimensionalDataPlotter.hpp
 include/UsefulStuff.hpp
 include/VectorlikeArray.hpp
 include/WaitingOnSubprocessExecutor.hpp
 source/ArgumentParser.cpp
 source/AsciiXmlParser.cpp
 source/BalancedPartitionCandidate.cpp
 source/BasicObserved.cpp
 source/BasicObserver.cpp
 source/BasicTimer.cpp
 source/CommentedTextParser.cpp
 source/FilePlaceholderManager.cpp
 source/InputFileToOutputFileClaimer.cpp
 source/StringParser.cpp
 source/TwoDimensionalDataPlotter.cpp
 source/UsefulStuff.cpp
 source/WaitingOnSubprocessExecutor.cpp
 Makefile
 and README.BOLlib.txt (copied as README.txt) which describes the package.
