/*
 * LinesAsStringsBlock.hpp
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

#ifndef LINESASSTRINGSBLOCK_HPP_
#define LINESASSTRINGSBLOCK_HPP_

#include <string>
#include "../SlhaBlock.hpp"
#include "InterpreterClasses/LinesAsStrings.hpp"

namespace LHPC
{
  namespace SLHA
  {
    /* this class interprets all the blocks with the same name, though
     * differing scale values, which are interpreted just as a set of lines as
     * std::strings.
     */
    class LinesAsStringsBlock : public SlhaBlock< std::string,
                                            InterpreterClass::LinesAsStrings >
    {
    public:
      LinesAsStringsBlock( std::string const& blockName,
                           bool const& isVerbose );
      virtual
      ~LinesAsStringsBlock();

      std::string
      operator()( int const whichLine ) const;
      // this returns operator() of the lowest-scale interpreter.


    protected:
      virtual std::string
      getThisScaleAsString( int const scaleIndex );
      // derived classes over-ride this to interpret their data as a
      // std::string.
    };





    inline std::string
    LinesAsStringsBlock::operator()( int const whichLine ) const
    // const version of above.
    {
      if( this->DataBlocks.isEmpty() )
      {
        return this->defaultUnsetValue;
      }
      else
      {
        return this->DataBlocks[ this->defaultDataBlockIndex() ]( whichLine );
      }
    }

    inline std::string
    LinesAsStringsBlock::getThisScaleAsString( int const scaleIndex )
    // derived classes over-ride this to interpret their data as a
    // std::string.
    {
      return this->DataBlocks[ scaleIndex - 1 ].interpretAsString();
    }

  }  // end of SLHA namespace

}  // end of LHPC namespace


#endif /* LINESASSTRINGSBLOCK_HPP_ */
