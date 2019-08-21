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
#include "player.h"

using namespace std;

Player* main_player;


static void resize(int width, int height) {
    glClearColor(0.0, 0.0, 0.0, 0.0);         // black background
    glMatrixMode(GL_PROJECTION);              // setup viewing projection
    glLoadIdentity();                           // start with identity matrix
    glOrtho(0.0, 20.0, 0.0, 20.0, -1.0, 1.0);   // setup a 20x20x2 viewing world
    // glOrtho(0.0, width * SCALE, 0.0, height * SCALE, -1.0, 1.0);   // setup a dynanically sized viewing world
}


// What to display
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	main_player->draw();

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
		case 'w':
			main_player->accelerate();
			break;
		case 'a':
			main_player->rotate('l');
			break;
		case 'd':
			main_player->rotate('r');
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
	// Define the polygons to make up the player
	/*
	vector<point> player_sprite_cockpit_points = {
			   {-1, 6}, {1, 6},
		{-2, 4},			  {2, 4},
		{-2, 2},			  {2, 2}
	};
	Polygon player_sprite_cockpit (player_sprite_cockpit_points);
	vector<point> player_sprite_body_points = {
			   {-2, 2},							 {2, 2},
		{-3, 0},										  {3, 0},

		{-3, -2}, {-2, -2},	      {0, -2},		 {2, -2}, {3, -2},
					      {-1, -3}, 	  {1, -3},
	};
	Polygon player_sprite_body (player_sprite_body_points);
	vector<point> player_sprite_left_wing_points = {
			    {-5, 0},  		  {-3, 0},
		{-6, -1},
								  {-3, -2},
						  {-4, -3},

			    {-5, -5}, {-4, -5},
		{-6, -6}
	};
	Polygon player_sprite_left_wing (player_sprite_left_wing_points);
	vector<point> player_sprite_right_wing_points = {
		{3, 0},		   {5, 0},
						    	 {6, -1},
		{3, 2},
			   {4, -3},

			   {4, -5}, {5, -5},
			   					 {6, -6}
	};
	Polygon player_sprite_right_wing (player_sprite_right_wing_points);
	
	main_player = new Player({player_sprite_cockpit});
	*/

	vector<point> square_points = { {-3, 3}, {3, 3}, {-3, -3}, { 3, -3} };
	Polygon square (square_points);
	main_player = new Player({square});

	
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
