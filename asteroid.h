#ifndef asteroid_h
#define asteroid_h
	#include <vector>
	#include <chrono>
	#include "entity.h"
	#include "polygon.h"
	#include "structs.h"
	class Asteroid: public Entity {
		private:
			unsigned int id;
			unsigned int last_asteroid_collided_with_id;
			std::chrono::_V2::system_clock::time_point asteroid_last_collission_time;
		public:
			Asteroid(std::vector<Polygon> graphic);
			void randomise_direction();
			void set_asteroid_collided_id(unsigned int collided_id);
			unsigned int get_asteroid_id();
			unsigned int get_asteroid_collided_id();
			long get_time_since_asteroid_collision(std::chrono::_V2::system_clock::time_point current_time);
	};

#endif