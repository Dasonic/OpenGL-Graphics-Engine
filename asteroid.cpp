#include "asteroid.h"

#include <ctime>
#include <chrono>
// #include <limits>
#include <stdlib.h>

Asteroid::Asteroid(std::vector<Polygon> graphic) {
	sprite = graphic;
	movement_speed = 0.025;
	max_speed = 0.025;
	min_speed = 0.020;
	drag = 1;
	last_collission_boundary = -1;

	srand(time(NULL));
	id = rand() % UINT32_MAX;
	asteroid_last_collission_time = std::chrono::high_resolution_clock::now();
	last_asteroid_collided_with_id = 0;
	randomise_direction();
	return;
}

void Asteroid::randomise_direction() {
	int turn_times = rand() % 8; // Generate number between 0 and 7
	for (int i = 0; i < turn_times; i ++) { // Rotate the asteroid turn_times times
		rotate('r', 'n');
	}
	return;
}

void Asteroid::set_asteroid_collided_id(unsigned int collided_id) {
	last_asteroid_collided_with_id = collided_id;
	asteroid_last_collission_time = std::chrono::high_resolution_clock::now();
	return;
}

unsigned int Asteroid::get_asteroid_id() {
	return id;
}

unsigned int Asteroid::get_asteroid_collided_id() {
	return last_asteroid_collided_with_id;
}

long Asteroid::get_time_since_asteroid_collision(std::chrono::_V2::system_clock::time_point current_time) {
	return std::chrono::duration_cast<std::chrono::nanoseconds>(current_time-asteroid_last_collission_time).count();
}