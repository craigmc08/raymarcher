#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <random>
#include <stdlib.h>

#include "Vector.hpp"
#include "util.hpp"
#include "BRDF.hpp"

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