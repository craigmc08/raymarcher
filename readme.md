# raytracing/raymarcher

## Running
This project has only been built with g++ 7.3.0 for Windows. No guarantees for other compilers.

If you are on windows, compile the executable with
```sh
g++ main.cpp
```

Then, run the executable with
```sh
./a.exe
```

This will take a little bit (a few minutes). It does use about 100% of your CPU.

## Developing

### Planned syntax for materials and stuff
This is the planned usage of this code to write scenes. Currently not implemented.
```cpp
#include "raymarcher.cpp"

int main() {
    Scene* scene = new Scene();
    scene.width = 512;
    scene.height = 512;
    scene.samples = 64;

    Camera* camera = new Camera();
    // Camera position. y is up
    camera.setPosition(Vector(0, 6, 6));
    camera.setFOV(45f); // field of view of camera in degrees
    // Setting camera view angles in degrees
    camera.setAzimuth(0f); // y axis rotation. 0 corresponds to -1 on z-axis being forward
    camera.setAltitude(-45f); // angle above/below horizon

    // Infinite level plane at y-height 0
    Floor* floor = new Floor(0f);
    // Checker size of 1, colors are white and black
    CheckerMaterial* floorMat = new CheckerMaterial(new LambertianBRDF(), 1, Vector(1, 1, 1), Vector(0, 0, 0));
    floor.material = floorMat;

    // Glossy sphere centered at (0, 1, 0) with radius = 1
    Sphere* sphere = new Sphere(Vector(0, 1, 0), 1);
    GlossyBRDF* sphereBRDF = new GlossyBRDF(0.4);
    // Solid color reflective material that's a desaturated purple
    SolidMaterial* sphereMat = new SolidMaterial(sphereBRDF, Vector(1, 0.5, 1));
    sphere.material = sphereMat;

    // Create sun pointing (-1, -1, -1) with color (1, 0.95, 0.9)
    scene.SetSun(Vector(-1, -1, -1), Vector(1, 0.95, 0.9));

    scene.SetCamera(camera);
    scene.AddObject(floor);
    scene.AddObject(sphere);

    // Render to file (in ppm format)
    scene.RenderToFile("raymarched.ppm");

    return 0;
}
```