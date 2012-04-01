/*
 * DoublyIndexedMultipleEntriesBlock.hpp
 *
 *  Created on: Apr 1, 2012 (really!)
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.LHPC_CPP.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#ifndef DOUBLYINDEXEDMULTIPLEENTRIESBLOCK_HPP_
#define DOUBLYINDEXEDMULTIPLEENTRIESBLOCK_HPP_

#include "../../MassEigenstateCollectionClasses/ExtendedMass.hpp"
#include "IndexedBlockTemplate.hpp"
#include "InterpreterClasses/MultipleDoublyIndexed.hpp"

namespace LHPC
{
  namespace SLHA
  {
    /* this template class interprets all the blocks with the same name, though
     * differing scale values, which are interpreted as having a single int
     * index which does not have to have entries for each value (nor even
     * necessarily positive index values), allowing for multiple entries with
     * the same index.
     */
    template< class ValueClass >
    class DoublyIndexedMultipleEntriesBlock : public IndexedBlockTemplate<
                                                                    ValueClass,
                        InterpreterClass::MultipleDoublyIndexed< ValueClass > >
    {
    public:
      DoublyIndexedMultipleEntriesBlock( std::string const& blockName,
                                         ValueClass const& defaultUnsetValue,
                                         bool const& isVerbose,
                                         int const firstIndexDigits = 5,
                                         int const secondIndexDigits = 5 );
      virtual
      ~DoublyIndexedMultipleEntriesBlock();

      std::list< ValueClass* >
      operator()( int const soughtIndex );
      // this returns operator() of the lowest-scale interpreter.
      std::list< ValueClass const* >
      operator()( int const soughtIndex ) const;
      // const version of above.
      bool
      hasEntry( int const soughtIndex ) const;
      // this returns hasEntry( soughtIndex ) of the lowest-scale interpreter.
    };





    template< class ValueClass >
    inline
    DoublyIndexedMultipleEntriesBlock< ValueClass
                                          >::DoublyIndexedMultipleEntriesBlock(
                                                  std::string const& blockName,
                                           ValueClass const& defaultUnsetValue,
                                                         bool const& isVerbose,
                                                    int const firstIndexDigits,
                                                int const secondIndexDigits ) :
        IndexedBlockTemplate< ValueClass,
                       InterpreterClass::MultipleDoublyIndexed< ValueClass > >(
                                                                     blockName,
                                                             defaultUnsetValue,
                                                                     isVerbose,
                           BOL::Vi( firstIndexDigits ).e( secondIndexDigits ) )
    {
      // just an initialization list.
    }

    template< class ValueClass >
    inline
    DoublyIndexedMultipleEntriesBlock< ValueClass
                                        >::~DoublyIndexedMultipleEntriesBlock()
    {
      // does nothing.
    }


    template< class ValueClass >
    inline std::list< ValueClass* >
    DoublyIndexedMultipleEntriesBlock< ValueClass >::operator()(
                                                        int const soughtIndex )
    // this returns operator() of the lowest-scale interpreter.
    {
      return this->DataBlocks[ this->lowestScaleIndex ]( soughtIndex );
    }

    template< class ValueClass >
    inline std::list< ValueClass const* >
    DoublyIndexedMultipleEntriesBlock< ValueClass >::operator()(
                                                  int const soughtIndex ) const
    // const version of above.
    {
      return this->DataBlocks[ this->lowestScaleIndex ]( soughtIndex );
    }

    template< class ValueClass >
    inline bool
    DoublyIndexedMultipleEntriesBlock< ValueClass >::hasEntry(
                                                  int const soughtIndex ) const
    // this returns hasEntry( soughtIndex ) of the lowest-scale interpreter.
    {
      return this->DataBlocks[ this->lowestIndex ].hasEntry( soughtIndex );
    }

  }  // end of SLHA namespace

}  // end of LHPC namespace

#endif /* DOUBLYINDEXEDMULTIPLEENTRIESBLOCK_HPP_ */
