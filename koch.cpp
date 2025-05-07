#include <GL/glut.h>
#include <cmath>

// recursion depth
const int LEVEL = 4;

// draw a Koch segment from (x1,y1) to (x2,y2) at given level
void koch(int level, float x1, float y1, float x2, float y2) {
    if (level == 0) {
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    } else {
        float dx = (x2 - x1) / 3.0f;
        float dy = (y2 - y1) / 3.0f;

        // points dividing the segment into thirds
        float x3 = x1 + dx,            y3 = y1 + dy;
        float x5 = x1 + 2*dx,          y5 = y1 + 2*dy;

        // peak point coordinates (rotated by 60° about (x3,y3))
        const float PI = 3.14159265f;
        float angle = PI/3; // 60°
        float x4 = x3 + dx * cosf(angle) - dy * sinf(angle);
        float y4 = y3 + dx * sinf(angle) + dy * cosf(angle);

        // recurse on the four sub‐segments
        koch(level-1, x1, y1, x3, y3);
        koch(level-1, x3, y3, x4, y4);
        koch(level-1, x4, y4, x5, y5);
        koch(level-1, x5, y5, x2, y2);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);  // Set color to red for better visibility

    glBegin(GL_LINES);
        // Draw one Koch curve, centered in the viewport, scale to fit
        koch(LEVEL, -0.5f, 0.0f, 0.5f, 0.0f);  // Example for a horizontal line
    glEnd();
                              
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    // Double-buffered RGB window
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Koch Fractal");

    // Set up an orthographic projection, adjust to fit the curve better
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);  // Keep the view range centered on (0,0)

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
