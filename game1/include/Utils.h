#ifndef UTILS_H
#define UTILS_H

#include <GL/glut.h>
#include <string>

// ---------------- Basic Math / Random ----------------
float randFloat(float min, float max);

// ---------------- Geometry Helpers ----------------
bool isColliding(float x1, float y1, float w1, float h1,
                 float x2, float y2, float w2, float h2);

// ---------------- Drawing Helpers ----------------
void drawRect(float x, float y, float w, float h,
              float r, float g, float b);

void drawText(float x, float y, const std::string &text,
              void *font = GLUT_BITMAP_HELVETICA_18);

#endif
