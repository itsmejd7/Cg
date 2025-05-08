#include <GL/glut.h>
#include <cstdlib>

#define ESCAPE 27

static int window;
static float rtri = 0.0f;   // Horizontal offset for triangle
static float angle = 0.0f;  // Rotation angle for spheres

// Ball positions
static const float ball1X = -0.5f;
static const float ball2X = +1.0f;
static const float ballY  =  0.0f;
static const float ballZ  =  0.0f;

// Initialize GL state
void InitGL(int width, int height) {
    glClearColor(1,1,1,1);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)width / (float)height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Reshape callback
void reshape(int width, int height) {
    InitGL(width, height);
}

// Draw two rotating spheres (“ball”)
void drawBalls() {
    // Sphere 1
    glPushMatrix();
      glTranslatef(ball1X, ballY, ballZ);
      glRotatef(angle, 0.0f, 1.0f, 0.0f);
      glColor3f(1.0f, 0.0f, 1.0f);
      glutSolidSphere(0.3, 50, 50);
    glPopMatrix();

    // Sphere 2
    glPushMatrix();
      glTranslatef(ball2X, ballY, ballZ);
      glRotatef(-angle, 1.0f, 0.0f, 0.0f);
      glColor3f(0.0f, 0.5f, 1.0f);
      glutSolidSphere(0.3, 50, 50);
    glPopMatrix();
}

// Main render loop
void DrawGLScene() {
    // Clear color + depth
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Camera
    gluLookAt( 0.0, 1.5, 6.0,   // eye position
               0.0, 0.0, 0.0,   // look-at point
               0.0, 1.0, 0.0 ); // up vector

    // Moving triangle (“car roof”)
    glPushMatrix();
      glTranslatef(rtri, 0.0f, 0.0f);
      glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-1.0f, 1.0f, 0.0f);
        glVertex3f( 0.4f, 1.0f, 0.0f);
        glVertex3f( 1.0f, 0.4f, 0.0f);
      glEnd();
    glPopMatrix();

    // Draw spheres
    drawBalls();

    // Update animation parameters
    rtri += 0.005f;
    if (rtri >  2.0f) rtri = -2.0f;
    angle += 0.3f;
    if (angle > 360.0f) angle -= 360.0f;

    glutSwapBuffers();
}

// Exit on ESC
void keyPressed(unsigned char key, int x, int y) {
    if (key == ESCAPE) {
        glutDestroyWindow(window);
        std::exit(0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    window = glutCreateWindow("Moving Car & Rotating Balls");

    glutDisplayFunc(DrawGLScene);
    glutIdleFunc(DrawGLScene);
    glutKeyboardFunc(keyPressed);
    glutReshapeFunc(reshape);

    InitGL(640, 480);
    glutMainLoop();
    return 0;
}

/*
 Best “Inputs” & Usage:
 - Compile: g++ yourfile.cpp -o moving_car -lGL -lGLU -lglut
 - Run:     ./moving_car
 - Controls:
     • ESC key exits the application
     • Resizing the window adjusts the viewport/projection automatically
 - Animation Parameters (tweak for different effects):
     • rtri speed  = 0.005f   // triangle translation increment
     • angle speed = 0.3f     // sphere rotation increment
     • Sphere radius = 0.3     // try 0.5 for a larger ball
     • Sphere complexity = (50,50) // reduce for faster rendering
*/

