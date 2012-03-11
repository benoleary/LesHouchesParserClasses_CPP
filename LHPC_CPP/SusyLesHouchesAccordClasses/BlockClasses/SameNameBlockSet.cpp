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
      stringBlocks(),
      scaleOrderedIndices(),
      scaleIndexIterator(),
      lowestScaleIndex( -1 ),
      currentStringBlock( NULL )
    {
      BOL::StringParser::transformToUppercase( blockNameInUppercase );
    }

    SameNameBlockSet::~SameNameBlockSet()
    {
      // does nothing.
    }


    bool
    SameNameBlockSet::hasRecordedScale( double const soughtScale,
                                        int& indexForLowerScale,
                                        int& indexForUpperScale,
                                        double& fractionFromLowerScale )
    /* this looks for the pair of blocks with energy scales closest to
     * soughtScale.
     * if there are no recorded copies of this block, none of the references
     * given are changed & false is returned.
     * if there is only one copy of the block, both indexForLowerScale &
     * indexForUpperScale are set to 1, fractionFromLowerScale is set to NaN,
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
          fractionFromLowerScale = BOL::UsefulStuff::notANumber;
        }
        else
          // otherwise, there are 2 or more copies.
        {
          std::list< std::pair< int, double > >::iterator
          scaleIterator( scaleOrderedIndices.begin() );
          indexForLowerScale = scaleIterator->first;
          // indexForLowerScale starts at the lowest scale.
          double lowerScale( scaleIterator->second );
          indexForUpperScale = (++scaleIterator)->first;
          // indexForUpperScale starts at the next lowest scale.
          double upperScale( scaleIterator->second );
          while( ( scaleWithIndexList.end() != scaleIterator )
                 &&
                 ( soughtScale >= scaleIterator->second ) )
            // until scaleIterator goes past soughtScale or hits the end of the
            // list...
          {
            indexForLowerScale = indexForUpperScale;
            indexForUpperScale = (++scaleIterator)->first;
            // both indices are moved up one copy.
            lowerScale = upperScale;
            upperScale = scaleIterator->second;
          }
          /* now if soughtScale was lower than the lowest scale, both indices
           * are still at the lowest pair of scales; if soughtScale was higher
           * than the highest scale, scaleIterator got to the end of the list &
           * the indices now are at the highest pair of scales; otherwise
           * indexForLowerScale is at the highest scale lower than soughtScale
           * & indexForUpperScale is at the lowest scale higher than
           * soughtScale.
           */
          if( 0.0 == ( upperScale - lowerScale ) )
          {
            fractionFromLowerScale = BOL::UsefulStuff::notANumber;
          }
          else
          {
            fractionFromLowerScale
            = ( ( soughtScale - lowerScale ) / ( upperScale - lowerScale ) );
          }
        }
        return true;
      }
    }

    void
    SameNameBlockSet::recordHeader( std::string const& headerString,
                                    std::string const& commentString,
                                    double const blockScale )
    // this prepares a new BaseBlockAsString for the impending block being
    // read as strings.
    {
      currentStringBlock = stringBlocks.newEnd().recordHeader( headerString,
                                                               commentString,
                                                               blockScale );
      if( 1 == stringBlocks.getSize() )
        // if this is the only copy so far...
      {
        lowestScaleIndex = 0;
      }
      else if( blockScale < stringBlocks[ lowestScaleIndex ].getScale() )
        /* otherwise, lowestScaleIndex is a valid index for stringBlocks, so
         * the comparison is valid, & if true, lowestScaleIndex is set
         * correctly.
         */
      {
        lowestScaleIndex = stringBlocks.getLastIndex();
      }
      for( int whichSource( interpretterSources.size() - 1 );
           0 <= whichSource;
           --whichSource )
      {
        interpretterSources[ whichSource ]->addInterpretter(
                                                          currentStringBlock );
      }
      scaleIndexIterator = scaleOrderedIndices.begin();
      while( ( scaleIndexIterator != scaleOrderedIndices.end() )
             &&
             ( scaleIndexIterator->second < blockScale ) )
      {
        ++scaleIndexIterator;
      }
      if( scaleIndexIterator == scaleOrderedIndices.end() )
      {
        // debugging:
        /**/std::cout << std::endl << "debugging:"
        << std::endl
        << "SameNameBlockSet::recordHeader( \"" << headerString << "\", \""
        << commentString << "\", " << blockScale
        << " ): scaleIndexIterator == scaleOrderedIndices.end(), so does"
        << " insert work with scaleOrderedIndices.end()?";
        std::cout << std::endl;/**/
      }

      // now scaleIndexIterator should either be at the index with scale just
      // above blockScale, or at the end of the list.
      scaleOrderedIndices.insert( scaleIndexIterator,
                                  std::pair< int, double >(
                                                   stringBlocks.getLastIndex(),
                                                            blockScale ) );
      if( scaleIndexIterator == scaleOrderedIndices.end() )
      {
        // debugging:
        /**/std::cout << std::endl << "debugging:"
        << std::endl
        << "apparently it does.";
        std::cout << std::endl;/**/
      }
    }

  }

}
