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
	last_used_point_list = points;
	fill_colour = {1, 1, 1};
	matrix transform_matrix(4, 4);
	
	transform_matrix.set_row(0, {1, 0, 0, (double)coordinates.x});
	transform_matrix.set_row(1, {0, 1, 0, (double)coordinates.y});
	transform_matrix.set_row(2, {0, 0, 1, 0});
	transform_matrix.set_row(3, {0, 0, 0, 1});

	transformation_matrix_list.push_back(transform_matrix);
}

Polygon::Polygon(std::vector<point> points)
:	Polygon(points, {0, 0})
{}

Polygon::Polygon()
:	Polygon({{0, 0}})
{}

void Polygon::change_points(std::vector<point> points) {
	point_list = points;
	last_used_point_list = points;
}

void Polygon::set_colour(colour RGB) {
	fill_colour = RGB;
}

void Polygon::draw() {
	matrix ts(4, 4);
	last_used_point_list.clear();
	
	for (int i = 0; i < point_list.size(); i++) {
		// Convert point to matrix
		matrix temp_point(4, 1);
		temp_point.set_col(0, {(double)point_list[i].x, (double)point_list[i].y, 1, 1});
		// Apply transformation to co-ords
		matrix use_point(4, 1);
		use_point = transformation_matrix_list.back().multiply(temp_point);
		// Add transformed points to vector
		last_used_point_list.push_back({(int)use_point.get_val(0, 0), (int)use_point.get_val(1, 0)});
	}
	// Draw polygon using transformed points
	drawPolygon(last_used_point_list, fill_colour);
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

void Polygon::translate(double x_offset, double y_offset) {
	matrix transform_matrix(4, 4);
	transform_matrix.set_up_transformation();
	transform_matrix.set_col(3, {x_offset, y_offset, 1, 1});
	transform(transform_matrix);
}

void Polygon::transform(matrix transform_matrix) {
	matrix temp(4, 4);
	temp = transformation_matrix_list.back().multiply(transform_matrix);
	transformation_matrix_list.push_back(temp);
}

// Finds the smallest x value and the highest y value
point Polygon::find_top_left_point() {
	point top_left = {999999, -999999}; 
	for (int i = 0; i < last_used_point_list.size(); i ++) {
		if (last_used_point_list[i].x < top_left.x)
			top_left.x = last_used_point_list[i].x;
		if (last_used_point_list[i].y > top_left.y)
			top_left.y = last_used_point_list[i].y;
	}
	return top_left;
}

// Finds the highest x value and the lowest y value
point Polygon::find_bottom_right_point() {
	point bottom_right = {-999999, 999999};
	for (int i = 0; i < last_used_point_list.size(); i ++) {
		if (last_used_point_list[i].x > bottom_right.x)
			bottom_right.x = last_used_point_list[i].x;
		if (last_used_point_list[i].y < bottom_right.y)
			bottom_right.y = last_used_point_list[i].y;
	}
	return bottom_right;
}

void Polygon::undo_transformation() {
	transformation_matrix_list.pop_back();
	return;
}