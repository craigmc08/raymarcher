#ifndef SCENEOBJECT_H_
#define SCENEOBJECT_H_

#include "Vector.hpp"
#include "Material.hpp"

// Base SceneObject class. Never returns collisions
class SceneObject {
public:
    Material* material;
    Material* GetMaterial();
    float GetDistance(Vector position);
};

class Sphere: public SceneObject {
private:
    Vector center;
    float radius;
public:
    Sphere(Vector center, float radius);
    float GetDistance(Vector position);
};

class Floor: public SceneObject {
private:
    float height;
public:
    Floor(float height);
    float GetDistance(Vector position);
};

#endif // SCENEOBJECT_H_