#include <GL/glut.h>

float angle = 0.0;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Apply Y-axis rotation
    glRotatef(angle, 0, 1, 0);

    glColor3f(1.0f, 0.0f, 0.0f); // Red color for the cube
    glutWireCube(1.5);

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':  // rotate left
            angle -= 5.0;
            if (angle < 0) angle += 360;
            glutPostRedisplay();
            break;
        case 'd':  // rotate right
            angle += 5.0;
            if (angle > 360) angle -= 360;
            glutPostRedisplay();
            break;
        case 'q':   // ESC key
            exit(0);
    }
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, 2, -2, 2, -2, 2);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Keyboard Rotating Cube");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
