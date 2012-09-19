/*
 * AsciiXmlStringParser.cpp
 *
 *  Created on: Jan 23, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *
 *      This file is part of BOLlib, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.BOLlib.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#include "AsciiXmlParser.hpp"

namespace BOL
{
  std::string const AsciiXmlParser::allowedXmlWhitespaceChars( " \t\r\n" );

  AsciiXmlParser::AsciiXmlParser( std::string const& defaultTag,
                                  bool const isVerbose ) :
      isVerbose( isVerbose ),
      fileParsingStream(),
      stringParsingStream(),
      textStream( &stringParsingStream ),
      fullElementContentAsFound( "" ),
      fullOpeningTagAsFound( "" ),
      attributesNotYetParsed( true ),
      attributesAsParsed(),
      tagParsingArray(),
      attributeParsingString( "" ),
      defaultTag( defaultTag ),
      soughtTag( defaultTag ),
      soughtTagLength( soughtTag.size() ),
      charPosition( 0 ),
      lastOperationSucceeded( true ),
      finishedSearching( false ),
      currentReadChar( ' ' ),
      lastReadChar( ' ' ),
      potentialClosingTag( "" )
  {
    // just an initialization list.
  }

  AsciiXmlParser::~AsciiXmlParser()
  {
    if( fileParsingStream.is_open() )
    {
      fileParsingStream.close();
    }
  }


  VectorlikeArray< std::pair< std::string, std::string > > const&
  AsciiXmlParser::getCurrentElementAttributes()
  {
    if( attributesNotYetParsed )
      // if the attributes need to be parsed...
    {
      attributesAsParsed.clearEntries();
      // the container is readied to take the attributes as they are parsed.
      if( fullOpeningTagAsFound.size() > soughtTag.size() )
        // if there are possibly attributes...
      {
        attributeParsingString.assign( fullOpeningTagAsFound.substr(
                                                          soughtTag.size() ) );
        if( '/'
            == attributeParsingString[ attributeParsingString.size() - 1 ] )
          // if the last char of the opening tag indicates that the tag also
          // closed the element...
        {
          // that ending '/' should be ignored:
          attributeParsingString.resize( attributeParsingString.size() - 1 );
        }
        // the various containers are cleared:
        tagParsingArray.clearEntries();
        // tagParsingArray is filled with the strings pairing each attribute
        // with its value:
        StringParser::parseByChar( attributeParsingString,
                                   tagParsingArray,
                                   allowedXmlWhitespaceChars );
        attributesAsParsed.setSize( tagParsingArray.getSize() );
        for( int attributeIndex( tagParsingArray.getLastIndex() );
             0 <= attributeIndex;
             --attributeIndex )
        {
          attributesAsParsed[ attributeIndex ].first.assign(
             StringParser::substringToFirst( tagParsingArray[ attributeIndex ],
                                             "=",
                                             &attributeParsingString ) );
          attributesAsParsed[ attributeIndex ].second.assign(
                                              attributeParsingString.substr( 2,
                                         attributeParsingString.size() - 3 ) );
        }
      }
      attributesNotYetParsed = false;
    }
    return attributesAsParsed;
  }

  bool
  AsciiXmlParser::recordToEndOfSoughtElement()
  /* this records from textStream up to the end of the current element (with
   * tag name given by soughtTag). if the current element is just a tag which
   * both opens and closes the element, then fullElementContentAsFound is set
   * to be empty & only fullOpeningTagAsFound is recorded. otherwise, all
   * characters up to the closing tag for this element are recorded as text,
   * including all markup and child elements, in fullElementContentAsFound.
   */
  {
    // flush any previous element before beginning:
    fullElementContentAsFound.clear();
    lastOperationSucceeded = true;
    if( '/' == fullOpeningTagAsFound[ fullOpeningTagAsFound.size() - 1 ] )
      // if the opening tag also closes the element...
    {
      // leave the content empty & note success:
      return true;
    }
    else
      // otherwise "</" followed by soughtTag followed by possible whitespace
      // followed by '>' has to be found.
    {
      finishedSearching = false;
      while( lastOperationSucceeded
             &&
             !finishedSearching )
        // the loop keeps looking for the closing tag until it either finds it
        // or runs out of textStream.
      {
        while( textStream->get( currentReadChar ).good()
               &&
               '<' != currentReadChar )
        {
          fullElementContentAsFound.append( 1,
                                            currentReadChar );
        }
        // everything up to the next potential closing tag is recorded.
        if( '<' == currentReadChar )
          // if there is a potential tag...
        {
          finishedSearching = foundSoughtClosingTag();
          /* foundSoughtClosingTag compares the potential tag, & returns true
           * if it found it. lastOperationSucceeded is set to false if it
           * failed to find a well-formed tag to compare against a valid
           * closing tag.
           */
        }
        else
          // otherwise textStream ran out of characters before a possible
          // closing tag was found.
        {
          lastOperationSucceeded = false;
        }
      }
      if( !lastOperationSucceeded
          &&
          isVerbose )
      {
        std::cout
        << std::endl
        << "BOL::AsciiXmlParser::warning! could not find \"</"
        << soughtTag << ">\" to close the open element!";
        std::cout << std::endl;
      }
      return lastOperationSucceeded;
    }
  }

  bool
  AsciiXmlParser::recordSoughtTagOrDiscard()
  /* this compares the next chars from textStream with soughtTag, & if the tag
   * is a valid XML tag for soughtTag, with or without attributes, it is
   * recorded into fullOpeningTagAsFound, & true is returned. otherwise the
   * read chars are discarded & false is returned. in either case, textStream
   * has been read up to either '>' or the end of the stream.
   */
  {
    charPosition = 0;
    while( textStream->get( currentReadChar ).good()
           &&
           ( currentReadChar == soughtTag[ charPosition ] )
           &&
           ( (++charPosition) < soughtTagLength ) )
    {
      // the conditional does the work of comparing up to either the end of
      // soughtTag or the 1st non-matching char.
    }
    if( charPosition == soughtTagLength )
      // if soughtTag was found, we need to check that it wasn't just a
      // substring of a different tag:
    {
      if( textStream->get( currentReadChar ).good() )
      {
        if( '>' == currentReadChar )
          // if the tag was indeed soughtTag, without attributes, note how it
          // was found, & stop looking:
        {
          fullOpeningTagAsFound.assign( soughtTag );
          return true;
        }
        else if( ( '/' == currentReadChar )
                 ||
                 StringParser::charIsIn( currentReadChar,
                                         allowedXmlWhitespaceChars ) )
          // if the tag was indeed soughtTag, with attributes, or just about to
          // close itself, note how it was found, & stop looking:
        {
          fullOpeningTagAsFound.assign( soughtTag );
          fullOpeningTagAsFound.append( 1,
                                        currentReadChar );
          while( textStream->get( currentReadChar ).good()
                 &&
                 '>' != currentReadChar )
          {
            fullOpeningTagAsFound.append( 1,
                                          currentReadChar );
            // this reads the rest of the opening tag into
            // fullOpeningTagAsFound.
          }
          return true;
        }
        else
          // otherwise there was a problem reading in the last char:
        {
          lastOperationSucceeded = false;
          return false;
        }
      }
      else
        // otherwise soughtTag was only found as a substring of another tag.
      {
        return false;
      }
    }
    else
      // otherwise, soughtTag was not found as a tag.
    {
      return false;
    }
  }

  bool
  AsciiXmlParser::foundSoughtClosingTag()
  /* this reads in a potential closing tag & checks to see if it is a valid
   * closing tag for the sought element. if it is, the function returns true.
   * otherwise, if it was a valid tag but not the closing tag for the element,
   * the tag (including '<', possible '/'s, & '>') is appended to
   * fullElementContentAsFound, & lastOperationSucceeded is left as true, but
   * false is returned. if no valid tag could be read in,
   * lastOperationSucceeded is set to false and false is returned.
   */
  {
    if( textStream->get( currentReadChar ).good() )
      // if there is a char after the '<' that triggered this function...
    {
      if( '/' == currentReadChar )
        // if it's a potential closing tag...
      {
        potentialClosingTag.clear();
        // potentialClosingTag is cleared so as to take in the tag.
        while( textStream->get( currentReadChar ).good()
               &&
               '>' != currentReadChar )
        {
          potentialClosingTag.append( 1,
                                      currentReadChar );
        }
        if( ( '>' == currentReadChar )
            &&
            ( 0 == StringParser::trimFromBack( potentialClosingTag,
                                               allowedXmlWhitespaceChars
                                                     ).compare( soughtTag ) ) )
          // if it was the closing tag...
        {
          // note that the tag did close the element:
          return true;
        }
        else
          // otherwise, record it as part of the element content:
        {
          fullElementContentAsFound.append( "</" );
          // the '<' triggered this function being called, & the '/' triggered
          // this branch of the if-else.
          fullElementContentAsFound.append( potentialClosingTag );
          fullElementContentAsFound.append( 1,
                                            currentReadChar );
          // currentReadChar will be forgotten about once this function ends,
          // so it needs to be recorded at this point.

          // note that the tag did not close the element:
          return false;
        }
      }
      else
        /* otherwise it was just '<' followed by stuff that is not the closing
         * tag, so the '<' that triggered this function gets appended, then
         * currentReadChar before it is forgotten about, then false is returned
         * without any other characters being read.
         */
      {
        fullElementContentAsFound.append( 1,
                                          '<' );
        fullElementContentAsFound.append( 1,
                                          currentReadChar );
        return false;
      }
    }
    else
      // otherwise the closing tag cannot be found in textStream, so
      // lastOperationSucceeded is set to false and false is returned:
    {
      lastOperationSucceeded = false;
      return false;
    }
  }

}
