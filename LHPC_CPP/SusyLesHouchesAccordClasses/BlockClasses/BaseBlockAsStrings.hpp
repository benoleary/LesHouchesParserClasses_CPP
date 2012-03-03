/*
 * BaseBlockAsStrings.hpp
 *
 *  Created on: Mar 3, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#ifndef BASEBLOCKASSTRINGS_HPP_
#define BASEBLOCKASSTRINGS_HPP_

namespace LHPC
{
  namespace SLHA
  {
    namespace BlockClass
    {
      // this class holds a SLHA block as a set of pairs of strings (data with
      // comment).
      class BaseBlockAsStrings
      {
      public:
        BaseBlockAsStrings();
        ~BaseBlockAsStrings();


      protected:
        typedef std::pair< double,
                           int > DoublePairedWithInt;
        typedef std::pair< std::string,
                           std::string > StringPairedWithString;
        typedef BOL::VectorlikeArray< StringPairedWithString > StringPairArray;

        //std::string blockNameInOriginalCase;
        std::string blockNameInUppercase;
        std::string blockHeaderComment;
        std::string blockAsStringWithHeader;
        BOL::VectorlikeArray< StringPairArray > blocksAsStringArrays;
        int lowestScaleIndex;
      };

    }

  }

}

#endif /* BASEBLOCKASSTRINGS_HPP_ */
