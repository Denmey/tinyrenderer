#include "tgaimage.h"
#include "model.h"
#include "geometry.h"
#include <iostream>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor   red = TGAColor(255, 0,   0,   255);
const TGAColor green = TGAColor(0,   255, 0,   255);
const TGAColor  blue = TGAColor(0,   0,   255, 255);
Model *model = NULL;
const int width  = 800;
const int height = 800;

void line(int x0, int y0, int x1, int y1, TGAImage &image, const TGAColor &color);
void triangle(Vec2i p1, Vec2i p2, Vec2i p3, TGAImage &image, const TGAColor &color);
void filledTriangle(Vec2i p1, Vec2i p2, Vec2i p3, TGAImage &image, const TGAColor &color);

int main(int argc, char const *argv[]) {
	TGAImage image(width, height, TGAImage::RGB);
	if (2==argc) {
		model = new Model(argv[1]);
	} else {
		model = new Model("../obj/african_head.obj");
	}
	// for (int i = 0; i < 1000000; ++i)
	// 	line(0, 0, 11,  100, image, red);
	// for (int i=0; i<model->nfaces(); i++) {
	// 	std::vector<int> face = model->face(i);
		// 	for (int j=0; j<3; j++) {
	// 		Vec3f v0 = model->vert(face[j]);
	// 		Vec3f v1 = model->vert(face[(j+1)%3]);
	// 		int x0 = (v0.x+1.)*width/2.;
	// 		int y0 = (v0.y+1.)*height/2.;
	// 		int x1 = (v1.x+1.)*width/2.;
	// 		int y1 = (v1.y+1.)*height/2.;
	// 		line(x0, y0, x1, y1, image, white);
	// 	}
	// }

	Vec2i t0[3] = {Vec2i(100, 100),   Vec2i(0, 0),  Vec2i(0, 100)};
	Vec2i t1[3] = {Vec2i(180, 50),  Vec2i(150, 1),   Vec2i(70, 180)};
	Vec2i t2[3] = {Vec2i(381, 746), Vec2i(355, 744), Vec2i(355, 715)};

	for(int i =0 ; i<model->nfaces(); ++i) {
		std::vector<int> face = model->face(i);
		Vec2i screen_coords[3];
		for(int j = 0; j <3; ++j) {
			Vec3f world_coords = model->vert(face[j]);
			if (i == 1680) {
				// filledTriangle(screen_coords[0], screen_coords[1], screen_coords[2], image, color);
				std::cout << world_coords.x << " " << world_coords.y << std::endl;
			}
			screen_coords[j] = Vec2i((world_coords.x+1.)*width/2.1, (world_coords.y+1.)*height/2.1);
		}
		// std::cout << "1" << std::endl;
		TGAColor color;
		// if (i > model->nfaces()/2+434) // 434-434
		// 	color = TGAColor(255,0,0,255);
		// else
		color = TGAColor(0,255,255,255);
		if (i == 1680) {
			filledTriangle(screen_coords[0], screen_coords[1], screen_coords[2], image, color);
			// std::cout << screen_coords[0].x << " " << screen_coords[0].y << std::endl;
			// std::cout << screen_coords[1].x << " " << screen_coords[1].y << std::endl;
			// std::cout << screen_coords[2].x << " " << screen_coords[2].y << std::endl;
			triangle(screen_coords[0], screen_coords[1], screen_coords[2], image, TGAColor(rand()%255, rand()%255, rand()%255, 255));
		}
		filledTriangle(screen_coords[0], screen_coords[1], screen_coords[2], image, TGAColor(rand()%255, rand()%255, rand()%255, 255));
		triangle(screen_coords[0], screen_coords[1], screen_coords[2], image, TGAColor(rand()%255, rand()%255, rand()%255, 255));
	}

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

int sign(int x) {
	return (x<0) ? -1 : 1;
}

void line(int x0, int y0, int x1, int y1, TGAImage &image, const TGAColor &color) {
	int dx = x1-x0;
	int dy = y1-y0;
	if (dx == 0 && dy == 0)
		image.set(x0, y0, color);
	if (std::abs(dx) >= std::abs(dy)) {
		float diff = std::abs(1.0f*dy/dx);
		for (int i = 0; i <= std::abs(dx); ++i)
			image.set(x0+sign(dx)*i, y0+std::floor(sign(dy)*i*diff), color);
	}
	else {
		float diff = std::abs(1.0f*dx/dy);
		for (int i = 0; i <= std::abs(dy); ++i)
			image.set(x0+std::floor(sign(dx)*i*diff), y0+sign(dy)*i, color);
	}
}

void triangle(Vec2i p1, Vec2i p2, Vec2i p3, TGAImage &image, const TGAColor &color) {
	if (p1.x > p2.x) std::swap(p1, p2);
	if (p2.x > p3.x) std::swap(p2, p3);
	if (p1.x > p3.x) std::swap(p1, p3);
	line(p1.x, p1.y, p2.x, p2.y, image, color);
	line(p2.x, p2.y, p3.x, p3.y, image, color);
	line(p3.x, p3.y, p1.x, p1.y, image, color);
}

void filledTriangle(Vec2i p1, Vec2i p2, Vec2i p3, TGAImage &image, const TGAColor &color) {
	if (p1.x > p2.x) std::swap(p1, p2);
	if (p2.x > p3.x) std::swap(p2, p3);
	if (p1.x > p2.x) std::swap(p1, p2);
	std::cout << p1.x << " " << p1.y << std::endl;
	std::cout << p2.x << " " << p2.y << std::endl;
	std::cout << p3.x << " " << p3.y << std::endl;
	int   x12  = std::abs(p2.x-p1.x),
	      x23  = std::abs(p3.x-p2.x),
	      x13  = x12 + x23;
	float currx  = p1.x,
	      curry1 = p1.y,
	      curry2 = p1.y,
	      dy12   = x12 == 0 ? p2.y-p1.y : float(p2.y-p1.y)/x12,
	      dy23   = x23 == 0 ? p3.y-p2.y : float(p3.y-p2.y)/x23,
	      dy13   = x13 == 0 ? p3.y-p1.y : float(p3.y-p1.y)/x13;
	if (x12 == 0)
		curry1 += dy12;
	std::cout << dy12 << " " << dy13 << " " << dy23 << '\n';
	for(; currx < p2.x; ++currx) {
		line(currx, curry1, currx, curry2, image, color);
		curry1 += dy12;
		curry2 += dy13;
	}
	for(; currx <= p3.x; ++currx) {
		line(currx, curry1, currx, curry2, image, color);
		curry1 += dy23;
		curry2 += dy13;
	}
}

// Vec3f barycentric()
