#ifndef SATELLITE_H
#define SATELLITE_H

#include "Vector.hpp"
#include <cmath>

const float MU = 3.986E14;
const float EARTH_RADIUS = 6.371E6;
const float LIGHT_SPEED = 299792458;

class Satellite {
public:
    Satellite();
    Satellite(int _id, float _sma, float _ecc, float _inc, float _raan, float _aop, float _ta);
    Satellite (Vector pos);

    Vector getPosition();

    bool isTargetVisible(Vector target);
    bool isTargetVisible(Satellite target);

    float getDistance(Vector target);
    float getDistance(Satellite target);

    void advanceTimeSecs(float s);

    int getId();

    bool operator==(Satellite other);
    bool operator!=(Satellite other);

private:
    int id;

    float sma;
    float ecc;
    float inc;
    float raan;
    float aop;
    float ta;

    Vector position;
};

#endif
