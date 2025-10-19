#include "Egg.h"
#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

// Constructor
Egg::Egg() {
    x = 0.0f;
    y = 0.0f;
    radius = 12.0f;
    fallSpeed = 4.0f;
    active = false;
    golden = false;
    textureID = 0;
}

// --------------------------------------------------
// Initialize egg system
// --------------------------------------------------
void Egg::init(int screenW, int screenH) {
    screenWidth = screenW;
    screenHeight = screenH;
    std::srand(static_cast<unsigned>(time(0)));

    // Load textures (placeholder IDs)
    // textureID = Utils::loadTexture("assets/textures/egg.png");
    // goldenTextureID = Utils::loadTexture("assets/textures/egg_gold.png");
    textureID = 1;
    goldenTextureID = 2;
}

// --------------------------------------------------
// Spawn egg under chicken
// --------------------------------------------------
void Egg::spawn(float cx, float cy) {
    if (active) return; // only one active egg at a time
    x = cx;
    y = cy - 20.0f;
    active = true;
    golden = (std::rand() % 10 == 0); // 10% chance of golden egg
}

// --------------------------------------------------
// Update egg fall
// --------------------------------------------------
void Egg::update() {
    if (!active) return;

    y -= fallSpeed;
    if (y < 0) {
        active = false; // missed egg
    }
}

// --------------------------------------------------
// Render egg (textured or fallback)
// --------------------------------------------------
void Egg::render() {
    if (!active) return;

    if (textureID == 0) {
        // Fallback: colored circle
        if (golden) glColor3f(1.0f, 0.85f, 0.0f);
        else glColor3f(1.0f, 1.0f, 1.0f);

        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y);
        for (int i = 0; i <= 20; i++) {
            float angle = i * 3.14159f * 2 / 20;
            glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
        }
        glEnd();
        return;
    }

    // Textured egg (choose texture)
    GLuint tex = golden ? goldenTextureID : textureID;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);
    glColor3f(1.0f, 1.0f, 1.0f);

    float w = radius * 2;
    float h = radius * 2.5f;

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(x - w/2, y - h/2);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(x + w/2, y - h/2);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(x + w/2, y + h/2);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(x - w/2, y + h/2);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

// --------------------------------------------------
// Reset egg to inactive
// --------------------------------------------------
void Egg::reset() {
    active = false;
    y = 0;
}

// --------------------------------------------------
// Getters
// --------------------------------------------------
bool Egg::isActive() const { return active; }
float Egg::getX() const { return x; }
float Egg::getY() const { return y; }
bool Egg::isGolden() const { return golden; }
