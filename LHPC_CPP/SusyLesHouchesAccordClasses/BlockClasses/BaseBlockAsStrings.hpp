/*
 * BaseBlockAsStrings.hpp
 *
 *  Created on: Mar 3, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#ifndef BASEBLOCKASSTRINGS_HPP_
#define BASEBLOCKASSTRINGS_HPP_

#include "../../BOLlib/Classes/BasicObserved.hpp"
#include "SingleScaleBlockInterpretter.hpp"

namespace LHPC
{
  namespace SLHA
  {
    namespace BlockClass
    {
      /* this class holds a SLHA block as a set of pairs of strings (data with
       * comment). it also holds the relevant pointers for those
       * SingleScaleBlockInterpretters which are interpretting it.
       */
      class BaseBlockAsStrings : public BOL::BasicObserved
      {
      public:
        BaseBlockAsStrings();
        ~BaseBlockAsStrings();

        void
        clearEntries();
        // this clears all the data that this block has recorded.
        BaseBlockAsStrings*
        recordHeader( std::string const& headerString,
                      std::string const& commentString );
        void
        recordBodyLine( std::string const& dataString,
                        std::string const& commentString );
        /* this records dataString & commentString in blocksAsStringArrays & then
         * copies dataString into comparisonString, trims it of whitespace, &
         * calls interpretBodyLine() if comparisonString is not then empty.
         */
        std::pair< std::string, std::string >&
        operator[]( int const whichLine );
        /* the std::pair< std::string, std::string > at index 0 is the block
         * name (with optional scale & anything else that appeared before the
         * '#') paired with its comment, & the rest of the
         * std::pair< std::string, std::string >s are the data lines paired
         * with their comments as recorded.
         */
        std::pair< std::string, std::string > const&
        operator[]( int const whichLine ) const;
        // const version of above.


      protected:
        std::string blockNameInOriginalCase;
        std::string blockAsStringWithHeader;
        BOL::VectorlikeArray< std::pair< std::string, std::string > >
        blocksAsStringArrays;
        /* the std::pair< std::string, std::string > at index 0 is the block
         * name (with optional scale & anything else that appeared before the
         * '#') paired with its comment, & the rest of the
         * std::pair< std::string, std::string >s are the data lines paired
         * with their comments as recorded.
         */
      };

    }

  }

}

#endif /* BASEBLOCKASSTRINGS_HPP_ */
