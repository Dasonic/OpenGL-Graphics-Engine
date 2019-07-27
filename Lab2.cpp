#include <GL/glut.h>
#include <stdlib.h>
#include <time.h> 
#include <vector>
#include <iostream>

using namespace std;

#define SCALE 0.5
#define MAX_X 20
#define MAX_Y 20
#define RAND_COLOUR() (rand()%256)/100
#define ROUND(x) ((int)(x + 0.5))

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


void fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, double R, double G, double B) {
    // Find out top and bottom points
    int topx, topy, botx, boty;
    if (y1 > y2 && y1 > y3) {
        topx = x1;
        topy = y1;
        if (y2 > y3) {
            botx = x3;
            boty = y3;
        } else {
            botx = x2;
            boty = y2;
        }
    } else if (y2 > y1 && y2 > y3) {
        topx = x2;
        topy = y2;
        if (y1 > y3) {
            botx = x3;
            boty = y3;
        } else {
            botx = x1;
            boty = y1;
        }
    } else {
        topx = x3;
        topy = y3;
        if (y2 > y1) {
            botx = x1;
            boty = y1;
        } else {
            botx = x2;
            boty = y2;
        }
    }
    int p1[2] = {x1, y1};
    int p2[2] = {x2, y2};
    int p3[2] = {x3, y3};
    int* points[3] = {p1, p2, p3};

    
    int size_of_array = (topy - boty);
    vector<vector<int>> x_at_y(size_of_array);
    for (int i = 0; i < 3; i++) {
        int warp_i = i + 1;
        if (i == 2)
            warp_i = 0;

        if (points[i][0] == points[warp_i][0]) { // If vertical line (x is same)
            int bottom = (points[i][1] < points[warp_i][1]) ? points[i][1] : points[warp_i][1];
            int top = (points[i][1] > points[warp_i][1]) ? points[i][1] : points[warp_i][1];
            for (int j = bottom; j < top; j++) { // Add x value to vector for values starting at the bottom to the top
                x_at_y[j].push_back(points[i][0]);
            }
        } else if (points[i][1] != points[warp_i][1]) { // Not horizontal (so at an angle)
            int bottom_y = (points[i][1] < points[warp_i][1]) ? points[i][1] : points[warp_i][1];
            int bottom_x = (points[i][1] < points[warp_i][1]) ? points[i][0] : points[warp_i][0];

            int top_y = (points[i][1] > points[warp_i][1]) ? points[i][1] : points[warp_i][1];
            int top_x = (points[i][1] > points[warp_i][1]) ? points[i][0] : points[warp_i][0];

            // Calculate gradient
            vector<int> xy = drawLineDDA(bottom_x, bottom_y, top_x, top_y, 1, 1, 1);
            int k = 0;
            for (int j = bottom_y - boty; j < top_y - boty; j++) { // Add x value to vector for values starting at the bottom to the top
                x_at_y[j].push_back(xy[k]);
                k++;
            }
        } // Horizontal lines do nothing
    }
    // Draw the lines
    for (int y = 0; y < topy - boty; y++) {
        drawLineDDA(x_at_y[y][0], y + boty, x_at_y[y][1], y + boty, 1, 1, 1);
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
    // drawTriangle(2, 2, 10, 5, 5, 10, 1, 1, 1);
    // fillTriangle(2, 2, 11, 6, 6, 11, 1, 1, 1);
    fillTriangle(12, 5, 2, 2, 5, 12, 1, 1, 1);

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

    glutCreateWindow("Lab 2");

    glutReshapeFunc(resize); // Takes in function name
    glutDisplayFunc(display); // Takes in function name
    glutKeyboardFunc(key); // Register key presses, takes in function name
    glutIdleFunc(idle); // Takes in function name

    glClearColor(0,0,0,0); // Clear values for colour buffers (background colour)

    glutMainLoop();

    return EXIT_SUCCESS;
} 
