#ifndef MATERIAL_H_
#define MATERIAL_H_

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

// Base Material class
class Material {
public:
    BRDF* brdf;

    Material();
    Vector SampleColor(Vector worldPosition);
};

// Solid colored material with BRDF
class SolidMaterial: public Material {
public:
    Vector surfaceColor;
    BRDF* brdf;

    SolidMaterial();
    SolidMaterial(BRDF* brdf, Vector surfaceColor);
    Vector SampleColor(Vector worldPosition);
};

class CheckerMaterial: public Material {
public:
    float checkerScale;
    Vector color1;
    Vector color2;
    BRDF* brdf;

    CheckerMaterial(BRDF* brdf, float checkerScale, Vector color1, Vector color2);
    Vector SampleColor(Vector worldPosition);
};

#endif // MATERIAL_H_