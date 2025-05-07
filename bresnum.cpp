#include <GL/glut.h>
#include <cmath>

void simpleBresenhamLine(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int p = 2 * dy - dx;
    int x = x1, y = y1;

    glColor3f(0.0f, 0.0f, 1.0f); // Blue line
    glBegin(GL_POINTS);
    while (x <= x2) {
        glVertex2i(x, y);
        x++;
        if (p < 0) {
            p = p + 2 * dy;
        } else {
            y++;
            p = p + 2 * (dy - dx);
        }
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    simpleBresenhamLine(50, 50, 300, 200);  // Works well for small slopes
    glutSwapBuffers();
}

void initGL() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 400.0, 0.0, 400.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Simple Bresenham Line");
    initGL();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
