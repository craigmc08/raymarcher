#ifndef _RAY_H
#define _RAY_H

#include "Vector.hpp"
#include <stdio.h>

struct Ray {
    Vector origin;
    Vector direction;
};

struct RayHit {
    Ray ray;
    Vector hitPos;
    Vector normal;
    float distance;
    float traveled;
    float closest;
    int steps;
    int material;
};

typedef float(DistanceEstimator)(Vector, int&);

RayHit RayMarch(Ray ray, DistanceEstimator* estimator, float maxDistance=100, float maxHits=99);

#endif