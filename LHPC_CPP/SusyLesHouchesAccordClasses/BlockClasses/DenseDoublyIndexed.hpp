/*
 * DenseDoublyIndexed.hpp
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

#ifndef DENSEDOUBLYINDEXED_HPP_
#define DENSEDOUBLYINDEXED_HPP_

#include "StandardBlockTemplate.hpp"

namespace LHPC
{
  namespace SLHA
  {
    namespace BlockClass
    {
      /* this template class derives from StandardBlockTemplate to interpret
       * SLHA blocks that have a pair of int indices with a single ValueType
       * value.
       */
      template< typename ValueType >
      class DenseDoublyIndexed : public StandardBlockTemplate< ValueType >
      {
      public:
        DenseDoublyIndexed( std::string const& blockName,
                            ValueType const& defaultUnsetValue,
                            bool const& isVerbose,
                            int const indexDigits = 5,
                            std::string const blockHeaderComment = "" );
        virtual
        ~DenseDoublyIndexed();

        ValueType&
        operator()( int firstIndex,
                    int secondIndex,
                    double const blockScale );
        /* this returns the ValueType indexed by firstIndex & secondIndex for
         * the data with energy scale nearest blockScale. if there is no
         * element at the sought indices, valueMatrixArray is extended with
         * copies of defaultUnsetValue until there is an element at the sought
         * indices.
         */
        ValueType const&
        operator()( int firstIndex,
                    int secondIndex,
                    double const blockScale ) const;
        /* const version of above, though it returns defaultUnsetValue rather
         * than copying in a new element at the sought indices if there isn't
         * an entry there already.
         */
        ValueType&
        operator()( int firstIndex,
                    int secondIndex );
        /* this returns the ValueType indexed by firstIndex & secondIndex for
         * the data with lowest energy scale. if there is no element at the
         * sought indices, valueMatrixArray is extended with copies of
         * defaultUnsetValue until there is an element at the sought indices.
         */
        ValueType const&
        operator()( int firstIndex,
                    int secondIndex ) const;
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
        BOL::VectorlikeArray< ValueRankTwoMatrix > valueMatrixArray;
        int firstRecordingIndex;
        size_t secondRecordingIndex;
        int largestFirstIndex;
        size_t largestSecondIndex;

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
                  int const secondIndex ) const;
        ValueType&
        findOrMakeEntry( int const whichData,
                         int const firstIndex,
                         int const secondIndex );
        // this ensures that the entry at the sought indices exists, filling
        // out with copies of defaultUnsetValue, & returns it.
      };





      template< typename ValueType >
      inline
      DenseDoublyIndexed< ValueType >::DenseDoublyIndexed(
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
          largestFirstIndex( 0 ),
          largestSecondIndex( 0 )
      {
        // just an initialization list.
      }

      template< typename ValueType >
      inline
      DenseDoublyIndexed< ValueType >::~DenseDoublyIndexed()
      {
        // does nothing.
      }


      template< typename ValueType >
      inline ValueType&
      DenseDoublyIndexed< ValueType >::operator()( int firstIndex,
                                                   int secondIndex,
                                                   double const blockScale )
      /* this returns the ValueType indexed by firstIndex & secondIndex for
       * the data with energy scale nearest blockScale. if there is no
       * element at the sought indices, valueMatrixArray is extended with
       * copies of defaultUnsetValue until there is an element at the sought
       * indices.
       */
      {
        return findOrMakeEntry( this->findScaleIndex( blockScale ),
                                (--firstIndex),
                                (--secondIndex) );
        /* in being decremented while being given to findOrMakeEntry, the
         * index variables have now become appropriate for looking up
         * directly (converted from SLHA sane starts-from-one to C++ silly
         * starts-from-zero).
         */
      }

      template< typename ValueType >
      inline ValueType const&
      DenseDoublyIndexed< ValueType >::operator()( int firstIndex,
                                                   int secondIndex,
                                                double const blockScale ) const
      /* const version of above, though it returns defaultUnsetValue rather
       * than copying in a new element at the sought indices if there isn't an
       * entry there already.
       */
      {
        int whichData( this->findScaleIndex( blockScale ) );
        if( hasEntry( whichData,
                      (--firstIndex),
                      (--secondIndex) ) )
          /* in being decremented while being given to the conditional, the
           * index variables have now become appropriate for looking up
           * directly (converted from SLHA sane starts-from-one to C++ silly
           * starts-from-zero).
           */
        {
          return valueMatrixArray[ whichData ][ firstIndex ][ secondIndex ];
        }
        else
        {
          return this->defaultUnsetValue;
        }
      }

      template< typename ValueType >
      inline ValueType&
      DenseDoublyIndexed< ValueType >::operator()( int firstIndex,
                                                   int secondIndex )
      /* this returns the ValueType indexed by firstIndex & secondIndex for
       * the data with lowest energy scale. if there is no element at the
       * sought indices, valueMatrixArray is extended with copies of
       * defaultUnsetValue until there is an element at the sought indices.
       */
      {
        return findOrMakeEntry( this->lowestScaleIndex,
                                (--firstIndex),
                                (--secondIndex) );
        /* in being decremented while being given to findOrMakeEntry, the
         * index variables have now become appropriate for looking up
         * directly (converted from SLHA sane starts-from-one to C++ silly
         * starts-from-zero).
         */
      }

      template< typename ValueType >
      inline ValueType const&
      DenseDoublyIndexed< ValueType >::operator()( int firstIndex,
                                                   int secondIndex ) const
      /* const version of above, though it returns defaultUnsetValue rather
       * than copying in a new element at the sought indices if there isn't an
       * entry there already.
       */
      {
        if( hasEntry( this->lowestScaleIndex,
                      (--firstIndex),
                      (--secondIndex) ) )
          /* in being decremented while being given to the conditional, the
           * index variables have now become appropriate for looking up
           * directly (converted from SLHA sane starts-from-one to C++ silly
           * starts-from-zero).
           */
        {
          return valueMatrixArray[ this->lowestScaleIndex ][ firstIndex
                                                              ][ secondIndex ];
        }
        else
        {
          return this->defaultUnsetValue;
        }
      }

      template< typename ValueType >
      inline std::string const&
      DenseDoublyIndexed< ValueType >::interpretAsString(
                                                      double const blockScale )
      // see base version's description.
      {
        this->currentIndex = this->findScaleIndex( blockScale );
        SlhaBlock::returnString.clear();
        for( int firstIndex( 0 );
             largestFirstIndex >= firstIndex;
             ++firstIndex )
        {
          for( size_t secondIndex( 0 );
               largestSecondIndex >= secondIndex;
               ++secondIndex )
          {
            this->putIndexIntoReturnString( firstIndex + 1 );
            this->putIndexIntoReturnString( secondIndex + 1 );
            // SLHA indices are in the sane starts-at-one format, while C++
            // code uses the silly starts-at-zero format.
            this->putValueIntoReturnString( findOrMakeEntry(
                                                            this->currentIndex,
                                                             firstIndex,
                                                             secondIndex ) );
          }
        }
        return SlhaBlock::returnString;
      }

      template< typename ValueType >
      inline void
      DenseDoublyIndexed< ValueType >::clearExtraStuff()
      // derived classes should clear their extra data here.
      {
        valueMatrixArray.clearEntries();
      }

      template< typename ValueType >
      inline void
      DenseDoublyIndexed< ValueType >::prepareExtraStuffForNewScale()
      {
        valueMatrixArray.newEnd().clearEntries();
        // this ensures that valueMatrixArray[ currentIndex ] is now an empty
        // VectorlikeArray of std::vectors.
      }

      template< typename ValueType >
      inline void
      DenseDoublyIndexed< ValueType >::interpretBodyLine()
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
          if( ( 0 < firstRecordingIndex )
              &&
              ( 0 < secondRecordingIndex ) )
          {
            /* in being decremented while being given to findOrMakeEntry, the
             * index variables have now become appropriate for looking up
             * directly (converted from SLHA sane starts-from-one to C++ silly
             * starts-from-zero).
             */
            findOrMakeEntry( this->currentIndex,
                             (--firstRecordingIndex),
                             (--secondRecordingIndex) )
            = this->stringToValue( BOL::StringParser::trimFromFrontAndBack(
                                                    SlhaBlock::secondRemainder,
                                                                 " \t\r\n" ) );
          }
          else if( this->isVerbose )
          {
            std::cout
            << std::endl
            << "LHPC::SLHA::error! expected to find 2 indices then a value,"
            << " instead found \"" << SlhaBlock::comparisonString << "\"";
            std::cout << std::endl;
          }
        }
      }

      template< typename ValueType >
      inline bool
      DenseDoublyIndexed< ValueType >::hasEntry( int const whichData,
                                                 int const firstIndex,
                                                 int const secondIndex ) const
      {
        /* the conditionals checking that the given indices were greater than
         * zero also decrement the variables in this function, so that if the
         * flow makes it through to the conditional checking that firstIndex is
         * not too large, the index variables have now become appropriate for
         * looking up directly (converted from SLHA sane starts-from-one to C++
         * silly starts-from-zero).
         */
        if( ( whichData < valueMatrixArray.getSize() )
            &&
            ( 0 <= firstIndex )
            &&
            ( 0 <= secondIndex )
            &&
            ( firstIndex < valueMatrixArray[ whichData ].getSize() )
            &&
            ( (size_t)secondIndex
              < valueMatrixArray[ whichData ][ firstIndex ].size() ) )
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
      DenseDoublyIndexed< ValueType >::findOrMakeEntry( int const whichData,
                                                        int const firstIndex,
                                                        int const secondIndex )
      // this ensures that the entry at the sought indices exists, filling
      // out with copies of defaultUnsetValue, & returns it.
      {
        if( firstIndex > largestFirstIndex )
        {
          largestFirstIndex = firstIndex;
        }
        if( (size_t)secondIndex > largestSecondIndex )
        {
          largestSecondIndex = secondIndex;
        }
        while( valueMatrixArray[ whichData ].getSize() <= firstIndex )
        {
          valueMatrixArray[ whichData ].newEnd().clear();
          // empty std::vectors are added as necessary.
        }
        if( valueMatrixArray[ whichData ][ firstIndex ].size()
            <= (size_t)secondIndex )
        {
          valueMatrixArray[ whichData ][ firstIndex ].resize(
                                                           ( secondIndex + 1 ),
                                                     this->defaultUnsetValue );
        }
        return valueMatrixArray[ whichData ][ firstIndex ][ secondIndex ];
      }

    }

  }

}

#endif /* DENSEDOUBLYINDEXED_HPP_ */
