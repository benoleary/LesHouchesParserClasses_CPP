/*
 * DenseTriplyIndexedBlock.hpp
 *
 *  Created on: Mar 12, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#ifndef DENSETRIPLYINDEXEDBLOCK_HPP_
#define DENSETRIPLYINDEXEDBLOCK_HPP_

#include "../SlhaBlock.hpp"
#include "InterpretterClasses/DenseTriplyIndexed.hpp"

namespace LHPC
{
  namespace SLHA
  {
    template< class ValueClass >
    class DenseTriplyIndexedBlock : public SlhaBlock< ValueClass,
                                    DenseTriplyIndexedBlockData< ValueClass > >
    {
    public:
      DenseTriplyIndexedBlock( std::string const& blockName,
                               ValueClass const& defaultUnsetValue,
                               bool const& isVerbose,
                               int const indexDigits = 5 );
      virtual
      ~DenseTriplyIndexedBlock();

      ValueClass&
      operator()( int const firstIndex,
                  int const secondIndex,
                  int const thirdIndex );
      // this returns operator() of the lowest-scale interpretter.
      ValueClass const&
      operator()( int const firstIndex,
                  int const secondIndex,
                  int const thirdIndex ) const;
      // const version of above.


    protected:
      int const indexDigits;
    };





    template< class ValueClass >
    inline
    DenseTriplyIndexedBlock< ValueClass >::DenseTriplyIndexedBlock(
                                                  std::string const& blockName,
                                           ValueClass const& defaultUnsetValue,
                                                         bool const& isVerbose,
                                                      int const indexDigits ) :
        SlhaBlock< ValueClass, DenseTriplyIndexedBlockData< ValueClass > >(
                                                                     blockName,
                                                             defaultUnsetValue,
                                                                   isVerbose ),
        indexDigits( indexDigits )
    {
      // just an initialization list.
    }

    template< class ValueClass >
    inline
    DenseTriplyIndexedBlock< ValueClass >::~DenseTriplyIndexedBlock()
    {
      // does nothing.
    }


    template< class ValueClass >
    inline ValueClass&
    DenseTriplyIndexedBlock< ValueClass >::operator()( int const firstIndex,
                                                       int const secondIndex,
                                                       int const thirdIndex )
    // this returns operator() of the lowest-scale interpretter.
    {
      return this->DataBlocks[ this->lowestScaleIndex() ]( firstIndex,
                                                           secondIndex,
                                                           thirdIndex );
    }

    template< class ValueClass >
    inline ValueClass const&
    DenseTriplyIndexedBlock< ValueClass >::operator()( int const firstIndex,
                                                       int const secondIndex,
                                                   int const thirdIndex ) const
    // const version of above.
    {
      return this->DataBlocks[ this->lowestScaleIndex() ]( firstIndex,
                                                           secondIndex,
                                                           thirdIndex );
    }

  }  // end of SLHA namespace

}  // end of LHPC namespace


#endif /* DENSETRIPLYINDEXEDBLOCK_HPP_ */
