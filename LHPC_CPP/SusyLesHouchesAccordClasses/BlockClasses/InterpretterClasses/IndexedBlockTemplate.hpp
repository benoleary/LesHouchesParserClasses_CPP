/*
 * IndexedBlockTemplate.hpp
 *
 *  Created on: Mar 12, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#ifndef INDEXEDBLOCKTEMPLATE_HPP_
#define INDEXEDBLOCKTEMPLATE_HPP_

#include "StandardBlockTemplate.hpp"

namespace LHPC
{
  namespace SLHA
  {
    namespace InterpretterClass
    {
      // this class extends StandardBlockTemplate for blocks with an index or
      // with indices.
      template< class ValueClass >
      class IndexedBlockTemplate : public StandardBlockTemplate< ValueClass >
      {
      public:
        IndexedBlockTemplate( ValueClass const& defaultUnsetValue,
                              bool const& isVerbose,
                              int const indexDigits );
        virtual
        ~IndexedBlockTemplate();


      protected:
        int const indexDigits;
        // this is the number of characters to print before the value,
        // including the characters used to print the index.
        std::string indexPrintingString;
        std::string indexHoldingString;
        int indexPadding;
        std::string currentWord;
        std::string lineRemainderA;
        std::string lineRemainderB;

        std::string const&
        indexToPrintingString( int indexToPrint );
        // this puts a single space then indexToPrint with indexDigits into
        // indexPrintingString & returns it.
      };





      template< class ValueClass >
      inline
      IndexedBlockTemplate< ValueClass >::IndexedBlockTemplate(
                                           ValueClass const& defaultUnsetValue,
                                                         bool const& isVerbose,
                                                      int const indexDigits ) :
          StandardBlockTemplate( defaultUnsetValue,
                                 isVerbose ),
          indexDigits( indexDigits ),
          indexPrintingString( "" ),
          indexHoldingString( "" ),
          indexPadding( 0 ),
          currentWord( "" ),
          lineRemainderA( "" ),
          lineRemainderB( "" )
      {
        // just an initialization list.
      }

      template< class ValueClass >
      inline
      IndexedBlockTemplate< ValueClass >::~IndexedBlockTemplate()
      {
        // does nothing.
      }


      template< class ValueClass >
      inline std::string const&
      IndexedBlockTemplate< ValueClass >::indexToPrintingString(
                                                             int indexToPrint )
      // this puts a single space then indexToPrint with indexDigits into
      // indexPrintingString & returns it.
      {
        indexHoldingString.assign(
                BlockInterpretter::slhaIntHelper.intToString( intToConvert ) );
        indexPadding = ( indexDigits - indexHoldingString.size() + 1 );
        if( 0 < indexPadding )
        {
          indexPrintingString.assign( ' ',
                                      indexPadding );
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

#endif /* INDEXEDBLOCKTEMPLATE_HPP_ */
