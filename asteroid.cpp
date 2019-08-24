#include "asteroid.h"

#include <ctime>
#include <stdlib.h>

Asteroid::Asteroid(std::vector<Polygon> graphic) {
	sprite = graphic;
	movement_speed = 0.025;
	max_speed = 0.025;
	min_speed = 0.020;
	drag = 1;
	last_collission_boundary = -1;

	srand(time(NULL));
	randomise_direction();
}

void Asteroid::randomise_direction() {
	int turn_times = rand() % 8; // Generate number between 0 and 7
	for (int i = 0; i < turn_times; i ++) { // Rotate the asteroid turn_times times
		rotate('r', 'n');
	}
}