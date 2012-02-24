/*
 * AsciiXmlParser.hpp
 *
 *  Created on: Jan 23, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#ifndef ASCIIXMLPARSER_HPP_
#define ASCIIXMLPARSER_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include "VectorlikeArray.hpp"
#include "StringParser.hpp"

namespace BOL
{
  /* this parses out blocks of ASCII text from a string between XML opening &
   * closing tags, & returns the text between the tags (without interpretting
   * it further as XML).
   */
  class AsciiXmlParser
  {
  public:
    typedef std::pair< std::string,
                       std::string > StringPair;
    typedef VectorlikeArray< StringPair > StringPairArray;
    AsciiXmlParser( std::string const& defaultTag,
                    bool const& isVerbose );
    ~AsciiXmlParser();

    std::string const&
    getDefaultTag() const;
    void
    setDefaultTag( std::string const& defaultTag );
    // this sets the default tag used by this instance.
    void
    loadString( std::string const& stringToParse );
    // this loads stringToParse into the internal stringstream for parsing. if
    // there was a file open, it is now closed.
    void
    openFile( std::string const& fileName );
    /* this loads the file with the given name into the internal ifstream for
     * parsing. if there was a problem loading the file, lastOperationSucceeded
     * is set to false. this closes the previously-loaded file, if it was open.
     */
    void
    closeFile();
    // this closes fileToParse, if it was open.
    std::string const&
    findNextElement( std::string const& tagString );
    /* this looks for the next complete XML element with the tag given by
     * tagString. the next element with the tag is returned, regardless of how
     * nested it is within other XML elements. if no element was found,
     * lastOperationSucceeded is set to false & an empty string is returned.
     * if the element is found, the entire string between its opening & closing
     * tags is returned without being further parsed as XML (&
     * lastOperationSucceeded is set to true).
     */
    std::string const&
    findNextElement();
    /* this looks for the next complete XML element with the tag given by
     * defaultTag. the next element with the tag is returned, regardless of how
     * nested it is within other XML elements. if no element was found,
     * lastOperationSucceeded is set to false & an empty string is returned.
     * if the element is found, the entire string between its opening & closing
     * tags is returned without being further parsed as XML (&
     * lastOperationSucceeded is set to true).
     */
    void
    returnToBeginningOfText();
    // this sets whichever stream textToParse is pointing at to start reading
    // again from its start.
    bool
    wasSuccessful() const;
    // this returns lastOperationSucceeded, which is set by all the other
    // member functions.
    std::string const&
    getCurrentElementContent() const;
    std::string const&
    getCurrentElementContentTrimmedOfWhitespace() const;
    std::string const&
    getCurrentOpeningTagAsFound() const;
    StringPairArray const&
    getCurrentElementAttributes();


  protected:
    static std::string const allowedXmlWhitespaceChars;

    bool const& isVerbose;
    std::fstream fileParsingStream;
    std::stringstream stringParsingStream;
    std::istream* textStream;
    std::string fullElementContentAsFound;
    // this includes any whitespace & child elements (as text); this does not
    // include the opening or closing tags (& so does not include attributes).
    std::string fullOpeningTagAsFound;
    // this includes any attributes; this does not include '<' or '>'.
    bool attributesNotYetParsed;
    StringPairArray attributesAsParsed;
    VectorlikeArray< std::string > tagParsingArray;
    std::string attributeParsingString;
    std::string defaultTag;
    std::string soughtTag;
    size_t soughtTagLength;
    size_t charPosition;
    bool lastOperationSucceeded;
    bool finishedSearching;
    char currentReadChar;
    char lastReadChar;
    std::string potentialClosingTag;


    bool
    findNextSoughtOpeningTagNoMatterHowNested();
    /* this looks for the next '<' then soughtTag followed by either a '>' or a
     * whitespace char in the stream. it returns true if a tag for soughtTag
     * was found (which also records the tag).
     */
    bool
    recordToEndOfSoughtElement();
    /* this records from textStream up to the end of the current element (with
     * tag name given by soughtTag). if the current element is just a tag which
     * both opens and closes the element, then fullElementContentAsFound is set
     * to be empty & only fullOpeningTagAsFound is recorded. otherwise, all
     * characters up to the closing tag for this element are recorded as text,
     * including all markup and child elements, in fullElementContentAsFound.
     */
    bool
    discardToNextTag();
    // this looks for the next '<' in textStream, discarding all preceding
    // chars. it returns true if a '<' was found before the end of textStream.
    bool
    recordSoughtTagOrDiscard();
    /* this compares the next chars from textStream with soughtTag, & if the
     * tag is a valid XML tag for soughtTag, with or without attributes, it is
     * recorded into fullOpeningTagAsFound, & true is returned. otherwise the
     * read chars are discarded & false is returned. in either case, textStream
     * has been read up to either '>' or the end of the stream.
     */
    bool
    foundSoughtClosingTag();
    /* this reads in a potential closing tag & checks to see if it is a valid
     * closing tag for the sought element. if it is, the function returns true.
     * otherwise, if it was a valid tag but not the closing tag for the
     * element, the tag (including '<', possible '/'s, & '>') is appended to
     * fullElementContentAsFound, & lastOperationSucceeded is left as true, but
     * false is returned. if no valid tag could be read in,
     * lastOperationSucceeded is set to false and false is returned.
     */
    void
    setToReturnEmptyString();
    // this clears fullOpeningTagAsFound & fullElementContentAsFound, & , if
    // isVerbose is true, reports that there are no more elements.
  };



  inline std::string const&
  AsciiXmlParser::getDefaultTag() const
  {
    return defaultTag;
  }

  inline void
  AsciiXmlParser::setDefaultTag( std::string const& defaultTag )
  // this sets the default tag used by this instance.
  {
    this->defaultTag.assign( defaultTag );
    soughtTag.assign( defaultTag );
    soughtTagLength = soughtTag.size();
    lastOperationSucceeded = true;
  }

  inline void
  AsciiXmlParser::loadString( std::string const& stringToParse )
  // this loads stringToParse into the internal stringstream for parsing. if
  // there was a file open, it is now closed.
  {
    if( fileParsingStream.is_open() )
    {
      fileParsingStream.close();
    }
    stringParsingStream.clear();
    stringParsingStream.str( stringToParse );
    textStream = &stringParsingStream;
    lastOperationSucceeded = true;
  }

  inline void
  AsciiXmlParser::openFile( std::string const& fileName )
  /* this loads the file with the given name into the internal ifstream for
   * parsing. if there was a problem loading the file, lastOperationSucceeded
   * is set to false. this closes the previously-loaded file, if it was open.
   */
  {
    if( fileParsingStream.is_open() )
    {
      fileParsingStream.close();
    }
    fileParsingStream.open( fileName.c_str() );
    if( fileParsingStream.is_open() )
    {
      lastOperationSucceeded = true;
      textStream = &fileParsingStream;
    }
    else
    {
      lastOperationSucceeded = false;
      textStream = &stringParsingStream;
      std::cout
      << std::endl
      << "BOL::error! AsciiXmlParser::openFile( " << fileName << " ) could not"
      << " open the file!";
      std::cout << std::endl;
    }
  }

  inline void
  AsciiXmlParser::closeFile()
  // this closes fileToParse, if it was open.
  {
    if( fileParsingStream.is_open() )
    {
      fileParsingStream.close();
    }
    textStream = &stringParsingStream;
    lastOperationSucceeded = true;
  }

  inline std::string const&
  AsciiXmlParser::findNextElement( std::string const& tagString )
  /* this looks for the next complete XML element with the tag given by
   * tagString. the next element with the tag is returned, regardless of how
   * nested it is within other XML elements. if no element was found,
   * lastOperationSucceeded is set to false & an empty string is returned.
   * if the element is found, the entire string between its opening & closing
   * tags is returned without being further parsed as XML (&
   * lastOperationSucceeded is set to true).
   */
  {
    soughtTag.assign( tagString );
    findNextElement();
    soughtTag.assign( defaultTag );
    return fullElementContentAsFound;
  }

  inline std::string const&
  AsciiXmlParser::findNextElement()
  /* this looks for the next complete XML element with the tag given by
   * defaultTag. the next element with the tag is returned, regardless of how
   * nested it is within other XML elements. if no element was found,
   * lastOperationSucceeded is set to false & an empty string is returned.
   * if the element is found, the entire string between its opening & closing
   * tags is returned without being further parsed as XML (&
   * lastOperationSucceeded is set to true).
   */
  {
    attributesNotYetParsed = true;
    if( soughtTag.empty() )
    {
      lastOperationSucceeded = false;
    }
    else
    {
      lastOperationSucceeded = findNextSoughtOpeningTagNoMatterHowNested();
    }
    if( lastOperationSucceeded )
    {
      lastOperationSucceeded = recordToEndOfSoughtElement();
    }
    if( !lastOperationSucceeded )
      // if the element was not found, an empty string should be returned:
    {
      setToReturnEmptyString();
    }
    return fullElementContentAsFound;
  }

  inline void
  AsciiXmlParser::returnToBeginningOfText()
  // this sets whichever stream textToParse is pointing at to start reading
  // again from its start.
  {
    textStream->clear();
    textStream->seekg( std::ios::beg );
    lastOperationSucceeded = true;
  }

  inline bool
  AsciiXmlParser::wasSuccessful() const
  // this returns lastOperationSucceeded, which is set by all the other
  // member functions.
  {
    return lastOperationSucceeded;
  }

  inline std::string const&
  AsciiXmlParser::getCurrentElementContent() const
  {
    return fullElementContentAsFound;
  }

  inline std::string const&
  AsciiXmlParser::getCurrentElementContentTrimmedOfWhitespace() const
  {
    return StringParser::trimFromFront( StringParser::trimFromBack(
                                                     fullElementContentAsFound,
                                                   allowedXmlWhitespaceChars ),
                                        allowedXmlWhitespaceChars );
  }

  inline std::string const&
  AsciiXmlParser::getCurrentOpeningTagAsFound() const
  {
    return fullOpeningTagAsFound;
  }

  inline bool
  AsciiXmlParser::findNextSoughtOpeningTagNoMatterHowNested()
  /* this looks for the next '<' then soughtTag followed by either a '>' or a
   * whitespace char in the stream. it returns true if a tag for soughtTag was
   * found (which also records the tag).
   */
  {
    finishedSearching = false;
    while( !finishedSearching
           &&
           discardToNextTag() )
      // this looks through all the tags until it is told to stop or
      // discardToNextTag fails to find a new tag.
    {
      finishedSearching = recordSoughtTagOrDiscard();
    }
    return finishedSearching;
  }

  inline bool
  AsciiXmlParser::discardToNextTag()
  // this looks for the next '<' in textStream, discarding all preceding
  // chars. it returns true if a '<' was found before the end of textStream.
  {
    while( textStream->get( currentReadChar ).good()
           &&
           '<' != currentReadChar )
    {
      // the conditional does the work of reading up to the next tag.
    }
    if( '<' == currentReadChar )
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  inline void
  AsciiXmlParser::setToReturnEmptyString()
  // this clears fullOpeningTagAsFound & fullElementContentAsFound, & , if
  // isVerbose is true, reports that there are no more elements.
  {
    fullOpeningTagAsFound.clear();
    fullElementContentAsFound.clear();
    if( isVerbose )
    {
      std::cout
      << std::endl
      << "BOL::AsciiXmlParser could not find any more complete \""
      << soughtTag << "\" elements.";
      std::cout << std::endl;
    }
  }

}

#endif /* ASCIIXMLPARSER_HPP_ */
