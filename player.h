#ifndef player_h
#define player_h
	#include <vector>
	#include "entity.h"
	#include "polygon.h"
	#include "structs.h"
	class Player: public Entity {
		private:
			int hp;
		public:
			Player(std::vector<Polygon> graphic);
	};

#endif