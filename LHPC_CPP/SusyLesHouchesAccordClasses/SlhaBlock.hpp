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
    class SlhaBlock
    {
    public:
      SlhaBlock( std::string const& blockName,
                 bool const& isVerbose,
                 std::string const blockHeaderComment = "" );
      virtual
      ~SlhaBlock();

      std::string const&
      getName() const;
      // this returns the name in uppercase.
      void
      clearEntries();
      // this clears all the data that this block has recorded.
      void
      recordScale( double const energyScale );
      void
      recordBodyLine( std::string const& dataString,
                      std::string const& commentString );
      /* this records dataString & commentString in blocksAsStringArrays & then
       * copies dataString into comparisonString, trims it of whitespace, &
       * calls interpretBodyLine() if comparisonString is not then empty.
       */
      virtual std::string const&
      interpretAsString( double const blockScale = 0.0 );
      /* derived classes should override this to form their strings directly
       * from their data (because the block may be being used as a way of
       * writing an input file in the SLHA format, or maybe because the
       * original formatting was incorrect, as it is in most spectrum
       * generators...). the block with scale closest to blockScale should be
       * returned. by default it just joins together the strings from
       * blocksAsSingleStrings.
       */
      std::string const&
      getAsStringIncludingHeader( double const blockScale = 0.0 );
      // this returns the header as a string appended with the return value of
      // getAsString( blockScale ).
      BOL::VectorlikeArray< std::string >&
      getLines( double const blockScale = 0.0 );
      /* this returns the lines without comments. if there is important
       * information encoded in the comments, the whole block in its original
       * form can be requested, & decoded by someone else's code, because
       * putting important information in comments is an entirely unacceptably
       * stupid idea, in my humble opinion.
       */
      bool
      nameMatches( std::string const& nameToCompare ) const;
      // this returns true if nameToCompare transformed to uppercase matches
      // blockNameInUppercase.


    protected:
      typedef std::pair< double,
                         int > DoublePairedWithInt;

      static std::string returnString;
      static BOL::StringParser slhaDoubleMaker;
      static BOL::StringParser slhaIntHelper;
      static BOL::StringParser particleCodeMaker;
      static std::string comparisonString;
      static DoublePairedWithInt pairMaker;
      static std::string currentWord;
      static std::string firstRemainder;
      static std::string secondRemainder;
      static std::string intString;

      static bool
      lowToHighScale( DoublePairedWithInt const& firstPair,
                      DoublePairedWithInt const& secondPair );
      // this returns true if firstPair's scale is lower than secondPair's.

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
      std::string const&
      spacePaddedSlhaInt( int const intToConvert,
                          int const returnStringLength );
      /* this returns a string for intToConvert that is at least
       * returnStringLength chars long, with no prefix for positive numbers &
       * '-' prefixing negative numbers, padded out with spaces before the
       * prefix.
       */
    };





    inline std::string const&
    SlhaBlock::getName() const
    // this returns the name in uppercase.
    {
      return blockNameInUppercase;
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

    inline std::string const&
    SlhaBlock::spacePaddedSlhaInt( int const intToConvert,
                                   int const returnStringLength )
    /* this returns a string for intToConvert that is at least
     * returnStringLength chars long, with no prefix for positive numbers &
     * '-' prefixing negative numbers, padded out with spaces before the
     * prefix.
     */
    {
      intString.assign( slhaIntHelper.intToString( intToConvert ) );
      if( (size_t)returnStringLength > intString.size() )
      {
        intString.insert( 0,
                          ( returnStringLength - intString.size() ),
                          ' ' );
      }
      return intString;
    }

  }

}

#endif /* SLHABLOCK_HPP_ */
