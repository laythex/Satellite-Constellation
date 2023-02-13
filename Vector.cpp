#include "Vector.hpp"

Vector::Vector() {}
Vector::Vector(float _x = 0, float _y = 0, float _z = 0) {
        x = _x;
        y = _y;
        z = _z;
    }

float Vector::getMagnitude() {
    return sqrt(dot(*this));
}

Vector Vector::normalize() {
    return (*this) / getMagnitude();
}

float Vector::dot(Vector other) {
    return x * other.getX() + y * other.getY() + z * other.getZ();
}

Vector Vector::cross(Vector other) {
    float xc = y * other.getZ() - z * other.getY();
    float yc = z * other.getX() - x * other.getZ();
    float zc = x * other.getY() - y * other.getX();
    return Vector(xc, yc, zc);
}

float Vector::getX() {
    return x;
}

float Vector::getY() {
    return y;
}

float Vector::getZ() {
    return z;
}

void Vector::setX(float _x) {
    x = _x;
}

void Vector::setY(float _y) {
    y = _y;
}

void Vector::setZ(float _z) {
    z = _z;
}

bool Vector::operator==(Vector other) {
    return x == other.getX() && y == other.getY() && z == other.getZ();
}

Vector Vector::operator+(Vector other) {
    return Vector(x + other.getX(), y + other.getY(), z + other.getZ());
}

Vector Vector::operator-(Vector other) {
    return Vector(x - other.getX(), y - other.getY(), z - other.getZ());
}

Vector Vector::operator*(float a) {
    return Vector(x * a, y * a, z * a);
}

Vector Vector::operator/(float a) {
    return Vector(x / a, y / a, z / a);
}
