#include "tgaimage.h"
#define IMAGE_WIDTH 100
#define IMAGE_HEIGHT 100

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor   red = TGAColor(255, 0,   0,   255);

int main(int argc, char const *argv[]) {
	TGAImage image(100, 100, TGAImage::RGB);
	image.set(52, 41, white);
	image.flip_vertically(); // Origin is at left-bottom
	image.write_tga_file("output.tga");
	return 0;
}
