#include "render.h"
#include "color.h"


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

void line(Vec2i p0, Vec2i p1, TGAImage& image, TGAColor color) {
    bool steep = false;


    if(std::abs(p0.x - p1.x) < std::abs(p0.y- p1.y)) {
        std::swap(p0.x, p0.y);
        std::swap(p1.x, p1.y);
        steep = true;
    }

    if(p0.x > p1.x) {
        std::swap(p0, p1);
    }

    for(int x = p0.x; x <= p1.x; x += 1) {
        float t = (x - p0.x) / (float) (p1.x - p0.x);
        int y = p0.y * (1. -t) + p1.y * t;

        if(steep)
            image.set(y, x, color);
        else
            image.set(x, y, color);

    }


}

void triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage& image, TGAColor color) {
    if(t0.y == t1.y && t0.y == t2.y) return;

    // t2 > t1 > 0
    if(t0.y > t1.y) std::swap(t0, t1);
    if(t0.y > t2.y) std::swap(t0, t2);
    if(t1.y > t2.y) std::swap(t1, t2);

    int total_height = t2.y - t0.y;

    for(int i = 0; i < total_height; i += 1) {
        bool second_half = i > t1.y - t0.y || t1.y == t0.y;
        int segment_height = second_half ? t2.y - t1.y : t1.y - t0.y;

        float alpha = (float) i / total_height;
        float beta = (float) (i - (second_half ? t1.y - t0.y : 0)) / segment_height;

        Vec2i A = t0 + (t2 - t0) * alpha;
        Vec2i B = second_half ? t1 + (t2 - t1) * beta : t0 + (t1 - t0) * beta;

        if(A.x > B.x)
            std::swap(A, B);

        for(int j = A.x; j <= B.x; j += 1)
            image.set(j, t0.y + i, color);
    }

}


void triangle(Vec2i* pts,  TGAImage& image, TGAColor color) {
    Vec2i bboxmin(image.get_width() - 1, image.get_height() - 1);
    Vec2i bboxmax(0, 0);
    Vec2i clamp(image.get_width() - 1, image.get_height() - 1);

    for(int i = 0; i < 3; i += 1) {
        bboxmin.x = std::max(0, std::min(bboxmin.x, pts[i].x));
        bboxmin.y = std::max(0, std::min(bboxmin.y, pts[i].y));


        bboxmax.x = std::min(clamp.x, std::max(bboxmax.x, pts[i].x));
        bboxmax.y = std::min(clamp.y, std::max(bboxmax.y, pts[i].y));
    }

    Vec2i P;

    for(P.x = bboxmin.x; P.x <= bboxmax.x; P.x += 1) {
        for(P.y = bboxmin.y; P.y <= bboxmax.y; P.y += 1) {
            Vec3f bc_screen = barycentric(pts, P);

            if(bc_screen.x < 0 || bc_screen.y < 0 || bc_screen.z < 0)
                continue;

            image.set(P.x, P.y, color);
        }

    }


}



Vec3f barycentric(Vec2i* pts, Vec2i P) {
     Vec3f u = Vec3f(pts[2].x-pts[0].x, pts[1].x-pts[0].x, pts[0].x-P.x) ^ Vec3f(pts[2].y-pts[0].y, pts[1].y-pts[0].y, pts[0].y-P.y);

     if(std::abs(u.z) < 1)
         return Vec3f(-1, 1, 1);

     return Vec3f(1.0f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
}
