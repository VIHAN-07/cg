#include <GL/freeglut.h>
#include <cmath>

#define WIDTH   500
#define HEIGHT  500

// colors
float boundaryColor[3] = {0.0f, 0.0f, 0.0f};  // black
float fillColor[3]     = {1.0f, 0.0f, 0.0f};  // red

bool  filled = false;  // have we clicked to fill yet?

// ———— pixel utilities ————

void setPixel(int x, int y, float* color) {
    glBegin(GL_POINTS);
      glColor3fv(color);
      glVertex2i(x, y);
    glEnd();
}

void getPixel(int x, int y, float* color) {
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);
}

bool isSameColor(float* a, float* b) {
    for (int i = 0; i < 3; i++)
        if (fabs(a[i] - b[i]) > 0.01f)
            return false;
    return true;
}

void boundaryFill(int x, int y) {
    float curr[3];
    getPixel(x, y, curr);

    if (!isSameColor(curr, boundaryColor) && !isSameColor(curr, fillColor)) {
        setPixel(x, y, fillColor);

        boundaryFill(x + 1, y);
        boundaryFill(x - 1, y);
        boundaryFill(x, y + 1);
        boundaryFill(x, y - 1);
    }
}

// ———— draw swastik using hard‑coded GL_POLYGONs ————

void drawSwastikOutline() {
    float cx    = WIDTH  / 2.0f;
    float cy    = HEIGHT / 2.0f;
    float unit  = 80.0f;   // half‑arm length
    float thick = 20.0f;   // arm thickness

    glColor3fv(boundaryColor);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // center vertical bar
    glBegin(GL_POLYGON);
      glVertex2f(cx - thick/2, cy - unit);
      glVertex2f(cx + thick/2, cy - unit);
      glVertex2f(cx + thick/2, cy + unit);
      glVertex2f(cx - thick/2, cy + unit);
    glEnd();

    // center horizontal bar
    glBegin(GL_POLYGON);
      glVertex2f(cx - unit, cy - thick/2);
      glVertex2f(cx + unit, cy - thick/2);
      glVertex2f(cx + unit, cy + thick/2);
      glVertex2f(cx - unit, cy + thick/2);
    glEnd();

    // top‑left arm
    glBegin(GL_POLYGON);
      glVertex2f(cx - unit,               cy + unit - thick/2);
      glVertex2f(cx - thick/2,           cy + unit - thick/2);
      glVertex2f(cx - thick/2,           cy + unit + thick/2);
      glVertex2f(cx - unit,               cy + unit + thick/2);
    glEnd();

    // top‑right arm
    glBegin(GL_POLYGON);
      glVertex2f(cx + unit - thick/2,     cy + thick/2);
      glVertex2f(cx + unit + thick/2,     cy + thick/2);
      glVertex2f(cx + unit + thick/2,     cy + unit);
      glVertex2f(cx + unit - thick/2,     cy + unit);
    glEnd();

    // bottom‑left arm
    glBegin(GL_POLYGON);
      glVertex2f(cx - unit - thick/2,     cy - unit);
      glVertex2f(cx - unit + thick/2,     cy - unit);
      glVertex2f(cx - unit + thick/2,     cy - thick/2);
      glVertex2f(cx - unit - thick/2,     cy - thick/2);
    glEnd();

    // bottom‑right arm
    glBegin(GL_POLYGON);
      glVertex2f(cx + thick/2,           cy - unit - thick/2);
      glVertex2f(cx + unit,               cy - unit - thick/2);
      glVertex2f(cx + unit,               cy - unit + thick/2);
      glVertex2f(cx + thick/2,           cy - unit + thick/2);
    glEnd();
}

// ———— GLUT callbacks ————

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // 1) draw the outline
    drawSwastikOutline();

    // 2) if clicked, fill from center
    if (filled) {
        int sx = WIDTH/2, sy = HEIGHT/2;
        boundaryFill(sx, sy);
    }

    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        filled = true;
        glutPostRedisplay();
    }
}

void initGL() {
    glClearColor(1,1,1,1);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
    glPointSize(1.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Swastik + Seed‑Fill");

    initGL();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
