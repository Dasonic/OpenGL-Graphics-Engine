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
	matrix transformation_matrix(4, 4);
	
	transformation_matrix.set_row(0, {1, 0, 0, (double)coordinates.x});
	transformation_matrix.set_row(1, {0, 1, 0, (double)coordinates.y});
	transformation_matrix.set_row(2, {0, 0, 1, 0});
	transformation_matrix.set_row(3, {0, 0, 0, 1});

	current_matrix = transformation_matrix;
	rotate_matrix.set_up_transformation();
	transform_matrix = transformation_matrix;

	// current_matrices.push_back(transform_matrix); // Translate matrix
	// current_matrices.push_back(transform_matrix);  // Rotate matrix
	// current_matrices.push_back(transform_matrix);  // Scale matrix
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
	// apply_transform();
	// current_matrix.print();
	matrix ts(4, 4);
	last_used_point_list.clear();
	// Multiply translate, rotate and scale matrices
	// matrix total_matrix(4, 4);
	// total_matrix = current_matrices[2].multiply(current_matrices[1].multiply(current_matrices[0]));
	// total_matrix.print();
	
	// Transform all points
	for (int i = 0; i < point_list.size(); i++) {
		// Convert point to matrix
		matrix temp_point(4, 1);
		temp_point.set_col(0, {(double)point_list[i].x, (double)point_list[i].y, 1, 1});
		// Apply transformation to co-ords
		matrix use_point(4, 1);
		// use_point = total_matrix.multiply(temp_point);
		use_point = rotate_matrix.multiply(temp_point);
		use_point.add_val(0, 0, transform_matrix.get_val(0, 3));
		use_point.add_val(1, 0, transform_matrix.get_val(1, 3));
		// use_point = transform_matrix.multiply(use_point);
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
	// apply_transform(transform_matrix, 2);
}

void Polygon::rotate(double angle) {
	matrix transformation_matrix(4, 4);
	// transformation_matrix.set_up_transformation();
	// Convert degrees to radians
	double theta = angle * (M_PI / 180);
	double cos_theta = cos(theta);
	double sin_theta = sin(theta);
	// Set values in matrix
	transformation_matrix.set_val(0, 0, cos_theta);
	transformation_matrix.set_val(0, 1, -sin_theta);
	transformation_matrix.set_val(1, 0, sin_theta);
	transformation_matrix.set_val(1, 1, cos_theta);
	// transformation_matrix.set_col(3, {40, 40, 1, 1});
	// transformation_matrix.print();
	// apply_transform(transformation_matrix, 1);
	rotate_matrix = transformation_matrix;
}

void Polygon::additive_rotate(double angle) {
	matrix transformation_matrix(4, 4);
	transformation_matrix.set_up_transformation();

	double theta = angle * (M_PI / 180);
	double cos_theta = cos(theta);
	double sin_theta = sin(theta);

	matrix * rotate_matrix_ptr = &rotate_matrix;
	// rotate_matrix.print();

	double tl = rotate_matrix_ptr->get_val(0, 0) + cos_theta;
	double tr = rotate_matrix_ptr->get_val(0, 1) - sin_theta;
	double bl = rotate_matrix_ptr->get_val(1, 0) + sin_theta;
	double br = rotate_matrix_ptr->get_val(1, 1) - cos_theta;

	transformation_matrix.set_val(0, 0, tl);
	transformation_matrix.set_val(0, 1, tr);
	transformation_matrix.set_val(1, 0, bl);
	transformation_matrix.set_val(1, 1, br);

	transformation_matrix.set_col(3, {20, 20, 1, 1});

	rotate_matrix = transformation_matrix;
	// apply_transform(transform_matrix, 1);

	return;
}

void Polygon::translate(double x_offset, double y_offset) {
	matrix transformation_matrix(4, 4);
	transformation_matrix.set_up_transformation();
	transformation_matrix.set_col(3, {x_offset, y_offset, 1, 1});
	transform_matrix = transformation_matrix;
	// apply_transform(transform_matrix, 0);
}

void Polygon::additive_translate(double x_offset, double y_offset) {
	// Get current x and y
	matrix * translate_matrix_ptr = &transform_matrix;
	double x = translate_matrix_ptr->get_val(0, 3);
	double y = translate_matrix_ptr->get_val(1, 3);
	x += x_offset;
	y += y_offset;
	translate(x, y);
	return;
}

void Polygon::apply_transform() {
	matrix temp(4, 4);
	// rotate_matrix.print();
	// cout << "+" << endl;
	// transform_matrix.print();
	// cout << "=" << endl;
	temp = transform_matrix.multiply(rotate_matrix);
	// temp = rotate_matrix.multiply(transform_matrix);
	current_matrix = temp;
	current_matrix.print();
	// current_matrices[matrix_type] = transformation_matrix;
	return;
}

void Polygon::save_transformation() {
	// matrix temp = current_matrices[0].multiply(current_matrices[1].multiply(current_matrices[2]));
	transformation_matrix_list.push_back(current_matrix);

	return;
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
	if (transformation_matrix_list.size() > 1)
		transformation_matrix_list.pop_back();
	return;
}