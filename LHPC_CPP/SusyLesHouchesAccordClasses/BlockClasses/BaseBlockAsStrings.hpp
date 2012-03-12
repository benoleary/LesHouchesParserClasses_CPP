/*
 * BaseBlockAsStrings.hpp
 *
 *  Created on: Mar 3, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#ifndef BASEBLOCKASSTRINGS_HPP_
#define BASEBLOCKASSTRINGS_HPP_

#include "../../BOLlib/Classes/BasicObserved.hpp"

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

        BaseBlockAsStrings*
        recordHeader( std::string const& headerString,
                      std::string const& commentString,
                      double const blockScale );
        // this sets the block to be just a header, so subsequent
        // recordBodyLine(...) calls write the block anew.
        void
        recordBodyLine( std::string const& dataString,
                        std::string const& commentString );
        /* this records dataString & commentString in blocksAsStringArrays &
         * then copies dataString into comparisonString, trims it of
         * whitespace, & calls interpretBodyLine() if comparisonString is not
         * then empty.
         */
        int
        getNumberOfLines() const;
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
        double
        getScale() const;


      protected:
        std::string blockAsStringWithHeader;
        BOL::VectorlikeArray< std::pair< std::string, std::string > >
        blocksAsStringArrays;
        /* the std::pair< std::string, std::string > at index 0 is the block
         * name (with optional scale & anything else that appeared before the
         * '#') paired with its comment, & the rest of the
         * std::pair< std::string, std::string >s are the data lines paired
         * with their comments as recorded.
         */
        double blockScale;
      };





      inline BaseBlockAsStrings*
      BaseBlockAsStrings::recordHeader( std::string const& headerString,
                                        std::string const& commentString,
                                        double const blockScale )
      {
        blocksAsStringArrays.setSize( 1 );
        blocksAsStringArrays.getFront().first.assign( headerString );
        blocksAsStringArrays.getFront().second.assign( commentString );
        this->blockScale = blockScale;
        return this;
      }

      inline void
      BaseBlockAsStrings::recordBodyLine( std::string const& dataString,
                                          std::string const& commentString )
      /* this records dataString & commentString in blocksAsStringArrays & then
       * copies dataString into comparisonString, trims it of whitespace, &
       * calls interpretBodyLine() if comparisonString is not then empty.
       */
      {
        blocksAsStringArrays.newEnd().first.assign( dataString );
        blocksAsStringArrays.getBack().second.assign( commentString );
      }

      inline std::pair< std::string, std::string >&
      BaseBlockAsStrings::operator[]( int const whichLine )
      /* the std::pair< std::string, std::string > at index 0 is the block
       * name (with optional scale & anything else that appeared before the
       * '#') paired with its comment, & the rest of the
       * std::pair< std::string, std::string >s are the data lines paired
       * with their comments as recorded.
       */
      {
        return blocksAsStringArrays[ whichLine ];
      }

      inline std::pair< std::string, std::string > const&
      BaseBlockAsStrings::operator[]( int const whichLine ) const
      // const version of above.
      {
        return blocksAsStringArrays[ whichLine ];
      }

      inline int
      BaseBlockAsStrings::getNumberOfLines() const
      {
        return blocksAsStringArrays.getSize();
      }

      inline double
      BaseBlockAsStrings::getScale() const
      {
        return blockScale;
      }

    }

  }

}

#endif /* BASEBLOCKASSTRINGS_HPP_ */
