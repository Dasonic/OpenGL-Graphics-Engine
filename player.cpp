#include <chrono>
#include "player.h"

Player::Player(std::vector<Polygon> graphic) {
	sprite = graphic;
	acceleration_value = 0.025;
	movement_speed = 0;
	max_speed = 0.07;
	rotation_speed = 45;
	hp = 20;
	drag = 0.999;
	last_collission_boundary = -1;

	return;
}