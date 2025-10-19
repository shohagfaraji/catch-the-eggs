#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Chicken.h"
#include "Egg.h"
#include "Basket.h"
#include "Background.h"
#include "UI.h"

enum GameState { STATE_MENU, STATE_PLAYING, STATE_GAMEOVER };

class Game {
private:
    int windowWidth, windowHeight;
    int score, lives;
    GameState gameState;
    int lastEggDropTime;

    Chicken chicken;
    Basket basket;
    Background background;
    UI ui;
    std::vector<Egg> eggs;

public:
    Game(int w, int h);

    void init();
    void update();
    void render();

    void handleKeyPress
