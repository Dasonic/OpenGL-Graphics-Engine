#ifndef asteroid_h
#define asteroid_h
	#include <vector>
	#include "entity.h"
	#include "polygon.h"
	#include "structs.h"
	class Asteroid: public Entity {
		public:
			Asteroid(std::vector<Polygon> graphic);
			void randomise_direction();
	};

#endif