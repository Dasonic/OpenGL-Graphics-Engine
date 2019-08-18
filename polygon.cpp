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
	matrix transform_matrix(4, 4);
	
	transform_matrix.set_row(0, {1, 0, 0, (double)coordinates.x});
	transform_matrix.set_row(1, {0, 1, 0, (double)coordinates.y});
	transform_matrix.set_row(2, {0, 0, 1, 0});
	transform_matrix.set_row(3, {0, 0, 0, 1});

	transformation_matrix_list.push_back(transform_matrix);

	coords = new matrix(4, 1);
	coords->set_col(0, {(double)coordinates.x, (double)coordinates.y, 1, 1});
}

void Polygon::set_colour(colour RGB) {
	fill_colour = RGB;
}

void Polygon::draw() {
	matrix ts(4, 4);

	std::vector<point> new_points;
	// cout << "---------------" << endl;
	for (int i = 0; i < point_list.size(); i++) {
		// Convert point to matrix
		matrix temp_point(4, 1);
		temp_point.set_col(0, {(double)point_list[i].x, (double)point_list[i].y, 1, 1});
		// Apply transformation to co-ords
		matrix use_point(4, 1);
		use_point = transformation_matrix_list.back().multiply(temp_point);
		// cout << "--" << endl;
		// use_point.print();
		// Add transformed points to vector
		new_points.push_back({(int)use_point.get_val(0, 0), (int)use_point.get_val(1, 0)});
	}
	// Draw polygon using transformed points
	drawPolygon(new_points, fill_colour);
}
void Polygon::scale(int x_scale, int y_scale) {
	matrix transform_matrix(4, 4);
	transform_matrix.set_up_transformation();
	transform_matrix.set_val(0, 0, x_scale);
	transform_matrix.set_val(1, 1, y_scale);
	transform(transform_matrix);
}

void Polygon::rotate(double angle) {
	matrix transform_matrix(4, 4);
	transform_matrix.set_up_transformation();
	// Convert degrees to radians
	double theta = angle * (M_PI / 180);
	double cos_theta = cos(theta);
	double sin_theta = sin(theta);
	// Set values in matrix
	transform_matrix.set_val(0, 0, cos_theta);
	transform_matrix.set_val(0, 1, -sin_theta);
	transform_matrix.set_val(1, 0, sin_theta);
	transform_matrix.set_val(1, 1, cos_theta);
	// transform_matrix.print();
	transform(transform_matrix);
}

void Polygon::translate(int x_offset, int y_offset) {
	matrix transform_matrix(4, 4);
	transform_matrix.set_up_transformation();
	transform_matrix.set_col(3, {(double)x_offset, (double)y_offset, 1, 1});
	transform(transform_matrix);
}

void Polygon::transform(matrix transform_matrix) {
	// transformation_matrix_list.push_back(transform_matrix.multiply(transformation_matrix_list.back()));
	// cout << "---------------" << endl;
	// transformation_matrix_list.back().print();
	// cout << "*" << endl;
	// transform_matrix.print();
	// cout << "=" << endl;
	matrix temp(4, 4);
	temp = transformation_matrix_list.back().multiply(transform_matrix);
	// temp.print();
	transformation_matrix_list.push_back(temp);
	// transformation_matrix_list.back().print();
	
}