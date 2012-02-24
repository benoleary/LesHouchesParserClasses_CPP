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

#include "StandardBlockTemplate.hpp"

namespace LHPC
{
  namespace SLHA
  {
    namespace BlockClass
    {
      /* this template class derives from StandardBlockTemplate to interpret
       * SLHA blocks that have a triple of int indices with a single ValueType
       * value.
       */
      template< typename ValueType >
      class DenseTriplyIndexed : public StandardBlockTemplate< ValueType >
      {
      public:
        DenseTriplyIndexed( std::string const& blockName,
                            ValueType const& defaultUnsetValue,
                            bool const& isVerbose,
                            int const indexDigits = 5,
                            std::string const blockHeaderComment = "" );
        virtual
        ~DenseTriplyIndexed();

        ValueType&
        operator()( int firstIndex,
                    int secondIndex,
                    int thirdIndex,
                    double const blockScale );
        /* this returns the ValueType indexed by firstIndex, secondIndex, &
         * thirdIndex for the data with energy scale nearest blockScale. if
         * there is no element at the sought indices, valueMatrixArray is
         * extended with copies of defaultUnsetValue until there is an element
         * at the sought indices.
         */
        ValueType const&
        operator()( int firstIndex,
                    int secondIndex,
                    int thirdIndex,
                    double const blockScale ) const;
        /* const version of above, though it returns defaultUnsetValue rather
         * than copying in a new element at the sought indices if there isn't
         * an entry there already.
         */
        ValueType&
        operator()( int firstIndex,
                    int secondIndex,
                    int thirdIndex );
        /* this returns the ValueType indexed by firstIndex, secondIndex, &
         * thirdIndex for the data with lowest energy scale. if there is no
         * element at the sought indices, valueMatrixArray is extended with
         * copies of defaultUnsetValue until there is an element at the sought
         * indices.
         */
        ValueType const&
        operator()( int firstIndex,
                    int secondIndex,
                    int thirdIndex ) const;
        /* const version of above, though it returns defaultUnsetValue rather
         * than copying in a new element at the sought indices if there isn't
         * an entry there already.
         */
        virtual std::string const&
        interpretAsString( double const blockScale = 0.0 );
        // see base version's description.


      protected:
        typedef typename
        BOL::VectorlikeArray< std::vector< ValueType > > ValueRankTwoMatrix;
        BOL::VectorlikeArray< BOL::VectorlikeArray< ValueRankTwoMatrix > >
        valueMatrixArray;
        int firstRecordingIndex;
        int secondRecordingIndex;
        size_t thirdRecordingIndex;
        int largestFirstIndex;
        int largestSecondIndex;
        size_t largestThirdIndex;

        virtual void
        clearExtraStuff();
        // derived classes should clear their extra data here.
        virtual void
        prepareExtraStuffForNewScale();
        // derived classes should prepare their extra data structure for
        // recording a new scale here.
        virtual void
        interpretBodyLine();
        // derived classes should interpret comparisonString at this point,
        // since it is a non-empty data line.
        bool
        hasEntry( int const whichData,
                  int const firstIndex,
                  int const secondIndex,
                  int const thirdIndex ) const;
        ValueType&
        findOrMakeEntry( int const whichData,
                         int const firstIndex,
                         int const secondIndex,
                         int const thirdIndex );
        // this ensures that the entry at the sought indices exists, filling
        // out with copies of defaultUnsetValue, & returns it.
      };





      template< typename ValueType >
      inline
      DenseTriplyIndexed< ValueType >::DenseTriplyIndexed(
                                                  std::string const& blockName,
                                            ValueType const& defaultUnsetValue,
                                                         bool const& isVerbose,
                                                         int const indexDigits,
                                       std::string const blockHeaderComment ) :
          StandardBlockTemplate< ValueType >( blockName,
                                              defaultUnsetValue,
                                              isVerbose,
                                              indexDigits,
                                              blockHeaderComment ),
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

      template< typename ValueType >
      inline
      DenseTriplyIndexed< ValueType >::~DenseTriplyIndexed()
      {
        // does nothing.
      }


      template< typename ValueType >
      inline ValueType&
      DenseTriplyIndexed< ValueType >::operator()( int firstIndex,
                                                   int secondIndex,
                                                   int thirdIndex,
                                                   double const blockScale )
      /* this returns the ValueType indexed by firstIndex, secondIndex, &
       * thirdIndex for the data with energy scale nearest blockScale. if
       * there is no element at the sought indices, valueMatrixArray is
       * extended with copies of defaultUnsetValue until there is an element
       * at the sought indices.
       */
      {
        return findOrMakeEntry( this->findScaleIndex( blockScale ),
                                (--firstIndex),
                                (--secondIndex),
                                (--thirdIndex) );
        /* in being decremented while being given to findOrMakeEntry, the
         * index variables have now become appropriate for looking up
         * directly (converted from SLHA sane starts-from-one to C++ silly
         * starts-from-zero).
         */
      }

