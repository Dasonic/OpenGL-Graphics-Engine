#include <chrono>
#include "player.h"

Player::Player(std::vector<Polygon> graphic) {
	sprite = graphic;
	acceleration_value = 0.025;
	travel = {0, 0, 0};
	max_speed = 0.005;
	drag = 0.5;
	last_collission_boundary = -1;

	return;
}