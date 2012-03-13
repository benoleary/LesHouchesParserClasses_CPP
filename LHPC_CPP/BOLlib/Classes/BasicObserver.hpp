/*
 * BasicObserver.hpp
 *
 *  Created on: Mar 4, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 *      Copyright 2012 Ben O'Leary
 *
 *      This file is part of LesHouchesParserClasses, released under the
 *      GNU General Public License. Please see the accompanying
 *      README.LHPC_CPP.txt file for a full list of files, brief documentation
 *      on how to use these classes, and further details on the license.
 */

#ifndef BASICOBSERVER_HPP_
#define BASICOBSERVER_HPP_

namespace BOL
{
  // this is an abstract base class that allows BasicObserved objects to
  // call updateSelf() on its observers.
  class BasicObserver
  {
  public:
    BasicObserver();
    virtual
    ~BasicObserver();

    virtual void
    updateSelf() = 0;
  };

}

#endif /* BASICOBSERVER_HPP_ */
