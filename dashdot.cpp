#include <GL/freeglut.h>
#include <cmath>
#include <iostream>

using namespace std;

void drawDDA(int x0, int y0, int x1, int y1, const string& pattern) {
    float dx = x1 - x0;
    float dy = y1 - y0;
    float steps = max(abs(dx), abs(dy)); // Using std::max like in code 2
    float xInc = dx / steps;
    float yInc = dy / steps;
    float x = x0, y = y0;
    
    int patternLength = pattern.size();
    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; ++i) {
        if (pattern[i % patternLength] == '1') {
            glVertex2f(x, y); // Direct approach without helper function
        }
        x += xInc;
        y += yInc;
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
        glVertex2i(-500, 0); glVertex2i(500, 0);
        glVertex2i(0, -500); glVertex2i(0, 500);
    glEnd();

    // Dash-Dot-Dash pattern (moved closer to center)
    drawDDA(-400, 100, 400, 100, "111001011100101");

    // Dash pattern (moved closer to center)
    drawDDA(-400, 50, 400, 50, "11110000");
    
    glutSwapBuffers();
}

void initGL() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500.0, 500.0, -500.0, 500.0);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("DDA Dash-Dot-Dash and Dash Lines");
    initGL();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}