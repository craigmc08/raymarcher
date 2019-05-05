#include "SceneObject.hpp"

Material* SceneObject::GetMaterial() {
    return material;
}
float SceneObject::GetDistance(Vector position) {
    return 1e9;
}

Sphere::Sphere(Vector center, float radius) {
    this->center = center;
    this->radius = radius;
}
float Sphere::GetDistance(Vector position) {
    Vector distanceToCenter = position - center;
    return distanceToCenter.magnitude() - radius;
}

Floor::Floor(float height) {
    this->height = height;
}
float Floor::GetDistance(Vector position) {
    return position.y - height;
}