/*
 * LineData.cpp
 *
 *  Created on: Feb 26, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.LHPC_CPP.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#include "LineData.hpp"

namespace LHPC
{
  namespace SLHA
  {
    namespace SpectrumPlotting
    {
      std::string LineData::remainderString( "" );
      BOL::StringParser LineData::overlargeMassPrinter( 1,
                                                        '0',
                                                        3,
                                                        2,
                                                        "" );

      LineData::LineData( std::string const& dataString,
                          double const massValue ) :
          columnIndex( 0 ),
          whichJustification( leftJustified ),
          massValue( massValue ),
          labelPosition( -1.0 ),
          labelString( "error" ),
          colorString( "black" )
      {
        if( 0.0 > massValue )
        {
          this->massValue = -massValue;
        }
        columnIndex
        = BOL::StringParser::stringToInt( BOL::StringParser::firstWordOf(
                                                                    dataString,
                                                              &remainderString,
                                        BOL::StringParser::whitespaceChars ) );
        if( 0 == ( columnIndex % 2 ) )
        {
          whichJustification = rightJustified;
        }
        colorString.assign( BOL::StringParser::firstWordOf( remainderString,
                                                            &labelString,
                                        BOL::StringParser::whitespaceChars ) );
        labelString.assign( BOL::StringParser::trimFromFrontAndBack(
                                                                   labelString,
                                        BOL::StringParser::whitespaceChars ) );
      }

      LineData::LineData( LineData const& copySource ) :
          columnIndex( copySource.columnIndex ),
          whichJustification( copySource.whichJustification ),
          massValue( copySource.massValue ),
          labelPosition( copySource.labelPosition ),
          labelString( copySource.labelString ),
          colorString( copySource.colorString )
      {
        // just an initialization list.
      }

      LineData::~LineData()
      {
        // does nothing.
      }

    }

  }

}
