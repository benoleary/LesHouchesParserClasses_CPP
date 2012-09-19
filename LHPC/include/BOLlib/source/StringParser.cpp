/*
 * StringParser.cpp
 *
 *  Created on: Jan 6, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *
 *      This file is part of BOLlib, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.BOLlib.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#include "StringParser.hpp"

namespace BOL
{
  std::string const StringParser::whitespaceChars( " \t" );
  std::string const StringParser::newlineChars( "\n\r" );
  std::string const StringParser::whitespaceAndNewlineChars( " \t\n\r" );

  char const StringParser::lowercaseMinusUppercase( 'a' - 'A' );
  std::stringstream StringParser::stringParsingStream;
  std::vector< char > StringParser::charBuffer;
  VectorlikeArray< std::string > StringParser::stringVector( 0 );


  std::string
  StringParser::intToString( int inputInt,
                             int const minimumNumberOfDigits,
                             std::string const prefixForPositiveNumbers,
                             std::string const prefixForNegativeNumbers,
                             char const paddingChar )
  /* this returns a std::string that is the ASCII version of an int in base
   * 10, prefixed with prefixForPositiveNumbers or prefixForNegativeNumbers
   * depending on whether it is positive or negative. it makes returnString
   * have at least minimumNumberOfDigits digit characters, filling it out
   * with paddingChars after
   * prefixForPositiveNumbers/prefixForNegativeNumbers
   * (e.g. intToString( 23, 4, "+", "-" ) returns "+0023").
   */
  {
    std::string returnString;
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
      std::string unpaddedIntAsString( positiveIntToString( inputInt ) );
      int numberOfZeroesToInsert( minimumNumberOfDigits
                                  - (int)(unpaddedIntAsString.size()) );
      // if numberOfZeroesToInsert is negative, then the number was longer than
      // the minimum output string length specified.
      if( 0 < numberOfZeroesToInsert )
      {
        returnString.append( (size_t)numberOfZeroesToInsert,
                             paddingChar );
      }
      returnString.append( unpaddedIntAsString );
    }
    return returnString;
  }

  std::string
  StringParser::doubleToString( double inputDouble,
                                int const numberOfMantissaDigits,
                                int const numberOfExponentDigits,
                                std::string const prefixForPositiveNumbers,
                                std::string const prefixForNegativeNumbers,
                                std::string const positiveExponentPrefix,
                                std::string const negativeExponentPrefix,
                                std::string const exponentCharacter )
  /* this returns a std::string that is the ASCII version of a double in base
   * 10, in the form specified thusly:
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
    std::string returnString;
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
        std::string mantissaTimesTenToSomePowerAsString( positiveIntToString(
                                          mantissaTimesTenToSomePowerAsInt ) );
        returnString.append( 1,
                             mantissaTimesTenToSomePowerAsString[ 0 ] );
        returnString.append( 1,
                             '.' );
        returnString.append( mantissaTimesTenToSomePowerAsString,
                             1,
                          ( mantissaTimesTenToSomePowerAsString.size() - 1 ) );
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
        std::string
        exponentIntAsString( positiveIntToString( formattedExponent ) );
        int exponentZeroesToPrepend( numberOfExponentDigits
                                     - (int)(exponentIntAsString.size()) );
        if( 0 < exponentZeroesToPrepend )
        {
          returnString.append( exponentZeroesToPrepend,
                               '0' );
        }
        returnString.append( exponentIntAsString );
      }
      else
        // if it failed the comparison, it should be a NaN.
      {
        returnString.assign( UsefulStuff::nanString );
      }
    }
    return returnString;
  }

  bool
  StringParser::stringsMatchIgnoringCase( std::string const& firstString,
                                          std::string const& secondString )
  // this returns true if both strings would be identical if all their
  // uppercase chars were converted to lowercase.
  {
    size_t stringSize( firstString.size() );
    if( secondString.size() == stringSize )
      // if the strings match in size...
    {
      bool returnBool( true );
      // it is assumed that the strings match, unless a char turns out to
      // differ.
      for( unsigned int charCounter( 0 );
           ( returnBool
             &&
             ( stringSize > charCounter ) );
           ++charCounter )
        // go through each character in the string:
      {
        // if the strings do not match at this char, check to see if they are
        // letters that just differ in case:
        if( ( secondString[ charCounter ] != firstString[ charCounter ] )
            &&
            !( ( firstString[ charCounter ] >= 'A' )
               &&
               ( firstString[ charCounter ] <= 'Z' )
               &&
               ( secondString[ charCounter ]
                 == ( firstString[ charCounter ]
                      + lowercaseMinusUppercase ) ) )
             &&
             !( ( firstString[ charCounter ] >= 'a' )
                &&
                ( firstString[ charCounter ] <= 'z' )
                &&
                ( secondString[ charCounter ]
                  == ( firstString[ charCounter ]
                       - lowercaseMinusUppercase ) ) ) )
        {
          returnBool = false;
        }
      }
      return returnBool;
    }
    else
    {
      return false;
    }
  }

  std::vector< int >
  StringParser::stringToIntVector( std::string stringToInterpret )
  {
    substituteCharacterWith( stringToInterpret,
                             ',',
                             ' ' );
    substituteCharacterWith( stringToInterpret,
                             ';',
                             ' ' );
    std::vector< int > returnVector;
    std::string indicesString( trimFromFrontAndBack( stringToInterpret,
                                                     whitespaceChars ) );
    if( !(indicesString.empty()) )
    {
      std::stringstream&
      streamToParse( getStringParsingStream( indicesString ) );
      double parsedIntAsDouble;
      while( streamToParse.good() )
      {
        streamToParse >> parsedIntAsDouble;
        returnVector.push_back( (int)parsedIntAsDouble );
      }
    }
    return returnVector;
  }

  std::string
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

    // now delimiterPosition marks the position of the first of any of the
    // strings in delimitersOfSubstring which were found in stringToParse.
    if( std::string::npos == delimiterPosition )
    {
      if( NULL != remainderString )
      {
        remainderString->assign( "" );
      }
      return stringToParse;
    }
    else
    {
      std::string returnString( stringToParse.begin(),
                               ( stringToParse.begin() + delimiterPosition ) );
      if( NULL != remainderString )
      {
        remainderString->assign( ( stringToParse.begin() + delimiterPosition ),
                                 stringToParse.end() );
      }
      return returnString;
    }
  }

  std::string
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
      if( NULL != remainderString )
      {
        remainderString->assign( "" );
      }
      return "";
    }
    else
    {
      size_t wordEnd( stringToParse.find_first_of( separatorChars,
                                                   wordStart ) );
      std::string returnString( stringToParse.substr( wordStart,
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
      return returnString;
    }
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

  std::string
  StringParser::positiveIntToString( int positiveInt )
  // this puts the digits of positiveInt into charBuffer in the order of
  // digit for highest power of 10 1st.
  {
    int numberOfDigits( 1 );
    int tenToNumberOfDigits( 10 );
    while( positiveInt >= tenToNumberOfDigits )
    {
      tenToNumberOfDigits *= 10;
      ++numberOfDigits;
    }
    std::string digitBuffer( "" );
    int digitInt;
    while( 0 < positiveInt )
    {
      tenToNumberOfDigits = ( tenToNumberOfDigits / 10 );
      digitInt = 0;
      while( tenToNumberOfDigits <= positiveInt )
      {
        positiveInt -= tenToNumberOfDigits;
        ++digitInt;
      }
      digitBuffer.push_back( charForSingleDigit( digitInt ) );
    }
    for( int zeroesToPushBack( numberOfDigits - digitBuffer.size() );
         0 < zeroesToPushBack;
         --zeroesToPushBack )
    {
      digitBuffer.push_back( '0' );
    }
    return digitBuffer;
  }

}
