/*
 * StandardBlockTemplate.hpp
 *
 *  Created on: Feb 8, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.LHPC_CPP.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#ifndef STANDARDBLOCKTEMPLATE_HPP_
#define STANDARDBLOCKTEMPLATE_HPP_

#include "../../BOLlib/Classes/UsefulStuff.hpp"
#include "../SlhaBlock.hpp"
#include "../../MassEigenstateCollectionClasses/ExtendedMass.hpp"

namespace LHPC
{
  namespace SLHA
  {
    namespace BlockClass
    {
      // this template class derives from SlhaBlock to provide a base class for
      // blocks with values which are indexed in various ways.
      template< typename ValueType >
      class StandardBlockTemplate : public SlhaBlock
      {
      public:
        StandardBlockTemplate( std::string const& blockName,
                               ValueType const& defaultUnsetValue,
                               bool const& isVerbose,
                               int const indexDigits,
                               std::string const blockHeaderComment );
        virtual
        ~StandardBlockTemplate();


      protected:
        ValueType const defaultUnsetValue;
        ValueType valueFromString;
        std::string stringFromValue;
        int const indexDigits;
        // this is the number of characters to print before the value,
        // including the characters used to print the index.
        std::string const blockHeaderComment;

        ValueType const&
        stringToValue( std::string const& stringToConvert );
        // this sets valueFromString according to the interpretation of
        // stringToConvert.
        std::string const&
        valueToString( ValueType const& valueToConvert );
        // this sets stringFromValue according to the interpretation of
        // valueToConvert.
        void
        putIndexIntoReturnString( int indexToPrint );
        // this puts a single space then indexToStream with indexDigits into
        // returnString.
        void
        putValueIntoReturnString( ValueType const& valueToPrint );
        /* this puts 3 spaces into returnString, then
         * valueToString( valueToPrint ), then either way afterwards three more
         * spaces then "# no comment\n" is appended.
         */
      };




      template< typename ValueType >
      inline
      StandardBlockTemplate< ValueType >::StandardBlockTemplate(
                                                  std::string const& blockName,
                                            ValueType const& defaultUnsetValue,
                                                         bool const& isVerbose,
                                                         int const indexDigits,
                                       std::string const blockHeaderComment ) :
          SlhaBlock( blockName,
                     isVerbose,
                     blockHeaderComment ),
          defaultUnsetValue( defaultUnsetValue ),
          valueFromString( defaultUnsetValue ),
          stringFromValue( "no_string_interpretation_given" ),
          indexDigits( indexDigits ),
          blockHeaderComment( blockHeaderComment )
      {
        // just an initialization list.
      }

      template< typename ValueType >
      inline
      StandardBlockTemplate< ValueType >::~StandardBlockTemplate()
      {
        // does nothing.
      }


      template< typename ValueType >
      inline void
      StandardBlockTemplate< ValueType >::putIndexIntoReturnString(
                                                             int indexToPrint )
      // this puts a single space then indexToStream with indexDigits into
      // stringParsingStream.
      {
        returnString.append( " " );
        if( 0 > indexToPrint )
        {
          currentWord.assign( "-" );
          indexToPrint = -indexToPrint;
        }
        else
        {
          currentWord.assign( "" );
        }
        currentWord.append( BOL::StringParser::intToString( indexToPrint,
                                                            1,
                                                            "" ) );
        if( (int)currentWord.size() < indexDigits )
        {
          returnString.append( ( indexDigits - currentWord.size() ),
                               ' ' );
        }
        returnString.append( currentWord );
      }

      template< typename ValueType >
      inline void
      StandardBlockTemplate< ValueType >::putValueIntoReturnString(
                                               ValueType const& valueToPrint )
      /* this puts 3 spaces into returnString, then
       * valueToString( valueToPrint ), then either way afterwards three more
       * spaces then "# no comment\n" is appended.
       */
      {
        returnString.append( "   " );
        this->valueToString( valueToPrint );
        returnString.append( stringFromValue );
        returnString.append( "   # no comment\n" );
      }

      template< typename ValueType >
      inline ValueType const&
      StandardBlockTemplate< ValueType >::stringToValue(
                                           std::string const& stringToConvert )
      /* this sets valueFromString according to the interpretation of
       * stringToConvert. this default version leaves stringFromValue as
       * defaultUnsetValue.
       */
      {
        return defaultUnsetValue;
      }

      template<>
      inline int const&
      StandardBlockTemplate< int >::stringToValue(
                                           std::string const& stringToConvert )
      // this sets valueFromString according to the interpretation of
      // stringToConvert.
      {
        valueFromString = BOL::StringParser::stringToInt( stringToConvert );
        return valueFromString;
      }

      template<>
      inline double const&
      StandardBlockTemplate< double >::stringToValue(
                                           std::string const& stringToConvert )
      // this sets valueFromString according to the interpretation of
      // stringToConvert.
      {
        valueFromString = BOL::StringParser::stringToDouble( stringToConvert );
        return valueFromString;
      }

      template<>
      inline std::string const&
      StandardBlockTemplate< std::string >::stringToValue(
                                           std::string const& stringToConvert )
      // this sets valueFromString according to the interpretation of
      // stringToConvert.
      {
        valueFromString.assign( stringToConvert );
        return valueFromString;
      }

      template<>
      inline ExtendedMass const&
      StandardBlockTemplate< ExtendedMass >::stringToValue(
                                           std::string const& stringToConvert )
      // this sets valueFromString according to the interpretation of
      // stringToConvert.
      {
        SlhaBlock::currentWord.assign( BOL::StringParser::firstWordOf(
                                                               stringToConvert,
                                                  &(SlhaBlock::firstRemainder),
                                                                 " \t\r\n" ) );
        double
        parsedDouble( BOL::StringParser::stringToDouble( currentWord ) );
        SlhaBlock::currentWord.assign( BOL::StringParser::firstWordOf(
                                                     SlhaBlock::firstRemainder,
                                                 &(SlhaBlock::secondRemainder),
                                                                 " \t\r\n" ) );
        valueFromString.setValues( parsedDouble,
                                 BOL::StringParser::stringToInt( currentWord ),
                        BOL::StringParser::stringToDouble( secondRemainder ) );
        return valueFromString;
      }

      template< typename ValueType >
      inline std::string const&
      StandardBlockTemplate< ValueType >::valueToString(
                                              ValueType const& valueToConvert )
      /* this sets stringFromValue according to the interpretation of
       * valueToConvert. this default version leaves stringFromValue as a
       * default error string.
       */
      {
        return stringFromValue;
      }

      template<>
      inline std::string const&
      StandardBlockTemplate< int >::valueToString( int const& valueToConvert )
      // this sets stringFromValue according to the interpretation of
      // valueToConvert.
      {
        stringFromValue.assign( BOL::StringParser::intToString( valueToConvert,
                                                                1,
                                                                "",
                                                                "-",
                                                                ' ' ) );
        return stringFromValue;
      }

      template<>
      inline std::string const&
      StandardBlockTemplate< double >::valueToString(
                                                 double const& valueToConvert )
      // this sets stringFromValue according to the interpretation of
      // valueToConvert.
      {
        stringFromValue.assign( slhaDoubleMaker.doubleToString(
                                                            valueToConvert ) );
        return stringFromValue;
      }

      template<>
      inline std::string const&
      StandardBlockTemplate< std::string >::valueToString(
                                            std::string const& valueToConvert )
      // this sets stringFromValue according to the interpretation of
      // valueToConvert.
      {
        stringFromValue.assign( valueToConvert );
        return stringFromValue;
      }

      template<>
      inline std::string const&
      StandardBlockTemplate< ExtendedMass >::valueToString(
                                           ExtendedMass const& valueToConvert )
      // this sets stringFromValue according to the interpretation of
      // valueToConvert.
      {
        stringFromValue.assign( slhaDoubleMaker.doubleToString(
                                                  valueToConvert.getMass() ) );
        stringFromValue.append( "   " );
        stringFromValue.append( BOL::StringParser::intToString(
                                                    valueToConvert.getScheme(),
                                                                2,
                                                                "",
                                                                "-",
                                                                ' ' ) );
        stringFromValue.append( "   " );
        stringFromValue.append( slhaDoubleMaker.doubleToString(
                                                 valueToConvert.getScale() ) );
        return stringFromValue;
      }

    }

  }

}

#endif /* STANDARDBLOCKTEMPLATE_HPP_ */
