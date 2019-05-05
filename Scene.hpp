#ifndef SCENE_H_
#define SCENE_H_

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <thread>
#include <chrono>

#include "Vector.hpp"
#include "Camera.hpp"
#include "SceneObject.hpp"
#include "Task.hpp"

class Scene {
private:
    int width;
    int height;
    int samples;

    Camera* camera;

    Vector sunDirection;
    Vector sunColor;

    std::vector<SceneObject*> objects;
public:
    void setSize(int width, int height);
    void setSamples(int samples);

    void SetCamera(Camera* camera);
    void SetSun(Vector direction, Vector color);
    void AddObject(SceneObject* object);

    std::vector<int> Render();

    void RenderToFile(const char* filename);
};

#endif // SCENE_H_