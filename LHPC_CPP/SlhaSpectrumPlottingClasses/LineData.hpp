/*
 * LineData.hpp
 *
 *  Created on: Feb 26, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.LHPC_CPP.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#ifndef LINEPLOTTINGDATA_HPP_
#define LINEPLOTTINGDATA_HPP_

#include <string>
#include "../BOLlib/Classes/StringParser.hpp"

namespace LHPC
{
  namespace SLHA
  {
    namespace SpectrumPlotting
    {
      // this class holds the co-ordinates of the line to plot to visualize the
      // mass of a particle from an SLHA file, along with the label.
      class LineData
      {
      public:
        LineData( std::string const& dataString,
                  double const massValue );
        ~LineData();

        int
        getColumn() const;
        double
        getMass() const;
        double
        getLabelPosition() const;
        void
        setLabelPosition( double const labelPosition );
        std::string const&
        getLabelString() const;
        std::string const&
        getColor() const;


      protected:
        static std::string remainderString;

        int columnIndex;
        double massValue;
        double labelPosition;
        std::string labelString;
        std::string colorString;
      };




      inline int
      LineData::getColumn() const
      {
        return columnIndex;
      }

      inline double
      LineData::getMass() const
      {
        return massValue;
      }

      inline double
      LineData::getLabelPosition() const
      {
        return labelPosition;
      }

      inline void
      LineData::setLabelPosition( double const labelPosition )
      {
        this->labelPosition = labelPosition;
      }

      inline std::string const&
      LineData::getLabelString() const
      {
        return labelString;
      }

      inline std::string const&
      LineData::getColor() const
      {
        return colorString;
      }

    }

  }

}

#endif /* LINEPLOTTINGDATA_HPP_ */
