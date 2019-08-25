#include <GL/glut.h>
#include <stdlib.h>
#include <time.h> 
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <list>

#include "matrix.h"
#include "structs.h"
#include "draw_commands.h"
#include "polygon.h"
#include "player.h"
#include "asteroid.h"

using namespace std;

#define MIN_TIME_SINCE_COLLISION 300000000

int frame_counter = 0;
Player* main_player;
list<Asteroid> asteroids = {};
const rectangle boundary_box[] = {{{0, 165}, {160, 159}}, {{0, 1}, {160, -5}}, {{-5, 160}, {1, 0}}, {{159, 160}, {165, 0}}};
int score = 0;

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
		// If the boundary is different to the last one the player collided with or a set amount of time has passed (prevents detecting same collision more than once)
		if (main_player->get_last_collided_boundary() != i || main_player->get_time_since_boundary_collision(check_collision_timer) > MIN_TIME_SINCE_COLLISION) {
			if (main_player->check_collision(boundary_box[i])) {
				main_player->bounce(i);
				main_player->set_last_collided_boundary(i);
			}
		}
		// Check asteroids
		for (list<Asteroid>::iterator asteroid=asteroids.begin(); asteroid != asteroids.end(); ++asteroid) {
			// If the boundary is different to the last one the asteroid collided with or a set amount of time has passed (prevents detecting same collision more than once)
			if (asteroid->get_last_collided_boundary() != i || asteroid->get_time_since_boundary_collision(check_collision_timer) > MIN_TIME_SINCE_COLLISION) {
				if (asteroid->check_collision(boundary_box[i])) {
					asteroid->bounce(i);
					asteroid->set_last_collided_boundary(i);
					break;
				}
			}
		}
	}
	// Check collision with asteroids
	for (list<Asteroid>::iterator asteroid=asteroids.begin(); asteroid != asteroids.end(); ++asteroid) {
		if (main_player->check_collision(asteroid->get_collision_box())) {
			// Destroy asteroid
			asteroid->destroy();
			asteroids.erase(asteroid++);
			score++;
		}
		for (list<Asteroid>::iterator other_asteroid=asteroids.begin(); other_asteroid != asteroids.end(); ++other_asteroid) {
			if (asteroid->get_asteroid_collided_id() != other_asteroid->get_asteroid_id() || (asteroid->get_asteroid_collided_id() == other_asteroid->get_asteroid_id() && asteroid->get_time_since_asteroid_collision(check_collision_timer)) > MIN_TIME_SINCE_COLLISION * 2) {
				if (asteroid->check_collision(other_asteroid->get_collision_box())) {
					asteroid->rotate('a', -1);
					other_asteroid->rotate('a', -1);
					asteroid->set_asteroid_collided_id(other_asteroid->get_asteroid_id());
					other_asteroid->set_asteroid_collided_id(asteroid->get_asteroid_id());
				}
			}
		}
	}

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

	// Generate new asteroid
	if (rand()%10000 == 0) {
		vector<point> asteroid_graphic = {{-3, 3}, {3, 3}, {3, -3}, {-3, -3}};
		Polygon temp_asteroid (asteroid_graphic, {50, 50});
		Asteroid test_asteroid({temp_asteroid});
		asteroids.push_back(test_asteroid);
	}

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Draw the player
	main_player->draw();
	// Draw the asteroids
	for (list<Asteroid>::iterator asteroid=asteroids.begin(); asteroid != asteroids.end(); ++asteroid) {
		asteroid->draw();
	}
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

	vector<point> player_sprite_boosters_points = {
		{-6, 0}, {-4, -4}, {-2, 0}, {-2, 0}, {0, -6}, {2, 0}, {2, 0}, {4, -4}, {6, 0},
	};
	Polygon player_sprite_boosters(player_sprite_boosters_points, {10, 10});
	player_sprite_boosters.set_colour({0.8, 0.2, 0.1});

	main_player = new Player({player_sprite_cockpit, player_sprite_body, player_sprite_boosters});

	srand(time(NULL));
	
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
