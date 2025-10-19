#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <GL/glut.h>

class Background {
private:
    unsigned int textureID;
    int width, height;

public:
    Background();
    void init();
    void render(int windowWidth, int windowHeight);
};

#endif
