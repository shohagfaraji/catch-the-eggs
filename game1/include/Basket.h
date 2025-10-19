#ifndef BASKET_H
#define BASKET_H

#include <GL/glut.h>

class Basket {
private:
    float x, y;
    float width, height;
    float speed;

public:
    Basket();

    void init(int windowWidth, int windowHeight);
    void moveLeft();
    void moveRight();
    void render();
    float getX() const;
    float getY() const;
    float getWidth() const;
    float getHeight() const;
};

#endif
