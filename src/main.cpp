#include "render.h"
#include "model.h"
#include "geometry.h"
#include <vector>
#include <iostream>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

Model* model = nullptr;
const int width = 800;
const int height = 800;

int main(int argc, char** argv) {

    model = new Model("obj/african_head.obj");
    TGAImage image(width, height, TGAImage::RGB);

    for(unsigned int i = 0; i < model->nfaces(); i += 1) {
        std::vector<int> face = model->face(i);

        for(unsigned int j = 0; j < 3; j += 1) {

            Vec3f v0 = model->vert(face[j]);
            Vec3f v1 = model->vert(face[(j + 1) % 3]);

            int x0 = (v0.x + 1.0f) * width / 2;
            int y0 = (v0.y + 1.0f) * height / 2;
            int x1 = (v1.x + 1.0f) * width / 2;
            int y1 = (v1.y + 1.0f) * height / 2;

            line(x0, y0, x1, y1, image, white);

            std::cout << x0 << " " << y0 << " " << x1 << " " << y1 << "\n";

        }

    }

    image.flip_vertically();
    image.write_tga_file("output.tga");

    /*
    std::cout << model->nfaces() << "\n";

    */
    return 0;
}
