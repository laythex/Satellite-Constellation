#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>

class Vector {
public:
    Vector();
    Vector(float _x, float _y, float _z);

    float getMagnitude();
    Vector normalize();

    float dot(Vector other);
    Vector cross(Vector other);

    float getX();
    float getY();
    float getZ();

    void setX(float _x);
    void setY(float _y);
    void setZ(float _z);

    bool operator==(Vector other);

    Vector operator+(Vector other);
    Vector operator-(Vector other);
    Vector operator*(float a);
    Vector operator/(float a);

private:
    float x, y, z;
};

#endif
