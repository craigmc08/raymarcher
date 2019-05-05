#ifndef BRDF_H_
#define BRDF_H_

#include <random>
#include <stdlib.h>

#include "Vector.hpp"
#include "util.hpp"

// Base brdf clas
class BRDF {
public:
    Vector SampleRay(Vector normal, Vector incoming, float &probability);
};

class MirrorBRDF: public BRDF {
public:
    Vector SampleRay(Vector normal, Vector incoming, float* probability);
};

class LambertianBRDF: public BRDF {
private:
    std::uniform_real_distribution<float> rand2Pi;
    std::uniform_real_distribution<float> randHalfPi;
public:
    LambertianBRDF();
    Vector SampleRay(Vector normal, Vector incoming, float* probability);
};

class GlossyBRDF: public BRDF {
private:
    std::uniform_real_distribution<float> rand2Pi;
    std::normal_distribution<float> randHalfPi;

    float roughness;
public:
    GlossyBRDF(float _roughness);

    void SetRoughness(float _roughness);
    float GetRoughness();

    Vector SampleRay(Vector normal, Vector incoming, float *probability);
};

#endif // BRDF_H_