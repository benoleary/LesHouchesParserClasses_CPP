/*
 * IndexedInterpreter.hpp
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

#ifndef INDEXEDINTERPRETER_HPP_
#define INDEXEDINTERPRETER_HPP_

#include "InterpreterTemplate.hpp"

namespace LHPC
{
  namespace SLHA
  {
    namespace InterpreterClass
    {
      // this class extends InterpreterTemplate for blocks with an
      // index or with indices.
      template< class ValueClass >
      class IndexedInterpreter : public InterpreterTemplate< ValueClass >
      {
      public:
        IndexedInterpreter();
        virtual
        ~IndexedInterpreter();

        virtual void
        setIndexDigits( int const indexDigits );


      protected:
        int indexDigits;
        // this is the number of characters to print before the value,
        // including the characters used to print the index.
        std::string indexPrintingString;
        std::string indexHoldingString;
        int indexPadding;

        std::string const&
        indexToPrintingString( int indexToPrint );
        // this puts a single space then indexToPrint with indexDigits into
        // indexPrintingString & returns it.
      };





      template< class ValueClass >
      inline
      IndexedInterpreter< ValueClass >::IndexedInterpreter() :
          InterpreterTemplate< ValueClass >(),
          indexDigits( 5 ),
          indexPrintingString( "" ),
          indexHoldingString( "" ),
          indexPadding( 0 )
      {
        // just an initialization list.
      }

      template< class ValueClass >
      inline
      IndexedInterpreter< ValueClass >::~IndexedInterpreter()
      {
        // does nothing.
      }


      template< class ValueClass >
      inline void
      IndexedInterpreter< ValueClass >::setIndexDigits( int const indexDigits )
      {
        this->indexDigits = indexDigits;
      }

      template< class ValueClass >
      inline std::string const&
      IndexedInterpreter< ValueClass >::indexToPrintingString(
                                                             int indexToPrint )
      // this puts a single space then indexToPrint with indexDigits into
      // indexPrintingString & returns it.
      {
        indexHoldingString.assign(
                BlockInterpreter::slhaIntHelper.intToString( indexToPrint ) );
        indexPadding = ( indexDigits - indexHoldingString.size() + 1 );
        if( 0 < indexPadding )
        {
          indexPrintingString.assign( indexPadding,
                                      ' ' );
        }
        else
        {
          indexPrintingString.assign( " " );
        }
        indexPrintingString.append( indexHoldingString );
        return indexPrintingString;
      }

    }

  }

}

#endif /* INDEXEDINTERPRETER_HPP_ */
