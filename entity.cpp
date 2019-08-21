#include "entity.h"
#include <cmath>
#include <iostream>

void Entity::draw() {
	// move();
	for (int i = 0; i < sprite.size(); i ++) {
		sprite[i].draw();
	}
	return;
}

void Entity::accelerate() {
	momentum.angle = direction_facing;
	momentum.speed += movement_speed;

	/// Convert speed to x and y
	double x = sin(momentum.angle) * momentum.speed;
	double y = cos(momentum.angle) * momentum.speed;

	std::cout << "x: " << x << " y: " << y << std::endl;
	for (int i = 0; i < sprite.size(); i++) {
		sprite[i].translate(x, y);
	}

	return;
}

void Entity::rotate(char direction) {
	// If rotating left, subtract from direction
	if (direction == 'l')
		direction_facing -= rotation_speed;
	// If rotating right, add to direction
	else if (direction == 'r')
		direction_facing += rotation_speed;
	
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


void Entity::destroy() {

}