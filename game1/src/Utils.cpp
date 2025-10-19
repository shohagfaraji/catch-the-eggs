#include "Utils.h"
#include <cstdlib>
#include <ctime>

// Random float between min and max
float randFloat(float min, float max) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

// AABB (Axis-Aligned Bounding Box) collision detection
bool isColliding(float x1, float y1, float w1, float h1,
                 float x2, float y2, float w2, float h2) {
    return !(x1 + w1 < x2 || x2 + w2 < x1 ||
             y1 + h1 < y2 || y2 + h2 < y1);
}

// Draw colored rectangle
void drawRect(float x, float y, float w, float h,
              float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y + h);
        glVertex2f(x, y + h);
    glEnd();
}

// Draw simple text on screen
void drawText(float x, float y, const std::string &text, void *font) {
    glRasterPos2f(x, y);
    for (char c : text)
        glutBitmapCharacter(font, c);
}
