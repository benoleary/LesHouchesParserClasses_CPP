/*
 * DenseTriplyIndexedBlock.hpp
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

#ifndef DENSETRIPLYINDEXEDBLOCK_HPP_
#define DENSETRIPLYINDEXEDBLOCK_HPP_

#include "../SlhaBlock.hpp"
#include "InterpreterClasses/DenseTriplyIndexed.hpp"

namespace LHPC
{
  namespace SLHA
  {
    /* this template class interprets all the blocks with the same name, though
     * differing scale values, which are interpreted as having a triple of int
     * indices which have to have entries for each value, each index beginning
     * at 1.
     */
    template< class ValueClass >
    class DenseTriplyIndexedBlock : public SlhaBlock< ValueClass,
                          InterpreterClass::DenseTriplyIndexed< ValueClass > >
    {
    public:
      DenseTriplyIndexedBlock( std::string const& blockName,
                               ValueClass const& defaultUnsetValue,
                               bool const& isVerbose,
                               int const indexDigits = 2 );
      virtual
      ~DenseTriplyIndexedBlock();

      ValueClass&
      operator()( int const firstIndex,
                  int const secondIndex,
                  int const thirdIndex );
      // this returns operator() of the lowest-scale interpreter.
      ValueClass const&
      operator()( int const firstIndex,
                  int const secondIndex,
                  int const thirdIndex ) const;
      // const version of above.


    protected:
      int const indexDigits;

      virtual std::string
      getThisScaleAsString( int const scaleIndex );
      // derived classes over-ride this to interpret their data as a
      // std::string.
      virtual void
      setExtraValuesForNewInterpreter();
    };





    template< class ValueClass >
    inline
    DenseTriplyIndexedBlock< ValueClass >::DenseTriplyIndexedBlock(
                                                  std::string const& blockName,
                                           ValueClass const& defaultUnsetValue,
                                                         bool const& isVerbose,
                                                      int const indexDigits ) :
        SlhaBlock< ValueClass,
                   InterpreterClass::DenseTriplyIndexed< ValueClass > >(
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
    // this returns operator() of the lowest-scale interpreter.
    {
      if( this->DataBlocks.isEmpty() )
      {
        this->DataBlocks.setSize( 1 );
      }
      return this->DataBlocks[ this->defaultDataBlockIndex() ]( firstIndex,
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
      if( this->DataBlocks.isEmpty() )
      {
        return this->defaultUnsetValue;
      }
      else
      {
        return this->DataBlocks[ this->defaultDataBlockIndex() ]( firstIndex,
                                                                  secondIndex,
                                                                  thirdIndex );
      }
    }

    template< class ValueClass >
    inline std::string
    DenseTriplyIndexedBlock< ValueClass >::getThisScaleAsString(
                                                         int const scaleIndex )
    // derived classes over-ride this to interpret their data as a
    // std::string.
    {
      return this->DataBlocks[ scaleIndex - 1 ].interpretAsString();
    }

    template< class ValueClass >
    inline void
    DenseTriplyIndexedBlock< ValueClass >::setExtraValuesForNewInterpreter()
    {
      this->DataBlocks.getBack().setIndexDigits( indexDigits );
    }

  }  // end of SLHA namespace

}  // end of LHPC namespace


#endif /* DENSETRIPLYINDEXEDBLOCK_HPP_ */
