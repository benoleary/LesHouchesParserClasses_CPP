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

#include "../SlhaBlock.hpp"
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
    class SparseSinglyIndexedBlock : public SlhaBlock< ValueClass,
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
      virtual std::map< int, ExtendedMass > const*
      getFmassMap() const;
      // this returns NULL. only a specific derived class should over-ride it
      // to return a non-NULL pointer.
      virtual std::map< int, double > const*
      getMassMap() const;
      // this returns NULL. only a specific derived class should over-ride it
      // to return a non-NULL pointer.


    protected:
      int const indexDigits;

      virtual void
      setExtraValuesForNewInterpreter();
    };





    template< class ValueClass >
    inline
    SparseSinglyIndexedBlock< ValueClass >::SparseSinglyIndexedBlock(
                                                  std::string const& blockName,
                                           ValueClass const& defaultUnsetValue,
                                                         bool const& isVerbose,
                                                      int const indexDigits ) :
        SlhaBlock< ValueClass,
                   InterpreterClass::SparseSinglyIndexed< ValueClass > >(
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
    SparseSinglyIndexedBlock< ValueClass >::operator()(
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
    inline std::map< int, ExtendedMass > const*
    SparseSinglyIndexedBlock< ValueClass >::getFmassMap() const
    {
      return NULL;
    }

    template<>
    inline std::map< int, ExtendedMass > const*
    SparseSinglyIndexedBlock< ExtendedMass >::getFmassMap() const
    {
      if( !(this->DataBlocks.isEmpty())
          &&
          nameMatches( "FMASS" ) )
      {
        return &(this->DataBlocks[ this->lowestScaleIndex() ].getValueMap());
      }
      else
      {
        return NULL;
      }
    }

    template< class ValueClass >
    inline std::map< int, double > const*
    SparseSinglyIndexedBlock< ValueClass >::getMassMap() const
    {
      return NULL;
    }

    template<>
    inline std::map< int, double > const*
    SparseSinglyIndexedBlock< double >::getMassMap() const
    {
      if( !(this->DataBlocks.isEmpty())
          &&
          nameMatches( "MASS" ) )
      {
        return &(this->DataBlocks[ this->lowestScaleIndex() ].getValueMap());
      }
      else
      {
        return NULL;
      }
    }

    template< class ValueClass >
    inline void
    SparseSinglyIndexedBlock< ValueClass >::setExtraValuesForNewInterpreter()
    {
      this->DataBlocks.getBack().setIndexDigits( indexDigits );
    }

  }  // end of SLHA namespace

}  // end of LHPC namespace

#endif /* SPARSESINGLYINDEXEDBLOCK_HPP_ */
