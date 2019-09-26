#include <GL/glut.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <cmath>
#include "matrix.h"
#include "structs.h"
#include "Polygon.h"

using namespace std;


// Point values[129][97] = {0};
vector<vector<Point>> values(129, std::vector<Point>(97, {0, 0, 0}));
Polygon *land;
int rotation = 0;

void readfile() {
	ifstream infile("landscape.txt");
	
	string line;
	getline(infile, line);
	int i = 0;
	while (getline(infile, line))
	{
		// values.push_back();
		if (line.size() > 0) {
			istringstream iss(line);
			vector<string> tokens{istream_iterator<string>{iss},
				istream_iterator<string>{}};
			for (int j = 0; j < 97; j++) {
				values[i][j] = {(double)i, stod(tokens[j]) * 100, (double)j};
			}
		}
		i++;
	}
}


static void resize(int width, int height) {
    glClearColor(0.0, 0.0, 0.0, 0.0);         // black background
    glMatrixMode(GL_PROJECTION);              // setup viewing projection
    glLoadIdentity();                           // start with identity matrix
    glOrtho(0.0, 100.0, 0.0, 100.0, -80.0, 80.0);   // setup a 80x80x2 viewing world
    // glOrtho(0.0, width * SCALE, 0.0, height * SCALE, -1.0, 1.0);   // setup a dynanically sized viewing world
}

// What to display
static void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3d(1, 1, 1); // Set colour
	land->rotate(rotation);
	land->draw();
	
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
		case 'a':
			rotation--;
			break;
		case 'd':
			rotation++;
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
	// double values[129][97] = {0};
	readfile();
	land = new Polygon(values, {20, 40, 0});
	// vector<Point> a = {{0, 0, 1}, {1, 0, 1}};
	// vector<Point> b = {{1, 1, 1}};
	// vector<vector<Point>> test = {a, b};
	// land = new Polygon(test, {0, 0, 0});

    glutInit(&argc, argv);
    glutInitWindowSize(800,800); // Size of the window (not including decorations, just usable space)
    glutInitWindowPosition(20,10); // Where on the screen the window appears (Top left of decoration for windows and linux) (x, y)
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    glutCreateWindow("Fractal Landscape");

    glutReshapeFunc(resize); // Takes in function name
    glutDisplayFunc(display); // Takes in function name
    glutKeyboardFunc(key); // Register key presses, takes in function name
    glutIdleFunc(idle); // Takes in function name

    glClearColor(0,0,0,0); // Clear values for colour buffers (background colour)

    glutMainLoop();

    return EXIT_SUCCESS;
} 