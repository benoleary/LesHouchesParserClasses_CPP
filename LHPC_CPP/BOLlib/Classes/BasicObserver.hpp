/*
 * BasicObserver.hpp
 *
 *  Created on: Mar 4, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
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
