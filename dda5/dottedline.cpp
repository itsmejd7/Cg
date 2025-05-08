#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;

float x1, x2, Y1, y2;

int sign(int a) {
    if (a > 0) return 1;
    else if (a < 0) return -1;
    else return 0;
}

void init() {
    glClearColor(1, 1, 1, 1);
    glColor3f(0.3, 2.0, 1.0);
    gluOrtho2D(-640, 640, -480, 480);
}

void Display() {
    float dy, dx, step, x, y, G, s1, s2;
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(3);
    glLineWidth(2);

    dx = abs(x2 - x1);
    dy = abs(y2 - Y1);

    step = (dx > dy) ? dx : dy;

    s1 = sign(x2 - x1);
    s2 = sign(y2 - Y1);
    G = (2 * dy) - dx;
    x = x1;
    y = Y1;

    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();

    for (int i = 1; i <= step; i++) {
        while (G >= 0) {
            y = y + s2;
            G = G - (2 * dx);
        }
        x = x + s1;
        G = G + (2 * dy);

        // Dotted pattern: draw point only when i is multiple of 8
        if (i % 8 == 0) {
            glBegin(GL_POINTS);
            glVertex2i(x, y);
            glEnd();
        }
    }

    // Draw axes
    glBegin(GL_LINES);
    glVertex2i(-640, 0);
    glVertex2i(640, 0);
    glVertex2i(0, -480);
    glVertex2i(0, 480);
    glEnd();

    glFlush();
}

int main(int argc, char **argv) {
    cout << "Enter x1 and y1" << endl;
    cin >> x1 >> Y1;
    cout << "Enter x2 and y2" << endl;
    cin >> x2 >> y2;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Dotted Line - Bresenham's Algorithm");
    init();
    glutDisplayFunc(Display);
    glutMainLoop();

    return 0;
}

