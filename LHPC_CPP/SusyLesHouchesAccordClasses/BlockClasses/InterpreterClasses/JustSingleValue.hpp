/*
 * JustSingleValue.hpp
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

#ifndef JUSTSINGLEVALUE_HPP_
#define JUSTSINGLEVALUE_HPP_

#include "StandardBlockTemplate.hpp"

namespace LHPC
{
  namespace SLHA
  {
    namespace InterpreterClass
    {
      // this template class interprets SLHA blocks that have a single
      // ValueClass value.
      template< class ValueClass >
      class JustSingleValue : public StandardBlockTemplate< ValueClass >
      {
      public:
        JustSingleValue();
        virtual
        ~JustSingleValue();

        ValueClass&
        operator()();
        // this returns the stored ValueType.
        ValueClass const&
        operator()() const;
        // const version of above.
        virtual std::string const&
        interpretAsString();
        // see base version's description.
        bool
        hasEntry() const;
        // this returns true if there is an entry.
        virtual void
        updateSelf();


      protected:
        ValueClass storedValue;
        bool entryRecorded;
      };



      template< class ValueClass >
      inline
      JustSingleValue< ValueClass >::JustSingleValue() :
          StandardBlockTemplate< ValueClass >(),
          storedValue(),
          entryRecorded( false )
      {
        // just an initialization list.
      }

      template< class ValueClass >
      inline
      JustSingleValue< ValueClass >::~JustSingleValue()
      {
        // does nothing.
      }


      template< class ValueClass >
      inline ValueClass&
      JustSingleValue< ValueClass >::operator()()
      // this returns the stored ValueType.
      {
        return storedValue;
      }

      template< class ValueClass >
      inline ValueClass const&
      JustSingleValue< ValueClass >::operator()() const
      // const version of above.
      {
        return storedValue;
      }

      template< class ValueClass >
      inline std::string const&
      JustSingleValue< ValueClass >::interpretAsString()
      // see base version's description.
      {
        this->stringInterpretation.assign( "      " );
        // 6 spaces.
        this->stringInterpretation.append( this->valueToPrintingString(
                                                               storedValue ) );
        this->stringInterpretation.append( "\n" );
        return this->stringInterpretation;
      }

      template< class ValueClass >
      inline bool
      JustSingleValue< ValueClass >::hasEntry() const
      // this returns true if there is an entry.
      {
        return entryRecorded;
      }

      template< class ValueClass >
      inline void
      JustSingleValue< ValueClass >::updateSelf()
      {
        entryRecorded = false;
        // first it is assumed that this update is on an empty block.
        for( int whichLine( 1 );
             ( !entryRecorded
               &&
               ( this->stringsToObserve->getNumberOfLines() > whichLine ) );
             ++whichLine )
          // each line after the header (if any) is looked at.
        {
          this->currentWord.assign( BOL::StringParser::trimFromFrontAndBack(
                                (*(this->stringsToObserve))[ whichLine ].first,
                                                                 " \t\r\n" ) );
          if( !(this->currentWord.empty()) )
            // if there is a non-empty line...
          {
            storedValue = this->stringToValue( this->currentWord );
            entryRecorded = true;
          }
        }
      }

    }

  }

}

#endif /* JUSTSINGLEVALUE_HPP_ */