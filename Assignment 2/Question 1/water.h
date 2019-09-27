#ifndef water_h
#define water_h
	#include <vector>
	#include "Polygon.h"
	class water : public Polygon {
		colour get_colour(double height);
		int lowest_point = 0;
		public:
			water(std::vector<std::vector<Point>> points, Point middle) : Polygon(points, middle) {}
			void set_water_level(int level);
			void set_lowest_point(int point);
			void draw();
	};
#endif