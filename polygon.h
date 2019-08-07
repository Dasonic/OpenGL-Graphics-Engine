#ifndef polygon_h
#define polygon_h
	#include <vector>
	#include "matrix.h"
	#include "structs.h"
	class Polygon {
		std::vector<point> point_list;
		matrix transform();
		colour fill_colour;
		public:
			Polygon(std::vector<point> points);
			void set_colour(colour RGB);
			void draw();
			void scale();
			void rotate();
			void translate();

	};
#endif