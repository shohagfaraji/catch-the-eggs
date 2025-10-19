#include <GL/glut.h>
#include "Game.h"

// Window dimensions
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

Game game(WINDOW_WIDTH, WINDOW_HEIGHT);

// ---------------- GLUT Callbacks ----------------

void displayCallback() {
    glClear(GL_COLOR_BUFFER_BIT);
    game.render();
    glutSwapBuffers();
}

void reshapeCallback(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    game.setWindowSize(w, h);
}

void keyboardCallback(unsigned char key, int x, int y) {
    game.handleKeyPress(key);
}

void specialKeyCallback(int key, int x, int y) {
    game.handleSpecialKey(key);
}

void timerCallback(int value) {
    game.update();
    glutPostRedisplay();
    glutTimerFunc(16, timerCallback, 0);  // ~60 FPS
}

// ---------------- Main Entry ----------------

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Chicken Eggs Catching Game");

    // Background color (farm theme)
    glClearColor(0.7f, 0.9f, 0.6f, 1.0f); // light green farmy tone

    // Initialize your game logic, load assets
    game.init();

    // Register callbacks
    glutDisplayFunc(displayCallback);
    glutReshapeFunc(reshapeCallback);
    glutKeyboardFunc(keyboardCallback);
    glutSpecialFunc(specialKeyCallback);
    glutTimerFunc(0, timerCallback, 0);

    glutMainLoop();
    return 0;
}
