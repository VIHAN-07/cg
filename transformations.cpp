#include <GL/glut.h>
#include <cmath>
#include <algorithm>  // for std::swap

// Triangle vertices
GLfloat triangle[3][2] = {
    { 0.0f,  0.2f},
    {-0.2f, -0.2f},
    { 0.2f, -0.2f}
};

// Transformation variables
float tx = 0.0f, ty = 0.0f;
float sx = 1.0f, sy = 1.0f;
float angle = 0.0f;
int reflectX = 1, reflectY = 1;    // 1: normal, -1: reflected about axis
int reflectXY = 1;                 // 1: normal, -1: reflect across line x=y
float shearX = 0.0f, shearY = 0.0f; // shearing factors

void drawAxes() {
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_LINES);
        glVertex2f(-1,  0); glVertex2f(1,  0);  // X-axis
        glVertex2f( 0, -1); glVertex2f(0,  1);  // Y-axis
    glEnd();
}

void drawPolygon() {
    glColor3f(0.2f, 0.8f, 0.2f);
    glBegin(GL_LINE_LOOP);  // Wireframe triangle

    for (int i = 0; i < 3; ++i) {
        float x = triangle[i][0];
        float y = triangle[i][1];

        // 1) Reflection about X/Y axes
        x *= reflectX;
        y *= reflectY;

        // 2) Reflection about line x = y
        if (reflectXY == -1) {
            std::swap(x, y);
        }

        // 3) Rotation
        float xRot = x * cos(angle) - y * sin(angle);
        float yRot = x * sin(angle) + y * cos(angle);

        // 4) Scaling
        xRot *= sx;
        yRot *= sy;

        // 5) Shearing
        float xShear = xRot + shearX * yRot;
        float yShear = yRot + shearY * xRot;

        // 6) Translation
        xShear += tx;
        yShear += ty;

        glVertex2f(xShear, yShear);
    }

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    drawPolygon();
    glFlush();
}

void keyboard(unsigned char key, int, int) {
    switch (key) {
        // Translation
        case 'w': ty += 0.05f; break;
        case 's': ty -= 0.05f; break;
        case 'a': tx -= 0.05f; break;
        case 'd': tx += 0.05f; break;

        // Scaling
        case 'z': sx += 0.1f; sy += 0.1f; break;
        case 'x': sx -= 0.1f; sy -= 0.1f; break;

        // Rotation
        case 'r': angle += 0.1f; break;

        // Reflection about axes
        case 'i': reflectX *= -1; break;  // Y-axis reflect
        case 'j': reflectY *= -1; break;  // X-axis reflect

        // Reflection about x = y
        case 'm': reflectXY *= -1; break;

        // Shearing
        case 'k': shearX += 0.1f; break;
        case 'l': shearY += 0.1f; break;

        // Quit
        case 'q': exit(0); break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2D Transformations with Reflection across x=y");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    // Set up an orthographic projection with range [-1,1] in both axes
    gluOrtho2D(-1, 1, -1, 1);

    glutMainLoop();
    return 0;
}
