/*
 * DenseDoublyIndexedBlock.hpp
 *
 *  Created on: Mar 12, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.LHPC_CPP.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#ifndef DENSEDOUBLYINDEXEDBLOCK_HPP_
#define DENSEDOUBLYINDEXEDBLOCK_HPP_

#include "../SlhaBlock.hpp"
#include "InterpreterClasses/DenseDoublyIndexed.hpp"

namespace LHPC
{
  namespace SLHA
  {
    /* this template class interprets all the blocks with the same name, though
     * differing scale values, which are interpreted as having a pair of int
     * indices which have to have entries for each value, each index beginning
     * at 1.
     */
    template< class ValueClass >
    class DenseDoublyIndexedBlock : public SlhaBlock< ValueClass,
                           InterpreterClass::DenseDoublyIndexed< ValueClass > >
    {
    public:
      DenseDoublyIndexedBlock( std::string const& blockName,
                               ValueClass const& defaultUnsetValue,
                               bool const& isVerbose,
                               int const indexDigits = 2 );
      virtual
      ~DenseDoublyIndexedBlock();

      ValueClass&
      operator()( int const firstIndex,
                  int const secondIndex );
      // this returns operator() of the lowest-scale interpreter.
      ValueClass const&
      operator()( int const firstIndex,
                  int const secondIndex ) const;
      // const version of above.


    protected:
      int const indexDigits;

      virtual std::string
      getThisScaleAsString( int const scaleIndex );
      // derived classes over-ride this to interpret their data as a
      // std::string.
      virtual void
      setExtraValuesForNewInterpreter();
    };





    template< class ValueClass >
    inline
    DenseDoublyIndexedBlock< ValueClass >::DenseDoublyIndexedBlock(
                                                  std::string const& blockName,
                                           ValueClass const& defaultUnsetValue,
                                                         bool const& isVerbose,
                                                      int const indexDigits ) :
        SlhaBlock< ValueClass,
                   InterpreterClass::DenseDoublyIndexed< ValueClass > >(
                                                                     blockName,
                                                             defaultUnsetValue,
                                                                   isVerbose ),
        indexDigits( indexDigits )
    {
      // just an initialization list.
    }

    template< class ValueClass >
    inline
    DenseDoublyIndexedBlock< ValueClass >::~DenseDoublyIndexedBlock()
    {
      // does nothing.
    }


    template< class ValueClass >
    inline ValueClass&
    DenseDoublyIndexedBlock< ValueClass >::operator()( int const firstIndex,
                                                       int const secondIndex )
    // this returns operator() of the lowest-scale interpreter.
    {
      if( this->DataBlocks.isEmpty() )
      {
        this->DataBlocks.setSize( 1 );
      }
      return this->DataBlocks[ this->defaultDataBlockIndex() ]( firstIndex,
                                                                secondIndex );
    }

    template< class ValueClass >
    inline ValueClass const&
    DenseDoublyIndexedBlock< ValueClass >::operator()( int const firstIndex,
                                                  int const secondIndex ) const
    // const version of above.
    {
      if( this->DataBlocks.isEmpty() )
      {
        return this->defaultUnsetValue;
      }
      else
      {
        return this->DataBlocks[ this->defaultDataBlockIndex() ]( firstIndex,
                                                                 secondIndex );
      }
    }

    template< class ValueClass >
    inline std::string
    DenseDoublyIndexedBlock< ValueClass >::getThisScaleAsString(
                                                         int const scaleIndex )
    // derived classes over-ride this to interpret their data as a
    // std::string.
    {
      return this->DataBlocks[ scaleIndex - 1 ].interpretAsString();
    }

    template< class ValueClass >
    inline void
    DenseDoublyIndexedBlock< ValueClass >::setExtraValuesForNewInterpreter()
    {
      this->DataBlocks.getBack().setIndexDigits( indexDigits );
    }

  }  // end of SLHA namespace

}  // end of LHPC namespace


#endif /* DENSEDOUBLYINDEXEDBLOCK_HPP_ */
