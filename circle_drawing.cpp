#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
using namespace std;

struct Circle {
    int xc, yc;
    int radius;
    float r, g, b;
};

Circle circles[10];
int numCircles;

void plot_point(int xc, int yc, int x, int y) {
    glBegin(GL_POINTS);
        glVertex2i( xc + x,  yc + y);
        glVertex2i( xc - x,  yc + y);
        glVertex2i( xc - x,  yc - y);
        glVertex2i( xc + x,  yc - y);
        glVertex2i( xc + y,  yc + x);
        glVertex2i( xc - y,  yc + x);
        glVertex2i( xc - y,  yc - x);
        glVertex2i( xc + y,  yc - x);
    glEnd();
}

void bresenham_circle(int xc, int yc, int r) {
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;        // decision parameter

    while (x <= y) {
        plot_point(xc, yc, x, y);
        if (d < 0) {
            // choose East pixel
            d += 4 * x + 6;
        } else {
            // choose South-East pixel
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < numCircles; ++i) {
        glColor3f(circles[i].r, circles[i].g, circles[i].b);
        bresenham_circle(circles[i].xc, circles[i].yc, circles[i].radius);
    }

    glFlush();
}

void Init() {
    // background color
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    // set point size
    glPointSize(4.0f);

    // set up projection: 2D orthographic
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1280, 0, 1024);

    // switch back to modelview for drawing
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    cout << "Enter number of circles to draw (max 10): ";
    cin >> numCircles;
    if (numCircles > 10) numCircles = 10;

    for (int i = 0; i < numCircles; ++i) {
        cout << "\nCircle " << (i + 1) << " details:\n";
        cout << "  Center (xc yc): ";
        cin >> circles[i].xc >> circles[i].yc;
        cout << "  Radius       : ";
        cin >> circles[i].radius;
        cout << "  Color (R G B): ";
        cin >> circles[i].r >> circles[i].g >> circles[i].b;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1280, 1024);
    glutCreateWindow("Bresenham Circles");

    Init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

