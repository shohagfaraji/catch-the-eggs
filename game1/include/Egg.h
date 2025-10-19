#ifndef EGG_H
#define EGG_H

#include <GL/glut.h>

class Egg {
private:
    float x, y;
    float radius;
    float fallSpeed;
    bool active;
    bool golden;
    unsigned int textureID;
    unsigned int goldenTextureID;
    int screenWidth, screenHeight;

public:
    Egg();

    void init(int screenW, int screenH);
    void spawn(float chickenX, float chickenY);
    void update();
    void render();
    void reset();

    bool isActive() const;
    float getX() const;
    float getY() const;
    bool isGolden() const;
};

#endif
