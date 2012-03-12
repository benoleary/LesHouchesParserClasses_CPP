/*
 * DenseDoublyIndexedBlock.hpp
 *
 *  Created on: Mar 12, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#ifndef DENSEDOUBLYINDEXEDBLOCK_HPP_
#define DENSEDOUBLYINDEXEDBLOCK_HPP_

#include "../SlhaBlock.hpp"
#include "InterpretterClasses/DenseDoublyIndexed.hpp"

namespace LHPC
{
  namespace SLHA
  {
    template< class ValueClass >
    class DenseDoublyIndexedBlock : public SlhaBlock< ValueClass,
                                    DenseDoublyIndexedBlockData< ValueClass > >
    {
    public:
      DenseDoublyIndexedBlock( std::string const& blockName,
                               ValueClass const& defaultUnsetValue,
                               bool const& isVerbose,
                               int const indexDigits = 5 );
      virtual
      ~DenseDoublyIndexedBlock();

      ValueClass&
      operator()( int const firstIndex,
                  int const secondIndex );
      // this returns operator() of the lowest-scale interpretter.
      ValueClass const&
      operator()( int const firstIndex,
                  int const secondIndex ) const;
      // const version of above.


    protected:
      int const indexDigits;
    };





    template< class ValueClass >
    inline
    DenseDoublyIndexedBlock< ValueClass >::DenseDoublyIndexedBlock(
                                                  std::string const& blockName,
                                           ValueClass const& defaultUnsetValue,
                                                         bool const& isVerbose,
                                                      int const indexDigits ) :
        SlhaBlock< ValueClass, DenseDoublyIndexedBlockData< ValueClass > >(
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
    // this returns operator() of the lowest-scale interpretter.
    {
      return this->DataBlocks[ this->lowestScaleIndex() ]( firstIndex,
                                                           secondIndex );
    }

    template< class ValueClass >
    inline ValueClass const&
    DenseDoublyIndexedBlock< ValueClass >::operator()( int const firstIndex,
                                                  int const secondIndex ) const
    // const version of above.
    {
      return this->DataBlocks[ this->lowestScaleIndex() ]( firstIndex,
                                                           secondIndex );
    }

  }  // end of SLHA namespace

}  // end of LHPC namespace


#endif /* DENSEDOUBLYINDEXEDBLOCK_HPP_ */
