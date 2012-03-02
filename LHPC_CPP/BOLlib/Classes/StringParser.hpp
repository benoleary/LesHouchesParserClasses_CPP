/*
 * StringParser.hpp
 *
 *  Created on: Jan 6, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.LHPC_CPP.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#ifndef STRINGPARSING_HPP_
#define STRINGPARSING_HPP_

#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include "VectorlikeArray.hpp"
#include "UsefulStuff.hpp"
#include "StdVectorFiller.hpp"

namespace BOL
{
  /* this is a class mainly of static functions for manipulating std::string
   * instances. instances of the StringParser class are just for handy storage
   * of custom arguments for some of these functions, such as doubleToString.
   */
  class StringParser
  {
  public:
    static std::string const whitespaceChars;
    static std::string const newlineChars;

    static int
    numberOfDigitsInInt( int inputInt );
    // this returns the number of digits of the int in base 10, ignoring '-'.
    static std::string
    intToString( int inputInt,
                 int const minimumNumberOfDigits,
                 std::string const prefixForPositiveNumbers = "+",
                 std::string const prefixForNegativeNumbers = "-",
                 char const paddingChar = '0' );
    /* this returns a reference to returnString after preparing it so that is
     * the ASCII version of an int in base 10, prefixed with
     * prefixForPositiveNumbers or prefixForNegativeNumbers depending on
     * whether it is positive or negative. it makes returnString have at least
     * minimumNumberOfDigits digit characters, filling it out with
     * paddingChars after prefixForPositiveNumbers/prefixForNegativeNumbers
     *  (e.g. intToString( 23, 4, "+", "-" ) returns "+0023").
     */
    static std::string
    doubleToString( double inputDouble,
                    int const numberOfMantissaDigits,
                    int const numberOfExponentDigits,
                    std::string const prefixForPositiveNumbers = "+",
                    std::string const prefixForNegativeNumbers = "-",
                    std::string const positiveExponentPrefix = "+",
                    std::string const negativeExponentPrefix = "-",
                    std::string const exponentCharacter = "E" );
    /* this returns returnString after preparing it so that is the ASCII
     * version of a double in base 10, in the form specified thusly:
     * 1st character: either "-" for negative numbers, or a "+" for
     *                positive numbers (or a string to replace this character),
     * 2nd character: the 1st digit,
     * 3rd character: the decimal point,
     * then ( numberOfMantissaDigits - 1 ) digits following the
     * decimal point (so that the mantissa is numberOfMantissaDigits
     * digits plus a decimal point)
     * then "E" (or a string to replace this character)
     * then "+" or "-", depending on the sign of the exponent (or a string to
     * replace this character),
     * then the absolute value of the exponent, with preceding 0s to fill to
     * numberOfExponentDigits digit characters.
     * NaNs are returned as "NaN".
     */
    static bool
    stringsMatchIgnoringCase( std::string const& firstString,
                              std::string const& secondString );
    // this returns true if both strings would be identical if all their
    // uppercase chars were converted to lowercase.
    static void
    transformToLowercase( std::string& stringToTransform );
    static void
    transformToUppercase( std::string& stringToTransform );
    static void
    substituteCharacterWith( std::string& stringToTransform,
                             char const charToBeReplaced,
                             char const charToBePutIn );
    static std::string const&
    ensureDirectoryExists( std::string const& fileName );
    static int
    stringToInt( std::string const& stringToInterpret );
    static double
    stringToDouble( std::string const& stringToInterpret );
    static bool
    charIsIn( char const queryChar,
              std::string const& charSet );
    static bool
    isOnlyCharsIn( std::string const& queryString,
                   std::string const& charSet );
    // this returns true if queryString consists only of chars in charSet.
    static std::string
    substringToFirst( std::string const& stringToParse,
                   VectorlikeArray< std::string > const& delimitersOfSubstring,
                      std::string* const remainderString = NULL );
    /* this returns the substring of stringToParse from its beginning up to the
     * first instance of any of the strings in delimitersOfSubstring within
     * stringToParse. if stringToParse does not contain any of those strings as
     * a substring, the whole of stringToParse is returned, otherwise the
     * substring up to but not including the first of any found strings from
     * delimitersOfSubstring is returned. if remainderString is not NULL, the
     * remainder of stringToParse that is not returned is put into
     * remainderString.
     */
    static std::string
    substringToFirst( std::string const& stringToParse,
                      std::string const& delimiterOfSubstring,
                      std::string* const remainderString = NULL );
    // this sets delimiterOfSubstring as the single element of stringVector &
    // calls the above substringToFirst with stringVector.
    static std::string
    trimFromFront( std::string const& stringToTrim,
                   std::string const& charsToTrim );
    /* this returns the substring of stringToTrim which has had all the chars
     * removed which are in charsToTrim and appear in stringToTrim before the
     * first char which is not in charsToTrim.
     */
    static std::string
    trimFromBack( std::string const& stringToTrim,
                  std::string const& charsToTrim );
    /* this returns the substring of stringToTrim which has had all the chars
     * removed which are in charsToTrim and appear in stringToTrim after the
     * last char which is not in charsToTrim.
     */
    static std::string
    trimFromFrontAndBack( std::string const& stringToTrim,
                          std::string const& charsToTrim );
    /* this returns the substring of stringToTrim which has had all the chars
     * removed which are in charsToTrim and appear in stringToTrim before the
     * first char which is not in charsToTrim and after the last char which is
     * not in charsToTrim.
     */
    static std::string
    firstWordOf( std::string const& stringToParse,
                 std::string* const remainderString = NULL,
                 std::string const& separatorChars = whitespaceChars );
    /* this parses the first substring without any of the characters in
     * separatorChars & returns it, filling remainderString with the rest if
     * it is not NULL.
     */
    static void
    parseByChar( std::string const& stringToParse,
                 VectorlikeArray< std::string >& destinationArray,
                 std::string const& divisionCharSet = whitespaceChars );
    /* this goes through stringToParse & creates new strings with all
     * characters between groups of 1 or more of any of the chars in
     * divisionCharSet, & puts them (as new strings) in order at the end of
     * destinationArray. the resulting strings in destinationArray will not
     * contain *any* instances of *any* of the characters in divisionCharSet.
     */
    static void
    parseByChar( std::string const& stringToParse,
                 VectorlikeArray< std::string >& destinationArray,
                 char const& divisionChar );
    // this calls parseByChar with a string that consists just of divisionChar.
    /*template< class ForwardIteratorOfString >
    static std::string
    joinWithSeparator( ForwardIteratorOfString const beginIterator,
                       ForwardIteratorOfString const endIterator,
                       std::string const& separatorString );*/
    /* this returns a string that is the concatenation of all the strings from
     * ForwardIterator beginIterator to ForwardIterator beginIterator,
     * separated by separatorString.
     */
    static std::string
    joinWithSeparator( VectorlikeArray< std::string > const& stringsToJoin,
                       std::string const& separatorString );
    // this returns a string that is the concatenation of all the strings in
    // stringsToJoin separated by separatorString.
    static std::string
    joinWithSeparator( std::vector< std::string* > const& stringsToJoin,
                       std::string const& separatorString );
    // this prepares destinationString so that is the concatenation of all the
    // strings in stringsToJoin separated by separatorString.
    static std::string
    joinWithSeparator( std::list< std::string* > const& stringsToJoin,
                       std::string const& separatorString );
    // this prepares destinationString so that is the concatenation of all the
    // strings in stringsToJoin separated by separatorString.

    StringParser( int const minimumNumberOfDigitsForInts = 6,
                  char const paddingCharForInts = '0',
                  int const numberOfMantissaDigits = 6,
                  int const numberOfExponentDigits = 2,
                  std::string const prefixForPositiveNumbers = "+",
                  std::string const prefixForNegativeNumbers = "-",
                  std::string const positiveExponentPrefix = "+",
                  std::string const negativeExponentPrefix = "-",
                  std::string const exponentCharacter = "E" );
    ~StringParser();

    StringParser&
    setDefaults( int const minimumNumberOfDigitsForInts = 6,
                 char const paddingCharForInts = '0',
                 int const numberOfMantissaDigits = 6,
                 int const numberOfExponentDigits = 2,
                 std::string const prefixForPositiveNumbers = "+",
                 std::string const prefixForNegativeNumbers = "-",
                 std::string const positiveExponentPrefix = "+",
                 std::string const negativeExponentPrefix = "-",
                 std::string const exponentCharacter = "E" );
    // this sets the default values that the StringParser instance uses as the
    // arguments for the static functions it calls with its own functions.
    std::string
    intToString( int inputInt ) const;
    // this calls the static intToString with the StringParser instance's
    // arguments.
    std::string
    doubleToString( double inputDouble ) const;
    // this calls the static doubleToString with the StringParser instance's
    // arguments.


  private:
    static char const lowercaseMinusUppercase;
    static std::stringstream stringParsingStream;
    static std::vector< char > charBuffer;
    static VectorlikeArray< std::string > stringVector;

    static std::stringstream&
    getStringParsingStream( std::string const& stringToParse );
    static char
    charForSingleDigit( int const singleDigitAsInt );
    static int
    intForSingleDigit( char const singleDigitAsChar );
    static void
    fillNumberOfDigitsAndTenTo( int const positiveInt );
    // this finds out how many digits, in base 10, positiveInt has, putting the
    // result in numberOfDigits, getting tenToNumberOfDigits in the process.
    static std::string
    positiveIntToString( int positiveInt );
    // this puts the digits of positiveInt into a std::string in the order of
    // digit for highest power of 10 1st, & returns it.

    int minimumNumberOfDigitsForInts;
    char paddingCharForInts;
    int numberOfMantissaDigits;
    int numberOfExponentDigits;
    std::string prefixForPositiveNumbers;
    std::string prefixForNegativeNumbers;
    std::string positiveExponentPrefix;
    std::string negativeExponentPrefix;
    std::string exponentCharacter;
  };



  inline int
  StringParser::numberOfDigitsInInt( int inputInt )
  // this returns the number of digits of the int in base 10, ignoring '-'.
  {
    if( 0 > inputInt )
    {
      inputInt = -inputInt;
    }
    int numberOfDigits( 1 );
    int tenToNumberOfDigits( 10 );
    while( inputInt >= tenToNumberOfDigits )
    {
      tenToNumberOfDigits *= 10;
      ++numberOfDigits;
    }
    return numberOfDigits;
  }

  inline void
  StringParser::transformToLowercase( std::string& stringToTransform )
  {
    unsigned int stringSize( stringToTransform.size() );
    for( unsigned int charCounter( 0 );
         stringSize > charCounter;
         ++charCounter )
      // go through each character in the string:
    {
      if( ( 'A' <= stringToTransform[ charCounter ] )
          &&
          ( 'Z' <= stringToTransform[ charCounter ] ) )
      // if it's an uppercase character, replace it with its lowercase:
      {
        stringToTransform[ charCounter ] += lowercaseMinusUppercase;
      }
    }
  }

  inline void
  StringParser::transformToUppercase( std::string& stringToTransform )
  {
    unsigned int stringSize( stringToTransform.size() );
    for( unsigned int charCounter( 0 );
         stringSize > charCounter;
         ++charCounter )
      // go through each character in the string:
    {
      if( ( 'a' <= stringToTransform[ charCounter ] )
          &&
          ( 'z' <= stringToTransform[ charCounter ] ) )
        // if it's a lowercase character, replace it with its uppercase:
      {
        stringToTransform[ charCounter ] -= lowercaseMinusUppercase;
      }
    }
  }

  inline void
  StringParser::substituteCharacterWith( std::string& stringToTransform,
                                         char const charToBeReplaced,
                                         char const charToBePutIn )
  {
    unsigned int stringSize( stringToTransform.size() );
    for( unsigned int charCounter( 0 );
         stringSize > charCounter;
         ++charCounter )
      // go through each character in the string:
    {
      // if it's charToBeReplaced, replace it with charToBePutIn:
      if( charToBeReplaced == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = charToBePutIn;
      }
    }
  }

  inline std::string const&
  StringParser::ensureDirectoryExists( std::string const& fileName )
  {
    if( std::string::npos != fileName.find_last_of( "/" ) )
    {
      std::string mkdirCommand( "mkdir -p " );
      mkdirCommand.append( fileName,
                           0,
                           fileName.find_last_of( "/" ) );
      int systemReturn( system( mkdirCommand.c_str() ) );
      if( -1 == systemReturn )
      {
        std::cout
        << std::endl
        << "BOL::error! StringParser::ensureDirectoryExists( "
        << fileName << " ) got a -1 from system(...); however, I have no"
        << " idea what to do about it.";
        std::cout << std::endl;
      }
    }
    return fileName;
  }

  inline int
  StringParser::stringToInt( std::string const& stringToInterpret )
  {
    int returnValue;
    getStringParsingStream( stringToInterpret ) >> returnValue;
    return returnValue;
  }

  inline double
  StringParser::stringToDouble( std::string const& stringToInterpret )
  {
    double returnValue;
    getStringParsingStream( stringToInterpret ) >> returnValue;
    return returnValue;
  }

  inline bool
  StringParser::charIsIn( char const queryChar,
                          std::string const& charSet )
  {
    if( charSet.find( queryChar ) != std::string::npos  )
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  inline bool
  StringParser::isOnlyCharsIn( std::string const& queryString,
                               std::string const& charSet )
  // this returns true if queryString consists only of chars in charSet.
  {
    if( queryString.empty() )
    {
      return true;
    }
    else if( queryString.find_first_not_of( charSet ) == std::string::npos )
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  inline std::string
  StringParser::substringToFirst( std::string const& stringToParse,
                                  std::string const& delimiterOfSubstring,
                                  std::string* const remainderString )
  // this sets delimiterOfSubstring as the single element of stringVector &
  // calls the above substringToFirst with stringVector.
  {
    stringVector.setSize( 1 );
    stringVector.getFront().assign( delimiterOfSubstring );
    return substringToFirst( stringToParse,
                             stringVector,
                             remainderString );
  }

  inline std::string
  StringParser::trimFromFront( std::string const& stringToTrim,
                               std::string const& charsToTrim )
  /* this returns the substring of stringToTrim which has had all the chars
   * removed which are in charsToTrim and appear in stringToTrim before the
   * first char which is not in charsToTrim.
   */
  {
    size_t
    startOfReturnString( stringToTrim.find_first_not_of( charsToTrim ) );
    if( startOfReturnString == std::string::npos )
    {
      return "";
    }
    else
    {
      return std::string( ( stringToTrim.begin() + startOfReturnString ),
                          stringToTrim.end() );
    }
  }

  inline std::string
  StringParser::trimFromBack( std::string const& stringToTrim,
                              std::string const& charsToTrim )
  /* this returns the substring of stringToTrim which has had all the chars
   * removed which are in charsToTrim and appear in stringToTrim after the
   * last char which is not in charsToTrim.
   */
  {
    size_t endOfReturnString( stringToTrim.find_last_not_of( charsToTrim ) );
    if( endOfReturnString == std::string::npos )
    {
      return "";
    }
    else
    {
      return std::string( stringToTrim.begin(),
                          ( stringToTrim.begin() + endOfReturnString + 1 ) );
    }
  }

  inline std::string
  StringParser::trimFromFrontAndBack( std::string const& stringToTrim,
                                      std::string const& charsToTrim )
  /* this returns the substring of stringToTrim which has had all the chars
   * removed which are in charsToTrim and appear in stringToTrim before the
   * first char which is not in charsToTrim and after the last char which is
   * not in charsToTrim.
   */
  {
    size_t
    startOfReturnString( stringToTrim.find_first_not_of( charsToTrim ) );
    if( startOfReturnString == std::string::npos )
    {
      return "";
    }
    else
    {
      return std::string( ( stringToTrim.begin() + startOfReturnString ),
                          ( stringToTrim.begin()
                            + stringToTrim.find_last_not_of( charsToTrim )
                            + 1 ) );
    }
  }

  inline void
  StringParser::parseByChar( std::string const& stringToParse,
                             VectorlikeArray< std::string >& destinationArray,
                             std::string const& divisionCharSet )
  /* this goes through stringToParse & creates new strings with all
   * characters between groups of 1 or more of any of the chars in
   * divisionCharSet, & puts them (as new strings) in order at the end of
   * destinationArray. the resulting strings in destinationArray will not
   * contain *any* instances of *any* of the characters in divisionCharSet.
   */
  {
    size_t wordStart( stringToParse.find_first_not_of( divisionCharSet ) );
    size_t wordEnd;
    while( wordStart != std::string::npos )
      // if there are any more chars in stringToParse that are not in
      // divisionCharSet, we have at least one substring to add.
    {
      wordEnd = stringToParse.find_first_of( divisionCharSet,
                                             wordStart );
      destinationArray.newEnd().assign( stringToParse.substr( wordStart,
                                                   ( wordEnd - wordStart ) ) );
      if( wordEnd != std::string::npos )
      {
        wordStart = stringToParse.find_first_not_of( divisionCharSet,
                                                     wordEnd );
      }
      else
      {
        wordStart = std::string::npos;
      }
    }
  }

  inline void
  StringParser::parseByChar( std::string const& stringToParse,
                             VectorlikeArray< std::string >& destinationArray,
                             char const& divisionChar )
  // this calls parseByChar with a string that consists just of divisionChar.
  {
    parseByChar( stringToParse,
                 destinationArray,
                 std::string( 1,
                              divisionChar ) );
  }

  /*template< class ForwardIteratorOfString >
  inline std::string
  joinWithSeparator( ForwardIteratorOfString const beginIterator,
                     ForwardIteratorOfString const endIterator,
                     std::string const& separatorString )
  *//* this returns a string that is the concatenation of all the strings from
   *  ForwardIterator beginIterator to  ForwardIterator beginIterator,
   * separated by separatorString.
   *//*
  {
    ForwardIteratorOfString localIterator( beginIterator );
    std::string returnString( "" );
    while( endIterator != beginIterator)
    {
      returnString.append( *localIterator );
      ++localIterator;
    }
    return returnString;
  }*/

  inline std::string
  StringParser::joinWithSeparator(
                           VectorlikeArray< std::string > const& stringsToJoin,
                                   std::string const& separatorString )
  // this prepares destinationString so that is the concatenation of all the
  // strings in stringsToJoin separated by separatorString.
  {
    if( 0 < stringsToJoin.getSize() )
    {
      std::string returnString( stringsToJoin.getFront() );
      for( int stringIndex( 1 );
           stringsToJoin.getSize() > stringIndex;
           ++stringIndex )
      {
        returnString.append( separatorString );
        returnString.append( stringsToJoin[ stringIndex ] );
      }
      return returnString;
    }
    else
    {
      return "";
    }
  }

  inline std::string
  StringParser::joinWithSeparator(
                              std::vector< std::string* > const& stringsToJoin,
                                   std::string const& separatorString )
  // this prepares destinationString so that is the concatenation of all the
  // strings in stringsToJoin separated by separatorString.
  {
    if( !(stringsToJoin.empty()) )
    {
      std::string returnString( *(stringsToJoin.front()) );
      for( std::vector< std::string* >::const_iterator
           stringIterator( stringsToJoin.begin() + 1 );
           stringsToJoin.end() > stringIterator;
           ++stringIterator )
      {
        returnString.append( separatorString );
        returnString.append( *(*stringIterator) );
      }
      return returnString;
    }
    else
    {
      return "";
    }
  }

  inline std::string
  StringParser::joinWithSeparator(
                                std::list< std::string* > const& stringsToJoin,
                                   std::string const& separatorString )
  // this prepares destinationString so that is the concatenation of all the
  // strings in stringsToJoin separated by separatorString.
  {
    if( !(stringsToJoin.empty()) )
    {
      std::list< std::string* >::const_iterator
      stringIterator( stringsToJoin.begin() );
      std::string returnString( *(*stringIterator) );
      ++stringIterator;
      while( stringsToJoin.end() != stringIterator )
      {
        returnString.append( separatorString );
        returnString.append( *(*stringIterator) );
        ++stringIterator;
      }
      return returnString;
    }
    else
    {
      return "";
    }
  }

  inline StringParser&
  StringParser::setDefaults( int const minimumNumberOfDigitsForInts,
                             char const paddingCharForInts,
                             int const numberOfMantissaDigits,
                             int const numberOfExponentDigits,
                             std::string const prefixForPositiveNumbers,
                             std::string const prefixForNegativeNumbers,
                             std::string const positiveExponentPrefix,
                             std::string const negativeExponentPrefix,
                             std::string const exponentCharacter )
  // this sets the default values that the StringParser instance uses as the
  // arguments for the static functions it calls with its own functions.
  {
    this->minimumNumberOfDigitsForInts = minimumNumberOfDigitsForInts;
    this->paddingCharForInts = paddingCharForInts;
    this->numberOfMantissaDigits = numberOfMantissaDigits;
    this->numberOfExponentDigits = numberOfExponentDigits;
    this->prefixForPositiveNumbers.assign( prefixForPositiveNumbers );
    this->prefixForNegativeNumbers.assign( prefixForNegativeNumbers );
    this->positiveExponentPrefix.assign( positiveExponentPrefix );
    this->negativeExponentPrefix.assign( negativeExponentPrefix );
    this->exponentCharacter.assign( exponentCharacter );
    return *this;
  }

  inline std::string
  StringParser::intToString( int inputInt ) const
  // this calls the static intToString with the StringParser instance's
  // arguments.
  {
    return intToString( inputInt,
                        minimumNumberOfDigitsForInts,
                        prefixForPositiveNumbers,
                        prefixForNegativeNumbers,
                        paddingCharForInts );
  }

  inline std::string
  StringParser::doubleToString( double inputDouble ) const
  // this calls the static doubleToString with the StringParser instance's
  // arguments.
  {
    return doubleToString( inputDouble,
                           numberOfMantissaDigits,
                           numberOfExponentDigits,
                           prefixForPositiveNumbers,
                           prefixForNegativeNumbers,
                           positiveExponentPrefix,
                           negativeExponentPrefix,
                           exponentCharacter );
  }

  inline std::stringstream&
  StringParser::getStringParsingStream( std::string const& stringToParse )
  {
    stringParsingStream.clear();
    stringParsingStream.str( stringToParse );
    return stringParsingStream;
  }

}

#endif /* STRINGPARSING_HPP_ */
