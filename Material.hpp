#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <random>
#include <stdlib.h>

#include "Vector.hpp"
#include "util.hpp"

// Base brdf clas
class BRDF {
public:
    Vector SampleRay(Vector normal, Vector incoming, float &probability) {
        return 0;
    }
};

class MirrorBRDF: public BRDF {
public:
    Vector SampleRay(Vector normal, Vector incoming, float* probability) {
        *probability = 1;
        return incoming + normal * (normal % incoming * -2);
    }
};

class LambertianBRDF: public BRDF {
private:
    std::uniform_real_distribution<float> rand2Pi;
    std::uniform_real_distribution<float> randHalfPi;
public:
    LambertianBRDF() {
        rand2Pi = std::uniform_real_distribution<float>(0, TWO_PI);
        randHalfPi = std::uniform_real_distribution<float>(0, HALF_PI);
    }
    Vector SampleRay(Vector normal, Vector incoming, float* probability) {
        Vector tangent = normal.cross(incoming);
        Vector bitangent = normal.cross(tangent);

        float sinaz, cosaz, sinal, cosal;
        float azimuth = rand2Pi(randomGenerator);
        float altitude = randHalfPi(randomGenerator);
        sincosf(azimuth, &sinaz, &cosaz);
        sincosf(altitude, &sinal, &cosal);
        
        *probability = 1 / TWO_PI;
        return (tangent * sinaz + bitangent * cosaz) * cosal + normal * sinal;
    }
};

class GlossyBRDF: public BRDF {
private:
    std::uniform_real_distribution<float> rand2Pi;
    std::normal_distribution<float> randHalfPi;

    float roughness;
public:
    GlossyBRDF(float _roughness) {
        SetRoughness(_roughness);
        rand2Pi = std::uniform_real_distribution<float>(0, TWO_PI);
    }

    void SetRoughness(float _roughness) {
        roughness = _roughness;
        randHalfPi = std::normal_distribution<float>(0.0, roughness / ROOT2);
    }
    float GetRoughness() { return roughness; }

    Vector SampleRay(Vector normal, Vector incoming, float *probability) {
        Vector up = normal;
        Vector right = up.cross(-incoming);
        Vector forward = up.cross(right);

        float sinaz, cosaz, sinal, cosal;
        float altitude = min(fabsf(randHalfPi(randomGenerator)), HALF_PI);
        float azimuth = rand2Pi(randomGenerator);
        sincosf(altitude, &sinal, &cosal);
        sincosf(azimuth, &sinaz, &cosaz);

        // Up is cosine(altitude) because altitude is weighted towards 0 rad
        Vector halfRay = (right * sinaz + forward * cosaz) * sinal + up * cosal;
        Vector reflectRay = incoming + halfRay * (halfRay % incoming * -2);

        // Probability is guassian microfacet probability * the angle probability (1 / TWO_PI)
        *probability = expf(-altitude * altitude / roughness / roughness) * (1 / TWO_PI);
        return reflectRay;
    }
};

class Material {
public:
    BRDF* brdf;

    Material() {
        brdf = new BRDF();
    }
    Vector SampleColor(Vector worldPosition) {
        return 0;
    }
};

// Solid colored material with BRDF
class SolidMaterial: public Material {
public:
    Vector surfaceColor;
    BRDF* brdf;

    SolidMaterial() {
        brdf = new BRDF();
        surfaceColor = Vector(1, 0, 1);
    }
    SolidMaterial(BRDF* brdf, Vector surfaceColor) {
        this->brdf = brdf;
        this->surfaceColor = surfaceColor;
    }
    Vector SampleColor(Vector worldPosition) {
        return surfaceColor;
    }
};

class CheckerMaterial: public Material {
public:
    float checkerScale;
    Vector color1;
    Vector color2;
    BRDF* brdf;

    CheckerMaterial(BRDF* brdf, float checkerScale, Vector color1, Vector color2) {
        this->brdf = brdf;
        this->checkerScale = checkerScale;
        this->color1 = color1;
        this->color2 = color2;
    }
    Vector SampleColor(Vector worldPosition) {
        float spacing = checkerScale;
        float quarterSpacing = checkerScale / 4;
        float cx = fmodf(fabsf(worldPosition.x) + quarterSpacing, spacing) / spacing * 2 - 1;
        float cy = fmodf(fabsf(worldPosition.z) + quarterSpacing, spacing) / spacing * 2 - 1;
        return cy * cx < 0 ? Vector(0.7) : Vector(1);
    }
};

#endif // MATERIAL_H_