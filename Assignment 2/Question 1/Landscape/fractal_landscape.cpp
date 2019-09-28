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
#include "water.h"

using namespace std;


// Point values[129][97] = {0};
vector<vector<Point>> values(129, std::vector<Point>(97, {0, 0, 0}));
Polygon *land;
// Polygon *water;
water *sea;

int rotation_x, rotation_y = 0;
int water_level = 1;

void readfile(string file_name) {
	ifstream infile(file_name);
	int halfway_x = (int)(129 / 2);
	int halfway_y = (int)(97 / 2);
	
	string line;
	// getline(infile, line);
	int i = 0;
	while (getline(infile, line))
	{
		// values.push_back();
		if (line.size() > 0) {
			istringstream iss(line);
			vector<string> tokens{istream_iterator<string>{iss},
				istream_iterator<string>{}};
			for (int j = 0; j < 97; j++) {
				values[i][j] = {(double)i - halfway_x, stod(tokens[j]) * 35, (double)j - halfway_y};
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
	land->rotate(rotation_x, rotation_y);
	land->draw();
	sea->rotate(rotation_x, rotation_y);
	sea->draw();
	// sea->set_water_level(water_level);
	// sea->draw();
    glutSwapBuffers();
}

// What happens when a key is pressed
static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'r':
            exit(0);
            break;
		case 'a':
			rotation_y--;
			break;
		case 'd':
			rotation_y++;
			break;
		case 'w':
			rotation_x--;
			break;
		case 's':
			rotation_x++;
			break;
		case 'q':
			water_level++;
			sea->set_water_level(water_level);
			break;
		case 'e':
			water_level--;
			sea->set_water_level(water_level);
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
	cout << argc <<  endl;
	readfile(argv[1]);
	land = new Polygon(values, {40, 40, 0});
	// vector<Point> a = {{values[0][0].x, 1, values[0][0].z}, {values[128][0].x, 1, values[128][0].z}};
	// vector<Point> b = {{values[128][96].x, 1, values[128][96].z}};
	// vector<vector<Point>> test = {a, b};

	// sea = new water(values, {40, 40, 0});
	// land = new Polygon(test, {0, 0, 0});
	vector<Point> a = {{values[0][0].x, 1, values[0][0].z}, {values[128][0].x, 1, values[128][0].z}};
	vector<Point> b = {{values[0][96].x, 1, values[0][96].z}, {values[128][96].x, 1, values[128][96].z}};
	vector<vector<Point>> test = {a, b};
	sea = new water(test, {40, 20, 0});
	sea->set_lowest_point(1);

    glutInit(&argc, argv);
    glutInitWindowSize(1000,1000); // Size of the window (not including decorations, just usable space)
    glutInitWindowPosition(20,10); // Where on the screen the window appears (Top left of decoration for windows and linux) (x, y)
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);

    glutCreateWindow("Fractal Landscape");

    glutReshapeFunc(resize); // Takes in function name
    glutDisplayFunc(display); // Takes in function name
    glutKeyboardFunc(key); // Register key presses, takes in function name
    glutIdleFunc(idle); // Takes in function name

	glEnable(GL_DEPTH_TEST); // Depth Testing
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0,0,0,0); // Clear values for colour buffers (background colour)

    glutMainLoop();

    return EXIT_SUCCESS;
} 