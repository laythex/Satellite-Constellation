#include "Constellation.hpp"

Constellation::Constellation(int _satCount, Satellite* _satellite) {
    satCount = _satCount;
    satellites = _satellite;
}

Constellation::~Constellation() {
    delete[] satellites;
}

void Constellation::advanceTimeSecs(float s) {
    for (int i = 0; i < satCount; i++) {
        satellites[i].advanceTimeSecs(s);
    }
}

void Constellation::sendMessage(float lat1, float lon1, float lat2, float lon2) {
    lat1 *= M_PI / 180;
    lon1 *= M_PI / 180;
    lat2 *= M_PI / 180;
    lon2 *= M_PI / 180;
    float x1 = EARTH_RADIUS * cos(lat1) * cos(lon1);
    float y1 = EARTH_RADIUS * cos(lat1) * sin(lon1);
    float z1 = EARTH_RADIUS * sin(lat1);
    Vector origin(x1, y1, z1);
    float x2 = EARTH_RADIUS * cos(lat2) * cos(lon2);
    float y2 = EARTH_RADIUS * cos(lat2) * sin(lon2);
    float z2 = EARTH_RADIUS * sin(lat2);
    Vector target(x2, y2, z2);

    Satellite startingPoint(origin);
    int route[DEPTH] = { 0 };
    int shortestRoute[DEPTH] = { 0 };
    float shortestLength = INF;
    findRecepient(startingPoint, target, 0, route, 0, shortestRoute, &shortestLength);

    if (shortestLength == INF) {
        std::cout << "Target is unreachable";
        return;
    }

    std::cout << "The shortest route takes " << shortestLength / LIGHT_SPEED << " seconds" << std::endl;
    std::cout << "It takes path: ";
    for (int i = 0; i < DEPTH; i++) {
        if (shortestRoute[i] == 0) break;
        std::cout << shortestRoute[i] << " ";
    }
}

void Constellation::findRecepient(Satellite current, Vector target, int step,
                                  int* route, float distance, int* shortestRoute, float* shortestLength) {
    if (step > DEPTH) return;

    if (current.isTargetVisible(target)) {
        distance += current.getDistance(target);
        if (distance < *shortestLength) {
            for (int i = 0; i < DEPTH; i++) {
                shortestRoute[i] = route[i];
            }
            *shortestLength = distance;
        }
        return;
    }

    for (int i = 0; i < satCount; i++) {

        if (satellites[i] == current) continue;

        bool isInRoute = false;
        for (int j = 0; j < DEPTH; j++) {
            if (route[j] == satellites[i].getId()) {
                isInRoute = true;
                break;
            }
        }

        if (isInRoute) continue;

        if (step > 0 && satellites[i].getDistance(target) > current.getDistance(target)) continue;

        if (!current.isTargetVisible(satellites[i])) continue;

        route[step] = satellites[i].getId();
        float d = current.getDistance(satellites[i]);
        findRecepient(satellites[i], target, step + 1, route, distance + d, shortestRoute, shortestLength);
        route[step] = 0;
    }
}
