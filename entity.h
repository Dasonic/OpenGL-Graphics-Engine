#ifndef entity_h
#define entity_h
	#include <vector>
	#include <chrono>
	#include "polygon.h"
	#include "structs.h"

	#define ROUND(x) ((int)(x + 0.5))
	#define EPSILON 0.0001
	#define ROTATION_SPEED 15

	class Entity {
		protected:
			double direction_facing, acceleration_value, max_speed, min_speed, drag = 0;
			velocity travel;
			std::vector<Polygon> sprite;
			rectangle collision_box;
			point middle_point;
			std::chrono::_V2::system_clock::time_point last_collission_time;
			int last_collission_boundary;
		public:
			void draw();
			void accelerate();
			void decelerate();
			void rotate(char direction);
			void bounce(char boundary);
			void destroy();
			rectangle get_collision_box();
			bool check_collision(rectangle other_entity);
			void refresh_collision_box();
			void set_last_collided_boundary(int boundary);
			int get_last_collided_boundary();
			long get_time_since_boundary_collision(std::chrono::_V2::system_clock::time_point current_time);
	};

#endif