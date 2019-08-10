#ifndef polygon_h
#define polygon_h
	#include <vector>
	#include "matrix.h"
	#include "structs.h"
	class Polygon {
		std::vector<point> point_list;
		matrix *transform_matrix;
		// matrix *coords;
		colour fill_colour;
		public:
			Polygon(std::vector<point> points, point coordinates);
			void set_colour(colour RGB);
			void draw();
			void scale(int x_scale, int y_scale);
			void rotate();
			void translate(int x_offset, int y_offset);

	};
#endif