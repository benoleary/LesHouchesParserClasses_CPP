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

#include "IndexedBlockTemplate.hpp"

namespace LHPC
{
  namespace SLHA
  {
    namespace InterpretterClass
    {
      // this template class interprets SLHA blocks that have a single int
      // index with a single ValueClass value.
      template< class ValueClass >
      class SparseSinglyIndexed : public IndexedBlockTemplate< ValueClass >
      {
      public:
        SparseSinglyIndexed( ValueClass const& defaultUnsetValue,
                             bool const& isVerbose,
                             int const indexDigits = 5 );
        virtual
        ~SparseSinglyIndexed();

        ValueClass&
        operator()( int const soughtIndex );
        /* this returns the ValueClass mapped to by soughtIndex. if there is no
         * element at soughtIndex, a new one is made & copied from
         * defaultUnsetValue.
         */
        ValueClass const&
        operator()( int const soughtIndex ) const;
        /* const version of above, though it returns defaultUnsetValue rather
         * than copying in a new element at soughtIndex if there isn't an entry
         * there already.
         */
        ValueClass&
        operator[]( int const soughtIndex ) { return (*this)( soughtIndex ); }
        ValueClass const&
        operator[]( int const soughtIndex ) const { return (*this)(
                                                               soughtIndex ); }
        virtual std::string const&
        interpretAsString();
        // see base version's description.
        virtual std::map< int, ValueClass > const&
        getValueMap() const;
        bool
        hasEntry( int const soughtIndex ) const;
        // this returns true if there is an entry at soughtIndex.
        virtual void
        updateSelf();


      protected:
        std::map< int, ValueClass > valueMap;
        std::pair< int, ValueClass > valueRecorder;
      };





      template< class ValueClass >
      inline
      SparseSinglyIndexed< ValueClass >::SparseSinglyIndexed(
                                           ValueClass const& defaultUnsetValue,
                                                         bool const& isVerbose,
                                                      int const indexDigits ) :
          IndexedBlockTemplate< ValueClass >( defaultUnsetValue,
                                              isVerbose,
                                              indexDigits ),
          valueMap(),
          valueRecorder()
      {
        // just an initialization list.
      }

      template< class ValueClass >
      inline
      SparseSinglyIndexed< ValueClass >::~SparseSinglyIndexed()
      {
        // does nothing.
      }


      template< class ValueClass >
      inline ValueClass&
      SparseSinglyIndexed< ValueClass >::operator()( int const soughtIndex )
      /* this returns the ValueClass mapped to by soughtIndex for the data
       * with lowest energy scale. if there is no element at soughtIndex, a new
       * one is made & copied from defaultUnsetValue.
       */
      {
        if( 0 >= valueMap.count( soughtIndex ) )
        {
          valueMap[ soughtIndex ] = this->defaultUnsetValue;
        }
        return valueMap[ soughtIndex ];
      }

      template< class ValueClass >
      inline ValueClass const&
      SparseSinglyIndexed< ValueClass >::operator()(
                                                  int const soughtIndex ) const
      /* const version of above, though it returns defaultUnsetValue rather
       * than copying in a new element at soughtIndex if there isn't an entry
       * there already.
       */
      {
        std::map< int, ValueClass >::const_iterator
        valueFinder( valueMap.find( soughtIndex ) );
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
      inline std::string const&
      SparseSinglyIndexed< ValueClass >::interpretAsString()
      // see base version's description.
      {
        this->stringInterpretation.clear();
        std::map< int, ValueClass >::const_iterator
        valueFinder( valueMap.begin() );
        while( valueFinder != valueMap.end() )
        {
          this->stringInterpretation.append( this->indexToPrintingString(
                                                        valueFinder->first ) );
          this->stringInterpretation.append( this->valueToPrintingString(
                                                       valueFinder->second ) );
          /* negative particle codes can be avoided in any block, I think.
           * well, the exact format is only specified for the MASS block, &
           * in that case, negative particle codes can be avoided, since the
           * charge-conjugate just has the same mass. if the charge-conjugate
           * pair has a mass splitting, I think they are defined with 2
           * separate codes. if negative codes end up here, it's not my
           * fault...
           */
          this->stringInterpretation.append( "\n" );
          ++valueFinder;
        }
        return this->stringInterpretation;
      }

      template< class ValueClass >
      inline std::map< int, ValueClass > const&
      SparseSinglyIndexed< ValueClass >::getValueMap() const
      {
        return valueMap;
      }

      template< class ValueClass >
      inline bool
      SparseSinglyIndexed< ValueClass >::hasEntry(
                                                  int const soughtIndex ) const
      // this returns true if there is an entry at soughtIndex.
      {
        return ( 0 >= valueMap.count( soughtIndex ) );
      }

      template< class ValueClass >
      inline void
      SparseSinglyIndexed< ValueClass >::updateSelf()
      {
        valueMap.clear();
        for( int whichLine( this->stringsToObserve->getNumberOfLines() );
             0 < whichLine;
             --whichLine )
        {
          this->currentWord.assign( BOL::StringParser::firstWordOf(
                                (*(this->stringsToObserve))[ whichLine ].first,
                                                       &(this->lineRemainderA),
                              BOL::StringParser::whitespaceAndNewlineChars ) );
          if( !(this->currentWord.empty()) )
          {
            valueRecorder.first
            = BOL::StringParser::stringToInt( this->currentWord );
            valueRecorder.second
            = this->stringToValue( BOL::StringParser::trimFromFrontAndBack(
                                                          this->lineRemainderA,
                              BOL::StringParser::whitespaceAndNewlineChars ) );
            valueMap.insert( valueRecorder );
          }
        }
      }

    }
    typedef typename
    InterpretterClass::SparseSinglyIndexed SparseSinglyIndexedBlockData;

  }

}

#endif /* SPARSESINGLYINDEXED_HPP_ */
