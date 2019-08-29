#include "asteroid.h"

#include <ctime>
#include <chrono>
#include <cmath>
// #include <limits>
#include <stdlib.h>
#include <iostream>

Asteroid::Asteroid(std::vector<Polygon> graphic) {
	sprite = graphic;
	travel = {0, 0, 0};
	max_speed = 0.025;
	min_speed = 0.000;
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
	double travel_direction = rand() % 360; // Generate number between 0 and 360

	// Break acceleration force into x and y values
	double theta = travel_direction * (M_PI / 180);
	double x = sin(theta) * max_speed;
	double y = cos(theta) * max_speed;

	// Calculate speed
	travel.speed = sqrt(pow(x, 2) + pow(y, 2));
	// std::cout << travel.speed << std::endl;
	travel.x = x;
	travel.y = y;
	if (travel.speed < min_speed + EPSILON)
		randomise_direction();
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

void Asteroid::collision_bounce() {
	if (abs(travel.x) > abs(travel.y))
		travel.x = -travel.x;
	else
		travel.y = -travel.y;
	return;
}