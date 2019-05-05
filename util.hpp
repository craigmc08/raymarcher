#ifndef _UTIL_H
#define _UTIL_H

#include <stdlib.h>
#include <random>

#define PI 3.141592653
#define TWO_PI 6.283185307
#define HALF_PI 1.57079632679
#define ROOT2 1.41421356237

float min(float l, float r);
float max(float l, float r);
float random();

extern std::default_random_engine randomGenerator;

#endif