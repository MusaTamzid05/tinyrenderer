#include "render.h"


void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color) {
    bool steep = false;

    if(std::abs(x0 - x1) < std::abs(y0 - y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }

    if(x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int dx = x1 - x0;
    int dy = y1 - y0;
    float derror = std::abs(dy) * 2;
    float error = 0;
    float y = y0;

    for(unsigned int x = x0; x <= x1; x+= 1) {
        if(steep)
            image.set(y, x, color);
        else
            image.set(x, y, color);

        error += derror;

        if(error > dx) {
            y += (y1 > y0 ? 1: -1);
            error -= dx * 2;
        }

    }

}
