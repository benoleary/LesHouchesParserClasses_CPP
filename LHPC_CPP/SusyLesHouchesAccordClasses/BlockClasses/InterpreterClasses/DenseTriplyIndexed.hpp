/*
 * DenseTriplyIndexed.hpp
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

#ifndef DENSETRIPLYINDEXED_HPP_
#define DENSETRIPLYINDEXED_HPP_

#include "IndexedBlockTemplate.hpp"

namespace LHPC
{
  namespace SLHA
  {
    namespace InterpreterClass
    {
      /* this template class derives from InterpreterTemplate to interpret
       * SLHA blocks that have a triple of int indices with a single ValueClass
       * value.
       */
      template< class ValueClass >
      class DenseTriplyIndexed : public IndexedBlockTemplate< ValueClass >
      {
      public:
        DenseTriplyIndexed();
        virtual
        ~DenseTriplyIndexed();

        ValueClass&
        operator()( int firstIndex,
                    int secondIndex,
                    int thirdIndex );
        /* this returns the ValueClass indexed by firstIndex, secondIndex, &
         * thirdIndex. if there is no element at the sought indices,
         * valueMatrixArray is extended with copies of defaultUnsetValue until
         * there is an element at the sought indices.
         */
        ValueClass const&
        operator()( int firstIndex,
                    int secondIndex,
                    int thirdIndex ) const;
        /* const version of above, though it returns defaultUnsetValue rather
         * than copying in a new element at the sought indices if there isn't
         * an entry there already.
         */
        virtual std::string const&
        interpretAsString();
        // see base version's description.
        bool
        hasEntry( int const firstIndex,
                  int const secondIndex,
                  int const thirdIndex ) const;
        // this returns true if there is an entry at the sought indices.
        virtual void
        respondToObservedSignal();


      protected:
        typedef class
        BOL::VectorlikeArray< std::vector< ValueClass > > ValueRankTwoMatrix;
        BOL::VectorlikeArray< ValueRankTwoMatrix > valueMatrixArray;
        int firstRecordingIndex;
        int secondRecordingIndex;
        size_t thirdRecordingIndex;
        int largestFirstIndex;
        int largestSecondIndex;
        size_t largestThirdIndex;

        ValueClass&
        findOrMakeEntry( int const firstIndex,
                         int const secondIndex,
                         int const thirdIndex );
        // this ensures that the entry at the sought indices exists, filling
        // out with copies of defaultUnsetValue, & returns it.
      };





      template< class ValueClass >
      inline
      DenseTriplyIndexed< ValueClass >::DenseTriplyIndexed() :
          IndexedBlockTemplate< ValueClass >(),
          valueMatrixArray(),
          firstRecordingIndex( 0 ),
          secondRecordingIndex( 0 ),
          thirdRecordingIndex( 0 ),
          largestFirstIndex( 0 ),
          largestSecondIndex( 0 ),
          largestThirdIndex( 0 )
      {
        // just an initialization list.
      }

      template< class ValueClass >
      inline
      DenseTriplyIndexed< ValueClass >::~DenseTriplyIndexed()
      {
        // does nothing.
      }


      template< class ValueClass >
      inline ValueClass&
      DenseTriplyIndexed< ValueClass >::operator()( int const firstIndex,
                                                    int const secondIndex,
                                                    int const thirdIndex )
      /* this returns the ValueClass indexed by firstIndex, secondIndex, &
       * thirdIndex. if there is no element at the sought indices,
       * valueMatrixArray is extended with copies of defaultUnsetValue until
       * there is an element at the sought indices.
       */
      {
        return findOrMakeEntry( firstIndex,
                                secondIndex,
                                thirdIndex );
      }

      template< class ValueClass >
      inline ValueClass const&
      DenseTriplyIndexed< ValueClass >::operator()( int firstIndex,
                                                   int secondIndex,
                                                   int thirdIndex ) const
      /* const version of above, though it returns defaultUnsetValue rather
       * than copying in a new element at the sought indices if there isn't
       * an entry there already.
       */
      {
        if( hasEntry( firstIndex,
                      secondIndex,
                      thirdIndex ) )
        {
          return valueMatrixArray[ firstIndex - 1 ][ secondIndex
                                                     - 1 ][ thirdIndex - 1 ];
        }
        else
        {
          return this->defaultUnsetValue;
        }
      }

      template< class ValueClass >
      inline std::string const&
      DenseTriplyIndexed< ValueClass >::interpretAsString()
      // see base version's description.
      {
        this->stringInterpretation.clear();
        for( int firstIndex( 1 );
             largestFirstIndex >= firstIndex;
             ++firstIndex )
        {
          for( int secondIndex( 1 );
               largestSecondIndex >= secondIndex;
               ++secondIndex )
          {
            for( size_t thirdIndex( 1 );
                 largestThirdIndex >= thirdIndex;
                 ++thirdIndex )
            {
              this->stringInterpretation.append( this->indexToPrintingString(
                                                                firstIndex ) );
              this->stringInterpretation.append( this->indexToPrintingString(
                                                               secondIndex ) );
              this->stringInterpretation.append( this->indexToPrintingString(
                                                                thirdIndex ) );
              // SLHA indices are in the sane starts-at-one format, while C++
              // code uses the silly starts-at-zero format.
              this->stringInterpretation.append( this->valueToPrintingString(
                                                   findOrMakeEntry( firstIndex,
                                                                   secondIndex,
                                                              thirdIndex ) ) );
              this->stringInterpretation.append( "\n" );
            }
          }
        }
        return this->stringInterpretation;
      }

      template< class ValueClass >
      inline bool
      DenseTriplyIndexed< ValueClass >::hasEntry( int firstIndex,
                                                  int secondIndex,
                                                  int const thirdIndex ) const
      {
        if( ( 0 < firstIndex )
            &&
            ( 0 < secondIndex )
            &&
            ( 0 < thirdIndex )
            &&
            ( (--firstIndex) < valueMatrixArray.getSize() )
            &&
            ( (--secondIndex) < valueMatrixArray[ firstIndex ].getSize() )
            &&
            ( (size_t)thirdIndex
               <= valueMatrixArray[ firstIndex ][ secondIndex ].size() ) )
        {
          return true;
        }
        else
        {
          return false;
        }
      }

      template< class ValueClass >
      inline void
      DenseTriplyIndexed< ValueClass >::respondToObservedSignal()
      {
        valueMatrixArray.clearEntries();
        for( int whichLine( this->stringsToObserve->getNumberOfBodyLines() );
             0 < whichLine;
             --whichLine )
        {
          this->currentWord.assign( BOL::StringParser::firstWordOf(
                                (*(this->stringsToObserve))[ whichLine ].first,
                                                       &(this->lineRemainderA),
                              BOL::StringParser::whitespaceAndNewlineChars ) );
          if( !(this->currentWord.empty()) )
          {
            firstRecordingIndex
            = BOL::StringParser::stringToInt( this->currentWord );
            this->currentWord.assign( BOL::StringParser::firstWordOf(
                                                          this->lineRemainderA,
                                                       &(this->lineRemainderB),
                              BOL::StringParser::whitespaceAndNewlineChars ) );
            secondRecordingIndex
            = BOL::StringParser::stringToInt( this->currentWord );
            this->currentWord.assign( BOL::StringParser::firstWordOf(
                                                          this->lineRemainderB,
                                                       &(this->lineRemainderA),
                              BOL::StringParser::whitespaceAndNewlineChars ) );
            thirdRecordingIndex
            = BOL::StringParser::stringToInt( this->currentWord );
            this->currentWord.assign( BOL::StringParser::trimFromFrontAndBack(
                                                          this->lineRemainderA,
                              BOL::StringParser::whitespaceAndNewlineChars ) );

            if( ( 0 < firstRecordingIndex )
                &&
                ( 0 < secondRecordingIndex )
                &&
                ( 0 < thirdRecordingIndex )
                &&
                !(this->currentWord.empty()) )
            {
              findOrMakeEntry( firstRecordingIndex,
                               secondRecordingIndex,
                               thirdRecordingIndex )
              = this->stringToValue( this->currentWord );
            }
            else if( this->isVerbose )
            {
              std::cout
              << std::endl
              << "LHPC::SLHA::error! expected to find 3 positive indices then"
              << " a value, instead found \""
              << (*(this->stringsToObserve))[ whichLine ].first << "\"";
              std::cout << std::endl;
            }
          }
        }
      }

      template< class ValueClass >
      inline ValueClass&
      DenseTriplyIndexed< ValueClass >::findOrMakeEntry( int firstIndex,
                                                         int secondIndex,
                                                         int const thirdIndex )
      // this ensures that the entry at the sought indices exists, filling
      // out with copies of defaultUnsetValue, & returns it.
      {
        if( firstIndex > largestFirstIndex )
        {
          largestFirstIndex = firstIndex;
        }
        if( secondIndex > largestSecondIndex )
        {
          largestSecondIndex = secondIndex;
        }
        if( (size_t)thirdIndex > largestThirdIndex )
        {
          largestThirdIndex = thirdIndex;
        }
        while( valueMatrixArray.getSize() < firstIndex )
        {
          valueMatrixArray.newEnd().clearEntries();
          // empty ValueRankTwoMatrixes are added as necessary.
        }
        --firstIndex;
        while( valueMatrixArray[ firstIndex ].getSize() < secondIndex )
        {
          valueMatrixArray[ firstIndex ].newEnd().clear();
          // empty std::vectors are added as necessary.
        }
        if( valueMatrixArray[ firstIndex ][ (--secondIndex) ].size()
            < (size_t)thirdIndex )
          // the conditional does the job of converting from sane starts-at-one
          // format to silly starts-at-zero format.
        {
          valueMatrixArray[ firstIndex ][ secondIndex ].resize( thirdIndex,
                                                     this->defaultUnsetValue );
        }
        return valueMatrixArray[ firstIndex ][ secondIndex ][ thirdIndex - 1 ];
      }

    }

  }

}

#endif /* DENSETRIPLYINDEXED_HPP_ */
