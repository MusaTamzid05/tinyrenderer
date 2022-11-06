#include "render.h"
#include "model.h"
#include "color.h"
#include "geometry.h"
#include <vector>
#include <iostream>


Model* model = nullptr;
const int width = 800;
const int height = 800;

void generate_wireframe();

int main(int argc, char** argv) {

    TGAImage image(width, height, TGAImage::RGB);

	Vec2i t0[3] = {Vec2i(10, 70),   Vec2i(50, 160),  Vec2i(70, 80)}; 
	Vec2i t1[3] = {Vec2i(180, 50),  Vec2i(150, 1),   Vec2i(70, 180)}; 
	Vec2i t2[3] = {Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180)}; 

	triangle(t0[0], t0[1], t0[2], image, red); 
	triangle(t1[0], t1[1], t1[2], image, white); 
	triangle(t2[0], t2[1], t2[2], image, green);

    image.flip_vertically();
    image.write_tga_file("triangle.tga");

    return 0;
}


void generate_wireframe() {


    model = new Model("obj/african_head.obj");
    TGAImage image(width, height, TGAImage::RGB);

    for(int i = 0; i < model->nfaces(); i += 1) {
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

}
