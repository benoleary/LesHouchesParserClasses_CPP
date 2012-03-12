/*
 * SparseSinglyIndexedBlock.hpp
 *
 *  Created on: Mar 12, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#ifndef SPARSESINGLYINDEXEDBLOCK_HPP_
#define SPARSESINGLYINDEXEDBLOCK_HPP_

#include "../SlhaBlock.hpp"
#include "InterpretterClasses/SparseSinglyIndexed.hpp"

namespace LHPC
{
  namespace SLHA
  {
    template< class ValueClass >
    class SparseSinglyIndexedBlock : public SlhaBlock< ValueClass,
                                   SparseSinglyIndexedBlockData< ValueClass > >
    {
    public:
      SparseSinglyIndexedBlock( std::string const& blockName,
                                ValueClass const& defaultUnsetValue,
                                bool const& isVerbose,
                                int const indexDigits = 5 );
      virtual
      ~SparseSinglyIndexedBlock();

      ValueClass&
      operator()( int const soughtIndex );
      // this returns operator() of the lowest-scale interpretter.
      ValueClass const&
      operator()( int const soughtIndex ) const;
      // const version of above.


    protected:
      int const indexDigits;
    };





    template< class ValueClass >
    inline
    SparseSinglyIndexedBlock< ValueClass >::SparseSinglyIndexedBlock(
                                                  std::string const& blockName,
                                           ValueClass const& defaultUnsetValue,
                                                         bool const& isVerbose,
                                                      int const indexDigits ) :
        SlhaBlock< ValueClass, SparseSinglyIndexedBlockData< ValueClass > >(
                                                                     blockName,
                                                             defaultUnsetValue,
                                                                   isVerbose ),
        indexDigits( indexDigits )
    {
      // just an initialization list.
    }

    template< class ValueClass >
    inline
    SparseSinglyIndexedBlock< ValueClass >::~SparseSinglyIndexedBlock()
    {
      // does nothing.
    }


    template< class ValueClass >
    inline ValueClass&
    SparseSinglyIndexedBlock< ValueClass >::operator()( int const soughtIndex )
    // this returns operator() of the lowest-scale interpretter.
    {
      return this->DataBlocks[ this->lowestScaleIndex() ]( soughtIndex );
    }

    template< class ValueClass >
    inline ValueClass const&
    SparseSinglyIndexedBlock< ValueClass >::operator()(
                                                  int const soughtIndex ) const
    // const version of above.
    {
      return this->DataBlocks[ this->lowestScaleIndex() ]( soughtIndex );
    }

  }  // end of SLHA namespace

}  // end of LHPC namespace

#endif /* SPARSESINGLYINDEXEDBLOCK_HPP_ */
