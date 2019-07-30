#include <GL/glut.h>
#include <stdlib.h>
#include <time.h> 
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

#define SCALE 0.5
#define MAX_X 20
#define MAX_Y 20
#define RAND_COLOUR() (rand()%256)/100
#define ROUND(x) ((int)(x + 0.5))

struct point {
    int x;
    int y;
};

static void resize(int width, int height) {
    glClearColor(0.0, 0.0, 0.0, 0.0);         // black background
    glMatrixMode(GL_PROJECTION);              // setup viewing projection
    glLoadIdentity();                           // start with identity matrix
    glOrtho(0.0, 10.0, 0.0, 10.0, -1.0, 1.0);   // setup a 10x10x2 viewing world
    // glOrtho(0.0, width * SCALE, 0.0, height * SCALE, -1.0, 1.0);   // setup a dynanically sized viewing world
}

void setPixel(int x, int y, double r, double g, double b) {
    glBegin(GL_QUADS);
        glColor3d(r, g, b); // Set colour
        // Define vertices
        glVertex3f((x - 1) * SCALE, (y - 1) * SCALE,0.0);
        glVertex3f(x * SCALE, (y - 1) * SCALE, 0.0);
        glVertex3f(x * SCALE, y * SCALE,0.0);
        glVertex3f((x - 1) * SCALE, y * SCALE,0.0);
    glEnd();
}

void randomPixels() {
    srand(time(NULL));
    for (int i = 0; i < 100; i++) {
        int randomLocX = (rand()%MAX_X);
        int randomLocY = (rand()%MAX_Y);
        setPixel(randomLocX, randomLocY, RAND_COLOUR(), RAND_COLOUR(), RAND_COLOUR());
    }

}

vector<int> drawLineDDA(int x1, int y1, int x2, int y2, double R, double G, double B) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps;
    
    if (abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);
    double x_inc = dx / (double) steps;
    double y_inc = dy / (double) steps;

    double x = x1;
    double y = y1;

    vector<int> x_at_y;
    setPixel(ROUND(x), ROUND(y), R, G, B);
    for (int i = 0; i < steps; i++) {
        x += x_inc;
        y += y_inc;
        x_at_y.push_back(ROUND(x));
        setPixel(ROUND(x), ROUND(y), R, G, B);
    }
    return x_at_y;
}

void randomLines() {
    srand(time(NULL));
    int x1, y1, x2, y2;

    for (int i = 0; i <= 10; i ++) {
        x1 = (rand()%MAX_X);
        y1 = (rand()%MAX_Y);
        x2 = (rand()%MAX_X);
        y2 = (rand()%MAX_Y);

        drawLineDDA(x1, y1, x2, y2, RAND_COLOUR(), RAND_COLOUR(), RAND_COLOUR());
    }
    return;
}


void fillTriangle(point p1, point p2, point p3, double R, double G, double B) {
    // Find out top and bottom points
    int topx, topy, botx, boty;
    if (p1.y >= p2.y && p1.y >= p3.y) {
        topx = p1.x;
        topy = p1.y;
        if (p2.y > p3.y) {
            botx = p3.x;
            boty = p3.y;
        } else {
            botx = p2.x;
            boty = p2.y;
        }
    } else if (p2.y >= p1.y && p2.y >= p3.y) {
        topx = p2.x;
        topy = p2.y;
        if (p1.y > p3.y) {
            botx = p3.x;
            boty = p3.y;
        } else {
            botx = p1.x;
            boty = p1.y;
        }
    } else {
        topx = p3.x;
        topy = p3.y;
        if (p2.y > p1.y) {
            botx = p1.x;
            boty = p1.y;
        } else {
            botx = p2.x;
            boty = p2.y;
        }
    }
    point points[3] = {p1, p2, p3};

    int size_of_array = (topy - boty);
    vector<vector<int>> x_at_y(size_of_array);
    for (int i = 0; i < 3; i++) {
        int warp_i = i + 1;
        if (i == 2)
            warp_i = 0;
        if (points[i].x == points[warp_i].x) { // If vertical line (x is same)
            int bottom = (points[i].y < points[warp_i].y) ? points[i].y : points[warp_i].y;
            int top = (points[i].y > points[warp_i].y) ? points[i].y : points[warp_i].y;
            for (int j = bottom - boty; j < top - boty; j++) { // Add x value to vector for values starting at the bottom to the top
                x_at_y[j].push_back(points[i].x);
            }
        } else if (points[i].y != points[warp_i].y) { // Not horizontal (so at an angle)
            int bottom_y = (points[i].y < points[warp_i].y) ? points[i].y : points[warp_i].y;
            int bottom_x = (points[i].y < points[warp_i].y) ? points[i].x : points[warp_i].x;

            int top_y = (points[i].y > points[warp_i].y) ? points[i].y : points[warp_i].y;
            int top_x = (points[i].y > points[warp_i].y) ? points[i].x : points[warp_i].x;

            // Calculate gradient
            vector<int> xy = drawLineDDA(bottom_x, bottom_y, top_x, top_y, 1, 1, 1);
            int k = 0;
            for (int j = bottom_y - boty; j < top_y - boty; j++) { // Add x value to vector for values starting at the bottom to the top
                x_at_y[j].push_back(xy[k]);
                k++;
            }
        } // Horizontal lines do nothing
    }
    // Draw the lines for filling triangle
    for (int y = 0; y < topy - boty; y++) {
        if (x_at_y[y][0] != x_at_y[y][1])
            drawLineDDA(x_at_y[y][0], y + boty + 1, x_at_y[y][1], y + boty + 1, R, G, B);
    }
    // Draw lines for outline
    drawLineDDA(p1.x, p1.y, p2.x, p2.y, 1, 1, 1);
    drawLineDDA(p2.x, p2.y, p3.x, p3.y, 1, 1, 1);
    drawLineDDA(p3.x, p3.y, p1.x, p1.y, 1, 1, 1);
}

