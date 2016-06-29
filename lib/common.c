//
// Created by Gwartney, David on 6/10/16.
//
#include <math.h>
#include <stdlib.h>
#include "common.h"

/** \brief Generates a random number in the specified range
 *
 *  @param min Minimum value of random number
 *  @param max Maximum value of random number
 *  @return random value between min and max parameters
 *
 */
double rand_range(int min, int max) {
    double rnum =rand()/(double)RAND_MAX;
    return floor(rnum * ((max - min) + 1)) + min;
}
