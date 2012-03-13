/*
 * DenseSinglyIndexedBlock.hpp
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

#ifndef DENSESINGLYINDEXEDBLOCK_HPP_
#define DENSESINGLYINDEXEDBLOCK_HPP_

#include "../SlhaBlock.hpp"
#include "InterpreterClasses/DenseSinglyIndexed.hpp"

namespace LHPC
{
  namespace SLHA
  {
    /* this template class interprets all the blocks with the same name, though
     * differing scale values, which are interpreted as having a single int
     * index which has to have entries for each value, beginning with index 1.
     */
    template< class ValueClass >
    class DenseSinglyIndexedBlock : public SlhaBlock< ValueClass,
                          InterpreterClass::DenseSinglyIndexed< ValueClass > >
    {
    public:
      DenseSinglyIndexedBlock( std::string const& blockName,
                               ValueClass const& defaultUnsetValue,
                               bool const& isVerbose,
                               int const indexDigits = 5 );
      virtual
      ~DenseSinglyIndexedBlock();

      ValueClass&
      operator()( int const soughtIndex );
      // this returns operator() of the lowest-scale interpreter.
      ValueClass const&
      operator()( int const soughtIndex ) const;
      // const version of above.


    protected:
      int const indexDigits;

      virtual void
      setExtraValuesForNewInterpreter();
    };





    template< class ValueClass >
    inline
    DenseSinglyIndexedBlock< ValueClass >::DenseSinglyIndexedBlock(
                                                  std::string const& blockName,
                                           ValueClass const& defaultUnsetValue,
                                                         bool const& isVerbose,
                                                      int const indexDigits ) :
        SlhaBlock< ValueClass,
                   InterpreterClass::DenseSinglyIndexed< ValueClass > >(
                                                                     blockName,
                                                             defaultUnsetValue,
                                                                   isVerbose ),
        indexDigits( indexDigits )
    {
      // just an initialization list.
    }

    template< class ValueClass >
    inline
    DenseSinglyIndexedBlock< ValueClass >::~DenseSinglyIndexedBlock()
    {
      // does nothing.
    }


    template< class ValueClass >
    inline ValueClass&
    DenseSinglyIndexedBlock< ValueClass >::operator()( int const soughtIndex )
    // this returns operator() of the lowest-scale interpreter.
    {
      if( this->DataBlocks.isEmpty() )
      {
        this->DataBlocks.setSize( 1 );
      }
      return this->DataBlocks[ this->lowestScaleIndex() ]( soughtIndex );
    }

    template< class ValueClass >
    inline ValueClass const&
    DenseSinglyIndexedBlock< ValueClass >::operator()(
                                                  int const soughtIndex ) const
    // const version of above.
    {
      if( this->DataBlocks.isEmpty() )
      {
        return this->defaultUnsetValue;
      }
      else
      {
        return this->DataBlocks[ this->lowestScaleIndex() ]( soughtIndex );
      }
    }

    template< class ValueClass >
    inline void
    DenseSinglyIndexedBlock< ValueClass >::setExtraValuesForNewInterpreter()
    {
      this->DataBlocks.getBack().setIndexDigits( indexDigits );
    }

  }  // end of SLHA namespace

}  // end of LHPC namespace


#endif /* DENSESINGLYINDEXEDBLOCK_HPP_ */
