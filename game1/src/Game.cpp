#include "Game.h"
#include <GL/glut.h>
#include <ctime>
#include <cstdlib>
#include <string>
#include <iostream>

// Constructor
Game::Game(int w, int h) {
    windowWidth = w;
    windowHeight = h;
    score = 0;
    lives = 3;
    gameState = STATE_MENU;
}

// --------------------------------------------------
// Initialize game: load assets, seed RNG, reset objects
// --------------------------------------------------
void Game::init() {
    srand(static_cast<unsigned>(time(0)));

    // Load your textures (placeholder)
    // chicken.loadTexture("assets/textures/chicken.png");
    // basket.loadTexture("assets/textures/basket.png");
    // background.loadTexture("assets/textures/farm_bg.png");

    chicken.init(windowWidth, windowHeight);
    basket.init(windowWidth, windowHeight);
    eggs.clear();

    lastEggDropTime = glutGet(GLUT_ELAPSED_TIME);
}

// --------------------------------------------------
// Called each frame (~60 FPS from timer)
// --------------------------------------------------
void Game::update() {
    if (gameState != STATE_PLAYING)
        return;

    chicken.update();

    // Drop eggs randomly
    int now = glutGet(GLUT_ELAPSED_TIME);
    if (now - lastEggDropTime > 1200) { // every 1.2s
        Egg newEgg;
        newEgg.spawnAt(chicken.getX(), chicken.getY());
        eggs.push_back(newEgg);
        lastEggDropTime = now;
    }

    // Update all eggs
    for (auto& egg : eggs)
        egg.update();

    // Check basket-egg collisions
    for (auto& egg : eggs) {
        if (!egg.isActive()) continue;
        if (basket.checkCatch(egg)) {
            egg.setActive(false);
            score += egg.isGolden() ? 5 : 1;
        } else if (egg.isMissed(windowHeight)) {
            egg.setActive(false);
            lives--;
            if (lives <= 0) gameState = STATE_GAMEOVER;
        }
    }

    // Remove inactive eggs
    eggs.erase(std::remove_if(eggs.begin(), eggs.end(),
                [](Egg& e){ return !e.isActive(); }), eggs.end());
}

// --------------------------------------------------
// Draw all game objects
// --------------------------------------------------
void Game::render() {
    glClear(GL_COLOR_BUFFER_BIT);

    switch (gameState) {
        case STATE_MENU:
            renderMenu();
            break;
        case STATE_PLAYING:
            renderGame();
            break;
        case STATE_GAMEOVER:
            renderGameOver();
            break;
    }

    glFlush();
}

// --------------------------------------------------
// Menu screen
// --------------------------------------------------
void Game::renderMenu() {
    drawText(windowWidth / 2 - 120, windowHeight / 2 + 30, "CHICKEN EGGS CATCHER", 1, 0, 0);
    drawText(windowWidth / 2 - 60, windowHeight / 2 - 10, "Press SPACE to Start", 0, 0, 0);
}

// --------------------------------------------------
// Main gameplay rendering
// --------------------------------------------------
void Game::renderGame() {
    background.render();

    chicken.render();
    basket.render();

    for (auto& egg : eggs)
        egg.render();

    // UI
    drawText(20, windowHeight - 30, ("Score: " + std::to_string(score)).c_str(), 0, 0, 0);
    drawText(windowWidth - 120, windowHeight - 30, ("Lives: " + std::to_string(lives)).c_str(), 1, 0, 0);
}

// --------------------------------------------------
// Game over screen
// --------------------------------------------------
void Game::renderGameOver() {
    drawText(windowWidth / 2 - 50, windowHeight / 2 + 30, "GAME OVER!", 1, 0, 0);
    drawText(windowWidth / 2 - 60, windowHeight / 2 - 10, ("Final Score: " + std::to_string(score)).c_str(), 0, 0, 0);
    drawText(windowWidth / 2 - 80, windowHeight / 2 - 40, "Press R to Restart", 0, 0, 0);
}

// --------------------------------------------------
// Keyboard input handling
// --------------------------------------------------
void Game::handleKeyPress(unsigned char key) {
    switch (key) {
        case 27: // ESC
            exit(0);
        case ' ':
            if (gameState == STATE_MENU) {
                reset();
                gameState = STATE_PLAYING;
            }
            break;
        case 'r':
        case 'R':
            if (gameState == STATE_GAMEOVER) {
                reset();
                gameState = STATE_PLAYING;
            }
            break;
    }
}

void Game::handleSpecialKey(int key) {
    if (gameState == STATE_PLAYING) {
        basket.handleKey(key);
    }
}

// --------------------------------------------------
// Utility: draw text using GLUT bitmap
// --------------------------------------------------
void Game::drawText(float x, float y, const char* text, float r, float g, float b) {
    glColor3f(r, g, b);
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
}

// --------------------------------------------------
// Reset everything for new game
// --------------------------------------------------
void Game::reset() {
    score = 0;
    lives = 3;
    eggs.clear();
    chicken.reset();
    basket.reset();
    lastEggDropTime = glutGet(GLUT_ELAPSED_TIME);
}

// --------------------------------------------------
// Update window size if resized
// --------------------------------------------------
void Game::setWindowSize(int w, int h) {
    windowWidth = w;
    windowHeight = h;
}
