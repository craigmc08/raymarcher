#include "BRDF.hpp"

Vector BRDF::SampleRay(Vector normal, Vector incoming, float &probability) {
    return 0;
}

Vector MirrorBRDF::SampleRay(Vector normal, Vector incoming, float* probability) {
    *probability = 1;
    return incoming + normal * (normal % incoming * -2);
}

LambertianBRDF::LambertianBRDF() {
    rand2Pi = std::uniform_real_distribution<float>(0, TWO_PI);
    randHalfPi = std::uniform_real_distribution<float>(0, HALF_PI);
}
Vector LambertianBRDF::SampleRay(Vector normal, Vector incoming, float* probability) {
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

GlossyBRDF::GlossyBRDF(float _roughness) {
    SetRoughness(_roughness);
    rand2Pi = std::uniform_real_distribution<float>(0, TWO_PI);
}

void GlossyBRDF::SetRoughness(float _roughness) {
    roughness = _roughness;
    randHalfPi = std::normal_distribution<float>(0.0, roughness / ROOT2);
}
float GlossyBRDF::GetRoughness() { return roughness; }

Vector GlossyBRDF::SampleRay(Vector normal, Vector incoming, float *probability) {
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