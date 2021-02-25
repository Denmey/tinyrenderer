#pragma once
#include "tgaimage.h"
#include "model.h"

void line(int x0, int y0, int x1, int y1, TGAImage &image, const TGAColor &color);

void draw_wireframe(Model* model, TGAImage& image);