      template< typename ValueType >
      inline ValueType const&
      DenseTriplyIndexed< ValueType >::operator()( int firstIndex,
                                                   int secondIndex,
                                                   int thirdIndex,
                                                double const blockScale ) const
      /* const version of above, though it returns defaultUnsetValue rather
       * than copying in a new element at the sought indices if there isn't
       * an entry there already.
       */
      {
        int whichData( this->findScaleIndex( blockScale ) );
        if( hasEntry( whichData,
                      (--firstIndex),
                      (--secondIndex),
                      (--thirdIndex) ) )
          /* in being decremented while being given to the conditional, the
           * index variables have now become appropriate for looking up
           * directly (converted from SLHA sane starts-from-one to C++ silly
           * starts-from-zero).
           */
        {
          return valueMatrixArray[ whichData ][ firstIndex ][ secondIndex ][
                                                                  thirdIndex ];
        }
        else
        {
          return this->defaultUnsetValue;
        }
      }

      template< typename ValueType >
      inline ValueType&
      DenseTriplyIndexed< ValueType >::operator()( int firstIndex,
                                                   int secondIndex,
                                                   int thirdIndex )
      /* this returns the ValueType indexed by firstIndex, secondIndex, &
       * thirdIndex for the data with lowest energy scale. if there is no
       * element at the sought indices, valueMatrixArray is extended with
       * copies of defaultUnsetValue until there is an element at the sought
       * indices.
       */
      {
        return findOrMakeEntry( this->lowestScaleIndex,
                                (--firstIndex),
                                (--secondIndex),
                                (--thirdIndex) );
        /* in being decremented while being given to findOrMakeEntry, the
         * index variables have now become appropriate for looking up
         * directly (converted from SLHA sane starts-from-one to C++ silly
         * starts-from-zero).
         */
      }

      template< typename ValueType >
      inline ValueType const&
      DenseTriplyIndexed< ValueType >::operator()( int firstIndex,
                                                   int secondIndex,
                                                   int thirdIndex ) const
      /* const version of above, though it returns defaultUnsetValue rather
       * than copying in a new element at the sought indices if there isn't
       * an entry there already.
       */
      {
        if( hasEntry( this->lowestScaleIndex,
                      (--firstIndex),
                      (--secondIndex),
                      (--thirdIndex) ) )
          /* in being decremented while being given to the conditional, the
           * index variables have now become appropriate for looking up
           * directly (converted from SLHA sane starts-from-one to C++ silly
           * starts-from-zero).
           */
        {
          return valueMatrixArray[ this->lowestScaleIndex ][ firstIndex
                                                          ][ secondIndex
                                                          ][ thirdIndex ];
        }
        else
        {
          return this->defaultUnsetValue;
        }
      }

      template< typename ValueType >
      inline std::string const&
      DenseTriplyIndexed< ValueType >::interpretAsString(
                                                      double const blockScale )
      // see base version's description.
      {
        this->currentIndex = this->findScaleIndex( blockScale );
        SlhaBlock::returnString.clear();
        for( int firstIndex( 0 );
             largestFirstIndex > firstIndex;
             ++firstIndex )
        {
          for( int secondIndex( 0 );
               largestSecondIndex >= secondIndex;
               ++secondIndex )
          {
            for( size_t thirdIndex( 0 );
                 largestThirdIndex >= thirdIndex;
                 ++thirdIndex )
            {
              this->putIndexIntoReturnString( firstIndex + 1 );
              this->putIndexIntoReturnString( secondIndex + 1 );
              this->putIndexIntoReturnString( thirdIndex + 1 );
              // SLHA indices are in the sane starts-at-one format, while C++
              // code uses the silly starts-at-zero format.
              this->putValueIntoReturnString( findOrMakeEntry(
                                                            this->currentIndex,
                                                               firstIndex,
                                                               secondIndex,
                                                               thirdIndex ) );
            }
          }
        }
        return SlhaBlock::returnString;
      }

      template< typename ValueType >
      inline void
      DenseTriplyIndexed< ValueType >::clearExtraStuff()
      // derived classes should clear their extra data here.
      {
        valueMatrixArray.clearEntries();
      }

