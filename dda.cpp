#include <GL/glut.h>
#include <cmath>

// DDA Line Drawing Algorithm (without round) with parameters
void ddaLine(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps = std::max(abs(dx), abs(dy)); // Determine number of steps

    float xIncrement = dx / steps;
    float yIncrement = dy / steps;

    float x = x1, y = y1;

    glColor3f(1.0f, 0.0f, 2.0f); // Set line color to red
    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        glVertex2f(x, y); // Plot the point directly (no rounding)
        x += xIncrement;
        y += yIncrement;
    }
    glEnd();
}

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Call the DDA function to draw different lines
    ddaLine(50.0f, 50.0f, 300.0f, 200.0f);  // Line 1
    ddaLine(100.0f, 100.0f, 350.0f, 250.0f); // Line 2
    ddaLine(1, 0, 400, 400); // Line 3

    glutSwapBuffers();
}

// Initialize OpenGL settings
void initGL() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to white
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 400.0, 0.0, 400.0); // Set 2D orthographic projection
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("DDA Line Drawing Algorithm With Parameters");
    initGL();
    glutInitWindowPosition(200,100);
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}
