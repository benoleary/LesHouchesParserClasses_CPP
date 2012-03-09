/*
 * BasicObserved.hpp
 *
 *  Created on: Mar 4, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#ifndef BASICOBSERVED_HPP_
#define BASICOBSERVED_HPP_

#include <list>
#include "BasicObserver.hpp"

namespace BOL
{
  // this class holds a list of BasicObserver pointers & calls
  // updateSelf() on them all with updateObservers().
  class BasicObserved
  {
  public:
    BasicObserved();
    virtual
    ~BasicObserved();

    virtual void
    updateObservers();
    virtual void
    registerObserver( BasicObserver* const joiningObserver );
    virtual void
    removeObserver( BasicObserver* const leavingObserver );


  protected:
    std::list< BasicObserver* > observerList;
  };





  inline void
  BasicObserved::updateObservers()
  {
    for( std::list< BasicObserver* >::iterator
         observerIterator( observerList.begin() );
         observerList.end() != observerIterator;
         ++observerIterator )
    {
      (*observerIterator)->updateSelf();
    }
  }

  inline void
  BasicObserved::registerObserver( BasicObserver* const joiningObserver )
  {
    observerList.push_back( joiningObserver );
  }

  inline void
  BasicObserved::removeObserver( BasicObserver* const leavingObserver )
  {
    observerList.remove( leavingObserver );
  }

}

#endif /* BASICOBSERVED_HPP_ */
