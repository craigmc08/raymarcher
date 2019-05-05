#ifndef _CAMERA_H
#define _CAMERA_H

#include <math.h>
#include "Vector.hpp"
#include "Ray.hpp"
#include "util.hpp"

class Camera {
private:
    float width;
    float height;
    float fov;

    Vector position;
    float altitude;
    float azimuth;

    Vector forward;
    Vector right;
    Vector up;
public:
    Camera();

    void setSceneSettings(int width, int height) {
        this->width = (float)width;
        this->height = (float)height;
    }

    void setPosition(Vector pos) {
        position = pos;
    }
    void setAltitude(float rot) {
        altitude = rot;
    }
    void setAzimuth(float rot) {
        azimuth = rot;
    }

    void cacheLookDir() {
        Vector axisForward = -Vector(sinf(azimuth), 0, cosf(azimuth));

        forward = axisForward * cosf(altitude) + Vector(0, 1, 0) * sinf(altitude);
        up = axisForward * -sinf(altitude) + Vector(0, 1, 0) * cosf(altitude);
        right = forward.cross(up);
    }

    // Calculate ray through image plane and convert to world coordinates
    Ray getCameraRay(int x, int y) {
        float aspect = width / height;
        // Magic number is in fact pi / 2 / 180
        float pixelMult = tanf(fov * 0.00872664625);
        float px = ((x + 0.5) / width * 2 - 1) * pixelMult * aspect;
        float py = ((height - y + 0.5) / height * 2 - 1) * pixelMult;

        Vector target = !Vector(px, py, 1);

        return {
            position,
            forward * target.z + right * target.x + up * target.y
        };
    }
};

#endif
