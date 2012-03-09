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
      SameNameBlockSet( std::string const& blockName );
      virtual
      ~SameNameBlockSet();

      std::string const&
      getName() const;
      // this returns the name in uppercase.
      bool
      nameMatches( std::string const& nameToCompare ) const;
      // this returns true if nameToCompare matches blockNameInUppercase
      // ignoring case.
      bool
      forScale( double const soughtScale,
                int& indexForLowerScale,
                int& indexForUpperScale,
                double& fractionFromLowerScale );
      /* this looks for the pair of blocks with energy scales closest to
       * soughtScale.
       * if there are no recorded copies of this block, none of the references
       * given are changed & false is returned.
       * if there is only one copy of the block, both indexForLowerScale &
       * indexForUpperScale are set to 1, fractionFromLowerScale is set to 0.0,
       * & true is returned.
       * if there are 2 or more copies of the block, indexForLowerScale &
       * indexForUpperScale are set as described below, fractionFromLowerScale
       * is set to be
       * ( ( soughtScale - [ scale of copy with lower scale ] )
       *   / [ difference of copy scales ] ), & true is returned.
       * fractionFromLowerScale will thus be between 0.0 & 1.0 if there are
       * copies with scales above & below soughtScale, but may be negative if
       * soughtScale is lower than the lowest scale of the copies, or greater
       * than 1.0 if soughtScale is higher than the highest scale of the
       * copies.
       * since the copies of the block with different scales are not
       * necessarily recorded in order of scale, indexForLowerScale will not
       * necessarily be smaller in value than indexForUpperScale.
       * indexForLowerScale & indexForUpperScale are set as follows:
       * if soughtScale is lower than the lowest scale of the copies,
       * indexForLowerScale is set to the index of the copy with lowest scale,
       * & indexForUpperScale is set to the index of the copy with the next
       * lowest scale.
       * if soughtScale is higher than the highest scale of the copies,
       * indexForUpperScale is set to the index of the copy with highest scale,
       * & indexForLowerScale is set to the index of the copy with the next
       * highest scale.
       * otherwise, indexForLowerScale is set to the index of the copy with
       * highest scale which is still lower than soughtScale, &
       * indexForUpperScale is set to the index of the copy with lowest scale
       * which is still higher than soughtScale.
       */
      BlockClass::BaseBlockAsStrings &
      operator[]( int const whichLine );
      // the BaseBlockAsStrings are indexed in the order in which they were
      // read. the index starts at 1 rather than 0, as well.
      BlockClass::BaseBlockAsStrings const&
      operator[]( int const whichLine ) const;
      // const version of above.
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
      void
      finishRecordingLines();
      // this tells the entry in stringBlocks that was being recorded to get
      // its interpretters to interpret the newly-recorded block.


    protected:
      std::string blockNameInUppercase;
      std::list< std::pair< double, int > > scaleWithIndexList;
      BOL::VectorlikeArray< BlockClass::BaseBlockAsStrings > stringBlocks;
      int currentIndex;
      int lowestScaleIndex;
    };





    inline std::string const&
    SameNameBlockSet::getName() const
    // this returns the name in uppercase.
    {
      return blockNameInUppercase;
    }

    inline bool
    SameNameBlockSet::nameMatches( std::string const& nameToCompare ) const
    // this returns true if nameToCompare matches blockNameInUppercase
    // ignoring case.
    {
      return BOL::StringParser::stringsMatchIgnoringCase( blockNameInUppercase,
                                                          nameToCompare );
    }

  }

}

#endif /* SAMENAMEBLOCKSET_HPP_ */
