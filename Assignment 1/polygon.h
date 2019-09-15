#ifndef polygon_h
#define polygon_h
	#include <vector>
	#include "matrix.h"
	#include "structs.h"

	class Polygon {
		std::vector<point> point_list;
		std::vector<point> last_used_point_list;
		matrix transform_matrix;
		matrix rotate_matrix;
		std::vector<matrix> transformation_matrix_list;
		colour fill_colour;
		public:
			Polygon(std::vector<point> points, point coordinates);
			Polygon(std::vector<point> points);
			Polygon();
			void change_points(std::vector<point> points);
			void set_colour(colour RGB);
			void draw();
			void scale(int x_scale, int y_scale);
			void rotate(double angle);
			void additive_rotate(double angle);
			void translate(double x_offset, double y_offset);
			void additive_translate(double x_offset, double y_offset);
			void save_transformation();
			void undo_transformation();
			point find_top_left_point();
			point find_bottom_right_point();
	};
#endif