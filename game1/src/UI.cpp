#include "UI.h"
#include <sstream>

// Constructor
UI::UI() : score(0), lives(3), goldEggs(0) {}

// Setters
void UI::setScore(int s) { score = s; }
void UI::setLives(int l) { lives = l; }
void UI::setGoldEggs(int g) { goldEggs = g; }

// Utility to draw text
static void drawText(float x, float y, const std::string &text, void *font = GLUT_BITMAP_HELVETICA_18) {
    glRasterPos2f(x, y);
    for (char c : text)
        glutBitmapCharacter(font, c);
}

// Render main UI (score, lives, gold eggs)
void UI::render(int windowWidth, int windowHeight) {
    glColor3f(0.1f, 0.1f, 0.1f); // dark text

    std::stringstream ss;
    ss << "Score: " << score;
    drawText(20, windowHeight - 30, ss.str());

    ss.str("");
    ss << "Lives: " << lives;
    drawText(200, windowHeight - 30, ss.str());

    ss.str("");
    ss << "Gold Eggs: " << goldEggs;
    drawText(400, windowHeight - 30, ss.str());
}

// Render game over screen
void UI::renderGameOver(int windowWidth, int windowHeight) {
    glColor3f(0.9f, 0.1f, 0.1f); // red text
    std::string msg = "GAME OVER!";
    drawText(windowWidth / 2 - 60, windowHeight / 2 + 20, msg, GLUT_BITMAP_HELVETICA_18);

    glColor3f(0.1f, 0.1f, 0.1f);
    std::stringstream ss;
    ss << "Final Score: " << score;
    drawText(windowWidth / 2 - 70, windowHeight / 2 - 20, ss.str(), GLUT_BITMAP_HELVETICA_18);
}
