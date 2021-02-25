#include <cmath>

#include "lesson1.h"
#include "utility.h"

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

void draw_wireframe(Model* model, TGAImage& image) {
    const auto width = image.get_width();
    const auto height = image.get_height();

    for (int i=0; i<model->nfaces(); i++) {
		std::vector<int> face = model->face(i);
			for (int j=0; j<3; j++) {
			Vec3f v0 = model->vert(face[j]);
			Vec3f v1 = model->vert(face[(j+1)%3]);
			int x0 = (v0.x+1.)*width/2.;
			int y0 = (v0.y+1.)*height/2.;
			int x1 = (v1.x+1.)*width/2.;
			int y1 = (v1.y+1.)*height/2.;
			line(x0, y0, x1, y1, image, white);
		}
	}
}