#ifndef _VECTOR_H
#define _VECTOR_H

#include <math.h>

struct Vector {
    float x, y, z;
    Vector(float a=0) { x = y = z = a; }
    Vector(float a, float b, float c) {
        x = a;
        y = b;
        z = c;
    }

    friend Vector operator+(Vector a, Vector b) {
        return Vector(a.x + b.x, a.y + b.y, a.z + b.z);
    }
    friend Vector operator+(Vector a, float b) {
        return Vector(a.x + b, a.y + b, a.z + b);
    }
    friend Vector operator+(float b, Vector a) {
        return Vector(a.x + b, a.y + b, a.z + b);
    }
    friend Vector operator-(Vector a, Vector b) {
        return a + b * -1;
    }
    friend Vector operator-(Vector a, float b) {
        return a + b*-1;
    }
    friend Vector operator-(float a, Vector b) {
        return a + b*-1;
    }

    friend Vector operator*(Vector a, Vector b) {
        return Vector(a.x * b.x, a.y * b.y, a.z * b.z);
    }
    friend Vector operator*(Vector a, float b) {
        return Vector(a.x * b, a.y * b, a.z * b);
    }
    friend Vector operator*(float b, Vector a) {
        return Vector(a.x * b, a.y * b, a.z * b);
    }
    friend Vector operator/(Vector a, Vector b) {
        return Vector(a.x / b.x, a.y / b.y, a.z / b.z);
    }
    friend Vector operator/(Vector a, float b) {
        return a * (1. / b);
    }
    friend Vector operator/(float a, Vector b) {
        return Vector(a / b.x, a / b.y, a / b.z);
    }

    float operator%(Vector o) {
        return x * o.x + y * o.y + z * o.z;
    }
    float sqrMagnitude() {
        return *this % *this;
    }
    float magnitude() {
        return sqrtf(*this % *this);
    }

    Vector operator-() {
        return Vector(-x, -y, -z);
    }
    Vector operator!() {
        return *this / sqrtf(*this % *this);
    }

    Vector cross(Vector o) {
        return Vector(
            y * o.z - z * o.y,
            z * o.x - x * o.z,
            x * o.y - y * o.x
        );
    }
    Vector dot(Vector o) {
        return *this % o;
    }
    
    float angleTo(Vector b) {
        return acosf(*this % b);
    }

    Vector normalized() {
        return !*this;
    }
};

Vector powv(Vector v, float p) {
    return Vector(powf(v.x, p), powf(v.y, p), powf(v.z, p));
}

#endif
