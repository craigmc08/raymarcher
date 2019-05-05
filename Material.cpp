#include "Material.hpp"

Material::Material() {
    brdf = new BRDF();
}
Vector Material::SampleColor(Vector worldPosition) {
    return 0;
}

SolidMaterial::SolidMaterial() {
    brdf = new BRDF();
    surfaceColor = Vector(1, 0, 1);
}
SolidMaterial::SolidMaterial(BRDF* brdf, Vector surfaceColor) {
    this->brdf = brdf;
    this->surfaceColor = surfaceColor;
}
Vector SolidMaterial::SampleColor(Vector worldPosition) {
    return surfaceColor;
}

CheckerMaterial::CheckerMaterial(BRDF* brdf, float checkerScale, Vector color1, Vector color2) {
    this->brdf = brdf;
    this->checkerScale = checkerScale;
    this->color1 = color1;
    this->color2 = color2;
}
Vector CheckerMaterial::SampleColor(Vector worldPosition) {
    float spacing = checkerScale;
    float quarterSpacing = checkerScale / 4;
    float cx = fmodf(fabsf(worldPosition.x) + quarterSpacing, spacing) / spacing * 2 - 1;
    float cy = fmodf(fabsf(worldPosition.z) + quarterSpacing, spacing) / spacing * 2 - 1;
    return cy * cx < 0 ? Vector(0.7) : Vector(1);
}