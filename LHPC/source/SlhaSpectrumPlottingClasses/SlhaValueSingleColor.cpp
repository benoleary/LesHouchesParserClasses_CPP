/*
 * SlhaValueSingleColor.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2015 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.LHPC_CPP.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#include "../../include/SlhaSpectrumPlottingClasses/SlhaValueSingleColor.hpp"

namespace LHPC
{
  namespace SLHA
  {

    SlhaValueSingleColor::SlhaValueSingleColor(
                                      std::string const& colorDefinitionXml ) :
        SlhaValueLineColoring(),
        lineColor( colorDefinitionXml )
    {
      // This constructor is just an initialization list.
    }

    SlhaValueSingleColor::~SlhaValueSingleColor()
    {
      // This does nothing.
    }

  } /* namespace SLHA */
} /* namespace LHPC */
