/*
 * SinglyIndexedMultiblock.hpp
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

#ifndef SINGLYINDEXEDMULTIBLOCK_HPP_
#define SINGLYINDEXEDMULTIBLOCK_HPP_

#include "../../MassEigenstateCollectionClasses/ExtendedMass.hpp"
#include "IndexedBlockTemplate.hpp"
#include "InterpreterClasses/MultipleSinglyIndexed.hpp"

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
    class SinglyIndexedMultiblock : public IndexedBlockTemplate< ValueClass,
                          InterpreterClass::SparseSinglyIndexed< ValueClass > >
    {
    public:
      SinglyIndexedMultiblock( std::string const& blockName,
                               ValueClass const& defaultUnsetValue,
                               bool const& isVerbose,
                               int const indexDigits = 5 );
      virtual
      ~SinglyIndexedMultiblock();

      std::list< ValueClass* >
      operator()( int const soughtIndex );
      // this returns operator() of the lowest-scale interpreter.
      std::list< ValueClass const* >
      operator()( int const soughtIndex ) const;
      // const version of above.
      bool
      hasEntry( int const soughtIndex ) const;
      // this returns hasEntry( soughtIndex ) of the lowest-scale interpreter.
      virtual bool
      isFmassBlock() const;
      // this returns false. only a specific derived class should over-ride it
      // to return true if it is actually an interpreter for a FMASS block.
      virtual std::multimap< int, double > const*
      getFmassMap() const;
      // this returns NULL. only a specific derived class should over-ride it
      // to return a non-NULL pointer.


    protected:
      bool isFmassBlockFlag;
    };





    template< class ValueClass >
    inline
    SinglyIndexedMultiblock< ValueClass >::SinglyIndexedMultiblock(
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
        isFmassBlockFlag( false )
    {
      if( this->nameMatches( "FMASS" ) )
      {
        isFmassBlockFlag = true;
      }
    }

    template< class ValueClass >
    inline
    SinglyIndexedMultiblock< ValueClass >::~SinglyIndexedMultiblock()
    {
      // does nothing.
    }


    template< class ValueClass >
    inline std::list< ValueClass* >
    SinglyIndexedMultiblock< ValueClass >::operator()( int const soughtIndex )
    // this returns operator() of the lowest-scale interpreter.
    {
      return this->DataBlocks[ this->lowestScaleIndex ]( soughtIndex );
    }

    template< class ValueClass >
    inline std::list< ValueClass const* >
    SinglyIndexedMultiblock< ValueClass >::operator()(
                                                  int const soughtIndex ) const
    // const version of above.
    {
      return this->DataBlocks[ this->lowestScaleIndex ]( soughtIndex );
    }

    template< class ValueClass >
    inline bool
    SinglyIndexedMultiblock< ValueClass >::hasEntry(
                                                  int const soughtIndex ) const
    // this returns hasEntry( soughtIndex ) of the lowest-scale interpreter.
    {
      return this->DataBlocks[ this->lowestIndex ].hasEntry( soughtIndex );
    }

    template< class ValueClass >
    inline bool
    SinglyIndexedMultiblock< ValueClass >::isFmassBlock() const
    // this returns false. only a specific derived class should over-ride it
    // to return true if it is actually an interpreter for an FMASS block.
    {
      return isFmassBlockFlag;
    }

    template< class ValueClass >
    inline std::multimap< int, double > const*
    SinglyIndexedMultiblock< ValueClass >::getFmassMap() const
    // this returns NULL. only a specific derived class should over-ride it
    // to return a non-NULL pointer.
    {
      return NULL;
    }

    template<>
    inline std::multimap< int, ExtendedMass > const*
    SinglyIndexedMultiblock< double >::getFmassMap() const
    // this over-rides the default to return a non-NULL pointer if appropriate.
    {
      if( isFmassBlockFlag )
      {
        return &(this->DataBlocks[ this->lowestScaleIndex ].getValueMap());
      }
      else
      {
        return NULL;
      }
    }

  }  // end of SLHA namespace

}  // end of LHPC namespace

#endif /* SINGLYINDEXEDMULTIBLOCK_HPP_ */
