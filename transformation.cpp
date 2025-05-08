#include <iostream>
#include <cmath>
#include <GL/glut.h>
using namespace std;

// Maximum number of vertices
const int MAX_VERT = 20;

// Homogeneous coordinate arrays
int  A[MAX_VERT][3], C[MAX_VERT][3];
float B[3][3];

// Transformation parameters
int n;           // number of vertices
int tx, ty;      // translation
int sx, sy;      // scaling
int shx, shy;    // shearing
float theta;     // rotation angle (degrees)

// Function prototypes
void lineDDA(int x1, int y1, int x2, int y2);
void unitMatrix();
void multiply();
void translation();
void scaling();
void shearing();
void rotation();
void reflection();
void display();
void initGL();

int main(int argc, char** argv) {
    int choice;

    cout << "\n2D Transformations\n";
    cout << "1. Translation\n"
         << "2. Scaling\n"
         << "3. Shearing\n"
         << "4. Rotation\n"
         << "5. Reflection\n"
         << "Enter your choice: ";
    cin >> choice;

    cout << "Enter number of vertices (<= " << MAX_VERT << "): ";
    cin >> n;
    if (n > MAX_VERT) n = MAX_VERT;

    // Read the polygon vertices in object‐space
    for (int i = 0; i < n; i++) {
        cout << "Vertex " << i+1 << " (x y): ";
        cin >> A[i][0] >> A[i][1];
        A[i][2] = 1;  // homogeneous w‐coordinate
    }

    // Perform the selected transformation
    switch (choice) {
        case 1: translation(); break;
        case 2: scaling();      break;
        case 3: shearing();     break;
        case 4: rotation();     break;
        case 5: reflection();   break;
        default:
            cout << "Invalid choice\n";
            return 0;
    }

    // Initialize GLUT and enter render loop
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1280, 1024);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2D Transformations");
    initGL();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

void initGL() {
    glClearColor(1,1,1,1);
    gluOrtho2D(0, 1280, 0, 1024);
}

// Set B to the 3×3 identity matrix
void unitMatrix() {
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        B[i][j] = (i == j) ? 1.0f : 0.0f;
}

// Multiply A × B → C
void multiply() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            C[i][j] = 0;
            for (int k = 0; k < 3; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
        C[i][2] = 1; // keep homogeneous coordinate = 1
    }
    // Copy C back into A for any further transforms
    for (int i = 0; i < n; i++)
      for (int j = 0; j < 3; j++)
        A[i][j] = C[i][j];
}

// Translation
void translation() {
    cout << "Enter tx ty: ";
    cin >> tx >> ty;
    unitMatrix();
    B[2][0] = tx;
    B[2][1] = ty;
    multiply();
}

// Scaling
void scaling() {
    cout << "Enter sx sy: ";
    cin >> sx >> sy;
    unitMatrix();
    B[0][0] = sx;
    B[1][1] = sy;
    multiply();
}

// Shearing
void shearing() {
    int ch;
    cout << "Shear about:\n"
         << "1. X-axis\n"
         << "2. Y-axis\n"
         << "3. Both\n"
         << "Choice: ";
    cin >> ch;
    unitMatrix();
    if (ch == 1) {
        cout << "Enter shx: "; cin >> shx;
        B[1][0] = shx;
    }
    else if (ch == 2) {
        cout << "Enter shy: "; cin >> shy;
        B[0][1] = shy;
    }
    else if (ch == 3) {
        cout << "Enter shx: "; cin >> shx;
        cout << "Enter shy: "; cin >> shy;
        B[1][0] = shx;
        B[0][1] = shy;
    }
    else {
        cout << "Invalid shear choice\n";
        return;
    }
    multiply();
}

// Rotation about origin
void rotation() {
    int dir;
    cout << "Enter angle (degrees): ";
    cin >> theta;
    cout << "Rotation:\n"
         << "1. Clockwise\n"
         << "2. Counter-clockwise\n"
         << "Choice: ";
    cin >> dir;

    float rad = theta * (M_PI / 180.0f);
    unitMatrix();
    B[0][0] =  cos(rad);
    B[1][1] =  cos(rad);
    B[0][1] = (dir==1 ? sin(rad) : -sin(rad));
    B[1][0] = (dir==1 ? -sin(rad) : sin(rad));
    multiply();
}

// Reflection
void reflection() {
    int ch;
    cout << "Reflect about:\n"
         << "1. X-axis\n"
         << "2. Y-axis\n"
         << "3. Line x = y\n"
         << "4. Line x = -y\n"
         << "5. Origin\n"
         << "Choice: ";
    cin >> ch;
    unitMatrix();
    switch (ch) {
        case 1: B[1][1] = -1;       break;
        case 2: B[0][0] = -1;       break;
        case 3: B[0][0]=0; B[1][1]=0; B[0][1]=1; B[1][0]=1; break;
        case 4: B[0][0]=0; B[1][1]=0; B[0][1]=-1; B[1][0]=-1; break;
        case 5: B[0][0] = -1; B[1][1] = -1; break;
        default:
            cout << "Invalid reflection choice\n";
            return;
    }
    multiply();
}

// DDA line-drawing
void lineDDA(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1, dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xInc = dx / (float)steps, yInc = dy / (float)steps;
    float x = x1, y = y1;

    glBegin(GL_POINTS);
      glVertex2i(round(x), round(y));
      for (int k = 0; k < steps; k++) {
        x += xInc;  y += yInc;
        glVertex2i(round(x), round(y));
      }
    glEnd();
}

// Render original axes, original polygon (blue), transformed (green)
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(2);
    glLineWidth(1);

    // Draw axes in red
    glColor3f(1,0,0);
    lineDDA(0, 512, 1280, 512);
    lineDDA(640, 0, 640, 1024);

    // Draw original polygon in blue
    glColor3f(0,0,1);
    for (int i = 0; i < n; i++) {
        int j = (i+1)%n;
        lineDDA(A[i][0]+640, A[i][1]+512,
                A[j][0]+640, A[j][1]+512);
    }

    // Draw transformed polygon in green
    glColor3f(0,1,0);
    for (int i = 0; i < n; i++) {
        int j = (i+1)%n;
        lineDDA(C[i][0]+640, C[i][1]+512,
                C[j][0]+640, C[j][1]+512);
    }

    glFlush();
}














/*=============================================================================
 Sample Inputs for a 100×100 Square centered at (0,0)

 Common polygon:
   n = 4
   Vertices:
     -50  -50
      50  -50
      50   50
     -50   50

 1) Translation
   Choice: 1
   tx ty: 200 150

 2) Scaling
   Choice: 2
   sx sy: 2 3

 3) Shearing (about X-axis)
   Choice: 3
   Shear menu: 1
   shx: 0.7

 4) Rotation (45° CCW)
   Choice: 4
   Angle: 45
   Dir: 2

 5) Reflection (about x=y)
   Choice: 5
   Reflect menu: 3
=============================================================================*/

