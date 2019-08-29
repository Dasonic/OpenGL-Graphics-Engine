#include <vector>
#include <iostream>
#include <cmath>

#include "polygon.h"
#include "structs.h"
#include "matrix.h"
#include "draw_commands.h"

using namespace std;

/**
 * Constructor for a polygon when give the points and a starting point
 * \param points vector of points representing the points making up the polygon
 * \param coordinates a point representing where the polygon should be drawn on the screen
 */
Polygon::Polygon(std::vector<point> points, point coordinates) {
	point_list = points;
	last_used_point_list = points;
	fill_colour = {1, 1, 1};
	matrix transformation_matrix(4, 4);
	
	transformation_matrix.set_row(0, {1, 0, 0, (double)coordinates.x});
	transformation_matrix.set_row(1, {0, 1, 0, (double)coordinates.y});
	transformation_matrix.set_row(2, {0, 0, 1, 0});
	transformation_matrix.set_row(3, {0, 0, 0, 1});

	rotate_matrix.set_up_transformation();
	transform_matrix = transformation_matrix;
}

/**
 * Constructor for a polygon when give the points. Draws the polygon at 0, 0
 * \param points vector of points representing the points making up the polygon
 */
Polygon::Polygon(std::vector<point> points)
:	Polygon(points, {0, 0})
{}

/**
 * Constructor for a blank Polygon. Defines one point at 0, 0 and draws it at 0, 0
 */
Polygon::Polygon()
:	Polygon({{0, 0}})
{}

/**
 * Replaces the vector the Polygon's points with the given vector
 * \param points vector of points representing the points making up the polygon
 */
void Polygon::change_points(std::vector<point> points) {
	point_list = points;
	last_used_point_list = points;
}

/**
 * Replaces the colour the Polygon is filled with with the given colour
 * \param RGB struct representing the 3 double values for R, G and B
 */
void Polygon::set_colour(colour RGB) {
	fill_colour = RGB;
}

/**
 * Draws the Polygon on the screen
 */
void Polygon::draw() {
	matrix ts(4, 4);
	last_used_point_list.clear();
	
	// Transform all points
	for (int i = 0; i < point_list.size(); i++) {
		// Convert point to matrix
		matrix temp_point(4, 1);
		temp_point.set_col(0, {(double)point_list[i].x, (double)point_list[i].y, 1, 1});
		// Apply transformation to co-ords
		matrix use_point(4, 1);
		use_point = rotate_matrix.multiply(temp_point);
		use_point.add_val(0, 0, transform_matrix.get_val(0, 3));
		use_point.add_val(1, 0, transform_matrix.get_val(1, 3));
		// Add transformed points to vector
		last_used_point_list.push_back({(int)use_point.get_val(0, 0), (int)use_point.get_val(1, 0)});
	}
	// Draw polygon using transformed points
	drawPolygon(last_used_point_list, fill_colour);
}

/**
 * Scales the Polygon by the given dimensions
 * \param x_scale integer representing what to multiply the x scale of the Polygon by
 * \param y_scale integer representing what to multiply the y scale of the Polygon by
 */
void Polygon::scale(int x_scale, int y_scale) {
	matrix transform_matrix(4, 4);
	transform_matrix.set_up_transformation();
	transform_matrix.set_val(0, 0, x_scale);
	transform_matrix.set_val(1, 1, y_scale);
}

/**
 * Rotates the Polygon to the given angle
 * \param angle double representing the angle in degrees
 */
void Polygon::rotate(double angle) {
	matrix transformation_matrix(4, 4);
	// Convert degrees to radians
	double theta = angle * (M_PI / 180);
	double cos_theta = cos(theta);
	double sin_theta = sin(theta);
	// Set values in matrix
	transformation_matrix.set_val(0, 0, cos_theta);
	transformation_matrix.set_val(0, 1, -sin_theta);
	transformation_matrix.set_val(1, 0, sin_theta);
	transformation_matrix.set_val(1, 1, cos_theta);
	rotate_matrix = transformation_matrix;
}

/**
 * Rotates the Polygon by the given angle (Adds to rotation)
 * \param angle double representing the angle in degrees
 */
void Polygon::additive_rotate(double angle) {
	matrix transformation_matrix(4, 4);
	transformation_matrix.set_up_transformation();

	double theta = angle * (M_PI / 180);
	double cos_theta = cos(theta);
	double sin_theta = sin(theta);

	matrix * rotate_matrix_ptr = &rotate_matrix;

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

	return;
}

/**
 * Translates the Polygon to the given dimensions
 * \param x_scale integer representing where to move the x value of the Polygon to
 * \param y_scale integer representing  where to move the y value of the Polygon to
 */
void Polygon::translate(double x_offset, double y_offset) {
	matrix transformation_matrix(4, 4);
	transformation_matrix.set_up_transformation();
	transformation_matrix.set_col(3, {x_offset, y_offset, 1, 1});
	transform_matrix = transformation_matrix;
}

/**
 * Translates the Polygon by the given dimensions (Adds to translation)
 * \param x_scale integer representing what to move the x value of the Polygon by
 * \param y_scale integer representing  what to move the y value of the Polygon by
 */
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

/**
 * Saves the currently used matrix to a stack
 */
void Polygon::save_transformation() {
	transformation_matrix_list.push_back(rotate_matrix.multiply(transform_matrix));
	return;
}

/**
 * Reverts the transformation matrix to the last saved matrix
 */
void Polygon::undo_transformation() {
	if (transformation_matrix_list.size() > 1)
		transformation_matrix_list.pop_back();
	return;
}

/**
 * Finds the smallest x value and the highest y value
 */
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

/**
 * Finds the highest x value and the smallest y value
 */
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
