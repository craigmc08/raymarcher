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

RayHit RayMarch(Ray ray, DistanceEstimator* estimator, float maxDistance=100, float maxHits=99) {
    float d = 0;
    float closest = 1e9;
    float totalD = 0;
    int steps = 0;
    int hitType;

    for (; totalD < maxDistance; totalD += d) {
        Vector hitPos = ray.origin + ray.direction * totalD;
        d = estimator(hitPos, hitType);
        if (d < closest) closest = d;
        if (d < 0.01) {
            Vector hitNorm = !Vector(
                estimator(hitPos + Vector(0.01, 0, 0), steps) - d,
                estimator(hitPos + Vector(0, 0.01, 0), steps) - d,
                estimator(hitPos + Vector(0, 0, 0.01), steps) - d
            );
            return {
                ray, hitPos, hitNorm,
                d, totalD, closest, steps,
                hitType
            };
        }
        if (++steps > maxHits) break;
    }
    return {
        ray, ray.origin + ray.direction * totalD, Vector(0),
        0, totalD, closest, steps,
        0
    };
}

#endif