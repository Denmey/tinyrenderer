#include "tgaimage.h"
#include "model.h"
#include "geometry.h"
#include <iostream>

#include "lesson1.h"
#include "lesson2.h"
#include "colors.h"

Model *model = NULL;
const int width  = 800;
const int height = 800;

int main(int argc, char const *argv[]) {
	TGAImage image(width, height, TGAImage::RGB);
	if (2==argc) {
		model = new Model(argv[1]);
	} else {
		model = new Model("../obj/african_head.obj");
	}
	// for (int i = 0; i < 1000000; ++i)
	// 	line(0, 0, 11,  100, image, red);
	// draw_wireframe(model, image);

	Vec2i t0[3] = {Vec2i(100, 100),   Vec2i(0, 0),  Vec2i(0, 100)};
	Vec2i t1[3] = {Vec2i(180, 50),  Vec2i(150, 1),   Vec2i(70, 180)};
	Vec2i t2[3] = {Vec2i(381, 746), Vec2i(355, 744), Vec2i(355, 715)};

	

	triangle(t0[0], t0[1], t0[2], image, white);
	triangle(t1[0], t1[1], t1[2], image, red);
	triangle(t2[0], t2[1], t2[2], image, white);
	filledTriangle(t0[0], t0[1], t0[2], image, red);
	filledTriangle(t1[0], t1[1], t1[2], image, white);
	filledTriangle(t2[0], t2[1], t2[2], image, green);

	image.flip_vertically(); // Origin is at left-bottom
	image.write_tga_file("output.tga");
	return 0;
}
