#include "render.h"
#include "model.h"
#include "color.h"
#include "geometry.h"
#include <vector>
#include <iostream>


Model* model = nullptr;
const int width = 800;
const int height = 800;

void generate_mesh();

int main(int argc, char** argv) {
    generate_mesh();

    return 0;
}


void generate_mesh() {


    model = new Model("obj/african_head.obj");
    TGAImage image(width, height, TGAImage::RGB);

    Vec3f light_dir(0, 0, -1);

    for(int i = 0; i < model->nfaces(); i += 1) {
        std::vector<int> face = model->face(i);
        Vec2i screen_croods[3];
        Vec3f world_coords[3];

        for(int j = 0; j < 3; j += 1) {
            Vec3f v = model->vert(face[j]);
            screen_croods[j] = Vec2i((v.x + 1.) * width / 2, (v.y + 1) * height / 2.);
            world_coords[j] = v;
        }


        Vec3f n = (world_coords[2] - world_coords[0]) ^ (world_coords[1] - world_coords[0]);
        n.normalize();

        float intensity = n * light_dir;

        if(intensity > 0)
            triangle(
                    screen_croods[0],
                    screen_croods[1],
                    screen_croods[2],
                    image,
                    TGAColor(intensity * 255, intensity * 255, intensity * 255, 255));

    }

    image.flip_vertically();
    image.write_tga_file("model_face.tga");

    /*
    std::cout << model->nfaces() << "\n";

    */

}
