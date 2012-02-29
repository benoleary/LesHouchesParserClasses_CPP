/*
 * DenseSinglyIndexed.hpp
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

#ifndef DENSESINGLYINDEXED_HPP_
#define DENSESINGLYINDEXED_HPP_

#include "StandardBlockTemplate.hpp"

namespace LHPC
{
  namespace SLHA
  {
    namespace BlockClass
    {
      /* this template class derives from StandardBlockTemplate to interpret
       * SLHA blocks that have a single int index with a single ValueType
       * value.
       */
      template< typename ValueType >
      class DenseSinglyIndexed : public StandardBlockTemplate< ValueType >
      {
      public:
        DenseSinglyIndexed( std::string const& blockName,
                            ValueType const& defaultUnsetValue,
                            bool const& isVerbose,
                            int const indexDigits = 5,
                            std::string const blockHeaderComment = "" );
        virtual
        ~DenseSinglyIndexed();

        ValueType&
        operator()( int soughtIndex,
                    double const blockScale );
        /* this returns the ValueType indexed by soughtIndex for the data with
         * energy scale nearest blockScale. if there is no element at
         * soughtIndex, valueVectorArray is extended with copies of
         * defaultUnsetValue until there is an element at soughtIndex.
         */
        ValueType const&
        operator()( int soughtIndex,
                    double const blockScale ) const;
        /* const version of above, though it returns defaultUnsetValue rather
         * than copying in a new element at soughtIndex if there isn't an
         * entry there already.
         */
        ValueType&
        operator()( int soughtIndex );
        /* this returns the ValueType indexed by soughtIndex for the data with
         * lowest energy scale. if there is no element at soughtIndex,
         * valueVectorArray is extended with copies of defaultUnsetValue until
         * there is an element at soughtIndex.
         */
        ValueType const&
        operator()( int soughtIndex ) const;
        /* const version of above, though it returns defaultUnsetValue rather
         * than copying in a new element at soughtIndex if there isn't an
         * entry there already.
         */
        ValueType&
        operator[]( int const soughtIndex ) { return (*this)( soughtIndex ); }
        ValueType const&
        operator[]( int const soughtIndex ) const { return (*this)(
                                                               soughtIndex ); }
        virtual std::string const&
        interpretAsString( double const blockScale = 0.0 );
        // see base version's description.


      protected:
        BOL::VectorlikeArray< std::vector< ValueType > > valueVectorArray;
        size_t recordingIndex;

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
                  int soughtIndex ) const;
        ValueType&
        findOrMakeEntry( int const whichData,
                         int const soughtIndex );
        // this ensures that the entry at soughtIndex exists, filling out with
        // copies of defaultUnsetValue, & returns it.
      };





      template< typename ValueType >
      inline
      DenseSinglyIndexed< ValueType >::DenseSinglyIndexed(
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
          valueVectorArray(),
          recordingIndex( 0 )
      {
        // just an initialization list.
      }

      template< typename ValueType >
      inline
      DenseSinglyIndexed< ValueType >::~DenseSinglyIndexed()
      {
        // does nothing.
      }


      template< typename ValueType >
      inline ValueType&
      DenseSinglyIndexed< ValueType >::operator()( int soughtIndex,
                                                   double const blockScale )
      /* this returns the ValueType indexed by soughtIndex for the data with
       * energy scale nearest blockScale. if there is no element at
       * soughtIndex, valueVectorArray is extended with copies of
       * defaultUnsetValue until there is an element at soughtIndex.
       */
      {
        return findOrMakeEntry( this->findScaleIndex( blockScale ),
                                (--soughtIndex) );
        /* in being decremented while being given to findOrMakeEntry, the
         * index variable has now become appropriate for looking up
         * directly (converted from SLHA sane starts-from-one to C++ silly
         * starts-from-zero).
         */
      }

      template< typename ValueType >
      inline ValueType const&
      DenseSinglyIndexed< ValueType >::operator()( int soughtIndex,
                                                double const blockScale ) const
      /* const version of above, though it returns defaultUnsetValue rather
       * than copying in a new element at soughtIndex if there isn't an
       * entry there already.
       */
      {
        int whichData( this->findScaleIndex( blockScale ) );
        if( hasEntry( whichData,
                      (--soughtIndex) ) )
          /* in being decremented while being given to the conditional, the
           * index variables have now become appropriate for looking up
           * directly (converted from SLHA sane starts-from-one to C++ silly
           * starts-from-zero).
           */
        {
          return valueVectorArray[ whichData ][ soughtIndex ];
        }
        else
        {
          return this->defaultUnsetValue;
        }
      }

      template< typename ValueType >
      inline ValueType&
      DenseSinglyIndexed< ValueType >::operator()( int soughtIndex )
      /* this returns the ValueType indexed by soughtIndex for the data with
       * lowest energy scale. if there is no element at soughtIndex,
       * valueVectorArray is extended with copies of defaultUnsetValue until
       * there is an element at soughtIndex.
       */
      {
        return findOrMakeEntry( this->lowestScaleIndex,
                                (--soughtIndex) );
        /* in being decremented while being given to findOrMakeEntry, the
         * index variable has now become appropriate for looking up
         * directly (converted from SLHA sane starts-from-one to C++ silly
         * starts-from-zero).
         */
      }

      template< typename ValueType >
      inline ValueType const&
      DenseSinglyIndexed< ValueType >::operator()( int soughtIndex ) const
      /* const version of above, though it returns defaultUnsetValue rather
       * than copying in a new element at soughtIndex if there isn't an
       * entry there already.
       */
      {
        if( hasEntry( this->lowestScaleIndex,
                      (--soughtIndex) ) )
          /* in being decremented while being given to the conditional, the
           * index variables have now become appropriate for looking up
           * directly (converted from SLHA sane starts-from-one to C++ silly
           * starts-from-zero).
           */
        {
          return valueVectorArray[ this->lowestScaleIndex ][ soughtIndex ];
        }
        else
        {
          return this->defaultUnsetValue;
        }
      }

      template< typename ValueType >
      inline std::string const&
      DenseSinglyIndexed< ValueType >::interpretAsString(
                                                      double const blockScale )
      // see base version's description.
      {
        this->findScaleIndex( blockScale );
        SlhaBlock::returnString.clear();
        for( unsigned int soughtIndex( 0 );
             valueVectorArray[ this->currentIndex ].size() > soughtIndex;
             ++soughtIndex )
        {
          this->putIndexIntoReturnString( soughtIndex + 1 );
          // SLHA indices are in the sane starts-at-one format, while C++ code
          // uses the silly starts-at-zero format.
          this->putValueIntoReturnString( findOrMakeEntry( this->currentIndex,
                                                           soughtIndex ) );
        }
        return SlhaBlock::returnString;
      }

      template< typename ValueType >
      inline void
      DenseSinglyIndexed< ValueType >::clearExtraStuff()
      // derived classes should clear their extra data here.
      {
        valueVectorArray.clearEntries();
      }

      template< typename ValueType >
      inline void
      DenseSinglyIndexed< ValueType >::prepareExtraStuffForNewScale()
      {
        valueVectorArray.newEnd().clear();
        // this ensures that valueVectorArray[ currentIndex ] is now an empty
        // std::vector.
      }

      template< typename ValueType >
      inline void
      DenseSinglyIndexed< ValueType >::interpretBodyLine()
      // derived classes should interpret comparisonString at this point, since
      // it is a non-empty data line.
      {
        SlhaBlock::currentWord.assign( BOL::StringParser::firstWordOf(
                                                   SlhaBlock::comparisonString,
                                                  &(SlhaBlock::firstRemainder),
                                                                 " \t\r\n" ) );
        if( !(SlhaBlock::currentWord.empty()) )
        {
          recordingIndex
          = BOL::StringParser::stringToInt( SlhaBlock::currentWord );
          if( 0 < recordingIndex )
          {
            /* in being decremented while being given to findOrMakeEntry, the
             * index variable has now become appropriate for looking up
             * directly (converted from SLHA sane starts-from-one to C++ silly
             * starts-from-zero).
             */
            findOrMakeEntry( this->currentIndex,
                             (--recordingIndex) )
            = this->stringToValue( BOL::StringParser::trimFromFrontAndBack(
                                                     SlhaBlock::firstRemainder,
                                                                 " \t\r\n" ) );
          }
          else if( this->isVerbose )
          {
            std::cout
            << std::endl
            << "LHPC::SLHA::error! expected to find 1 index then a value,"
            << " instead found \"" << SlhaBlock::comparisonString << "\"";
            std::cout << std::endl;
          }
        }
      }

      template< typename ValueType >
      inline bool
      DenseSinglyIndexed< ValueType >::hasEntry( int const whichData,
                                                 int const soughtIndex ) const
      {
        /* the conditional checking that the given indices were greater than
         * zero also decrements the variable in this function, so that if the
         * flow makes it through to the conditional checking that firstIndex is
         * not too large, the index variables have now become appropriate for
         * looking up directly (converted from SLHA sane starts-from-one to C++
         * silly starts-from-zero).
         */
        if( ( whichData < valueVectorArray.getSize() )
            &&
            ( 0 <= soughtIndex )
            &&
            ( (size_t)soughtIndex < valueVectorArray[ whichData ].size() ) )
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
      DenseSinglyIndexed< ValueType >::findOrMakeEntry( int const whichData,
                                                        int const soughtIndex )
      // this ensures that the entry at soughtIndex exists, filling out with
      // copies of defaultUnsetValue, & returns it.
      {
        if( valueVectorArray[ whichData ].size() <= (size_t)soughtIndex )
        {
          valueVectorArray[ whichData ].resize( ( soughtIndex + 1 ),
                                                this->defaultUnsetValue );
        }
        return valueVectorArray[ whichData ][ soughtIndex ];
      }

    }

  }

}

#endif /* DENSESINGLYINDEXED_HPP_ */
