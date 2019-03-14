#include "tgaimage.h"
#include <iostream>
#define IMAGE_WIDTH 100
#define IMAGE_HEIGHT 100

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor   red = TGAColor(255, 0,   0,   255);

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color);

int main(int argc, char const *argv[]) {
	TGAImage image(100, 100, TGAImage::RGB);
	image.set(52, 41, white);
	line(0, 0, 11,  100, image, red);
	line(22, 100, 0, 0, image, white);
	line(0, 0, 100, 11,  image, white);
	line(100, 22, 0, 0,  image, red);
	line(0,0,0,100, image, white);
	line(0,0,100,0, image, white);
	line(20,20,20,20,image,red);
	image.flip_vertically(); // Origin is at left-bottom
	image.write_tga_file("output.tga");
	return 0;
}

int sign(int x) {
	return (x<0) ? -1 : 1;
}

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
	int dx = x1-x0;
	int dy = y1-y0;
	if (dx == 0 && dy == 0)
		image.set(x0, y0, color);
	if (std::abs(dx) >= std::abs(dy)) {
		float diff = std::abs(1.0f*dy/dx);
		for (int i = 0; i <= std::abs(dx); ++i)
			image.set(x0+sign(dx)*i, y0+sign(dy)*i*diff, color);
	}
	else {
		float diff = std::abs(1.0f*dx/dy);
		for (int i = 0; i <= std::abs(dy); ++i)
			image.set(x0+sign(dx)*i*diff, y0+sign(dy)*i, color);
	}
}
