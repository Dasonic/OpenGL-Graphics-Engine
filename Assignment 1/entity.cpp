#include "entity.h"
#include <cmath>
#include <iostream>
#include <chrono>

#include "draw_commands.h"

using namespace std;

void Entity::draw() {

	if (travel.speed - EPSILON > min_speed) {
		for (int i = 0; i < sprite.size(); i++) {
			sprite[i].additive_translate(travel.x, travel.y);
		}
	}

	// Move collission box
	refresh_collision_box();

	for (int i = 0; i < sprite.size(); i ++) {
		sprite[i].draw();
	}
	return;
}

void Entity::accelerate() {
	// Break acceleration force into x and y values
	double theta = direction_facing * (M_PI / 180);
	double x = travel.x - sin(theta) * acceleration_value;
	double y = travel.y + cos(theta) * acceleration_value;

	// Calculate speed
	double speed = sqrt(pow(x, 2) + pow(y, 2));

	if (speed <= max_speed) {
		travel.x = x;
		travel.y = y;
		travel.speed = speed;
	}

	return;
}

void Entity::decelerate() {
	if (travel.speed - EPSILON > min_speed) {
		travel.x *= drag;
		travel.y *= drag;
		travel.speed = sqrt(pow(travel.x, 2) + pow(travel.y, 2));
	} else {
		travel.x = 0;
		travel.y = 0;
		travel.speed = 0;
	}
	return;
}

void Entity::rotate(char direction) {
	// If rotating left, subtract from direction
	if (direction == 'l')
		direction_facing += ROTATION_SPEED;
	// If rotating right, add to direction
	else if (direction == 'r')
		direction_facing -= ROTATION_SPEED;
	else if (direction == 'a') // Asteroid
		direction_facing += 0.1;
	// Make sure direction lays between 0 and 360
	if (direction_facing >= 360)
		direction_facing -= 360;
	else if (direction_facing < 0)
		direction_facing += 360;
	for (int i = 0; i < sprite.size(); i++) {
		sprite[i].rotate(direction_facing);
	}

	return;
}

void Entity::bounce(char boundary) {
	if (boundary == 0 && travel.y > 0 || boundary == 1 && travel.y < 0) // Top/Bottom Boundary
			travel.y = -travel.y;
	else if (boundary == 2 && travel.x < 0 || boundary == 3 && travel.x > 0) // Left/Right Boundary
		travel.x = -travel.x;
	return;
}

void Entity::destroy() {

}

rectangle Entity::get_collision_box() {
	return collision_box;
}

bool Entity::check_collision(rectangle other_entity) {
	if (collision_box.top_left.x > other_entity.bottom_right.x ||
		other_entity.top_left.x > collision_box.bottom_right.x)
		return false;
	if (collision_box.top_left.y < other_entity.bottom_right.y ||
		other_entity.top_left.y < collision_box.bottom_right.y)
		return false;
	return true;
}

void Entity::refresh_collision_box() {
	// Set up collision box
	point top_left = {999999, -999999}; // top left will be the point with the lowest x but highest y
	point bottom_right = {-999999, 999999}; // bottom right will be the point with the highest x but lowest y
	for (int i = 0; i < sprite.size(); i++) {
		point sprite_top_left = sprite[i].find_top_left_point();
		point sprite_bottom_right = sprite[i].find_bottom_right_point();
		if (sprite_top_left.x <= top_left.x)
			top_left.x = sprite_top_left.x;
		if (sprite_top_left.y >= top_left.y)
			top_left.y = sprite_top_left.y;
		if (sprite_bottom_right.x >= bottom_right.x)
			bottom_right.x = sprite_bottom_right.x;
		if (sprite_bottom_right.y <= bottom_right.y)
			bottom_right.y = sprite_bottom_right.y;
	}
	collision_box = {top_left, bottom_right};
}

void Entity::set_last_collided_boundary(int boundary) {
	last_collission_boundary = boundary;
	last_collission_time = chrono::high_resolution_clock::now();
	return;
}

int Entity::get_last_collided_boundary() {
	return last_collission_boundary;
}

long Entity::get_time_since_boundary_collision(chrono::_V2::system_clock::time_point current_time) {
	return chrono::duration_cast<chrono::nanoseconds>(current_time-last_collission_time).count();
}