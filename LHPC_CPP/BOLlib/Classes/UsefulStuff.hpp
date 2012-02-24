/*
 * UsefulStuff.hpp
 *
 *  Created on: Jan 6, 2012
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#ifndef USEFULSTUFF_HPP_
#define USEFULSTUFF_HPP_

#include <cstdlib>
#include <ctime>
#include <string>
#include <cmath>

namespace BOL
{
  class UsefulStuff
  {
  public:
    static double const notANumber;
    static std::string const nanString;

    static bool
    doublesCloseEnough( double const firstDouble,
                        double const secondDouble,
                        double maximumDifference );
    // this returns true if the difference between firstDouble & secondDouble
    // is less than maximumDifference.
    static double
    flatRandomDouble( double const lowerLimit,
                      double const upperLimit );
    /* this returns a double from a flat probability distribution from the
     * *inclusive* lower limit of lowerLimit to the *exclusive* upper limit
     * of upperLimit.
     */
    static int
    zeroOrOne();
    // this returns 0 or 1 with a 50:50 chance for each.
    static int
    plusOrMinusOne();
    // this returns -1 or +1 with a 50:50 chance for each.

  private:
    static bool randomSeedNotYetSet;

    static void
    ensureRandomSeedIsSet();
  };



  inline bool
  UsefulStuff::doublesCloseEnough( double const firstDouble,
                                   double const secondDouble,
                                   double maximumDifference )
  // this returns true if the difference between firstDouble & secondDouble
  // is less than maximumDifference.
  {
    if( 0.0 > maximumDifference )
    {
      maximumDifference = -maximumDifference;
    }
    double differenceOfDoubles( firstDouble - secondDouble );
    if( 0.0 > differenceOfDoubles )
    {
      differenceOfDoubles = -differenceOfDoubles;
    }
    if( maximumDifference > differenceOfDoubles )
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  inline double
  UsefulStuff::flatRandomDouble( double const lowerLimit,
                                 double const upperLimit )
  /* this returns a double from a flat probability distribution from the
   * *inclusive* lower limit of lower_limit to the *exclusive* upper limit
   * of upper_limit.
   */
  {
    ensureRandomSeedIsSet();
    return ( lowerLimit + ( (double)(rand()) / (double)RAND_MAX )
                          * ( upperLimit - lowerLimit ) );
  }

  inline int
  UsefulStuff::zeroOrOne()
  // this returns 0 or 1 with a 50:50 chance for each.
  {
    ensureRandomSeedIsSet();
    return ( (rand()) % 2 );
  }

  inline int
  UsefulStuff::plusOrMinusOne()
  // this returns -1 or +1 with a 50:50 chance for each.
  {
    if( 0 == zeroOrOne() )
    {
      return -1;
    }
    else
    {
      return 1;
    }
  }

  inline void
  UsefulStuff::ensureRandomSeedIsSet()
  // this sets the random seed if it had not already been set.
  {
    if( randomSeedNotYetSet )
    {
      // debugging:
      /**time_t currentTime = time( NULL );
      srand( currentTime );
      std::cout << std::endl << "currentTime = " << currentTime;**/
      srand( time( NULL ) );
      randomSeedNotYetSet = false;
    }
  }

}

#endif /* USEFULSTUFF_HPP_ */
