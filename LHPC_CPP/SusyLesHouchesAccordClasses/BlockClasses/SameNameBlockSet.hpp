/*
 * SameNameBlockSet.hpp
 *
 *  Created on: Mar 4, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#ifndef SAMENAMEBLOCKSET_HPP_
#define SAMENAMEBLOCKSET_HPP_

#include "../../BOLlib/Classes/VectorlikeArray.hpp"
#include "BaseBlockAsStrings.hpp"

namespace LHPC
{
  namespace SLHA
  {
    /* instances of this class hold together all copies of a block which have
     * the same name (if there are 2 or more copies, it is assumed that they
     * have different energy scale values). it also holds the relevant
     * SlhaBlock pointers for the BaseBlockAsString instances.
     */
    class SameNameBlockSet
    {
    public:
      SameNameBlockSet();
      virtual
      ~SameNameBlockSet();

      std::string const&
      getName() const;
      // this returns the name in uppercase.
      bool
      nameMatches( std::string const& nameToCompare ) const;
      // this returns true if nameToCompare matches blockNameInUppercase
      // ignoring case.
      void
      clearEntries();
      // this clears all the data that this block set has recorded.
      void
      recordHeader( std::string const& headerString,
                    std::string const& commentString );
      // this prepares a new BaseBlockAsString for the impending block being
      // read as strings.
      void
      recordBodyLine( std::string const& dataString,
                      std::string const& commentString );
      // this sends the lines to the last BaseBlockAsString prepared by
      // recordHeader( ... ).
      BaseBlockAsString &
      operator[]( int const whichLine );
      // the BaseBlockAsStrings are indexed in the order in which they were
      // read. the index starts at 1 rather than 0, as well.
      BaseBlockAsString const&
      operator[]( int const whichLine ) const;
      // const version of above.


    protected:
      std::string blockNameInUppercase;
      std::list< std::pair< double, int > > scaleWithIndexList;
      BOL::VectorlikeArray< BaseBlockAsString > stringBlocks;
      int currentIndex;
      int lowestScaleIndex;
    };

  }

}

#endif /* SAMENAMEBLOCKSET_HPP_ */
