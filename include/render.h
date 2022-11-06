#ifndef LINE_H
#define LINE_H

#include "tgaimage.h"
#include "geometry.h"

void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color);
void line(Vec2i p0, Vec2i p1, TGAImage& image, TGAColor color);
void triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage& image, TGAColor color);

#endif
