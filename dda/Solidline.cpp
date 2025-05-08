

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

float x_start, y_start, x_end, y_end;

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glColor3f(0.3f, 2.0f, 1.0f);
    gluOrtho2D(-640, 640, -480, 480);
}

void Display() {
    float dx = x_end - x_start;
    float dy = y_end - y_start;
    float step, Xin, Yin, x, y;

    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(3);
    glLineWidth(2);

    // Determine number of steps needed
    if (std::fabs(dx) > std::fabs(dy))
        step = std::fabs(dx);
    else
        step = std::fabs(dy);

    // Calculate increment in x & y for each step
    Xin = dx / step;
    Yin = dy / step;
    x = x_start;
    y = y_start;

    // Plot the initial point
    glBegin(GL_POINTS);
        glVertex2i(static_cast<int>(std::round(x)), static_cast<int>(std::round(y)));
    glEnd();

    // Solid Line: plot every point continuously
    for (int i = 1; i <= static_cast<int>(step); i++) {
        x += Xin;
        y += Yin;
        glBegin(GL_POINTS);
            glVertex2i(static_cast<int>(std::round(x)), static_cast<int>(std::round(y)));
        glEnd();
    }

    // Draw coordinate axes
    glBegin(GL_LINES);
        glVertex2i(-640, 0);
        glVertex2i( 640, 0);
        glVertex2i(   0, -480);
        glVertex2i(   0,  480);
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
    glutCreateWindow("DDA: Solid Line");
    init();
    glutDisplayFunc(Display);
    glutMainLoop();
    return 0;
}


// Simple Line
// > Enter x1 and y1:  -300  -200   // gentle diagonal
// > Enter x2 and y2:   300   200   // slope ≈ 0.67

// Dotted Line
// > Enter x1 and y1:  -300  -200   // same diagonal, spaced dots
// > Enter x2 and y2:   300   200

// Solid Line
// > Enter x1 and y1:  -300  -200   // continuous points
// > Enter x2 and y2:   300   200
