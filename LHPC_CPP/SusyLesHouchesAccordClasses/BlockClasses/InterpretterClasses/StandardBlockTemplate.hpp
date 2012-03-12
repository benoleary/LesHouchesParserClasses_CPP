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

#include "../../../BOLlib/Classes/UsefulStuff.hpp"
#include "BlockInterpretter.hpp"
#include "../../../MassEigenstateCollectionClasses/ExtendedMass.hpp"

namespace LHPC
{
  namespace SLHA
  {
    namespace InterpretterClass
    {
      // this template class derives from SlhaBlock to provide a base class for
      // blocks with values which are indexed in various ways.
      template< class ValueType >
      class StandardBlockTemplate : public BlockInterpretter
      {
      public:
        StandardBlockTemplate( ValueType const& defaultUnsetValue,
                               bool const& isVerbose );
        virtual
        ~StandardBlockTemplate();


      protected:
        bool const& isVerbose;
        ValueType const defaultUnsetValue;
        ValueType valueFromString;
        std::string stringFromValue;
        std::string valuePrintingString;

        ValueType const&
        stringToValue( std::string const& stringToConvert );
        // this sets valueFromString according to the interpretation of
        // stringToConvert.
        std::string const&
        valueToString( ValueType const& valueToConvert );
        // this sets stringFromValue according to the interpretation of
        // valueToConvert.
        std::string const&
        valueToPrintingString( ValueType const& valueToPrint );
        // this puts 3 spaces into valuePrintingString, then
        // valueToString( valueToPrint ).
      };





      template< class ValueType >
      inline
      StandardBlockTemplate< ValueType >::StandardBlockTemplate(
                                            ValueType const& defaultUnsetValue,
                                                      bool const& isVerbose ) :
          BlockInterpretter(),
          defaultUnsetValue( defaultUnsetValue ),
          isVerbose( isVerbose ),
          valueFromString( defaultUnsetValue ),
          stringFromValue( "no_string_interpretation_given" ),
          valuePrintingString( "   no_string_interpretation_given" )
      {
        // just an initialization list.
      }

      template< class ValueType >
      inline
      StandardBlockTemplate< ValueType >::~StandardBlockTemplate()
      {
        // does nothing.
      }

      template< class ValueType >
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

      template< class ValueType >
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

      template< class ValueType >
      inline std::string const&
      StandardBlockTemplate< ValueType >::valueToPrintingString(
                                               ValueType const& valueToPrint )
      /* this puts 3 spaces into returnString, then
       * valueToString( valueToPrint ), then either way afterwards three more
       * spaces then "# no comment\n" is appended.
       */
      {
        valuePrintingString.assign( "   " );
        valuePrintingString.append( this->valueToString( valueToPrint ) );
        return valuePrintingString;
      }

    }

  }

}

#endif /* STANDARDBLOCKTEMPLATE_HPP_ */
