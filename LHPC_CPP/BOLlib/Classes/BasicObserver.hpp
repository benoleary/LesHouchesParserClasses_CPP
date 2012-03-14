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

#include <list>

namespace BOL
{
  // this is an abstract base class that allows BasicObserved objects to
  // call respondToObservedSignal() on its observers.
  class BasicObserver
  {
  public:
    BasicObserver();
    virtual
    ~BasicObserver();

    virtual void
    respondToObservedSignal() = 0;
    void
    acceptFlagFromObserved( bool* const flagFromObserved );
    void
    discardFlagFromObserved( bool* const flagFromObserved );
    void
    clearObservingFlags();

  protected:
    std::list< bool* > stillObservingFlags;
  };





  inline void
  BasicObserver::acceptFlagFromObserved( bool* const flagFromObserved )
  {
    stillObservingFlags.push_back( flagFromObserved );
  }

  inline void
  BasicObserver::discardFlagFromObserved( bool* const flagFromObserved )
  {
    stillObservingFlags.remove( flagFromObserved );
  }

  inline void
  BasicObserver::clearObservingFlags()
  {
    for( std::list< bool* >::iterator
         flagIterator( stillObservingFlags.begin() );
         stillObservingFlags.end() != flagIterator;
         ++flagIterator )
    {
      *(*flagIterator) = false;
    }
    stillObservingFlags.clear();
  }

}

#endif /* BASICOBSERVER_HPP_ */
