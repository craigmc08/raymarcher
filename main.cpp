#include "Scene.hpp"

#define WIDTH 512
#define HEIGHT 512
#define SAMPLES 64

int main() {
    Scene* scene = new Scene();
    scene->setSize(WIDTH, HEIGHT);
    scene->setSamples(SAMPLES);

    Camera* camera = new Camera();
    // Camera position. y is up
    camera->setPosition(Vector(0, 6, 6));
    camera->setFOV(45.f); // field of view of camera in degrees
    // Setting camera view angles in degrees
    camera->setAzimuth(0.f); // y axis rotation. 0 corresponds to -1 on z-axis being forward
    camera->setAltitude(-45.f); // angle above/below horizon

    // Infinite level plane at y-height 0
    Floor* floor = new Floor(0.f);
    // Checker size of 1, colors are white and black
    CheckerMaterial* floorMat = new CheckerMaterial(new LambertianBRDF(), 1, Vector(1, 1, 1), Vector(0, 0, 0));
    floor->material = floorMat;

    // Glossy sphere centered at (0, 1, 0) with radius = 1
    Sphere* sphere = new Sphere(Vector(0, 1, 0), 1);
    GlossyBRDF* sphereBRDF = new GlossyBRDF(0.4);
    // Solid color reflective material that's a desaturated purple
    SolidMaterial* sphereMat = new SolidMaterial(sphereBRDF, Vector(1, 0.5, 1));
    sphere->material = sphereMat;

    // Create sun pointing (-1, -1, -1) with color (1, 0.95, 0.9)
    scene->SetSun(Vector(-1, -1, -1), Vector(1, 0.95, 0.9));

    scene->SetCamera(camera);
    scene->AddObject(floor);
    scene->AddObject(sphere);

    // Render to file (in ppm format)
    scene->RenderToFile("raymarched.ppm");

    return 0;
}