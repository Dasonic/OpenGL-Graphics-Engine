#ifndef entity_h
#define entity_h
	#include <vector>
	#include "polygon.h"
	#include "structs.h"
	class Entity {
		protected:
			double direction_facing = 0;
			direction_angle momentum = {0, 0};
			double movement_speed = 0;
			std::vector<Polygon> sprite;
			double rotation_speed = 0;
		public:
			void draw();
			void accelerate();
			void rotate(char direction);
			void destroy();
	};

#endif