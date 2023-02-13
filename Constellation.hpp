#ifndef CONSTELLATION_H
#define CONSTELLATION_H

#include "Vector.hpp"
#include "Satellite.hpp"
#include <cmath>
#include <iostream>

const int DEPTH = 20;
const float INF = std::numeric_limits<float>::infinity();

class Constellation {
public:
    Constellation(int _satCount, Satellite* _satellite);
    ~Constellation();

    void advanceTimeSecs(float s);

    void sendMessage(float lat1, float lon1, float lat2, float lon2);

private:
    int satCount;
    Satellite* satellites;

    void findRecepient(Satellite current, Vector target, int step,
                       int* route, float distance, int* shortestRoute, float* shortestLength);
};

#endif
