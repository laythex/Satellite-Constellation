#include "Satellite.hpp"

Satellite::Satellite() {}

Satellite::Satellite(int _id = 0, float _sma = 0, float _ecc = 0, float _inc = 0, float _raan = 0, float _aop = 0, float _ta = 0) {
    id = _id;
    sma = _sma;
    ecc = _ecc;
    inc = _inc;
    raan = _raan;
    aop = _aop;
    ta = _ta;

    position = Vector(0, 0, 0);
}

Satellite::Satellite (Vector pos) {
    position = pos;
}

Vector Satellite::getPosition() {
    if (position.getMagnitude() > 0) return position;

    float ea = 2 * atan(tan(ta / 2) * sqrt((1 - ecc) / (1 + ecc)));
    float rMag = sma * (1 - ecc * cos(ea));

    float x = rMag * (cos(raan) * cos(aop + ta) - sin(raan) * sin(aop + ta) * cos(inc));
    float y = rMag * (sin(raan) * cos(aop + ta) + cos(raan) * sin(aop + ta) * cos(inc));
    float z = rMag * (sin(inc) * sin(aop + ta));

    position = Vector(x, y, z);

    return position;
}

bool Satellite::isTargetVisible(Vector target) {
    Vector pos = getPosition();
    Vector dir = target - pos;
    float t = -pos.dot(dir) / dir.dot(dir);

    if (0 < t && t < 1) return (pos + dir * t).getMagnitude() >= EARTH_RADIUS;

    return true;
}

bool Satellite::isTargetVisible(Satellite target) {
    return isTargetVisible(target.getPosition());
}

float Satellite::getDistance(Vector target) {
    return (getPosition() - target).getMagnitude();
}

float Satellite::getDistance(Satellite target) {
    return getDistance(target.getPosition());
}

void Satellite::advanceTimeSecs(float s) {
    Vector pos = Vector(0, 0, 0);

    float T = 2 * M_PI * sqrt(sma * sma * sma / MU);

    float E0 = 2 * atan(tan(ta / 2) * sqrt((1 - ecc) / (1 + ecc)));
    float M0 = E0 - ecc * sin(E0);

    float M = M0 + 2 * M_PI * s / T;
    float E = M;
    for (int i = 0; i < 3; i++) {
        E -= (E - ecc * sin(E) - M) / (1 - ecc * cos(E));
    }
    ta = 2 * atan(tan(E / 2) * sqrt((1 + ecc) / (1 - ecc)));
}

int Satellite::getId(){
    return id;
}

bool Satellite::operator==(Satellite other) {
    return id == other.getId();
}

bool Satellite::operator!=(Satellite other) {
    return id != other.getId();
}
