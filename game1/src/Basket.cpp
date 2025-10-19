#include "Basket.h"
#include <GL/glut.h>
#include <iostream>

// Constructor
Basket::Basket() {
    x = 400;
    y = 60;
    width = 100;
    height = 60;
    speed = 15;
    textureID = 0;
}

// --------------------------------------------------
// Initialize basket position and texture
// --------------------------------------------------
void Basket::init(int screenW, int screenH) {
    screenWidth = screenW;
    screenHeight = screenH;
    x = screenW / 2.0f;
    y = 60.0f;

    // Example of texture loading (replace with Utils later)
    // textureID = Utils::loadTexture("assets/textures/basket.png");
    textureID = 1;  // placeholder
    std::cout << "Basket initialized." << std::endl;
}

// --------------------------------------------------
// Render the basket at its current position
// --------------------------------------------------
void Basket::render() {
    if (textureID == 0) {
        // Fallback: simple colored rectangle
        glColor3f(0.5f, 0.25f, 0.0f);
        glBegin(GL_QUADS);
            glVertex2f(x - width/2, y - height/2);
            glVertex2f(x + width/2, y - height/2);
            glVertex2f(x + width/2, y + height/2);
            glVertex2f(x - width/2, y + height/2);
        glEnd();
        return;
    }

    // Draw textured basket
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(x - width/2, y - height/2);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(x + width/2, y - height/2);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(x + width/2, y + height/2);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(x - width/2, y + height/2);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

// --------------------------------------------------
// Handle arrow key movement
// --------------------------------------------------
void Basket::handleKey(int key) {
    switch (key) {
        case GLUT_KEY_LEFT:
            x -= speed;
            if (x - width / 2 < 0) x = width / 2;
            break;
        case GLUT_KEY_RIGHT:
            x += speed;
            if (x + width / 2 > screenWidth) x = screenWidth - width / 2;
            break;
    }
}

// --------------------------------------------------
// Check if an egg is caught by the basket
// --------------------------------------------------
bool Basket::checkCatch(Egg& egg) {
    float ex = egg.getX();
    float ey = egg.getY();

    bool caught = (ex >= x - width/2 && ex <= x + width/2 &&
                   ey >= y - height/2 && ey <= y + height/2);

    if (caught)
        std::cout << "Caught egg at (" << ex << ", " << ey << ")\n";

    return caught;
}

// --------------------------------------------------
// Reset basket to center (new game)
// --------------------------------------------------
void Basket::reset() {
    x = screenWidth / 2.0f;
    y = 60.0f;
}
