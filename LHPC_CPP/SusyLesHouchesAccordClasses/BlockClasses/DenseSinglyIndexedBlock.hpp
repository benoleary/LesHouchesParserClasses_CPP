/*
 * DenseSinglyIndexedBlock.hpp
 *
 *  Created on: Mar 12, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#ifndef DENSESINGLYINDEXEDBLOCK_HPP_
#define DENSESINGLYINDEXEDBLOCK_HPP_

#include "../SlhaBlock.hpp"
#include "InterpretterClasses/DenseSinglyIndexed.hpp"

namespace LHPC
{
  namespace SLHA
  {
    template< class ValueClass >
    class DenseSinglyIndexedBlock : public SlhaBlock< ValueClass,
                                    DenseSinglyIndexedBlockData< ValueClass > >
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
      // this returns operator() of the lowest-scale interpretter.
      ValueClass const&
      operator()( int const soughtIndex ) const;
      // const version of above.


    protected:
      int const indexDigits;
    };





    template< class ValueClass >
    inline
    DenseSinglyIndexedBlock< ValueClass >::DenseSinglyIndexedBlock(
                                                  std::string const& blockName,
                                           ValueClass const& defaultUnsetValue,
                                                         bool const& isVerbose,
                                                      int const indexDigits ) :
        SlhaBlock< ValueClass, DenseSinglyIndexedBlockData< ValueClass > >(
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
    // this returns operator() of the lowest-scale interpretter.
    {
      return this->DataBlocks[ this->lowestScaleIndex() ]( soughtIndex );
    }

    template< class ValueClass >
    inline ValueClass const&
    DenseSinglyIndexedBlock< ValueClass >::operator()(
                                                  int const soughtIndex ) const
    // const version of above.
    {
      return this->DataBlocks[ this->lowestScaleIndex() ]( soughtIndex );
    }

  }  // end of SLHA namespace

}  // end of LHPC namespace


#endif /* DENSESINGLYINDEXEDBLOCK_HPP_ */
