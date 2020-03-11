#include "Polygon.h"
#include "matrix.h"
#include "structs.h"
#include <GL/glut.h>
#include <cmath>
#include <iostream>

using namespace std;

Polygon::Polygon(std::vector<std::vector<Point>> points, Point middle) {
	all_points = points;
	transformed_points = points;
	matrix transformation_matrix(4, 4);
	
	transformation_matrix.set_row(0, {1, 0, 0, middle.x});
	transformation_matrix.set_row(1, {0, 1, 0, middle.y});
	transformation_matrix.set_row(2, {0, 0, 1, middle.z});
	transformation_matrix.set_row(3, {0, 0, 0, 1});

	rotate_matrix.set_up_transformation();
	transform_matrix = transformation_matrix;
	apply_transformations();
	return;
}

void Polygon::rotate(double angle_x, double angle_y) {
	// Convert degrees to radians
	double theta_x = angle_x * (M_PI / 180);
	double cos_theta_x = cos(theta_x);
	double sin_theta_x = sin(theta_x);
	double theta_y = angle_y * (M_PI / 180);
	double cos_theta_y = cos(theta_y);
	double sin_theta_y = sin(theta_y);
	matrix rotate_matrix_y;
	rotate_matrix_y.set_up_transformation();
	// Set all_points in matrix
	rotate_matrix_y.set_val(0, 0, cos_theta_y);
	rotate_matrix_y.set_val(0, 2, -sin_theta_y);
	rotate_matrix_y.set_val(2, 0, sin_theta_y);
	rotate_matrix_y.set_val(2, 2, cos_theta_y);
	matrix rotate_matrix_x;
	rotate_matrix_x.set_up_transformation();
	rotate_matrix_x.set_val(1, 1, cos_theta_x);
	rotate_matrix_x.set_val(2, 1, -sin_theta_x);
	rotate_matrix_x.set_val(1, 2, sin_theta_x);
	rotate_matrix_x.set_val(2, 2, cos_theta_x);

	rotate_matrix = rotate_matrix_x.multiply(rotate_matrix_y);
	apply_transformations();
	return;
}

void Polygon::apply_transformations() {
	// Transform all points
	for (int x = 0; x < all_points.size(); x++) {
		for (int z = 0; z < all_points[0].size(); z++) {
			// Convert point to matrix
			matrix temp_point(4, 1);
			temp_point.set_col(0, {all_points[x][z].x, all_points[x][z].y, all_points[x][z].z, 1});
			// Apply transformation to co-ords
			matrix use_point(4, 1);
			use_point = rotate_matrix.multiply(temp_point);
			use_point.add_val(0, 0, transform_matrix.get_val(0, 3));
			use_point.add_val(1, 0, transform_matrix.get_val(1, 3));
			use_point.add_val(2, 0, transform_matrix.get_val(2, 3));
			// Replace transformed points
			transformed_points[x][z] = {use_point.get_val(0, 0), use_point.get_val(1, 0), use_point.get_val(2, 0)};
		}
	}
	return;
}

colour Polygon::get_colour(double height) {
	if (height < -15) {
		return {0.76, 0.70, 0.50};
	} else if (height < 15) {
		return {0, 0.50, 0};
	} else {
		return {0.94, 0.97, 1};
	}
}

void Polygon::draw() {
	// Draw polygon using transformed points
	for (int x = 0; x < all_points.size() - 1; x++) {
		for (int z = 0; z < all_points[0].size() - 1; z++) {
			colour RGB;
			glBegin(GL_TRIANGLES);
				RGB = get_colour(all_points[x][z].y);
				glColor3d(RGB.R, RGB.G, RGB.B); // Set colour
				glVertex3f(transformed_points[x][z].x, transformed_points[x][z].y, transformed_points[x][z].z);

				RGB = get_colour(all_points[x + 1][z].y);
				glColor3d(RGB.R, RGB.G, RGB.B); // Set colour
				glVertex3f(transformed_points[x + 1][z].x, transformed_points[x + 1][z].y, transformed_points[x + 1][z].z);

				RGB = get_colour(all_points[x][z + 1].y);
				glColor3d(RGB.R, RGB.G, RGB.B); // Set colour
				glVertex3f(transformed_points[x][z+1].x, transformed_points[x][z+1].y, transformed_points[x][z+1].z);
			glEnd();
			glBegin(GL_TRIANGLES);
				RGB = get_colour(all_points[x + 1][z].y);
				glColor3d(RGB.R, RGB.G, RGB.B); // Set colour
				glVertex3f(transformed_points[x + 1][z].x, transformed_points[x + 1][z].y, transformed_points[x + 1][z].z);

				RGB = get_colour(all_points[x][z + 1].y);
				glColor3d(RGB.R, RGB.G, RGB.B); // Set colour
				glVertex3f(transformed_points[x][z + 1].x, transformed_points[x][z + 1].y, transformed_points[x][z + 1].z);

				RGB = get_colour(all_points[x + 1][z + 1].y);
				glColor3d(RGB.R, RGB.G, RGB.B); // Set colour
				glVertex3f(transformed_points[x + 1][z + 1].x, transformed_points[x + 1][z + 1].y, transformed_points[x + 1][z + 1].z);
			glEnd();
			glColor3d(0, 0, 0);
			glBegin(GL_LINES);
				glVertex3f(transformed_points[x][z].x, transformed_points[x][z].y, transformed_points[x][z].z);
			 	glVertex3f(transformed_points[x + 1][z].x, transformed_points[x + 1][z].y, transformed_points[x + 1][z].z);
				
				glVertex3f(transformed_points[x + 1][z].x, transformed_points[x + 1][z].y, transformed_points[x + 1][z].z);
				glVertex3f(transformed_points[x][z+1].x, transformed_points[x][z+1].y, transformed_points[x][z+1].z);

				glVertex3f(transformed_points[x][z+1].x, transformed_points[x][z+1].y, transformed_points[x][z+1].z);
				glVertex3f(transformed_points[x][z].x, transformed_points[x][z].y, transformed_points[x][z].z);
			glEnd();
		}
	}
}