#include "Background.h"
#include <GL/glut.h>
#include <iostream>

// Constructor
Background::Background() {
    textureID = 0;
    width = height = 0;
}

// --------------------------------------------------
// Load texture (placeholder for now)
// --------------------------------------------------
bool Background::loadTexture(const std::string& filename) {
    // You’ll replace this with your own texture loading function
    // using SOIL, stb_image, or your Utils::loadTexture()

    // Example:
    // textureID = Utils::loadTexture(filename.c_str());
    // if (textureID == 0) {
    //     std::cerr << "Failed to load background: " << filename << std::endl;
    //     return false;
    // }

    // For now, we’ll just pretend we loaded it:
    textureID = 1;
    std::cout << "Loaded background texture: " << filename << std::endl;
    return true;
}

// --------------------------------------------------
// Initialize background settings
// --------------------------------------------------
void Background::init(int screenW, int screenH) {
    width = screenW;
    height = screenH;
    // Example file path:
    loadTexture("assets/textures/farm_bg.png");
}

// --------------------------------------------------
// Render the background full-screen
// --------------------------------------------------
void Background::render() {
    if (textureID == 0) {
        // Fallback: draw a simple color ground
        glColor3f(0.65f, 0.9f, 0.55f);
        glBegin(GL_QUADS);
            glVertex2f(0, 0);
            glVertex2f(width, 0);
            glVertex2f(width, height);
            glVertex2f(0, height);
        glEnd();
        return;
    }

    // If using texture (replace later when you have real texture loading)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(0, 0);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(width, 0);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(width, height);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(0, height);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}
