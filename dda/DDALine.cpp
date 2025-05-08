#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath> // For abs()
using namespace std;

float x1, x2, Y1, y2;
int ch;

void init() {
    glClearColor(1, 1, 1, 1);
    glColor3f(0.3, 0.2, 0.1); // Corrected color values to be within 0.0 to 1.0
    gluOrtho2D(-640, 640, -480, 480);
}

void Display() {
    float dy, dx, step, x, y, Xin, Yin;
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(3);
    glLineWidth(2);

    dx = x2 - x1;
    dy = y2 - Y1;

    if (abs(dx) > abs(dy)) {
        step = abs(dx);
    } else {
        step = abs(dy);
    }

    Xin = dx / step;
    Yin = dy / step;
    x = x1;
    y = Y1;

    glBegin(GL_POINTS);
    glVertex2f(x, y); // Use glVertex2f for float coordinates
    glEnd();

    switch (ch) {
    case 1: {
        for (int i = 1; i <= step; i++) { // Dash line
            x = x + Xin;
            y = y + Yin;
            if (i % 16 <= 8) {
                glBegin(GL_POINTS);
                glVertex2f(x, y);
                glEnd();
            }
        }
        break;
    }
    case 2: {
        for (int i = 1; i <= step; i++) { // Dotted line
            x = x + Xin;
            y = y + Yin;
            if (i % 8 == 0) { // Corrected the condition for dotted line
                glBegin(GL_POINTS);
                glVertex2f(x, y);
                glEnd();
            }
        }
        break;
    }
    case 3: {
        for (int i = 1; i <= step; i++) { // Center line
            x = x + Xin;
            y = y + Yin;

            int cycle = i % 35;
            if ((cycle < 10) || (cycle >= 20 && cycle < 25) || (cycle >= 30)) { // Corrected the center line condition
                glBegin(GL_POINTS);
                glVertex2f(x, y);
                glEnd();
            }
        }
        break;
    }
    case 4: {
        for (int i = 1; i <= step; i++) { // Simple Line
            x = x + Xin;
            y = y + Yin;
            glBegin(GL_POINTS);
            glVertex2f(x, y);
            glEnd();
        }
        break;
    }
    default:
        cout << "Wrong Choice !!!" << endl;
    }

    glColor3f(0.0f, 0.0f, 0.0f); // Set color for axes
    glBegin(GL_LINES);
    glVertex2f(-640, 0);
    glVertex2f(640, 0);
    glVertex2f(0, -480);
    glVertex2f(0, 480);
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    cout << "Enter x1 and y1" << endl; // Accept end point coordinates of line
    cin >> x1 >> Y1;
    cout << "Enter x2 and y2" << endl;
    cin >> x2 >> y2;

    cout << "1.Dashed line\n2.Dotted line\n3.Center line\n4.Simple Line" << endl;
    cout << "Enter your choice: ";
    cin >> ch;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100); // Adjusted window position for better visibility
    glutInitWindowSize(640, 480);

    glutCreateWindow("DDA");
    init();
    glutDisplayFunc(Display);
    glutMainLoop();
    return 0;
}
