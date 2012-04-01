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
        IndexedInterpreter( int const numberOfIndices );
        virtual
        ~IndexedInterpreter();

        virtual void
        setIndexDigits( std::vector< int > const& indexDigitsVector );


      protected:
        int const numberOfIndices;
        std::vector< int > indexDigitsVector;
        // this is the number of characters to print before the value,
        // including the characters used to print the index, for each index.
        std::vector< int > indexPrintingVector;
        std::string indexPrintingString;
        std::string indexHoldingString;
        int indexPadding;

        std::string const&
        indicesToPrintingString();
        /* this puts a single space then each indexPrintingVector entry with
         * its corresponding indexDigitsVector entry into indexPrintingString &
         * returns it.
         */
      };





      template< class ValueClass >
      inline
      IndexedInterpreter< ValueClass >::IndexedInterpreter(
                                                  int const numberOfIndices ) :
          InterpreterTemplate< ValueClass >(),
          numberOfIndices( numberOfIndices ),
          indexDigitsVector( numberOfIndices,
                             0 ),
          indexPrintingVector( numberOfIndices,
                               0 ),
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
      IndexedInterpreter< ValueClass >::setIndexDigits(
                                  std::vector< int > const& indexDigitsVector )
      {
        this->indexDigitsVector = indexDigitsVector;
      }

      template< class ValueClass >
      inline std::string const&
      IndexedInterpreter< ValueClass >::indicesToPrintingString()
      /* this puts a single space then each indexPrintingVector entry with
       * its corresponding indexDigitsVector entry into indexPrintingString &
       * returns it.
       */
      {
        indexPrintingString.clear();
        for( int whichIndex( 0 );
             numberOfIndices > whichIndex;
             ++whichIndex )
        {
          indexHoldingString.assign(
                                   BlockInterpreter::slhaIntHelper.intToString(
                                         indexPrintingVector[ whichIndex ] ) );
          indexPadding = ( indexDigitsVector[ whichIndex ]
                           - indexHoldingString.size() + 1 );
          if( 0 < indexPadding )
          {
            indexPrintingString.append( indexPadding,
                                        ' ' );
          }
          else
          {
            indexPrintingString.append( " " );
          }
          indexPrintingString.append( indexHoldingString );
        }
        return indexPrintingString;
      }

    }

  }

}

#endif /* INDEXEDINTERPRETER_HPP_ */
