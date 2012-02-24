/*
 * JustSingleValue.hpp
 *
 *  Created on: Feb 8, 2012
 *      Author: oleary
 */

#ifndef JUSTSINGLEVALUE_HPP_
#define JUSTSINGLEVALUE_HPP_

#include "StandardBlockTemplate.hpp"

namespace LHPC
{
  namespace SLHA
  {
    namespace BlockClass
    {
      // forward declaration because of template issues:
      template< typename ValueType > class StandardBlockTemplate;

      // this template class derives from StandardBlockTemplate to interpret
      // SLHA blocks that have a single ValueType value.
      template< typename ValueType >
      class JustSingleValue : public StandardBlockTemplate< ValueType >
      {
      public:
        JustSingleValue( std::string const& blockName,
                         ValueType const& defaultUnsetValue,
                         bool const& isVerbose,
                         std::string const blockHeaderComment = "" );
        virtual
        ~JustSingleValue();

        ValueType&
        operator()( double const blockScale );
        // this returns the stored ValueType for the data with energy scale
        // nearest blockScale.
        ValueType const&
        operator()( double const blockScale ) const;
        // const version of above.
        ValueType&
        operator()();
        // this returns the stored ValueType for the data with lowest energy
        // scale.
        ValueType const&
        operator()() const;
        // const version of above.
        virtual std::string const&
        interpretAsString( double const blockScale = 0.0 );
        // see base version's description.


      protected:
        BOL::VectorlikeArray< ValueType > valueArray;

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
      JustSingleValue< ValueType >::JustSingleValue(
                                                  std::string const& blockName,
                                            ValueType const& defaultUnsetValue,
                                                     bool const& isVerbose,
                                       std::string const blockHeaderComment ) :
          StandardBlockTemplate< ValueType >( blockName,
                                              defaultUnsetValue,
                                              isVerbose,
                                              1,
                                              blockHeaderComment ),
          valueArray()
      {
        // just an initialization list.
      }

      template< typename ValueType >
      inline
      JustSingleValue< ValueType >::~JustSingleValue()
      {
        // does nothing.
      }


      template< typename ValueType >
      inline ValueType&
      JustSingleValue< ValueType >::operator()( double const blockScale )
      // this returns the stored ValueType for the data with energy scale
      // nearest blockScale.
      {
        return valueArray[ this->findScaleIndex( blockScale ) ];
      }

      template< typename ValueType >
      inline ValueType const&
      JustSingleValue< ValueType >::operator()( double const blockScale ) const
      // this returns the stored ValueType for the data with energy scale
      // nearest blockScale.
      {
        return valueArray[ this->findScaleIndex( blockScale ) ];
      }

      template< typename ValueType >
      inline ValueType&
      JustSingleValue< ValueType >::operator()()
      // this returns the stored ValueType for the data with lowest energy
      // scale.
      {
        return valueArray[ this->lowestScaleIndex ];
      }

      template< typename ValueType >
      inline ValueType const&
      JustSingleValue< ValueType >::operator()() const
      // this returns the stored ValueType for the data with lowest energy
      // scale.
      {
        return valueArray[ this->lowestScaleIndex ];
      }

      template< typename ValueType >
      inline std::string const&
      JustSingleValue< ValueType >::interpretAsString(
                                                      double const blockScale )
      // see base version's description.
      {
        this->findScaleIndex( blockScale );
        SlhaBlock::returnString.assign( "      " );
        // 6 spaces.
        this->putValueIntoReturnString( valueArray[ this->currentIndex ] );
        return SlhaBlock::returnString;
      }

      template< typename ValueType >
      inline void
      JustSingleValue< ValueType >::clearExtraStuff()
      // derived classes should clear their extra data here.
      {
        valueArray.clearEntries();
      }

      template< typename ValueType >
      inline void
      JustSingleValue< ValueType >::prepareExtraStuffForNewScale()
      {
        valueArray.newEnd() = this->defaultUnsetValue;
        // this ensures that valueArray[ currentIndex ] exists & is set to the
        // default value.
      }

      template< typename ValueType >
      inline void
      JustSingleValue< ValueType >::interpretBodyLine()
      // this interprets the entirity of comparisonString as the held value.
      {
        SlhaBlock::currentWord.assign( BOL::StringParser::trimFromFront(
                                               BOL::StringParser::trimFromBack(
                                                   SlhaBlock::comparisonString,
                                                                   " \t\r\n" ),
                                                                 " \t\r\n" ) );
        if( !(SlhaBlock::currentWord.empty()) )
        {
          valueArray[ this->currentIndex ]
          = this->stringToValue( SlhaBlock::currentWord );
        }
      }

    }

  }

}

#endif /* JUSTSINGLEVALUE_HPP_ */
