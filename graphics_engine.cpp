#include <GL/glut.h>
#include <stdlib.h>
#include <time.h> 
#include <vector>
#include <iostream>
#include <algorithm>

#include "matrix.h"
#include "structs.h"
#include "draw_commands.h"
#include "polygon.h"

using namespace std;



static void resize(int width, int height) {
    glClearColor(0.0, 0.0, 0.0, 0.0);         // black background
    glMatrixMode(GL_PROJECTION);              // setup viewing projection
    glLoadIdentity();                           // start with identity matrix
    glOrtho(0.0, 10.0, 0.0, 10.0, -1.0, 1.0);   // setup a 10x10x2 viewing world
    // glOrtho(0.0, width * SCALE, 0.0, height * SCALE, -1.0, 1.0);   // setup a dynanically sized viewing world
}


void transform(int x, int y, int z, int tx, int ty, int tz) {
	matrix t(4, 4);
	t.set_row(0, vector<int> {1, 0, 0, tx});
	t.set_row(1, vector<int> {0, 1, 0, ty});
	t.set_row(2, vector<int> {0, 0, 1, tz});
	t.set_row(3, vector<int> {0, 0, 0, 1});
	t.print();
	cout << endl;

	matrix p(4, 1);
	p.set_col(0, vector<int> {x, y, z, 1});
	p.print();

	cout << endl;

	matrix p1(4, 1);
	p1 = t.multiply(p);
	p1.print();

	

	
}

// What to display
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    
	// Weird shape
    // point a = {1, 15};
    // point b = {5, 19};
    // point c = {3, 12};
    // point d = {15, 1};
    // point e = {2, 1};
    // vector<point> points = {a, b, c, d, e};

	// Square
	point a = {1, 5};
    point b = {5, 5};
    point c = {5, 1};
    point d = {1, 1};
    vector<point> points = {a, b, c, d};

	Polygon testpoly(points, {6, 6});
	testpoly.set_colour({0.25, 0.5, 0.75});
	// testpoly.translate(2, 2);
	// testpoly.scale(2, 2);
	testpoly.draw();
	// drawLineDDA({1, 1}, {10, 10}, {1, 1, 1});
	// setPixel({1, 1}, {0.1, 0.1, 0.1});


	// transform(1, 1, 1, 2, 2, 2);
	// exit(1);

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
