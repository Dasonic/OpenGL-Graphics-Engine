#include <GL/glut.h>
#include <stdlib.h>
#include <time.h> 
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>

#include "matrix.h"
#include "structs.h"
#include "draw_commands.h"
#include "polygon.h"
#include "player.h"

using namespace std;

int out_of_bounds_counter = 0;
int frame_counter = 0;
Player* main_player;
vector<Entity> asteroids;
const rectangle boundary_box[] = {{{0, 165}, {160, 159}}, {{0, 1}, {160, -5}}, {{-5, 160}, {1, 0}}, {{159, 160}, {165, 0}}};

static void resize(int width, int height) {
    glClearColor(0.0, 0.0, 0.0, 0.0);         // black background
    glMatrixMode(GL_PROJECTION);              // setup viewing projection
    glLoadIdentity();                           // start with identity matrix
    glOrtho(0.0, 80.0, 0.0, 80.0, -1.0, 1.0);   // setup a 40x40x2 viewing world
    // glOrtho(0.0, width * SCALE, 0.0, height * SCALE, -1.0, 1.0);   // setup a dynanically sized viewing world
}

void register_collisions() {
	chrono::_V2::system_clock::time_point check_collision_timer = std::chrono::high_resolution_clock::now();
	// First check boundary box
	for (int i = 0; i < 4; i++) {
		if (main_player->check_collision(boundary_box[i])) {
			// cout << main_player->get_time_since_boundary_collision(check_collision_timer) << endl;
			if (main_player->get_last_collided_boundary() != i || main_player->get_time_since_boundary_collision(check_collision_timer) > 300000000) {
				out_of_bounds_counter++;
				cout << "OUT OF BOUNDS " << out_of_bounds_counter << endl;
				main_player->bounce(i);
				main_player->set_last_collided_boundary(i);
			}
		}
	}
	// Check if player out of bounds
	// if (main_player->check_collision)
}


// What to display
static void display(void)
{
	frame_counter++;
	if (frame_counter == 100) {
		// std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end_timer-start_timer).count() << "ns" << std::endl;
		register_collisions();
		frame_counter = 0;
	}
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// drawLineDDA({0, 160}, {160, 160}, {0.3, 0.2, 0.1});
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
			main_player->rotate('l', 'n');
			break;
		case 's':
			// main_player->bounce();
			break;
		case 'd':
			main_player->rotate('r', 'n');
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
	
	main_player = new Player({player_sprite_cockpit, player_sprite_body, player_sprite_left_wing, player_sprite_right_wing});
	*/
	vector<point> player_sprite_cockpit_points = {
				{0, 6},
		{-2, 2}, 	   {2, 2}
	};
	Polygon player_sprite_cockpit (player_sprite_cockpit_points, {10, 10});
	player_sprite_cockpit.set_colour({0.1, 0.2, 0.3});

	vector<point> player_sprite_body_points = {
			   {-2, 2}, 	   					{2, 2},
		{-6, 0},										{6, 0}
	};
	Polygon player_sprite_body (player_sprite_body_points, {10, 10});

	// vector<point> player_sprite_body_booster_points = {
	// 	{-2, 0},	 	{2, 0},
	// 			{0, -6}
	// };
	// Polygon player_sprite_body_booster (player_sprite_body_booster_points, {10, 10});
	// player_sprite_body_booster.set_colour({0.8, 0.1, 0.4});


	// vector<point> player_sprite_left_wing_points = {
	// 	{-6, 0}, 		{-2, 0},
	// 			{-4, -4}
	// };
	// Polygon player_sprite_left_wing (player_sprite_left_wing_points, {10, 10});
	// player_sprite_left_wing.set_colour({0.8, 0.2, 0.1});

	// vector<point> player_sprite_right_wing_points = {
	// 	{2, 0}, 		{6, 0},
	// 			{4, -4}
	// };
	// Polygon player_sprite_right_wing (player_sprite_right_wing_points, {10, 10});
	// player_sprite_right_wing.set_colour({0.8, 0.2, 0.1});
	vector<point> player_sprite_boosters_points = {
		{-6, 0}, {-4, -4}, {-2, 0}, {-2, 0}, {0, -6}, {2, 0}, {2, 0}, {4, -4}, {6, 0},
	};
	Polygon player_sprite_boosters(player_sprite_boosters_points, {10, 10});
	player_sprite_boosters.set_colour({0.8, 0.2, 0.1});

	main_player = new Player({player_sprite_cockpit, player_sprite_body, player_sprite_boosters});
	// vector<point> triangle_points = { {0, 3}, {-3, -3}, { 3, -3} };
	// vector<point> square_points = {{-3, -3}, {3, -3}, {-3, -5}, {3, -5}};

	// Polygon triangle (triangle_points);
	// Polygon square (square_points);
	// main_player = new Player({triangle, square});

	
    glutInit(&argc, argv);
    glutInitWindowSize(800,800); // Size of the window (not including decorations, just usable space)
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