      template< typename ValueType >
      inline void
      DenseTriplyIndexed< ValueType >::prepareExtraStuffForNewScale()
      {
        valueMatrixArray.newEnd().clearEntries();
        // this ensures that valueMatrixArray[ currentIndex ] is now an empty
        // VectorlikeArray of ValueRankTwoMatrixs.
      }

      template< typename ValueType >
      inline void
      DenseTriplyIndexed< ValueType >::interpretBodyLine()
      // derived classes should interpret comparisonString at this point, since
      // it is a non-empty data line.
      {
        SlhaBlock::currentWord.assign( BOL::StringParser::firstWordOf(
                                                   SlhaBlock::comparisonString,
                                                  &(SlhaBlock::firstRemainder),
                                                                 " \t\r\n" ) );
        if( !(SlhaBlock::currentWord.empty()) )
        {
          firstRecordingIndex
          = BOL::StringParser::stringToInt( SlhaBlock::currentWord );
          SlhaBlock::currentWord.assign( BOL::StringParser::firstWordOf(
                                                     SlhaBlock::firstRemainder,
                                                 &(SlhaBlock::secondRemainder),
                                                                 " \t\r\n" ) );
          secondRecordingIndex
          = BOL::StringParser::stringToInt( SlhaBlock::currentWord );
          SlhaBlock::currentWord.assign( BOL::StringParser::firstWordOf(
                                                    SlhaBlock::secondRemainder,
                                                  &(SlhaBlock::firstRemainder),
                                                                 " \t\r\n" ) );
          thirdRecordingIndex
          = BOL::StringParser::stringToInt( SlhaBlock::currentWord );

          if( ( 0 < firstRecordingIndex )
              &&
              ( 0 < secondRecordingIndex )
              &&
              ( 0 < thirdRecordingIndex ) )
          {
            /* in being decremented while being given to findOrMakeEntry, the
             * index variables have now become appropriate for looking up
             * directly (converted from SLHA sane starts-from-one to C++ silly
             * starts-from-zero).
             */
            findOrMakeEntry( this->currentIndex,
                             (--firstRecordingIndex),
                             (--secondRecordingIndex),
                             (--thirdRecordingIndex) )
            = this->stringToValue( SlhaBlock::firstRemainder );
          }
          else if( this->isVerbose )
          {
            std::cout
            << std::endl
            << "LHPC::SLHA::error! expected to find 3 indices then a value,"
            << " instead found \"" << SlhaBlock::comparisonString << "\"";
            std::cout << std::endl;
          }
        }
      }

      template< typename ValueType >
      inline bool
      DenseTriplyIndexed< ValueType >::hasEntry( int const whichData,
                                                 int const firstIndex,
                                                 int const secondIndex,
                                                 int const thirdIndex ) const
      {
        if( ( 0 <= firstIndex )
            &&
            ( 0 <= secondIndex )
            &&
            ( 0 <= thirdIndex )
            &&
            ( firstIndex
              < valueMatrixArray[ whichData ].getSize() )
            &&
            ( secondIndex < valueMatrixArray[ whichData
                                           ][ firstIndex ].getSize() )
            &&
            ( (size_t)thirdIndex < valueMatrixArray[ whichData
                                                  ][ firstIndex
                                                  ][ secondIndex ].size() ) )
        {
          return true;
        }
        else
        {
          return false;
        }
      }

      template< typename ValueType >
      inline ValueType&
      DenseTriplyIndexed< ValueType >::findOrMakeEntry( int const whichData,
                                                        int const firstIndex,
                                                        int const secondIndex,
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
        while( valueMatrixArray[ whichData ].getSize() <= firstIndex )
        {
          valueMatrixArray[ whichData ].newEnd().clearEntries();
          // empty ValueRankTwoMatrixes are added as necessary.
        }
        while( valueMatrixArray[ whichData ][ firstIndex ].getSize()
               <= secondIndex )
        {
          valueMatrixArray[ whichData ][ firstIndex ].newEnd().clear();
          // empty std::vectors are added as necessary.
        }
        if( valueMatrixArray[ whichData ][ firstIndex ][ secondIndex ].size()
            <= (size_t)thirdIndex )
        {
          valueMatrixArray[ whichData ][ firstIndex ][ secondIndex ].resize(
                                                            ( thirdIndex + 1 ),
                                                     this->defaultUnsetValue );
        }
        return valueMatrixArray[ whichData ][ firstIndex ][ secondIndex ][
                                                                  thirdIndex ];
      }

    }

  }

}

#endif /* DENSETRIPLYINDEXED_HPP_ */
