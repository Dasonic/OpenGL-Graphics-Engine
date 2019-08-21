#include "player.h"


Player::Player(std::vector<Polygon> graphic) {
	sprite = graphic;
	movement_speed = 1;
	rotation_speed = 1;
	hp = 20;
}