#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

float x_start, y_start, x_end, y_end;

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
   glColor3f(0.2f, 0.0f, 1.0f); 
   gluOrtho2D(-640, 640, -480, 480);

}

void Display() {
    float dx = x_end - x_start;
    float dy = y_end - y_start;
    float step, Xin, Yin, x, y;

    // Clear and setup
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(3);
    glLineWidth(2);

    // Compute number of steps
    if (fabs(dx) > fabs(dy))
        step = fabs(dx);
    else
        step = fabs(dy);

    // Compute increments
    Xin = dx / step;
    Yin = dy / step;
    x = x_start;
    y = y_start;

    // Draw all points in one batch
    glBegin(GL_POINTS);
        // first point
        glVertex2i((int)round(x), (int)round(y));

        // remaining points
        for (int i = 1; i <= (int)step; ++i) {
            x += Xin;
            y += Yin;
            glVertex2i((int)round(x), (int)round(y));
        }
    glEnd();

    // Draw coordinate axes
    glBegin(GL_LINES);
        glVertex2i(-640, 0);
        glVertex2i( 640, 0);
        glVertex2i(   0,-480);
        glVertex2i(   0, 480);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    cout << "Enter x1 and y1: ";
    cin  >> x_start >> y_start;
    cout << "Enter x2 and y2: ";
    cin  >> x_end >> y_end;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 480);
    glutCreateWindow("DDA: Simple Line");
    init();
    glutDisplayFunc(Display);
    glutMainLoop();
    return 0;
}

