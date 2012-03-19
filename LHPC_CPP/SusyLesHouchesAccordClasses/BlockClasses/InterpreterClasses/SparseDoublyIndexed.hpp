/*
 * SparseDoublyIndexed.hpp
 *
 *  Created on: Mar 19, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.LHPC_CPP.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#ifndef SPARSEDOUBLYINDEXED_HPP_
#define SPARSEDOUBLYINDEXED_HPP_

#include <map>
#include "IndexedInterpreter.hpp"

namespace LHPC
{
  namespace SLHA
  {
    namespace InterpreterClass
    {
      // this template class interprets SLHA blocks that have a single int
      // index with a single ValueClass value.
      template< class ValueClass >
      class SparseDoublyIndexed : public IndexedInterpreter< ValueClass >
      {
      public:
        SparseDoublyIndexed();
        virtual
        ~SparseDoublyIndexed();

        ValueClass&
        operator()( int const firstIndex,
                    int const secondIndex );
        /* this returns the ValueClass mapped to by firstIndex & secondIndex.
         * if there is no element at the sought indices, a new one is made &
         * copied from defaultUnsetValue.
         */
        ValueClass const&
        operator()( int const firstIndex,
                    int const secondIndex ) const;
        /* const version of above, though it returns defaultUnsetValue rather
         * than copying in a new element at the sought indices if there isn't
         * an entry there already.
         */
        bool
        hasEntry( int const firstIndex,
                  int const secondIndex ) const;
        // this returns true if there is an entry at the sought indices.
        virtual std::string const&
        getAsString();
        // see base version's description.
        virtual void
        clearEntries();
        // derived classes should clear their interpreted values.


      protected:
        typedef typename
        std::map< std::pair< int, int >, ValueClass >::const_iterator
        mapIterator;

        std::map< std::pair< int, int >, ValueClass > valueMap;
        std::pair< int, int > mapKey;
        std::pair< std::pair< int, int >, ValueClass > valueRecorder;

        virtual void
        interpretCurrentStringBlock();
      };





      template< class ValueClass >
      inline
      SparseDoublyIndexed< ValueClass >::SparseDoublyIndexed() :
          IndexedInterpreter< ValueClass >(),
          valueMap(),
          mapKey( 0,
                  0 ),
          valueRecorder()
      {
        // just an initialization list.
      }

      template< class ValueClass >
      inline
      SparseDoublyIndexed< ValueClass >::~SparseDoublyIndexed()
      {
        // does nothing.
      }


      template< class ValueClass >
      inline ValueClass&
      SparseDoublyIndexed< ValueClass >::operator()( int const firstIndex,
                                                     int const secondIndex )
      /* this returns the ValueClass mapped to by firstIndex & secondIndex.
       * if there is no element at the sought indices, a new one is made &
       * copied from defaultUnsetValue.
       */
      {
        mapKey.first = firstIndex;
        mapKey.second = secondIndex;
        if( 0 >= valueMap.count( mapKey ) )
        {
          valueMap[ mapKey ] = this->defaultUnsetValue;
        }
        return valueMap[ mapKey ];
      }

      template< class ValueClass >
      inline ValueClass const&
      SparseDoublyIndexed< ValueClass >::operator()( int const firstIndex,
                                                  int const secondIndex ) const
      /* const version of above, though it returns defaultUnsetValue rather
       * than copying in a new element at the sought indices if there isn't
       * an entry there already.
       */
      {
        mapIterator
        valueFinder( valueMap.find( std::pair< int, int >( firstIndex,
                                                           secondIndex ) ) );
        if( valueMap.end() != valueFinder )
        {
          return valueFinder->second;
        }
        else
        {
          return this->defaultUnsetValue;
        }
      }

      template< class ValueClass >
      inline bool
      SparseDoublyIndexed< ValueClass >::hasEntry( int const firstIndex,
                                                  int const secondIndex ) const
      // this returns true if there is an entry at soughtIndex.
      {
        return ( 0 < valueMap.count( std::pair< int, int >( firstIndex,
                                                            secondIndex ) ) );
      }

      template< class ValueClass >
      inline std::string const&
      SparseDoublyIndexed< ValueClass >::getAsString()
      // see base version's description.
      {
        this->stringInterpretation.clear();
        mapIterator valueFinder( valueMap.begin() );
        while( valueFinder != valueMap.end() )
        {
          this->stringInterpretation.append( this->indexToPrintingString(
                                                  valueFinder->first.first ) );
          this->stringInterpretation.append( this->indexToPrintingString(
                                                 valueFinder->first.second ) );
          this->stringInterpretation.append( this->valueToPrintingString(
                                                       valueFinder->second ) );
          this->stringInterpretation.append( "\n" );
          ++valueFinder;
        }
        return this->stringInterpretation;
      }

      template< class ValueClass >
      inline void
      SparseDoublyIndexed< ValueClass >::clearEntries()
      {
        valueMap.clear();
      }

      template< class ValueClass >
      inline void
      SparseDoublyIndexed< ValueClass >::interpretCurrentStringBlock()
      {
        for( int whichLine( this->currentStringBlock->getNumberOfBodyLines() );
             0 < whichLine;
             --whichLine )
        {
          this->currentWord.assign( BOL::StringParser::firstWordOf(
                              (*(this->currentStringBlock))[ whichLine ].first,
                                                       &(this->lineRemainderA),
                              BOL::StringParser::whitespaceAndNewlineChars ) );
          if( !(this->currentWord.empty()) )
          {
            valueRecorder.first.first
            = BOL::StringParser::stringToInt( this->currentWord );
            this->currentWord.assign( BOL::StringParser::firstWordOf(
                                                          this->lineRemainderA,
                                                       &(this->lineRemainderB),
                              BOL::StringParser::whitespaceAndNewlineChars ) );
            if( !(this->currentWord.empty()) )
            {
              valueRecorder.first.second
              = BOL::StringParser::stringToInt( this->currentWord );
              valueRecorder.second
              = this->stringToValue( BOL::StringParser::trimFromFrontAndBack(
                                                          this->lineRemainderB,
                              BOL::StringParser::whitespaceAndNewlineChars ) );
              valueMap.insert( valueRecorder );
            }
          }
        }
      }

    }

  }

}

#endif /* SPARSEDOUBLYINDEXED_HPP_ */
