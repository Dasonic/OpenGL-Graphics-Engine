#ifndef polygon_h
#define polygon_h
	#include <vector>
	#include "matrix.h"
	#include "structs.h"

	class Polygon {
		protected:
			std::vector<std::vector<Point>> all_points;
			std::vector<std::vector<Point>> transformed_points;
			matrix transform_matrix;
			matrix rotate_matrix;
			colour get_colour(double height);
		public:
			Polygon(std::vector<std::vector<Point>> points, Point middle);
			void draw();
			void rotate(double angle_x, double angle_y);
			void apply_transformations();

	};
#endif