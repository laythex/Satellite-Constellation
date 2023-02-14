#include "Satellite.hpp"
#include "Constellation.hpp"

#include <cmath>

int main() {
    // Опишите свою спутниковую группировку, указав начальные значения кеплеровых элементов орбиты
    int n = 25;
    Satellite* net = new Satellite[n];
    for (int i = 0; i < n; i++) {
        net[i] = Satellite(i + 1, EARTH_RADIUS * 1.1, 0, M_PI / 4, 2 * M_PI / n * i, 0, 2 * M_PI / n * i);
    }
    Constellation cons(n, net);

    // Вы можете подождать определенный промежуток времени
    cons.advanceTimeSecs(1E4);
    // Попробуйте отправить сообщение из одной точки на поверхности Земли в другую, используя вашу спутниковую группировку, указав координаты точек
    cons.sendMessage(60, 0, -40, 180);

    return 0;
}
