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

#include <string>
#include "../BOLlib/Classes/StringParser.hpp"
#include "../BOLlib/Classes/VectorlikeArray.hpp"
#include "BlockClasses/InterpretterClasses/BlockInterpretterFactory.hpp"
#include "BlockClasses/SameNameBlockSet.hpp"
#include "BlockClasses/BaseBlockAsStrings.hpp"
#include "SlhaParser.hpp"

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
    template< class ValueClass, class BlockData >
    class SlhaBlock : public InterpretterClass::BlockInterpretterFactory
    {
    public:
      SlhaBlock( std::string const& blockName,
                 ValueClass const& defaultUnsetValue,
                 bool const& isVerbose );
      virtual
      ~SlhaBlock();

      BlockData&
      operator[]( int whichScaleIndex = 0 );
      /* the interpretters are indexed in the order in which they were
       * read (or created). the index starts at 1 rather than 0, as well. if 0
       * is given as the argument, the index corresponding to the copy with the
       * lowest scale is used.
       */
      BlockData const&
      operator[]( int whichScaleIndex = 0 ) const;
      // const version of above.
      virtual void
      registerWith( SlhaParser& registeringParser );
      // this registers this SlhaBlock with registeringParser so that the data
      // of this block update when registeringParser reads a file.
      std::string const&
      getName() const;
      // this returns the name in uppercase.
      bool
      nameMatches( std::string const& nameToCompare ) const;
      // this returns true if nameToCompare matches the block name ignoring
      // case.
      bool
      hasRecordedScale( double const soughtScale,
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
      void
      clearEntries();
      // this clears all the data that this block has interpretted or had
      // assigned.
      virtual void
      addAndUpdateInterpretter( BaseBlockAsStrings* observedStrings );


    protected:
      std::string const blockName;
      bool const& isVerbose;
      ValueClass const defaultUnsetValue;
      SameNameBlockSet* observedStringBlock;
      BOL::VectorlikeArray< BlockData > DataBlocks;

      virtual std::string
      getThisScaleAsString( int const scaleIndex );
      // derived classes over-ride this to interpret their data as a
      // std::string.
      int
      lowestScaleIndex() const;
    };





    template< class ValueClass, class BlockData >
    inline
    SlhaBlock< ValueClass, BlockData >::SlhaBlock(
                                                  std::string const& blockName,
                                           ValueClass const& defaultUnsetValue,
                                                   bool const& isVerbose ) :
        InterpretterClass::BlockInterpretterFactory(),
        blockName( blockName ),
        isVerbose( isVerbose ),
        defaultUnsetValue( defaultUnsetValue ),
        observedStringBlock( NULL )
    {
      BOL::StringParser::transformToUppercase( this->blockName );
    }

    template< class ValueClass, class BlockData >
    inline
    SlhaBlock< ValueClass, BlockData >::~SlhaBlock()
    {
      // does nothing.
    }


    template< class ValueClass, class BlockData >
    inline BlockData&
    SlhaBlock< ValueClass, BlockData >::operator[]( int whichScaleIndex )
    /* the interpretters are indexed in the order in which they were
     * read (or created). the index starts at 1 rather than 0, as well. if 0
     * is given as the argument, the index corresponding to the copy with the
     * lowest scale is used.
     */
    {
      if( 0 == whichScaleIndex )
      {
        return DataBlocks[ this->lowestScaleIndex() ];
      }
      else
      {
        return DataBlocks[ (--whichScaleIndex) ];
      }
    }

    template< class ValueClass, class BlockData >
    inline BlockData const&
    SlhaBlock< ValueClass, BlockData >::operator[]( int whichScaleIndex ) const
    // const version of above.
    {
      if( 0 == whichScaleIndex )
      {
        return DataBlocks[ this->lowestScaleIndex() ];
      }
      else
      {
        return DataBlocks[ (--whichScaleIndex) ];
      }
    }

    template< class ValueClass, class BlockData >
    inline void
    SlhaBlock< ValueClass, BlockData >::registerWith(
                                                SlhaParser& registeringParser )
    // this registers this SlhaBlock with registeringParser so that the data
    // of this block update when registeringParser reads a file.
    {
      observedStringBlock = registeringParser.registerBlock( *this );
    }

    template< class ValueClass, class BlockData >
    inline std::string const&
    SlhaBlock< ValueClass, BlockData >::getName() const
    // this returns the name in uppercase.
    {
      return blockName;
    }

    template< class ValueClass, class BlockData >
    inline bool
    SlhaBlock< ValueClass, BlockData >::nameMatches(
                                       std::string const& nameToCompare ) const
    // this returns true if nameToCompare matches the block name ignoring
    // case.
    {
      return BOL::StringParser::stringsMatchIgnoringCase( nameToCompare,
                                                          blockName );
    }

    template< class ValueClass, class BlockData >
    inline bool
    SlhaBlock< ValueClass, BlockData >:: hasRecordedScale(
                                                      double const soughtScale,
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
      return observedStringBlock->hasRecordedScale( soughtScale,
                                                    indexForLowerScale,
                                                    indexForUpperScale,
                                                    fractionFromLowerScale );
    }

    template< class ValueClass, class BlockData >
    inline std::string const&
    SlhaBlock< ValueClass, BlockData >::interpretAsString(
                                           bool onlyShowScalesGreaterThanZero )
    /* derived classes should override getThisScaleAsString to form their
     * strings directly from their data (because the block may be being used as
     * a way of writing an input file in the SLHA format, or maybe because the
     * original formatting was incorrect, as it is in most spectrum
     * generators...). by default it just joins together the strings from
     * blocksAsSingleStrings. each different-scale copy is concatenated. if
     * onlyShowScalesGreaterThanZero is true, blocks with scales of 0.0 or
     * less just do not have the "Q=" etc. printed.
     */
    {
      std::string returnString( "" );
      for( int scaleIndex( 0 );
           observedStringBlock->getNumberOfCopies() > scaleIndex;
           ++scaleIndex )
      {
        returnString.append( SlhaParser::blockIdentifierString );
        returnString.append( " " );
        returnString.append( blockName );
        if( onlyShowScalesGreaterThanZero
            ||
            ( 0.0 > blockScale ) )
        {
          returnString.append( " Q= " );
          returnString.append(
                             BlockInterpretter::slhaDoubleMaker.doubleToString(
                           (*observedStringBlock)[ scaleIndex ].getScale() ) );
        }
        returnString.append( "\n" );
        returnString.append( this->getThisScaleAsString( scaleIndex ) );
      }
      return blockAsStringWithHeader;
    }

    template< class ValueClass, class BlockData >
    inline void
    SlhaBlock< ValueClass, BlockData >::clearEntries()
    // this clears all the data that this block has interpretted or had
    // assigned.
    {
      DataBlocks.clearEntries();
    }

    template< class ValueClass, class BlockData >
    inline virtual void
    SlhaBlock< ValueClass, BlockData >::addAndUpdateInterpretter(
                                          BaseBlockAsStrings* observedStrings )
    {
      DataBlocks.newEnd().observeStrings( observedStrings );
    }

    template< class ValueClass, class BlockData >
    inline std::string
    SlhaBlock< ValueClass, BlockData >::getThisScaleAsString(
                                                         int const scaleIndex )
    // derived classes over-ride this to interpret their data as a
    // std::string.
    {
      std::string returnString( "" );
      for( int whichLine( 0 );
           (*observedStringBlock)[ scaleIndex ].getNumberOfLines() > whichLine;
           ++whichLine )
      {
        returnString.append(
                           (*observedStringBlock)[ scaleIndex ][ whichLine ] );
        returnString.append( "\n" );
      }

    }

    template< class ValueClass, class BlockData >
    inline int
    SlhaBlock< ValueClass, BlockData >::lowestScaleIndex() const
    {
      return this->observedStringBlock->getLowestScaleIndex();
    }

  }

}

#endif /* SLHABLOCK_HPP_ */
