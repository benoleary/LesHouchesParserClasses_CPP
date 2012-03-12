/*
 * JustSingleValueBlock.hpp
 *
 *  Created on: Mar 12, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#ifndef JUSTSINGLEVALUEBLOCK_HPP_
#define JUSTSINGLEVALUEBLOCK_HPP_

#include "../SlhaBlock.hpp"
#include "InterpretterClasses/JustSingleValue.hpp"

namespace LHPC
{
  namespace SLHA
  {
    typedef typename
    InterpretterClass::JustSingleValue JustSingleValueBlockData;
    template< class ValueClass >
    class JustSingleValueBlock : public SlhaBlock< ValueClass,
                                       JustSingleValueBlockData< ValueClass > >
    {
    public:
      JustSingleValueBlock( std::string const& blockName,
                            ValueClass const& defaultUnsetValue,
                            bool const& isVerbose );
      virtual
      ~JustSingleValueBlock();

      ValueClass&
      operator()();
      // this returns operator() of the lowest-scale interpretter.
      ValueClass const&
      operator()() const;
      // const version of above.
    };





    template< class ValueClass >
    inline
    JustSingleValueBlock< ValueClass >::JustSingleValueBlock(
                                                  std::string const& blockName,
                                           ValueClass const& defaultUnsetValue,
                                                      bool const& isVerbose ) :
        SlhaBlock< ValueClass, JustSingleValueBlockData< ValueClass > >(
                                                                     blockName,
                                                             defaultUnsetValue,
                                                                    isVerbose )
    {
      // just an initialization list.
    }

    template< class ValueClass >
    inline
    JustSingleValueBlock< ValueClass >::~JustSingleValueBlock()
    {
      // does nothing.
    }


    template< class ValueClass >
    inline ValueClass&
    JustSingleValueBlock< ValueClass >::operator()()
    // this returns operator() of the lowest-scale interpretter.
    {
      return this->DataBlocks[ this->lowestScaleIndex() ]();
    }

    template< class ValueClass >
    inline ValueClass const&
    JustSingleValueBlock< ValueClass >::operator()() const
    // const version of above.
    {
      return this->DataBlocks[ this->lowestScaleIndex() ]();
    }

  }  // end of SLHA namespace

}  // end of LHPC namespace

#endif /* JUSTSINGLEVALUEBLOCK_HPP_ */
