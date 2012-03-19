/*
 * SparseDoublyIndexedBlock.hpp
 *
 *  Created on: Mar 19, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.LHPC_CPP.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#ifndef SPARSEDOUBLYINDEXEDBLOCK_HPP_
#define SPARSEDOUBLYINDEXEDBLOCK_HPP_

#include "IndexedBlockTemplate.hpp"
#include "InterpreterClasses/SparseDoublyIndexed.hpp"

namespace LHPC
{
  namespace SLHA
  {
    /* this template class interprets all the blocks with the same name, though
     * differing scale values, which are interpreted as having a pair of int
     * indices which does not have to have entries for each value (nor even
     * necessarily positive index values).
     */
    template< class ValueClass >
    class SparseDoublyIndexedBlock : public IndexedBlockTemplate< ValueClass,
                          InterpreterClass::SparseDoublyIndexed< ValueClass > >
    {
    public:
      SparseDoublyIndexedBlock( std::string const& blockName,
                                ValueClass const& defaultUnsetValue,
                                bool const& isVerbose,
                                int const indexDigits = 2 );
      virtual
      ~SparseDoublyIndexedBlock();

      ValueClass&
      operator()( int const firstIndex,
                  int const secondIndex );
      // this returns operator() of the lowest-scale interpreter.
      ValueClass const&
      operator()( int const firstIndex,
                  int const secondIndex ) const;
      // const version of above.
      bool
      hasEntry( int const firstIndex,
                int const secondIndex ) const;
      // this returns hasEntry( soughtIndex ) of the lowest-scale interpreter.
    };





    template< class ValueClass >
    inline
    SparseDoublyIndexedBlock< ValueClass >::SparseDoublyIndexedBlock(
                                                  std::string const& blockName,
                                           ValueClass const& defaultUnsetValue,
                                                         bool const& isVerbose,
                                                      int const indexDigits ) :
        IndexedBlockTemplate< ValueClass,
                         InterpreterClass::SparseDoublyIndexed< ValueClass > >(
                                                                     blockName,
                                                             defaultUnsetValue,
                                                                     isVerbose,
                                                                 indexDigits )
    {
      // just an initialization list.
    }

    template< class ValueClass >
    inline
    SparseDoublyIndexedBlock< ValueClass >::~SparseDoublyIndexedBlock()
    {
      // does nothing.
    }


    template< class ValueClass >
    inline ValueClass&
    SparseDoublyIndexedBlock< ValueClass >::operator()( int const firstIndex,
                                                        int const secondIndex )
    // this returns operator() of the lowest-scale interpreter.
    {
      return this->DataBlocks[ this->lowestScaleIndex ]( firstIndex,
                                                         secondIndex );
    }

    template< class ValueClass >
    inline ValueClass const&
    SparseDoublyIndexedBlock< ValueClass >::operator()( int const firstIndex,
                                                  int const secondIndex ) const
    // const version of above.
    {
      return this->DataBlocks[ this->lowestScaleIndex ]( firstIndex,
                                                         secondIndex );
    }

    template< class ValueClass >
    inline bool
    SparseDoublyIndexedBlock< ValueClass >::hasEntry( int const firstIndex,
                                                  int const secondIndex ) const
    // derived classes over-ride this to interpret their data as a
    // std::string.
    {
      return this->DataBlocks[ this->lowestScaleIndex ]( firstIndex,
                                                         secondIndex );
    }

  }  // end of SLHA namespace

}  // end of LHPC namespace


#endif /* SPARSEDOUBLYINDEXEDBLOCK_HPP_ */
