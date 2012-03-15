/*
 * SparseSinglyIndexedBlock.hpp
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

#ifndef SPARSESINGLYINDEXEDBLOCK_HPP_
#define SPARSESINGLYINDEXEDBLOCK_HPP_

#include "IndexedBlockTemplate.hpp"
#include "InterpreterClasses/SparseSinglyIndexed.hpp"

namespace LHPC
{
  namespace SLHA
  {
    /* this template class interprets all the blocks with the same name, though
     * differing scale values, which are interpreted as having a single int
     * index which does not have to have entries for each value (nor even
     * necessarily positive index values).
     */
    template< class ValueClass >
    class SparseSinglyIndexedBlock : public IndexedBlockTemplate< ValueClass,
                          InterpreterClass::SparseSinglyIndexed< ValueClass > >
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
      // this returns operator() of the lowest-scale interpreter.
      ValueClass const&
      operator()( int const soughtIndex ) const;
      // const version of above.
      bool
      hasEntry( int const soughtIndex ) const;
      // this returns hasEntry( soughtIndex ) of the lowest-scale interpreter.
      virtual bool
      isFmassBlock() const;
      // this returns false. only a specific derived class should over-ride it
      // to return true if it is actually an interpreter for an FMASS block.
      virtual std::map< int, ExtendedMass > const*
      getFmassMap() const;
      // this returns NULL. only a specific derived class should over-ride it
      // to return a non-NULL pointer.
      virtual bool
      isMassBlock() const;
      // this returns false. only a specific derived class should over-ride it
      // to return true if it is actually an interpreter for a MASS block.
      virtual std::map< int, double > const*
      getMassMap() const;
      // this returns NULL. only a specific derived class should over-ride it
      // to return a non-NULL pointer.


    protected:
      bool isFmassBlock;
      bool isMassBlock;
    };





    template< class ValueClass >
    inline
    SparseSinglyIndexedBlock< ValueClass >::SparseSinglyIndexedBlock(
                                                  std::string const& blockName,
                                           ValueClass const& defaultUnsetValue,
                                                         bool const& isVerbose,
                                                      int const indexDigits ) :
        IndexedBlockTemplate< ValueClass,
                         InterpreterClass::SparseSinglyIndexed< ValueClass > >(
                                                                     blockName,
                                                             defaultUnsetValue,
                                                                   isVerbose,
                                                                 indexDigits ),
        isFmassBlock( false ),
        isMassBlock( false )
    {
      if( this->nameMatches( "FMASS" ) )
      {
        this->isFmassBlock = true;
      }
      else if( this->nameMatches( "MASS" ) )
      {
        this->isMassBlock = true;
      }
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
    // this returns operator() of the lowest-scale interpreter.
    {
      return this->DataBlocks[ this->lowestIndex ]( soughtIndex );
    }

    template< class ValueClass >
    inline ValueClass const&
    SparseSinglyIndexedBlock< ValueClass >::operator()(
                                                  int const soughtIndex ) const
    // const version of above.
    {
      return this->DataBlocks[ this->lowestIndex ]( soughtIndex );
    }

    template< class ValueClass >
    inline bool
    SparseSinglyIndexedBlock< ValueClass >::hasEntry(
                                                  int const soughtIndex ) const
    // this returns hasEntry( soughtIndex ) of the lowest-scale interpreter.
    {
      return this->DataBlocks[ this->lowestIndex ].hasEntry( soughtIndex );
    }

    template< class ValueClass >
    inline bool
    SparseSinglyIndexedBlock< ValueClass >::isFmassBlock() const
    // this returns false. only a specific derived class should over-ride it
    // to return true if it is actually an interpreter for an FMASS block.
    {
      return this->isFmassBlock;
    }

    template< class ValueClass >
    inline std::map< int, ExtendedMass > const*
    SparseSinglyIndexedBlock< ValueClass >::getFmassMap() const
    {
      return NULL;
    }

    template<>
    inline std::map< int, ExtendedMass > const*
    SparseSinglyIndexedBlock< ExtendedMass >::getFmassMap() const
    // this over-rides the default to return a non-NULL pointer if appropriate.
    {
      if( this->isFmassBlock )
      {
        return &(this->DataBlocks[ this->lowestIndex ].getValueMap());
      }
      else
      {
        return NULL;
      }
    }

    template< class ValueClass >
    inline bool
    SparseSinglyIndexedBlock< ValueClass >::isMassBlock() const
    // this returns false. only a specific derived class should over-ride it
    // to return true if it is actually an interpreter for an FMASS block.
    {
      return this->isMassBlock;
    }

    template< class ValueClass >
    inline std::map< int, double > const*
    SparseSinglyIndexedBlock< ValueClass >::getMassMap() const
    // this returns NULL. only a specific derived class should over-ride it
    // to return a non-NULL pointer.
    {
      return NULL;
    }

    template<>
    inline std::map< int, double > const*
    SparseSinglyIndexedBlock< double >::getMassMap() const
    // this over-rides the default to return a non-NULL pointer if appropriate.
    {
      if( this->isMassBlock )
      {
        return &(this->DataBlocks[ this->lowestIndex ].getValueMap());
      }
      else
      {
        return NULL;
      }
    }

  }  // end of SLHA namespace

}  // end of LHPC namespace

#endif /* SPARSESINGLYINDEXEDBLOCK_HPP_ */