bool same_side(point a, point b, point I1, point I2) {
    // I1 and I2 are ends of the line
    int apt = (a.x - I1.x) * (I2.y - I1.y) - (I2.x - I1.x) * (a.y - I1.y);
    int bpt = (b.x - I1.x) * (I2.y - I1.y) - (I2.x - I1.x) * (b.y - I1.y);
    // Returns true if both a and b are on the same side
    return ((apt * bpt) > 0);
}

// Checks if a point is inside a triangle
bool inside(point p, point a, point b, point c) {
    return same_side(p, a, b, c) && same_side(p, b, a, c) && same_side(p, c, b, a);
}

bool check_inside_polygon(vector<point> points, point vertex_a, point vertex_b, point vertex_c) {
    // Find min and max points
    point min, max;
    if (vertex_a.x < vertex_b.x && vertex_a.x < vertex_c.x) {
        min.x = vertex_a.x;
        min.y = vertex_a.y;
        if (vertex_b.x > vertex_c.x) {
            max.x = vertex_b.x;
            max.y = vertex_b.y;
        }
        else {
            max.x = vertex_c.x;
            max.y = vertex_c.y;
        }
    } else if (vertex_b.x < vertex_a.x && vertex_b.x < vertex_c.x) {
        min.x = vertex_b.x;
        min.y = vertex_b.y;
        if (vertex_a.x > vertex_c.x) {
            max.x = vertex_a.x;
            max.y = vertex_a.y;
        }
        else {
            max.x = vertex_c.x;
            max.y = vertex_c.y;
        }
    } else {
        min.x = vertex_c.x;
        min.y = vertex_c.y;
        if (vertex_a.x > vertex_b.x) {
            max.x = vertex_a.x;
            max.y = vertex_a.y;
        }
        else {
            max.x = vertex_b.x;
            max.y = vertex_b.y;
        }
    }
    
    // Check if point inside rectangle
    for (int y = 0; y < points.size(); y++) {
        if (y != vertex_a.y && y != vertex_b.y && y != vertex_c.y) {
            int px = points[y].y;
            if (!(px < min.x && px > max.x && y < min.y && y > max.y)) {
                // Point inside rectangle, now do inside triangle test
                point p;
                p.x = px;
                p.y = y;
                if (inside(p, vertex_a, vertex_b, vertex_c)) {
                    // Point is inside triangle
                    return true;
                }
            }
        }
    }
    return false;
}

void drawPolygon(vector<point> points, double R, double G, double B) {
    vector<int> used = {}; // stores index of used points
    while (used.size() < points.size()) {
        // Find leftmost vertex
        point vertex_a = {999999999, -1};
        int vertex_a_index = -1;
        for (int i = 0; i < points.size(); i++) {
            if (find(used.begin(), used.end(), i) == used.end() && points[i].x < vertex_a.x) {
                vertex_a = points[i];
                vertex_a_index = i;
            }
        }
    
        if (vertex_a_index == -1)
            exit(1);

        used.push_back(vertex_a_index);
        // Form triangle with 2 adjacent vertices
        point vertex_b, vertex_c;
        if (vertex_a_index + 1 < points.size()) // Make sure the next index isn't out of bounds, if so, wrap around
            vertex_b = {points[vertex_a_index + 1].x, points[vertex_a_index + 1].y};
        else
            vertex_b = {points[0].x, points[0].y};
        if (vertex_a_index != 0) // Make sure the previous index isn't out of bounds, if so, wrap around
            vertex_c = {points[vertex_a_index - 1].x, points[vertex_a_index - 1].y};
        else
            vertex_c = {points[points.size() - 1].x, points[points.size() - 1].y};

        if (!check_inside_polygon(points, vertex_a, vertex_b, vertex_c)) { // If no of the points are in the triangle
            fillTriangle(vertex_a, vertex_b, vertex_c, RAND_COLOUR(), RAND_COLOUR(), RAND_COLOUR());
        }
    }

}

// What to display
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //randomPixels();
    //drawLineDDA(13, 10, -12, -9);
    // randomLines();
    // setPixel(20, 20, 1, 1, 1);

    point a = {1, 15};
    point b = {5, 19};
    point c = {3, 12};
    point d = {15, 1};
    point e = {2, 1};
    vector<point> points = {a, b, c, d, e};
    drawPolygon(points, RAND_COLOUR(), RAND_COLOUR(), RAND_COLOUR());
    setPixel(a.x, a.y, 0.5, 0.5, 0.5);
    setPixel(b.x, b.y, 0.5, 0.5, 0.5);
    setPixel(c.x, c.y, 0.5, 0.5, 0.5);
    setPixel(d.x, d.y, 0.5, 0.5, 0.5);
    setPixel(e.x, e.y, 0.5, 0.5, 0.5);
    glutSwapBuffers();
}


// What happens when a key is pressed
static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;
    }
    glutPostRedisplay();
}

// What happens when idling?
static void idle(void)
{
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(480,480); // Size of the window (not including decorations, just usable space)
    glutInitWindowPosition(20,10); // Where on the screen the window appears (Top left of decoration for windows and linux) (x, y)
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    glutCreateWindow("Graphics Engine");

    glutReshapeFunc(resize); // Takes in function name
    glutDisplayFunc(display); // Takes in function name
    glutKeyboardFunc(key); // Register key presses, takes in function name
    glutIdleFunc(idle); // Takes in function name

    glClearColor(0,0,0,0); // Clear values for colour buffers (background colour)

    glutMainLoop();

    return EXIT_SUCCESS;
} 
