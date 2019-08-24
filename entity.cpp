#include "entity.h"
#include <cmath>
#include <iostream>
#include <chrono>

#include "draw_commands.h"

using namespace std;

void Entity::draw() {

	if (movement_speed - EPSILON > min_speed) {
		for (int i = 0; i < sprite.size(); i++) {
			sprite[i].translate(0, movement_speed);
		}
		movement_speed *= drag;
	}

	// Move collission box
	refresh_collision_box();
	// std::cout << collision_box.top_left.x << ", " << collision_box.top_left.y << std::endl;
	drawLineDDA(collision_box.top_left, collision_box.bottom_right, {0.3, 0.2, 0.1});

	for (int i = 0; i < sprite.size(); i ++) {
		sprite[i].draw();
	}
	return;
}

void Entity::accelerate() {
	// cout << direction_facing << endl;
	if (movement_speed + acceleration_value <= max_speed)
		movement_speed += acceleration_value;

	return;
}

void Entity::decelerate() {
	movement_speed = movement_speed * (drag - 0.2);

	return;
}

void Entity::rotate(char direction, int boundary) {
	// If rotating left, subtract from direction
	if (direction == 'l')
		direction_facing += ROTATION_SPEED;
	// If rotating right, add to direction
	else if (direction == 'r')
		direction_facing -= ROTATION_SPEED;
	// If bouncing back, flip direction
	else if (direction == 'b')
		if (direction_facing == 0 || direction_facing == 90 || direction_facing == 180 || direction_facing == 270)
			direction_facing += 180;
		// Special cases where the ship needs to flip the other way
		else if (boundary == 0 && direction_facing == 315)
			direction_facing -= 90;
		else if (boundary == 1 && direction_facing == 135)
			direction_facing -= 90;
		else if (boundary == 2 && direction_facing == 45)
			direction_facing -= 90;
		else if (boundary == 3 && direction_facing == 225)
			direction_facing -= 90;
		else
			direction_facing += 90;
	// Make sure direction lays between 0 and 360
	if (direction_facing >= 360)
		direction_facing -= 360;
	else if (direction_facing < 0)
		direction_facing += 360;

	
	for (int i = 0; i < sprite.size(); i++) {
		if (direction == 'l')
			sprite[i].rotate(ROTATION_SPEED);
		else if (direction == 'r')
			sprite[i].rotate(-ROTATION_SPEED);
		// If bouncing back, flip direction
		else if (direction == 'b') {
			if (direction_facing == 0 || direction_facing == 90 || direction_facing == 180 || direction_facing == 270)
				sprite[i].rotate(180);
			// Special cases where the ship needs to flip the other way
			else if (boundary == 0 && direction_facing == 225)
				sprite[i].rotate(-90);
			else if (boundary == 1 && direction_facing == 45)
				sprite[i].rotate(-90);
			else if (boundary == 2 && direction_facing == 315)
				sprite[i].rotate(-90);
			else if (boundary == 3 && direction_facing == 135)
				sprite[i].rotate(-90);
			else
				sprite[i].rotate(90);
		}
	}

	return;
}

void Entity::bounce(char boundary) {
	rotate('b', boundary);
	accelerate();
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
}

int Entity::get_last_collided_boundary() {
	return last_collission_boundary;
}

long Entity::get_time_since_boundary_collision(chrono::_V2::system_clock::time_point current_time) {
	return chrono::duration_cast<chrono::nanoseconds>(current_time-last_collission_time).count();
}