#ifndef UI_H
#define UI_H

#include <string>
#include <GL/glut.h>

class UI {
private:
    int score;
    int lives;
    int goldEggs;

public:
    UI();

    void setScore(int s);
    void setLives(int l);
    void setGoldEggs(int g);
    void render(int windowWidth, int windowHeight);
    void renderGameOver(int windowWidth, int windowHeight);
};

#endif
