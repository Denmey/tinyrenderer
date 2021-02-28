#include "lesson2.h"

#include "lesson1.h"

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
	// std::cout << p1.x << " " << p1.y << std::endl;
	// std::cout << p2.x << " " << p2.y << std::endl;
	// std::cout << p3.x << " " << p3.y << std::endl;
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
	// std::cout << dy12 << " " << dy13 << " " << dy23 << '\n';
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

void drawMesh(Model* model, TGAImage& image) {
    const auto width = image.get_width();
    const auto height = image.get_height();
    
    for(int i =0 ; i<model->nfaces(); ++i) {
		std::vector<int> face = model->face(i);
		Vec2i screen_coords[3];
		for(int j = 0; j <3; ++j) {
			Vec3f world_coords = model->vert(face[j]);
			if (i == 1680) {
				// filledTriangle(screen_coords[0], screen_coords[1], screen_coords[2], image, color);
				// std::cout << world_coords.x << " " << world_coords.y << std::endl;
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
}