#ifndef _VECTOR_H
#define _VECTOR_H

#include <math.h>

struct Vector {
    float x, y, z;
    Vector(float a=0);
    Vector(float a, float b, float c);

    friend Vector operator+(Vector a, Vector b);
    friend Vector operator+(Vector a, float b);
    friend Vector operator+(float b, Vector a);
    friend Vector operator-(Vector a, Vector b);
    friend Vector operator-(Vector a, float b);
    friend Vector operator-(float a, Vector b);

    friend Vector operator*(Vector a, Vector b);
    friend Vector operator*(Vector a, float b);
    friend Vector operator*(float b, Vector a);
    friend Vector operator/(Vector a, Vector b);
    friend Vector operator/(Vector a, float b);
    friend Vector operator/(float a, Vector b);

    float operator%(Vector o);
    float sqrMagnitude();
    float magnitude();

    Vector operator-();
    Vector operator!();

    Vector cross(Vector o);
    Vector dot(Vector o);
    
    float angleTo(Vector b);

    Vector normalized();
};

Vector powv(Vector v, float p);

#endif
