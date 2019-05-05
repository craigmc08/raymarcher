#ifndef SCENEOBJECT_H_
#define SCENEOBJECT_H_

#include "Vector.hpp"
#include "Material.hpp"

// Base SceneObject class. Never returns collisions
class SceneObject {
private:
public:
    Material* material;

    Material* GetMaterial() { return material; }
    float GetDistance(Vector position) { return 1e9; }
};

class Sphere: public SceneObject {
private:
    Vector center;
    float radius;
public:
    Sphere(Vector center, float radius) {
        this->center = center;
        this->radius = radius;
    }
    float GetDistance(Vector position) {
        Vector distanceToCenter = position - center;
        return distanceToCenter.magnitude() - radius;
    }
};

class Floor: public SceneObject {
private:
    float height;
public:
    Floor(float height) {
        this->height = height;
    }
    float GetDistance(Vector position) {
        return position.y - height;
    }
};

#endif // SCENEOBJECT_H_