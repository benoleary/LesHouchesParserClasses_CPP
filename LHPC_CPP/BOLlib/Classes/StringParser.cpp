/*
 * StringParser.cpp
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

#include "StringParser.hpp"

namespace BOL
{
  std::string StringParser::returnString;
  std::stringstream StringParser::stringParsingStream;
  std::string const StringParser::whitespaceChars( " \t" );
  std::string const StringParser::newlineChars( "\n\r" );
  std::vector< char > StringParser::charBuffer;
  VectorlikeArray< std::string > StringParser::stringVector( 0 );
  int StringParser::numberOfDigits( 0 );
  int StringParser::tenToNumberOfDigits( 0 );


  std::string const&
  StringParser::intToString( int inputInt,
                             int const minimumNumberOfDigits,
                             std::string const prefixForPositiveNumbers,
                             std::string const prefixForNegativeNumbers,
                             char const paddingChar )
  /* this returns a reference to returnString after preparing it so that is
   * the ASCII version of an int in base 10, prefixed with
   * prefixForPositiveNumbers or prefixForNegativeNumbers depending on
   * whether it is positive or negative. it makes returnString have at least
   * minimumNumberOfDigits digit characters, filling it out with
   * paddingChars after prefixForPositiveNumbers/prefixForNegativeNumbers
   *  (e.g. intToString( 23, 4, "+", "-", '0' ) returns "+0023").
   */
  {
    if( 0 >= minimumNumberOfDigits )
    {
      std::cout
      << std::endl
      << "BOL::warning! StringParser::intToString( "
      << inputInt << ", " << minimumNumberOfDigits << ", "
      << prefixForPositiveNumbers << ", " << prefixForNegativeNumbers
      << " ) could not fit the integer into the given size!";
      // report a warning message.
      returnString.assign( "please_give_a_positive_number_of_digits" );
    }
    else
    {
      if( 0 > inputInt )
      {
        returnString.assign( prefixForNegativeNumbers );
        inputInt = -inputInt;
      }
      else
      {
        returnString.assign( prefixForPositiveNumbers );
      }
      // now the '+' or '-' or whatever is substituting has been inserted &
      // inputInt is positive semi-definite.
      positiveIntToCharBuffer( inputInt );
      int numberOfZeroesToInsert( minimumNumberOfDigits - numberOfDigits );
      // if numberOfZeroesToInsert is negative, then the number was longer than
      // the minimum output string length specified.
      if( 0 < numberOfZeroesToInsert )
      {
        returnString.append( (size_t)numberOfZeroesToInsert,
                             paddingChar );
      }
      returnString.append( charBuffer.begin(),
                           charBuffer.end() );
    }
    return returnString;
  }

  std::string const&
  StringParser::doubleToString( double inputDouble,
                                int const numberOfMantissaDigits,
                                int const numberOfExponentDigits,
                                std::string const prefixForPositiveNumbers,
                                std::string const prefixForNegativeNumbers,
                                std::string const positiveExponentPrefix,
                                std::string const negativeExponentPrefix,
                                std::string const exponentCharacter )
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
  {
    if( ( 0 >= numberOfMantissaDigits )
        ||
        ( 0 >= numberOfExponentDigits ) )
    {
      std::cout
      << std::endl
      << "BOL::warning! StringParser::doubleToString( "
      << inputDouble << ", " << numberOfMantissaDigits << ", "
      << numberOfExponentDigits << ", " << prefixForPositiveNumbers << ", "
      << prefixForNegativeNumbers << ", " << positiveExponentPrefix<< ", "
      << negativeExponentPrefix<< ", " << exponentCharacter
      << " ) could not fit the double into the given size!";
      // report a warning message.
      returnString.assign( "please_give_a_positive_number_of_digits" );
    }
    else
    {
      double formattedMantissa;
      if( 0.0 > inputDouble )
      {
        returnString.assign( prefixForNegativeNumbers );
        formattedMantissa = -inputDouble;
      }
      else
      {
        returnString.assign( prefixForPositiveNumbers );
        formattedMantissa = inputDouble;
      }
      if( 0.0 == formattedMantissa )
      {
        returnString.append( "0." );
        returnString.append( ( numberOfMantissaDigits - 1 ),
                             '0' );
        returnString.append( exponentCharacter );
        returnString.append( positiveExponentPrefix );
        returnString.append( numberOfExponentDigits,
                             '0' );
      }
      else if( 0.0 < formattedMantissa )
        // at this point any negative numbers will now be positive, so any
        // that fail this comparison should be NaN.
      {
        int tenToDigitsMinusOneAsInt( 1 );
        for( int mantissaDigitCount( 1 );
             numberOfMantissaDigits > mantissaDigitCount;
             ++mantissaDigitCount )
        {
          tenToDigitsMinusOneAsInt *= 10;
        }
        double tenToDigitsMinusOneAsDouble( (double)tenToDigitsMinusOneAsInt );
        double tenToDigits( 10.0 * tenToDigitsMinusOneAsDouble );
        int formattedExponent( 0 );
        while( tenToDigits <= formattedMantissa )
        {
          formattedMantissa *= 0.1;
          ++formattedExponent;
        }
        while( tenToDigitsMinusOneAsDouble > formattedMantissa )
        {
          formattedMantissa *= 10.0;
          --formattedExponent;
        }
        /* now formattedMantissa is between tenToDigitsMinusOneAsDouble
         * & tenToDigits, & hence has numberOfMantissaCharacters digits before
         * the decimal point.
         * however, now we have to round correctly:
         */
        int mantissaTimesTenToSomePowerAsInt( (int)formattedMantissa );
        if( 0.5 <= ( formattedMantissa
                     - (double)mantissaTimesTenToSomePowerAsInt ) )
        {
          ++mantissaTimesTenToSomePowerAsInt;
        }
        if( mantissaTimesTenToSomePowerAsInt
            >= ( 10 * tenToDigitsMinusOneAsInt) )
          // if rounding pushed mantissaTimesTenToSomePowerAsInt into having
          // too many digits...
        {
          mantissaTimesTenToSomePowerAsInt
          = ( mantissaTimesTenToSomePowerAsInt / 10 );
          ++formattedExponent;
        }
        positiveIntToCharBuffer( mantissaTimesTenToSomePowerAsInt );
        returnString.append( 1,
                             charBuffer[ 0 ] );
        returnString.append( 1,
                             '.' );
        returnString.append( ( charBuffer.begin() + 1 ),
                             charBuffer.end() );
        formattedExponent += ( numberOfMantissaDigits - 1 );
        // this accounts for all the multiplication to get the mantissa as an
        // int of the appropriate length.
        returnString.append( exponentCharacter );
        if( 0 > formattedExponent )
        {
          returnString.append( negativeExponentPrefix );
          formattedExponent = -formattedExponent;
        }
        else
        {
          returnString.append( positiveExponentPrefix );
        }
        positiveIntToCharBuffer( formattedExponent );
        int exponentZeroesToPrepend( numberOfExponentDigits - numberOfDigits );
        if( 0 < exponentZeroesToPrepend )
        {
          returnString.append( exponentZeroesToPrepend,
                               '0' );
        }
        returnString.append( charBuffer.begin(),
                             charBuffer.end() );
      }
      else
        // if it failed the comparison, it should be a NaN.
      {
        returnString.assign( UsefulStuff::nanString );
      }
    }
    return returnString;
  }

  void
  StringParser::transformToLowercase( std::string& stringToTransform )
  {
    unsigned int stringSize( stringToTransform.size() );
    for( unsigned int charCounter( 0 );
         stringSize > charCounter;
         ++charCounter )
      // go through each character in the string:
    {
      // if it's a lowercase character, replace it with its uppercase:
      if( 'A' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'a';
      }
      else if( 'B' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'b';
      }
      else if( 'C' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'c';
      }
      else if( 'D' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'd';
      }
      else if( 'E' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'e';
      }
      else if( 'F' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'f';
      }
      else if( 'F' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'g';
      }
      else if( 'H' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'h';
      }
      else if( 'I' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'i';
      }
      else if( 'J' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'j';
      }
      else if( 'K' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'k';
      }
      else if( 'L' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'l';
      }
      else if( 'M' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'm';
      }
      else if( 'N' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'n';
      }
      else if( 'O' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'o';
      }
      else if( 'P' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'p';
      }
      else if( 'Q' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'q';
      }
      else if( 'R' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'r';
      }
      else if( 'S' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 's';
      }
      else if( 'T' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 't';
      }
      else if( 'U' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'u';
      }
      else if( 'V' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'v';
      }
      else if( 'W' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'w';
      }
      else if( 'X' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'x';
      }
      else if( 'Y' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'y';
      }
      else if( 'Z' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'z';
      }
    }
  }

  void
  StringParser::transformToUppercase( std::string& stringToTransform )
  {
    unsigned int stringSize( stringToTransform.size() );
    for( unsigned int charCounter( 0 );
         stringSize > charCounter;
         ++charCounter )
      // go through each character in the string:
    {
      // if it's a lowercase character, replace it with its uppercase:
      if( 'a' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'A';
      }
      else if( 'b' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'B';
      }
      else if( 'c' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'C';
      }
      else if( 'd' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'D';
      }
      else if( 'e' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'E';
      }
      else if( 'f' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'F';
      }
      else if( 'g' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'G';
      }
      else if( 'h' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'H';
      }
      else if( 'i' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'I';
      }
      else if( 'j' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'J';
      }
      else if( 'k' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'K';
      }
      else if( 'l' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'L';
      }
      else if( 'm' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'M';
      }
      else if( 'n' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'N';
      }
      else if( 'o' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'O';
      }
      else if( 'p' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'P';
      }
      else if( 'q' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'Q';
      }
      else if( 'r' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'R';
      }
      else if( 's' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'S';
      }
      else if( 't' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'T';
      }
      else if( 'u' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'U';
      }
      else if( 'v' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'V';
      }
      else if( 'w' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'W';
      }
      else if( 'x' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'X';
      }
      else if( 'y' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'Y';
      }
      else if( 'z' == stringToTransform[ charCounter ] )
      {
        stringToTransform[ charCounter ] = 'Z';
      }
    }
  }

  char
  StringParser::charForSingleDigit( int const singleDigitAsInt )
  {
    char returnChar( '?' );
    if( 0 == singleDigitAsInt )
    {
      returnChar = '0';
    }
    else if( 1 == singleDigitAsInt )
    {
      returnChar = '1';
    }
    else if( 2 == singleDigitAsInt )
    {
      returnChar = '2';
    }
    else if( 3 == singleDigitAsInt )
    {
      returnChar = '3';
    }
    else if( 4 == singleDigitAsInt )
    {
      returnChar = '4';
    }
    else if( 5 == singleDigitAsInt )
    {
      returnChar = '5';
    }
    else if( 6 == singleDigitAsInt )
    {
      returnChar = '6';
    }
    else if( 7 == singleDigitAsInt )
    {
      returnChar = '7';
    }
    else if( 8 == singleDigitAsInt )
    {
      returnChar = '8';
    }
    else if( 9 == singleDigitAsInt )
    {
      returnChar = '9';
    }
    else if( 10 == singleDigitAsInt )
    {
      returnChar = 'A';
    }
    else if( 11 == singleDigitAsInt )
    {
      returnChar = 'B';
    }
    else if( 12 == singleDigitAsInt )
    {
      returnChar = 'C';
    }
    else if( 13 == singleDigitAsInt )
    {
      returnChar = 'D';
    }
    else if( 14 == singleDigitAsInt )
    {
      returnChar = 'E';
    }
    else if( 15 == singleDigitAsInt )
    {
      returnChar = 'F';
    }
    return returnChar;
  }

  std::string const&
  StringParser::substringToFirst( std::string const& stringToParse,
                   VectorlikeArray< std::string > const& delimitersOfSubstring,
                                  std::string* const remainderString )
  /* this returns the substring of stringToParse from its beginning up to the
   * first instance of any of the strings in delimitersOfSubstring within
   * stringToParse. if stringToParse does not contain any of those strings as
   * a substring, the whole of stringToParse is returned, otherwise the
   * substring up to but not including the first of any found strings from
   * delimitersOfSubstring is returned. if remainderString is not NULL, the
   * remainder of stringToParse that is not returned is put into
   * remainderString.
   */
  {
    size_t
    delimiterPosition( stringToParse.find( delimitersOfSubstring[ 0 ] ) );
    size_t comparisonPosition;
    for( int stringIndex( delimitersOfSubstring.getLastIndex() );
         0 < stringIndex;
         --stringIndex )
    {
      comparisonPosition
      = stringToParse.find( delimitersOfSubstring[ stringIndex ] );
      if( comparisonPosition < delimiterPosition )
      {
        delimiterPosition = comparisonPosition;
      }
    }
    // debugging:
    /**std::cout << std::endl << "debugging:"
    << std::endl
    << "StringParser::substringToFirst( \n\"" << stringToParse << "\", \""
    << delimitersOfSubstring[ 0 ] << "\" + "
    << delimitersOfSubstring.getLastIndex() << " other delimiter strings, "
    << remainderString << " ) found delimiterPosition = " << delimiterPosition;
    std::cout << std::endl;**/

    // now delimiterPosition marks the position of the first of any of the
    // strings in delimitersOfSubstring which were found in stringToParse.
    if( std::string::npos == delimiterPosition )
    {
      return stringToParse;
      if( NULL != remainderString )
      {
        remainderString->assign( "" );
      }
    }
    else
    {
      returnString.assign( stringToParse.begin(),
                           ( stringToParse.begin() + delimiterPosition ) );
      if( NULL != remainderString )
      {
        remainderString->assign( ( stringToParse.begin() + delimiterPosition ),
                                 stringToParse.end() );
      }
      return returnString;
    }
  }

  std::string const&
  StringParser::firstWordOf( std::string const& stringToParse,
                             std::string* const remainderString,
                             std::string const& separatorChars )
  /* this parses the first substring without any of the characters in
   * separatorChars & returns it, filling remainderString with the rest if
   * it is not NULL.
   */
  {
    size_t wordStart( stringToParse.find_first_not_of( separatorChars ) );
    if( std::string::npos == wordStart )
    {
      returnString.assign( "" );
      if( NULL != remainderString )
      {
        remainderString->assign( "" );
      }
    }
    else
    {
      size_t wordEnd( stringToParse.find_first_of( separatorChars,
                                                   wordStart ) );
      returnString.assign( stringToParse.substr( wordStart,
                                                 ( wordEnd - wordStart ) ) );
      if( NULL != remainderString )
      {
        wordStart = stringToParse.find_first_not_of( separatorChars,
                                                     wordEnd );
        if( std::string::npos != wordStart )
        {
          remainderString->assign( stringToParse.substr( wordStart ) );
        }
        else
        {
          remainderString->assign( "" );
        }
      }
    }
    return returnString;
  }

  int
  StringParser::intForSingleDigit( char const singleDigitAsChar )
  {
    char returnInt( (int)(UsefulStuff::notANumber) );
    if( '0' == singleDigitAsChar )
    {
      returnInt = 0;
    }
    else if( '1' == singleDigitAsChar )
    {
      returnInt = 1;
    }
    else if( '2' == singleDigitAsChar )
    {
      returnInt = 2;
    }
    else if( '3' == singleDigitAsChar )
    {
      returnInt = 3;
    }
    else if( '4' == singleDigitAsChar )
    {
      returnInt = 4;
    }
    else if( '5' == singleDigitAsChar )
    {
      returnInt = 5;
    }
    else if( '6' == singleDigitAsChar )
    {
      returnInt = 6;
    }
    else if( '7' == singleDigitAsChar )
    {
      returnInt = 7;
    }
    else if( '8' == singleDigitAsChar )
    {
      returnInt = 8;
    }
    else if( '9' == singleDigitAsChar )
    {
      returnInt = 9;
    }
    else if( 'A' == singleDigitAsChar )
    {
      returnInt = 10;
    }
    else if( 'B' == singleDigitAsChar )
    {
      returnInt = 11;
    }
    else if( 'C' == singleDigitAsChar )
    {
      returnInt = 12;
    }
    else if( 'D' == singleDigitAsChar )
    {
      returnInt = 13;
    }
    else if( 'E' == singleDigitAsChar )
    {
      returnInt = 14;
    }
    else if( 'F' == singleDigitAsChar )
    {
      returnInt = 15;
    }
    return returnInt;
  }


  StringParser::StringParser( int const minimumNumberOfDigitsForInts,
                              char const paddingCharForInts,
                              int const numberOfMantissaDigits,
                              int const numberOfExponentDigits,
                              std::string const prefixForPositiveNumbers,
                              std::string const prefixForNegativeNumbers,
                              std::string const positiveExponentPrefix,
                              std::string const negativeExponentPrefix,
                              std::string const exponentCharacter ) :
      minimumNumberOfDigitsForInts( minimumNumberOfDigitsForInts ),
      paddingCharForInts( paddingCharForInts ),
      numberOfMantissaDigits( numberOfMantissaDigits ),
      numberOfExponentDigits( numberOfExponentDigits ),
      prefixForPositiveNumbers( prefixForPositiveNumbers ),
      prefixForNegativeNumbers( prefixForNegativeNumbers ),
      positiveExponentPrefix( positiveExponentPrefix ),
      negativeExponentPrefix( negativeExponentPrefix ),
      exponentCharacter( exponentCharacter )
  {
    // just an initialization list.
  }

  StringParser::~StringParser()
  {
    // does nothing.
  }

}
