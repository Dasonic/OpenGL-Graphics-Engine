#include <vector>
#include <iostream>
#include <cmath>

#include "polygon.h"
#include "structs.h"
#include "matrix.h"
#include "draw_commands.h"

using namespace std;

Polygon::Polygon(std::vector<point> points, point coordinates) {
	point_list = points;
	fill_colour = {1, 1, 1};
	transform_matrix = new matrix(4, 4);
	transform_matrix->set_row(0, {1, 0, 0, (double)coordinates.x});
	transform_matrix->set_row(1, {0, 1, 0, (double)coordinates.y});
	transform_matrix->set_row(2, {0, 0, 1, 0});
	transform_matrix->set_row(3, {0, 0, 0, 1});

	scale_matrix = new matrix(4, 4);
	coords = new matrix(4, 1);
	coords->set_col(0, {(double)coordinates.x, (double)coordinates.y, 1, 1});
}

void Polygon::set_colour(colour RGB) {
	fill_colour = RGB;
}
void Polygon::draw() {
	matrix ts(4, 4);

	std::vector<point> new_points;
	for (int i = 0; i < point_list.size(); i++) {
		// Convert point to matrix
		matrix temp_point(4, 1);
		temp_point.set_col(0, {(double)point_list[i].x, (double)point_list[i].y, 1, 1});
		// Apply transformation to co-ords
		matrix use_point(4, 1);
		if (scale_matrix->get_val(0, 0) == 0) // If no scale values
			use_point = transform_matrix->multiply(temp_point);
		else {
			ts = scale_matrix->multiply(*transform_matrix);
			use_point = ts.multiply(temp_point);
			// use_point.print();
			// cout << endl;
		}
		// Add transformed points to vector
		new_points.push_back({(int)use_point.get_val(0, 0), (int)use_point.get_val(1, 0)});
	}
	// Draw polygon using transformed points
	drawPolygon(new_points, fill_colour);
}
void Polygon::scale(int x_scale, int y_scale) {
	// transform_matrix->set_val(0, 0, x_scale);
	// transform_matrix->set_val(1, 1, y_scale);

	int x = transform_matrix->get_val(0, 3);
	int y = transform_matrix->get_val(1, 3);

	scale_matrix->set_row(0, {(double)x_scale, 0, 0, (double)(1 - x_scale) * x});
	scale_matrix->set_row(1, {0, (double)y_scale, 0, (double)(1 - y_scale) * y});
	scale_matrix->set_row(2, {0, 0, 1, 0});
	scale_matrix->set_row(3, {0, 0, 0, 1});

	// int x = transform_matrix->get_val(0, 3);
	// int y = transform_matrix->get_val(1, 3);
	// transform_matrix->set_col(3, {(1 - x_scale) * x, (1 - y_scale) * y, 1, 1});
	// transform_matrix->print();
}
void Polygon::rotate(double angle) {
	double theta = angle * (M_PI / 180);
	double cos_theta = cos(theta);
	double sin_theta = sin(theta);
	// cout << cos_theta << endl;
	transform_matrix->set_val(0, 0, cos_theta);
	transform_matrix->set_val(0, 1, -sin_theta);
	transform_matrix->set_val(1, 0, sin_theta);
	transform_matrix->set_val(1, 1, cos_theta);
	// transform_matrix->print();
}
void Polygon::translate(int x_offset, int y_offset) {
	transform_matrix->set_col(3, {(double)x_offset, (double)y_offset, 1, 1});
}
