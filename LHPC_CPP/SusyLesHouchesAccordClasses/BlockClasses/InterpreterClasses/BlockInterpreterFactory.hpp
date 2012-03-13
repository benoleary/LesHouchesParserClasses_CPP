/*
 * BlockInterpreterFactory.hpp
 *
 *  Created on: Mar 11, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.LHPC_CPP.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#ifndef BLOCKINTERPRETERFACTORY_HPP_
#define BLOCKINTERPRETERFACTORY_HPP_

#include <string>
#include <map>
#include "../../../BOLlib/Classes/StringParser.hpp"
#include "../BaseBlockAsStrings.hpp"
#include "../../../MassEigenstateCollectionClasses/ExtendedMass.hpp"

namespace LHPC
{
  namespace SLHA
  {
    namespace InterpreterClass
    {
      // this abstract base class allows SameNameBlockSet to register its
      // BaseBlockAsStrings instances with derived classes.
      class BlockInterpreterFactory
      {
      public:
        BlockInterpreterFactory( std::string const& blockName );
        virtual
        ~BlockInterpreterFactory();

        std::string const&
        getName() const;
        // this returns the name in uppercase.
        bool
        nameMatches( std::string const& nameToCompare ) const;
        // this returns true if nameToCompare matches the block name ignoring
        // case.
        virtual void
        clearEntries() = 0;
        virtual void
        addInterpreter( BlockClass::BaseBlockAsStrings* observedStrings ) = 0;
        virtual std::map< int, ExtendedMass > const*
        getFmassMap() const;
        // this returns NULL. only a specific derived class should over-ride it
        // to return a non-NULL pointer.
        virtual std::map< int, double > const*
        getMassMap() const;
        // this returns NULL. only a specific derived class should over-ride it
        // to return a non-NULL pointer.


      protected:
        std::string blockName;
      };




      inline std::string const&
      BlockInterpreterFactory::getName() const
      // this returns the name in uppercase.
      {
        return blockName;
      }

      inline bool
      BlockInterpreterFactory::nameMatches(
                                       std::string const& nameToCompare ) const
      // this returns true if nameToCompare matches the block name ignoring
      // case.
      {
        return BOL::StringParser::stringsMatchIgnoringCase( nameToCompare,
                                                            blockName );
      }

      inline std::map< int, ExtendedMass > const*
      BlockInterpreterFactory::getFmassMap() const
      {
        return NULL;
      }

      inline std::map< int, double > const*
      BlockInterpreterFactory::getMassMap() const
      {
        return NULL;
      }

    }

  }

}

#endif /* BLOCKINTERPRETERFACTORY_HPP_ */
