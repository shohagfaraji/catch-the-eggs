#include<windows.h>
#include<stdio.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define CIRCLE_RADIUS  0.15f
#define PI 3.14159265358979323846

int eggs_caught=0, missed_eggs=0, level_count=1, points=0;
int egg_xc=-100, egg_yc=-100;  // egg is hidden initially
int basket_x, basket_y;
int a=600, b=650; // screen size
int s=0;
int dropped_eggs=0;
int speed_1=1, speed_2=1.5, speed_3=2, speed_4=2.5;

// Chicken variables
int chicken_x = 100;
int chicken_dir = 1; // 1 = right, -1 = left
int chicken_speed = 2;

void myinit();
void display(void);
void basket_set(int,int);
void egg();
void chicken(); // ADDED
void move_chicken(int); // ADDED
void lay_egg(); // ADDED

void myinit() {
    glViewport(0, 0, a, b);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, a, 0, b);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}

void egg() {
    if (egg_yc < 0) return; // Skip drawing if egg not falling

    float x, y, z;
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    for(int t=0; t<=360; t+=1) {
        x = egg_xc + 8 * cos(t * PI / 180);
        y = egg_yc + 16 * sin(t * PI / 180);
        z = 0;
        glVertex3f(x, y, z);
    }
    glEnd();
}

void basket(int i, int j) {
    j = 10;
    if(i >= a - 60) i = a - 60;
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(0.0+i, 30.0+j);
    glVertex2f(10.0+i, 10.0+j);
    glVertex2f(50.0+i, 10.0+j);
    glVertex2f(60.0+i, 30.0+j);
    glEnd();
}

void chicken() {
    // Chicken body
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(chicken_x, 560);
    glVertex2f(chicken_x + 30, 560);
    glVertex2f(chicken_x + 30, 580);
    glVertex2f(chicken_x, 580);
    glEnd();

    // Head
    glColor3f(1.0, 0.5, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(chicken_x + 30, 570);
    glVertex2f(chicken_x + 40, 570);
    glVertex2f(chicken_x + 40, 580);
    glVertex2f(chicken_x + 30, 580);
    glEnd();
}

void move_chicken(int value) {
    chicken_x += chicken_dir * chicken_speed;

    // Change direction at edges
    if (chicken_x <= 0 || chicken_x >= a - 60) {
        chicken_dir *= -1;
    }

    // Randomly lay egg
    if (rand() % 100 < 5 && egg_yc < 0) { // 5% chance and only if no egg falling
        lay_egg();
    }

    glutPostRedisplay();
    glutTimerFunc(30, move_chicken, 0); // Call every 30 ms
}

void lay_egg() {
    egg_xc = chicken_x + 15;  // Center under chicken
    egg_yc = 560;
    dropped_eggs++;
}

void score() {
    if(egg_yc <= 50 && (egg_xc >= basket_x && egg_xc <= basket_x + 60)) {
        eggs_caught++;
        egg_yc = -100; // hide egg
    }
    missed_eggs = dropped_eggs - eggs_caught;

    if(missed_eggs >= 10) {
        printf("\n\n\t\tGAME OVER\n\n");
        printf("Caught: %d\nMissed: %d\n", eggs_caught, missed_eggs);
        exit(0);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Background
    glColor3f(0.4, 0.8, 1.0); // Sky blue
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(a, 0);
    glVertex2f(a, b);
    glVertex2f(0, b);
    glEnd();

    // Ground
    glColor3f(0.2, 0.7, 0.3);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(a, 0);
    glVertex2f(a, 100);
    glVertex2f(0, 100);
    glEnd();

    if(s >= 1) {
        chicken();      // ADDED
        egg();          // ADDED
        basket(basket_x, basket_y);

        if (egg_yc >= 0)
        {
            if(eggs_caught >= 30) {
                egg_yc -= speed_4;
                level_count = 4;
            } else if(eggs_caught >= 20) {
                egg_yc -= speed_3;
                level_count = 3;
            } else if(eggs_caught >= 10) {
                egg_yc -= speed_2;
                level_count = 2;
            } else {
                egg_yc -= speed_1;
                level_count = 1;
            }
        }

        score();
    } else {
        char msg[] = "Press 'S' to Start";
        glColor3f(1, 0, 0);
        glRasterPos2i(220, 300);
        for (int i = 0; i < strlen(msg); i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, msg[i]);
        }
    }

    glFlush();
    glutSwapBuffers();
}

void basket_set(int x, int y) {
    basket_x = x;
    basket_y = y;
    glutPostRedisplay();
}

void myReshape(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    a = w;
    b = h;
}

void keys(unsigned char key, int x, int y) {
    if(key == 'q' || key == 'Q') {
        printf("QUIT\n");
        exit(0);
    }
    if(key == 's' || key == 'S') {
        s = 1;
    }
}

int main(int argc, char **argv) {
    printf("Welcome to Chicken Egg Game!\n");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(a, b);
    glutCreateWindow("Chicken Egg Game");
    myinit();

    glutDisplayFunc(display);
    glutKeyboardFunc(keys);
    glutPassiveMotionFunc(basket_set);
    glutReshapeFunc(myReshape);
    glutIdleFunc(display);

    glutTimerFunc(0, move_chicken, 0); // Start chicken movement

    glutMainLoop();
    return 0;
}
