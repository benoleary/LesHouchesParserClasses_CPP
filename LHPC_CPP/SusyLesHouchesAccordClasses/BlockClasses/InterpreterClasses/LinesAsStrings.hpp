/*
 * LinesAsStrings.hpp
 *
 *  Created on: Mar 12, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.LHPC_CPP.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#ifndef LINESASSTRINGS_HPP_
#define LINESASSTRINGS_HPP_

#include <string>
#include "StandardBlockTemplate.hpp"

namespace LHPC
{
  namespace SLHA
  {
    namespace InterpreterClass
    {
      // this class interprets SLHA blocks as just a set of full lines as
      // std::strings.
      class LinesAsStrings : public InterpreterTemplate< std::string >
      {
      public:
        LinesAsStrings();
        virtual
        ~LinesAsStrings();

        std::string
        operator()( int const whichLine ) const;
        // this just returns the equivalent line from
        std::string
        operator[]( int const whichLine ) const { return (*this)(
                                                                 whichLine ); }
        virtual std::string const&
        interpretAsString();
        // see base version's description.
        virtual void
        respondToObservedSignal();
      };





      inline std::string
      LinesAsStrings::operator()( int const whichLine ) const
      // const version of above.
      {
        std::string
        returnString( (*(this->stringsToInterpret))[ whichLine ].first );
        returnString.append( (*(this->stringsToInterpret))[ whichLine ].second );
        return returnString;
      }

      inline std::string const&
      LinesAsStrings::interpretAsString()
      // see base version's description.
      {
        this->stringInterpretation.clear();
        for( int whichLine( 1 );
             this->stringsToInterpret->getNumberOfBodyLines() >= whichLine;
             ++whichLine )
        {
          this->stringInterpretation.append(
                              (*(this->stringsToInterpret))[ whichLine ].first );
          this->stringInterpretation.append(
                             (*(this->stringsToInterpret))[ whichLine ].second );
          this->stringInterpretation.append( "\n" );
        }
        return this->stringInterpretation;
      }

      inline void
      LinesAsStrings::respondToObservedSignal()
      {
        // does nothing.
      }

    }

  }

}


#endif /* LINESASSTRINGS_HPP_ */
