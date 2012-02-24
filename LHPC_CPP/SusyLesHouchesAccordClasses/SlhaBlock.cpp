/*
 * SlhaBlock.cpp
 *
 *  Created on: Feb 1, 2012
 *      Author: oleary
 */

#include "SlhaBlock.hpp"

namespace LHPC
{
  namespace SLHA
  {
    std::string SlhaBlock::returnString( "" );
    BOL::StringParser SlhaBlock::slhaDoubleMaker( 9,
                                                  ' ',
                                                  9,
                                                  3 );
    BOL::StringParser SlhaBlock::particleCodeMaker( 9,
                                                    ' ',
                                                    1,
                                                    1,
                                                    "" );
    std::string SlhaBlock::comparisonString( "" );
    SlhaBlock::DoublePairedWithInt SlhaBlock::pairMaker( 0.0,
                                                         0 );
    std::string SlhaBlock::currentWord( "" );
    std::string SlhaBlock::firstRemainder( "" );
    std::string SlhaBlock::secondRemainder( "" );

    SlhaBlock::SlhaBlock( std::string const& blockName,
                          bool const& isVerbose,
                          std::string const blockHeaderComment ) :
        isVerbose( isVerbose ),
        scaleWithIndexList(),
        blocksAsSingleStrings( 1 ),
        blocksAsStringArrays( 1 ),
        lowestScaleIndex( 0 ),
        currentIndex( 0 ),
        blockNameInOriginalCase( blockName ),
        blockNameInUppercase( blockName ),
        blockHeaderComment( blockHeaderComment ),
        blockAsStringWithHeader( "" )
    {
      BOL::StringParser::transformToUppercase( blockNameInUppercase );
    }

    SlhaBlock::~SlhaBlock()
    {
      // does nothing.
    }


    int
    SlhaBlock::findScaleIndex( double const blockScale ) const
    // this returns the appropriate index for looking up values based on
    // blockScale.
    {
      //aha! the 1st recording of a block with a scale has
      //0 == scaleWithIndexList.size(), which is causing the problem here.
      if( 1 == scaleWithIndexList.size() )
        // the simple case is simple!
      {
        return 0;
      }
      else if( 1 < scaleWithIndexList.size() )
        // if the nearest scale has to be found...
      {
        int returnIndex;
        double nearestScale;

        // start at the lowest scale & go along until either the end of the
        // list is reached or the current scale is larger than blockScale:
        std::list< DoublePairedWithInt >::const_iterator
        scaleIterator( scaleWithIndexList.begin() );
        while( ( scaleIterator != scaleWithIndexList.end() )
               &&
               ( blockScale > scaleIterator->first ) )
        {
          ++scaleIterator;
        }
        if( scaleIterator == scaleWithIndexList.end() )
          // if the end of the list was reached without finding a larger
          // scale...
        {
          nearestScale = scaleWithIndexList.back().first;
          returnIndex = scaleWithIndexList.back().second;
          // the last element should be taken.
        }
        else
        {
          /* otherwise the lowest scale larger than blockScale is assumed to be
           * the nearest, then the largest scale lower than blockScale is
           * checked:
           */
          nearestScale = scaleIterator->first;
          returnIndex = scaleIterator->second;
          --scaleIterator;
          if( ( nearestScale - blockScale )
              > ( blockScale - scaleIterator->first ) )
            // nearestScale is larger than blockScale, & blockScale is larger
            // than scaleIterator->first, so the differences are positive.
          {
            nearestScale = scaleIterator->first;
            returnIndex = scaleIterator->second;
          }
        }
        return returnIndex;
      }
      else
      {
        throw
        std::out_of_range( "BaseSlhaBlock::findScaleIndex out-of-range" );
      }
    }

    double
    SlhaBlock::findNearestScale( double const blockScale ) const
    // this finds the recorded scale nearest blockScale.
    {
      if( 1 == scaleWithIndexList.size() )
        // the simple case is simple!
      {
        return scaleWithIndexList.front().first;
      }
      else if( 1 < scaleWithIndexList.size() )
        // if the nearest scale has to be found...
      {
        // start at the lowest scale & go along until either the end of the
        // list is reached or the current scale is larger than blockScale:
        std::list< DoublePairedWithInt >::const_iterator
        scaleIterator( scaleWithIndexList.begin() );
        while( ( scaleIterator != scaleWithIndexList.end() )
               &&
               ( blockScale > scaleIterator->first ) )
        {
          ++scaleIterator;
        }
        if( scaleIterator == scaleWithIndexList.end() )
          // if the end of the list was reached without finding a larger
          // scale...
        {
          return scaleWithIndexList.back().first;
          // the last element should be taken.
        }
        else
        {
          /* otherwise the lowest scale larger than blockScale is assumed to be
           * the nearest, then the largest scale lower than blockScale is
           * checked:
           */
          double nearestScale( scaleIterator->first );
          --scaleIterator;
          if( ( nearestScale - blockScale )
              > ( blockScale - scaleIterator->first ) )
            // nearestScale is larger than blockScale, & blockScale is larger
            // than scaleIterator->first, so the differences are positive.
          {
            return scaleIterator->first;
          }
          else
          {
            return nearestScale;
          }
        }
      }
      else
      {
        throw
        std::out_of_range( "BaseSlhaBlock::findScaleIndex out-of-range" );
      }
    }


  }

}
