#include "Vector.hpp"

Vector::Vector(float a) { x = y = z = a; }
Vector::Vector(float a, float b, float c) {
    x = a;
    y = b;
    z = c;
};

float Vector::sqrMagnitude() {
    return *this % *this;
}
float Vector::magnitude() {
    return sqrtf(*this % *this);
}

Vector Vector::cross(Vector o) {
    return Vector(
        y * o.z - z * o.y,
        z * o.x - x * o.z,
        x * o.y - y * o.x
    );
}
Vector Vector::dot(Vector o) {
    return *this % o;
}
float Vector::angleTo(Vector b) {
    return acosf(*this % b);
}
Vector Vector::normalized() {
    return !*this;
}

Vector powv(Vector v, float p) {
    return Vector(powf(v.x, p), powf(v.y, p), powf(v.z, p));
}

Vector operator+(Vector a, Vector b) {
    return Vector(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector operator+(Vector a, float b) {
    return Vector(a.x + b, a.y + b, a.z + b);
}

Vector operator+(float b, Vector a) {
    return Vector(a.x + b, a.y + b, a.z + b);
}
Vector operator-(Vector a, Vector b) {
    return a + b * -1;
}
Vector operator-(Vector a, float b) {
    return a + b*-1;
}
Vector operator-(float a, Vector b) {
    return a + b*-1;
}

Vector operator*(Vector a, Vector b) {
    return Vector(a.x * b.x, a.y * b.y, a.z * b.z);
}
Vector operator*(Vector a, float b) {
    return Vector(a.x * b, a.y * b, a.z * b);
}
Vector operator*(float b, Vector a) {
    return Vector(a.x * b, a.y * b, a.z * b);
}
Vector operator/(Vector a, Vector b) {
    return Vector(a.x / b.x, a.y / b.y, a.z / b.z);
}
Vector operator/(Vector a, float b) {
    return a * (1. / b);
}
Vector operator/(float a, Vector b) {
    return Vector(a / b.x, a / b.y, a / b.z);
}

float Vector::operator%(Vector o) {
    return x * o.x + y * o.y + z * o.z;
}

Vector Vector::operator-() {
    return Vector(-x, -y, -z);
}
Vector Vector::operator!() {
    return *this / sqrtf(*this % *this);
}
