/*
 * SparseSinglyIndexed.hpp
 *
 *  Created on: Feb 7, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.LHPC_CPP.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#ifndef SPARSESINGLYINDEXED_HPP_
#define SPARSESINGLYINDEXED_HPP_

#include "StandardBlockTemplate.hpp"

namespace LHPC
{
  namespace SLHA
  {
    namespace BlockClass
    {
      // this template class derives from SlhaBlock to interpret SLHA
      // blocks that have a single int index with a single ValueType value.
      template< typename ValueType >
      class SparseSinglyIndexed : public StandardBlockTemplate< ValueType >
      {
      public:
        typedef typename std::map< int,
                                   ValueType > IntToValueMap;

        SparseSinglyIndexed( std::string const& blockName,
                             ValueType const& defaultUnsetValue,
                             bool const& isVerbose,
                             int const indexDigits = 5,
                             std::string const blockHeaderComment = "" );
        virtual
        ~SparseSinglyIndexed();

        ValueType&
        operator()( int const soughtIndex,
                    double const blockScale );
        /* this returns the ValueType mapped to by soughtIndex for the data
         * with energy scale nearest blockScale. if there is no element at
         * soughtIndex, a new one is made & copied from defaultUnsetValue.
         */
        ValueType const&
        operator()( int const soughtIndex,
                    double const blockScale ) const;
        /* const version of above, though it returns defaultUnsetValue rather
         * than copying in a new element at soughtIndex if there isn't an entry
         * there already.
         */
        ValueType&
        operator()( int const soughtIndex );
        /* this returns the ValueType mapped to by soughtIndex for the data
         * with lowest energy scale. if there is no element at soughtIndex, a
         * new one is made & copied from defaultUnsetValue.
         */
        ValueType const&
        operator()( int const soughtIndex ) const;
        /* const version of above, though it returns defaultUnsetValue rather
         * than copying in a new element at soughtIndex if there isn't an entry
         * there already.
         */
        ValueType&
        operator[]( int const soughtIndex ) { return (*this)( soughtIndex ); }
        ValueType const&
        operator[]( int const soughtIndex ) const { return (*this)(
                                                               soughtIndex ); }
        virtual std::string const&
        interpretAsString( double const blockScale = 0.0 );
        // see base version's description.
        virtual IntToValueMap const*
        getMap( double const blockScale = 0.0 );
        // this returns a pointer to the scale-appropriate std::map.


      protected:
        typedef typename std::map< int,
                                   ValueType >::iterator IntToValueMapIterator;

        BOL::VectorlikeArray< IntToValueMap > valueMapArray;
        IntToValueMapIterator valueFinder;
        std::pair< int,
                   ValueType > valueRecorder;

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
      };





      template< typename ValueType >
      inline
      SparseSinglyIndexed< ValueType >::SparseSinglyIndexed(
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
          valueMapArray(),
          valueFinder(),
          valueRecorder()
      {
        // just an initialization list.
      }

      template< typename ValueType >
      inline
      SparseSinglyIndexed< ValueType >::~SparseSinglyIndexed()
      {
        // does nothing.
      }


      template< typename ValueType >
      inline ValueType&
      SparseSinglyIndexed< ValueType >::operator()( int const soughtIndex,
                                                    double const blockScale )
      /* this returns the ValueType mapped to by soughtIndex for the data
       * with energy scale nearest blockScale. if there is no element at
       * soughtIndex, a new one is made & copied from defaultUnsetValue.
       */
      {
        this->currentIndex = this->findScaleIndex( blockScale );
        if( 0 >= valueMapArray[ this->currentIndex ].count( soughtIndex ) )
        {
          valueMapArray[ this->currentIndex ][ soughtIndex ]
          = this->defaultUnsetValue;
        }
        return
        valueMapArray[ this->currentIndex ][ soughtIndex ];
      }

      template< typename ValueType >
      inline ValueType const&
      SparseSinglyIndexed< ValueType >::operator()( int const soughtIndex,
                                                double const blockScale ) const
      /* const version of above, though it returns defaultUnsetValue rather
       * than copying in a new element at soughtIndex if there isn't an entry
       * there already.
       */
      {
        valueFinder = valueMapArray[ this->findScaleIndex( blockScale )
                                                         ].find( soughtIndex );
        if( valueMapArray.end() != valueFinder )
        {
          return valueFinder->second;
        }
        else
        {
          return this->defaultUnsetValue;
        }
      }

      template< typename ValueType >
      inline ValueType&
      SparseSinglyIndexed< ValueType >::operator()( int const soughtIndex )
      /* this returns the ValueType mapped to by soughtIndex for the data
       * with lowest energy scale. if there is no element at soughtIndex, a new
       * one is made & copied from defaultUnsetValue.
       */
      {
        if( 0 >= valueMapArray[ this->lowestScaleIndex ].count( soughtIndex ) )
        {
          valueMapArray[ this->currentIndex ][ soughtIndex ]
          = this->defaultUnsetValue;
        }
        return valueMapArray[ this->lowestScaleIndex ][ soughtIndex ];
      }

      template< typename ValueType >
      inline ValueType const&
      SparseSinglyIndexed< ValueType >::operator()(
                                                  int const soughtIndex ) const
      /* const version of above, though it returns defaultUnsetValue rather
       * than copying in a new element at soughtIndex if there isn't an entry
       * there already.
       */
      {
        valueFinder
        = valueMapArray[ this->lowestScaleIndex ].find( soughtIndex );
        if( valueMapArray.end() != valueFinder )
        {
          return valueFinder->second;
        }
        else
        {
          return this->defaultUnsetValue;
        }
      }

      template< typename ValueType >
      inline std::string const&
      SparseSinglyIndexed< ValueType >::interpretAsString(
                                                      double const blockScale )
      // see base version's description.
      {
        this->currentIndex = this->findScaleIndex( blockScale );
        SlhaBlock::returnString.clear();
        valueFinder = valueMapArray[ this->currentIndex ].begin();
        while( valueFinder != valueMapArray[ this->currentIndex ].end() )
        {
          this->putIndexIntoReturnString( valueFinder->first );
          this->putValueIntoReturnString( valueFinder->second );
          /* negative particle codes can be avoided in any block, I think.
           * well, the exact format is only specified for the MASS block, &
           * in that case, negative particle codes can be avoided, since the
           * charge-conjugate just has the same mass. if the charge-conjugate
           * pair has a mass splitting, I think they are defined with 2
           * separate codes. if negative codes end up here, it's not my
           * fault...
           */
          ++valueFinder;
        }
        return SlhaBlock::returnString;
      }

      template< typename ValueType >
      inline void
      SparseSinglyIndexed< ValueType >::clearExtraStuff()
      // derived classes should clear their extra data here.
      {
        valueMapArray.clearEntries();
      }

      template< typename ValueType >
      inline void
      SparseSinglyIndexed< ValueType >::prepareExtraStuffForNewScale()
      {
        valueMapArray.newEnd().clear();
        // this ensures that valueMapArray[ currentIndex ] is now an empty map.
      }

      template< typename ValueType >
      inline void
      SparseSinglyIndexed< ValueType >::interpretBodyLine()
      // derived classes should interpret comparisonString at this point, since
      // it is a non-empty data line.
      {
        SlhaBlock::currentWord.assign( BOL::StringParser::firstWordOf(
                                                   SlhaBlock::comparisonString,
                                                  &(SlhaBlock::firstRemainder),
                                                                 " \t\r\n" ) );
        if( !(SlhaBlock::currentWord.empty()) )
        {
          valueRecorder.first
          = BOL::StringParser::stringToInt( SlhaBlock::currentWord );
          SlhaBlock::currentWord.assign( BOL::StringParser::firstWordOf(
                                                     SlhaBlock::firstRemainder,
                                                 &(SlhaBlock::secondRemainder),
                                                                 " \t\r\n" ) );
          valueRecorder.second = this->stringToValue( SlhaBlock::currentWord );
          valueMapArray[ this->currentIndex ].insert( valueRecorder );
        }
      }

      template< typename ValueType >
      inline std::map< int,
                       ValueType > const*
      SparseSinglyIndexed< ValueType >::getMap( double const blockScale )
      // this returns a pointer to the scale-appropriate std::map.
      {
        if( valueMapArray.isEmpty() )
        {
          return NULL;
        }
        else
        {
          return
          valueMapArray.getPointer( this->findScaleIndex( blockScale ) );
        }
      }

    }

  }

}

#endif /* SPARSESINGLYINDEXED_HPP_ */
