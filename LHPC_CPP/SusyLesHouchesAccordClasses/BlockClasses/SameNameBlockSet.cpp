/*
 * SameNameBlockSet.cpp
 *
 *  Created on: Mar 4, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#include "SameNameBlockSet.hpp"

namespace LHPC
{
  namespace SLHA
  {
    SameNameBlockSet::SameNameBlockSet( std::string const& blockName ) :
      blockNameInUppercase( BOL::StringParser::trimFromFrontAndBack( blockName,
                              BOL::StringParser::whitespaceAndNewlineChars ) ),
      scaleWithIndexList(),
      stringBlocks(),
      currentIndex( -1 ),
      lowestScaleIndex( -1 )
    {
      BOL::StringParser::transformToUppercase( blockNameInUppercase );
    }

    SameNameBlockSet::~SameNameBlockSet()
    {
      // does nothing.
    }


    bool
    SameNameBlockSet::forScale( double const soughtScale,
                                int& indexForLowerScale,
                                int& indexForUpperScale,
                                double& fractionFromLowerScale )
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
    {
      if( stringBlocks.isEmpty() )
      {
        return false;
      }
      else
      {
        if( 1 == stringBlocks.getSize() )
        {
          indexForLowerScale = 1;
          indexForUpperScale = 1;
          fractionFromLowerScale = 0.0;
        }
        else
          // otherwise, there are 2 or more copies.
        {
          std::list< std::pair< double, int > >::iterator
          lowerScale( scaleWithIndexList.begin() );
          std::list< std::pair< double, int > >::iterator
          upperScale( scaleWithIndexList.end() );
          bool notYetFinished( true );
          while( notYetFinished )
          {
            doSomething();
          }
        }
        return true;
      }
    }

    BlockClass::BaseBlockAsStrings &
    SameNameBlockSet::operator[]( int const whichLine );
    // the BaseBlockAsStrings are indexed in the order in which they were
    // read. the index starts at 1 rather than 0, as well.
    BlockClass::BaseBlockAsStrings const&
    SameNameBlockSet::operator[]( int const whichLine ) const;
    // const version of above.
    void
    SameNameBlockSet::clearEntries();
    // this clears all the data that this block set has recorded.
    void
    SameNameBlockSet::recordHeader( std::string const& headerString,
                  std::string const& commentString );
    // this prepares a new BaseBlockAsString for the impending block being
    // read as strings.
    void
    SameNameBlockSet::recordBodyLine( std::string const& dataString,
                    std::string const& commentString );
    // this sends the lines to the last BaseBlockAsString prepared by
    // recordHeader( ... ).
    void
    SameNameBlockSet::finishRecordingLines();
    // this tells the entry in stringBlocks that was being recorded to get
    // its interpretters to interpret the newly-recorded block.

  }

}
