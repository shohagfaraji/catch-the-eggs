#ifndef CHICKEN_H
#define CHICKEN_H

#include <GL/glut.h>

class Chicken {
private:
    float x, y;
    float width, height;
    float speed;
    int direction; // 1 = right, -1 = left
    unsigned int textureID;
    int screenWidth, screenHeight;

public:
    Chicken();

    void init(int screenW, int screenH);
    void update();
    void render();

    float getX() const;
    float getY() const;

    void reset();
};

#endif
