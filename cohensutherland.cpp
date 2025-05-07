// Simple Cohen-Sutherland Line Clipping using OpenGL
// Compile: g++ cohen_simple.cpp -lGL -lGLU -lglut -o cohen_simple

#include <GL/freeglut.h>

const int xmin = 100, ymin = 100, xmax = 300, ymax = 300;

const int INSIDE = 0, LEFT = 1, RIGHT = 2, BOTTOM = 4, TOP = 8;

int computeOutCode(int x, int y) {
    int code = INSIDE;
    if (x < xmin) code |= LEFT;
    else if (x > xmax) code |= RIGHT;
    if (y < ymin) code |= BOTTOM;
    else if (y > ymax) code |= TOP;
    return code;
}

void cohenClip(int x0, int y0, int x1, int y1) {
    int outcode0 = computeOutCode(x0, y0);
    int outcode1 = computeOutCode(x1, y1);
    bool accept = false;

    while (true) {
        if (!(outcode0 | outcode1)) { accept = true; break; }
        else if (outcode0 & outcode1) break;
        else {
            int out = outcode0 ? outcode0 : outcode1;
            int x, y;

            if (out & TOP)    { x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0); y = ymax; }
            else if (out & BOTTOM) { x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0); y = ymin; }
            else if (out & RIGHT)  { y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0); x = xmax; }
            else /* LEFT */   { y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0); x = xmin; }

            if (out == outcode0) { x0 = x; y0 = y; outcode0 = computeOutCode(x0, y0); }
            else { x1 = x; y1 = y; outcode1 = computeOutCode(x1, y1); }
        }
    }

    if (accept) {
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_LINES);
        glVertex2i(x0, y0); glVertex2i(x1, y1);
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw clip window
    glColor3f(1, 1, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2i(xmin, ymin); glVertex2i(xmax, ymin);
    glVertex2i(xmax, ymax); glVertex2i(xmin, ymax);
    glEnd();

    // Original line (red)
    int x0 = 50, y0 = 350, x1 = 350, y1 = 50;
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    glVertex2i(x0, y0); glVertex2i(x1, y1);
    glEnd();

    // Clipped line (green)
    cohenClip(x0, y0, x1, y1);

    glFlush();
}

void init() {
    glClearColor(0, 0, 0, 1);
    gluOrtho2D(0, 400, 0, 400);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Simple Cohen-Sutherland Clipping");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}