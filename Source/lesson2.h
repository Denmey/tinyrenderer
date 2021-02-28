#pragma once

#include "tgaimage.h"
#include "geometry.h"
#include "model.h"

void triangle(Vec2i p1, Vec2i p2, Vec2i p3, TGAImage &image, const TGAColor &color);
void filledTriangle(Vec2i p1, Vec2i p2, Vec2i p3, TGAImage &image, const TGAColor &color);
// Vec3f barycentric()
void drawMesh(Model* model, TGAImage& image);