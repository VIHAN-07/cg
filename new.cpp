#include <GL/glut.h>

void drawAxes() {
    // Set axes color to gray
    glColor3f(0.5f, 0.5f, 0.5f);
    
    // Draw the X and Y axes
    glBegin(GL_LINES);
        // X-axis (horizontal)
        glVertex2f(-1.0f, 0.0f);
        glVertex2f(1.0f, 0.0f);
        
        // Y-axis (vertical)
        glVertex2f(0.0f, -1.0f);
        glVertex2f(0.0f, 1.0f);
    glEnd();
}

void display() {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw coordinate axes
    drawAxes();
    
    // Ensure all drawing commands are executed
    glFlush();
}

int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    
    // Set display mode (single buffer with RGB color model)
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    // Set window size and position
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    
    // Create the window with a title
    glutCreateWindow("Basic Coordinate Axes");
    
    // Set background color to white
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    // Set up the coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    
    // Register the display callback function
    glutDisplayFunc(display);
    
    // Enter the GLUT main event loop
    glutMainLoop();
    
    return 0;
}