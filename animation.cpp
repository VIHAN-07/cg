// This is file chit4.cpp
// windmill.cpp
#include <GL/glut.h>

float angle = 0.0f;  // rotation angle

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw rod (a vertical line)
    glColor3f(0.6f, 0.3f, 0.0f);
    glLineWidth(5);
    glBegin(GL_LINES);
      glVertex2f(0.0f, -0.8f);
      glVertex2f(0.0f,  0.2f);
    glEnd();

    // Rotate about the pivot at (0,0.2)
    glPushMatrix();
      glTranslatef(0.0f, 0.2f, 0.0f);
      glRotatef(angle, 0, 0, 1);

      // Draw a triangle blade
      glColor3f(0.2f, 0.6f, 1.0f);
      glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.5f, 0.2f);
        glVertex2f(0.5f,-0.2f);
      glEnd();
    glPopMatrix();

    glutSwapBuffers();
}

void idle() {
    angle += 0.5f;
    if (angle >= 360.0f) angle -= 360.0f;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500,500);
    glutCreateWindow("Windmill Animation");

    // set up a simple orthographic view
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1,1,-1,1);

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
