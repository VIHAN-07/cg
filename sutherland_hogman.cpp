// sutherland_hodgman_hardcoded.cpp
// Compile with: g++ sutherland_hodgman_hardcoded.cpp -lGL -lGLU -lglut -o clip_hardcoded

#include <GL/freeglut.h>
#include <vector>

struct Point {
    double x, y;
};

// Clipping square coordinates (hardcoded)
static const double clipXmin = 100.0, clipYmin = 100.0;
static const double clipXmax = 300.0, clipYmax = 300.0;

// Hardcoded subject hexagon vertices (clockwise order)
static const std::vector<Point> subjectHexagon = {
    {150.0,  50.0},
    {300.0, 150.0},
    {250.0, 300.0},
    {150.0, 350.0},
    { 50.0, 300.0},
    {  0.0, 150.0}
};

std::vector<Point> clippedPoly;

// Compute intersection of segment (p1->p2) with clipping boundary
Point intersect(const Point& p1, const Point& p2, int edge) {
    Point i;
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    switch (edge) {
        case 0: // left (x = clipXmin)
            i.x = clipXmin;
            i.y = p1.y + dy * (clipXmin - p1.x) / dx;
            break;
        case 1: // top (y = clipYmax)
            i.y = clipYmax;
            i.x = p1.x + dx * (clipYmax - p1.y) / dy;
            break;
        case 2: // right (x = clipXmax)
            i.x = clipXmax;
            i.y = p1.y + dy * (clipXmax - p1.x) / dx;
            break;
        case 3: // bottom (y = clipYmin)
            i.y = clipYmin;
            i.x = p1.x + dx * (clipYmin - p1.y) / dy;
            break;
    }
    return i;
}

bool inside(const Point& p, int edge) {
    switch (edge) {
        case 0: return p.x >= clipXmin;
        case 1: return p.y <= clipYmax;
        case 2: return p.x <= clipXmax;
        case 3: return p.y >= clipYmin;
    }
    return false;
}

std::vector<Point> sutherlandHodgman(const std::vector<Point>& inPoly) {
    std::vector<Point> output = inPoly;
    for (int edge = 0; edge < 4; ++edge) {
        std::vector<Point> input = output;
        output.clear();
        if (input.empty()) break;
        Point S = input.back();
        for (const Point& P : input) {
            if (inside(P, edge)) {
                if (!inside(S, edge))
                    output.push_back(intersect(S, P, edge));
                output.push_back(P);
            } else if (inside(S, edge)) {
                output.push_back(intersect(S, P, edge));
            }
            S = P;
        }
    }
    return output;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw clipping square (white)
    glColor3d(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
        glVertex2d(clipXmin, clipYmin);
        glVertex2d(clipXmax, clipYmin);
        glVertex2d(clipXmax, clipYmax);
        glVertex2d(clipXmin, clipYmax);
    glEnd();

    // Draw subject hexagon (red)
    glColor3d(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
        for (const auto& p : subjectHexagon)
            glVertex2d(p.x, p.y);
    glEnd();

    // Clip and draw clipped polygon (green)
    clippedPoly = sutherlandHodgman(subjectHexagon);
    glColor3d(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
        for (const auto& p : clippedPoly)
            glVertex2d(p.x, p.y);
    glEnd();

    glutSwapBuffers();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    gluOrtho2D(0.0, 400.0, 0.0, 400.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Hardcoded Square & Hexagon Clipping");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
