#include "Chicken.h"
#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

// Constructor
Chicken::Chicken() {
    x = 400;
    y = 500;
    width = 100;
    height = 80;
    speed = 3.0f;
    direction = 1; // 1 = right, -1 = left
    textureID = 0;
}

// --------------------------------------------------
// Initialize chicken with screen size and texture
// --------------------------------------------------
void Chicken::init(int screenW, int screenH) {
    screenWidth = screenW;
    screenHeight = screenH;
    x = screenW / 2.0f;
    y = screenH - 100.0f;

    // Load chicken texture (placeholder)
    // textureID = Utils::loadTexture("assets/textures/chicken.png");
    textureID = 1; // Placeholder
    std::srand(static_cast<unsigned>(time(0)));
}

// --------------------------------------------------
// Update chicken movement (auto left-right)
// --------------------------------------------------
void Chicken::update() {
    x += direction * speed;

    // Reverse direction if hitting screen bounds
    if (x - width/2 < 0) {
        x = width/2;
        direction = 1;
    } else if (x + width/2 > screenWidth) {
        x = screenWidth - width/2;
        direction = -1;
    }

    // Occasionally change direction randomly
    if (std::rand() % 200 == 0)
        direction *= -1;
}

// --------------------------------------------------
// Render chicken sprite or fallback shape
// --------------------------------------------------
void Chicken::render() {
    if (textureID == 0) {
        // Fallback simple shape
        glColor3f(1.0f, 1.0f, 0.8f);
        glBegin(GL_POLYGON);
            glVertex2f(x - width/2, y - height/2);
            glVertex2f(x + width/2, y - height/2);
            glVertex2f(x + width/2, y + height/2);
            glVertex2f(x - width/2, y + height/2);
        glEnd();
        return;
    }

    // Draw textured chicken
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
// Getters
// --------------------------------------------------
float Chicken::getX() const { return x; }
float Chicken::getY() const { return y; }

// --------------------------------------------------
// Reset chicken to center (used on restart)
// --------------------------------------------------
void Chicken::reset() {
    x = screenWidth / 2.0f;
    y = screenHeight - 100.0f;
    direction = (std::rand() % 2 == 0) ? 1 : -1;
}
