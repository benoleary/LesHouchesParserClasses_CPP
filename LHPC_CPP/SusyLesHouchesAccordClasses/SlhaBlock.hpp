/*
 * SlhaBlock.hpp
 *
 *  Created on: Feb 1, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.LHPC_CPP.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#ifndef SLHABLOCK_HPP_
#define SLHABLOCK_HPP_

#include <cstdlib>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include "../BOLlib/Classes/StringParser.hpp"
#include "../BOLlib/Classes/VectorlikeArray.hpp"
#include "BlockInterpretter.hpp"

namespace LHPC
{
  namespace SLHA
  {
    /* issues for specific blocks:
     * MODSEL: annoying mix of ints & doubles (everything but Q_max is an int).
     *       - set it as a string block & interpret with the general filters?
     *       - set it as a double block, but write a separate routine to
     *         write it in a way SPheno can understand?
     *       - set it as a double block, but get Werner to fix SPheno so it's
     *         not so silly?
     * SPINFO: multiple lines with the same index.
     *       - leave it as a SlhaBlock, because it really has no useful
     *         information
     * SPHENOINPUT: multiple lines with the same index.
     *            - leave it as a SlhaBlock, because it really has no
     *              useful information
     * SPHENOCROSSSECTIONS: just stupid.
     *                    - leave it as a SlhaBlock, to be interpretted by
     *                      the general filters.
     */

    /* this is a class to hold a block from a file in the SLHA format, only
     * interpretting it at the basic level: as set of strings. if multiple
     * blocks with the same name but different scales are recorded, the copy
     * with the lowest scale is defaulted to if no scale is given when seeking
     * information.
     * classes which interpret the strings further derive from this class.
     */
    template< class InterpretterClass >
    class SlhaBlock
    {
    public:
      SlhaBlock( std::string const& blockName,
                 bool const& isVerbose );
      virtual
      ~SlhaBlock();

      std::string const&
      getName() const;
      // this returns the name in uppercase.
      bool
      nameMatches( std::string const& nameToCompare ) const;
      // this returns true if nameToCompare matches the block name ignoring
      // case.
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
      InterpretterClass&
      operator[]( int whichScaleIndex = 0 );
      /* the interpretters are indexed in the order in which they were
       * read (or created). the index starts at 1 rather than 0, as well. if 0
       * is given as the argument, the index corresponding to the copy with the
       * lowest scale is used.
       */
      InterpretterClass const&
      operator[]( int whichScaleIndex = 0 ) const;
      // const version of above.
      void
      clearEntries();
      // this clears all the data that this block has interpretted or had
      // assigned.
      virtual std::string const&
      interpretAsString( bool onlyShowScalesGreaterThanZero = true );
      /* derived classes should override this to form their strings directly
       * from their data (because the block may be being used as a way of
       * writing an input file in the SLHA format, or maybe because the
       * original formatting was incorrect, as it is in most spectrum
       * generators...). by default it just joins together the strings from
       * blocksAsSingleStrings. each different-scale copy is concatenated. if
       * onlyShowScalesGreaterThanZero is true, blocks with scales of 0.0 or
       * less just do not have the "Q=" etc. printed.
       */


    protected:
      typedef std::pair< double,
                         int > DoublePairedWithInt;

      std::string const blockName;
      bool const& isVerbose;
      std::list< DoublePairedWithInt > scaleWithIndexList;
      BOL::VectorlikeArray< std::string > blocksAsSingleStrings;
      BOL::VectorlikeArray< BOL::VectorlikeArray< std::string > >
      blocksAsStringArrays;
      int lowestScaleIndex;
      int currentIndex;
      std::string blockNameInOriginalCase;
      std::string blockNameInUppercase;
      std::string blockHeaderComment;
      std::string blockAsStringWithHeader;

      virtual void
      clearExtraStuff();
      // derived classes should clear their extra data here.
      virtual void
      prepareExtraStuffForNewScale();
      // derived classes should prepare their extra data structure for
      // recording a new scale here.
      virtual void
      interpretBodyLine();
      // derived classes should interpret comparisonString at this point, since
      // it is a non-empty data line.
      int
      findScaleIndex( double const blockScale ) const;
      // this returns the appropriate index for looking up values based on
      // blockScale.
      double
      findNearestScale( double const blockScale ) const;
      // this finds the recorded scale nearest blockScale.
    };





    inline std::string const&
    SlhaBlock::getName() const
    // this returns the name in uppercase.
    {
      return blockNameInUppercase;
    }

    inline BlockClass::BlockInterpretter &
    SlhaBlock::operator[]( int whichScaleIndex )
    // the BlockInterpretters are indexed in the order in which they were
    // read (or created). the index starts at 1 rather than 0, as well.
    {
      return ;
    }

    inline BlockClass::BlockInterpretter const&
    SlhaBlock::operator[]( int whichScaleIndex ) const
    // const version of above.
    {

    }

    inline void
    SlhaBlock::clearEntries()
    // this clears all the data that this block has recorded.
    {
      scaleWithIndexList.clear();
      blocksAsSingleStrings.clearEntries();
      blocksAsStringArrays.clearEntries();
      lowestScaleIndex = 0;
      currentIndex = 0;
      clearExtraStuff();
    }

    inline void
    SlhaBlock::recordScale( double const energyScale )
    {
      blocksAsSingleStrings.newEnd().clear();
      blocksAsStringArrays.newEnd().clearEntries();
      currentIndex = blocksAsSingleStrings.getLastIndex();
      pairMaker.first = energyScale;
      pairMaker.second = currentIndex;
      scaleWithIndexList.push_back( pairMaker );
      scaleWithIndexList.sort( &lowToHighScale );
      lowestScaleIndex = scaleWithIndexList.front().second;
      prepareExtraStuffForNewScale();
    }

    inline void
    SlhaBlock::recordBodyLine( std::string const& dataString,
                               std::string const& commentString )
    /* this records dataString & commentString in blocksAsStringArrays & then
     * copies dataString into comparisonString, trimmed of whitespace, &
     * calls interpretBodyLine() if comparisonString is not then empty.
     */
    {
      comparisonString.assign( BOL::StringParser::trimFromFrontAndBack(
                                                                    dataString,
                                        BOL::StringParser::whitespaceChars ) );
      if( !(comparisonString.empty()) )
      {
        blocksAsStringArrays[ currentIndex ].newEnd().assign(
                                                            comparisonString );
      }
      blocksAsSingleStrings[ currentIndex ].append( dataString );
      blocksAsSingleStrings[ currentIndex ].append( commentString );
      blocksAsSingleStrings[ currentIndex ].append( "\n" );
      // finally dataString is interpretted:
      this->interpretBodyLine();
    }

    inline std::string const&
    SlhaBlock::interpretAsString( double const blockScale )
    /* derived classes should override this to form their strings directly
     * from their data (because the block may be being used as a way of
     * writing an input file in the SLHA format, or maybe because the
     * original formatting was incorrect, as it is in most spectrum
     * generators...). the block with scale closest to blockScale should be
     * returned. by default it just joins together the strings from
     * blocksAsSingleStrings.
     */
    {
      currentIndex = findScaleIndex( blockScale );
      return blocksAsSingleStrings[ currentIndex ];
    }

    inline std::string const&
    SlhaBlock::getAsStringIncludingHeader( double const blockScale )
    // this returns the header as a string appended with the return value of
    // getAsString( blockScale ).
    {
      blockAsStringWithHeader.assign( "Block " );
      blockAsStringWithHeader.append( blockNameInOriginalCase );
      if( 0.0 < blockScale )
      {
        blockAsStringWithHeader.append( " Q= " );
        blockAsStringWithHeader.append( slhaDoubleMaker.doubleToString(
                                            findNearestScale( blockScale ) ) );
      }
      blockAsStringWithHeader.append( "   # " );
      blockAsStringWithHeader.append( blockHeaderComment );
      blockAsStringWithHeader.append( "\n" );
      blockAsStringWithHeader.append( interpretAsString( blockScale ) );
      return blockAsStringWithHeader;
    }

    inline BOL::VectorlikeArray< std::string >&
    SlhaBlock::getLines( double const blockScale )
    /* this returns the lines without comments. if there is important
     * information encoded in the comments, the whole block in its original
     * form can be requested, & decoded by someone else's code, because
     * putting important information in comments is an entirely unacceptably
     * stupid idea, in my humble opinion.
     */
    {
      return blocksAsStringArrays[ findScaleIndex( blockScale ) ];
    }

    inline bool
    SlhaBlock::nameMatches( std::string const& nameToCompare ) const
    // this returns true if nameToCompare transformed to uppercase matches
    // blockNameInUppercase.
    {
      comparisonString.assign( nameToCompare );
      BOL::StringParser::transformToUppercase( comparisonString );
      if( 0 == comparisonString.compare( blockNameInUppercase ) )
      {
        return true;
      }
      else
      {
        return false;
      }
    }

    inline bool
    SlhaBlock::lowToHighScale( DoublePairedWithInt const& firstPair,
                               DoublePairedWithInt const& secondPair )
    // this returns true if firstPair's scale is lower than secondPair's.
    {
      if( firstPair.first <= secondPair.first )
      {
        return true;
      }
      else
      {
        return false;
      }
    }

    inline void
    SlhaBlock::clearExtraStuff()
    // derived classes should clear their extra data here.
    {
      // the default version doesn't clear any extra stuff.
    }

    inline void
    SlhaBlock::prepareExtraStuffForNewScale()
    // derived classes should prepare their extra data structure for recording
    // a new scale here.
    {
      // the default version doesn't prepare any extra stuff.
    }

    inline void
    SlhaBlock::interpretBodyLine()
    // derived classes should interpret comparisonString at this point, since
    // it is a non-empty data line.
    {
      // the default version doesn't interpret anything.
    }



  }

}

#endif /* SLHABLOCK_HPP_ */
