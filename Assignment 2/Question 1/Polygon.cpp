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
	// vector<Point> temp_row(all_points[0].size(), {0, 0, 0});
	// for (int i = 0; i < all_points.size(); i++) {
	// 	transformed_points.push_back(temp_row);
	// }
	// cout << "test" << endl;
	// transformed_points(all_points.size(), std::vector<Point>(all_points[0].size(), {0, 0, 0}));
	apply_transformations();
	return;
}

void Polygon::rotate(double angle) {
	// Convert degrees to radians
	double theta = angle * (M_PI / 180);
	double cos_theta = cos(theta);
	double sin_theta = sin(theta);
	// Set all_points in matrix
	rotate_matrix.set_val(0, 0, cos_theta);
	rotate_matrix.set_val(0, 2, -sin_theta);
	rotate_matrix.set_val(2, 0, sin_theta);
	rotate_matrix.set_val(2, 2, cos_theta);
	apply_transformations();
	return;
}

void Polygon::apply_transformations() {
	// transformed_points.clear();
	// Transform all points
	// cout << all_points.size() << " " << all_points[0].size() << endl;
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
			// cout << x << " " << z << endl;
			// cout << use_point.get_val(0, 0) << " " << use_point.get_val(1, 0) << " " << use_point.get_val(2, 0) << endl;
			transformed_points[x][z] = {use_point.get_val(0, 0), use_point.get_val(1, 0), use_point.get_val(2, 0)};
			// cout << "test" << endl;
		}
	}
	return;
}

void Polygon::draw() {
	// apply_transformations();
	// Draw polygon using transformed points
	for (int x = 0; x < all_points.size() - 1; x++) {
		for (int z = 0; z < all_points[0].size() - 1; z++) {
			// glBegin(GL_TRIANGLES);
			// 	glVertex3f(transformed_points[x][z].x, transformed_points[x][z].y, transformed_points[x][z].z);
			// 	glVertex3f(transformed_points[x + 1][z].x, transformed_points[x + 1][z].y, transformed_points[x + 1][z].z);
			// 	glVertex3f(transformed_points[x][z+1].x, transformed_points[x][z+1].y, transformed_points[x][z+1].z);
			// glEnd();
			// glBegin(GL_TRIANGLES);
			// 	glVertex3f(transformed_points[x + 1][z].x, transformed_points[x + 1][z].y, transformed_points[x + 1][z].z);
			// 	glVertex3f(transformed_points[x][z + 1].x, transformed_points[x][z + 1].y, transformed_points[x][z + 1].z);
			// 	glVertex3f(transformed_points[x + 1][z + 1].x, transformed_points[x + 1][z + 1].y, transformed_points[x + 1][z + 1].z);
			// glEnd();
			glBegin(GL_LINES);
				glVertex3f(transformed_points[x][z].x, transformed_points[x][z].y, transformed_points[x][z].z);
			 	glVertex3f(transformed_points[x + 1][z].x, transformed_points[x + 1][z].y, transformed_points[x + 1][z].z);
				
				glVertex3f(transformed_points[x + 1][z].x, transformed_points[x + 1][z].y, transformed_points[x + 1][z].z);
				glVertex3f(transformed_points[x][z+1].x, transformed_points[x][z+1].y, transformed_points[x][z+1].z);

				glVertex3f(transformed_points[x][z+1].x, transformed_points[x][z+1].y, transformed_points[x][z+1].z);
				glVertex3f(transformed_points[x][z].x, transformed_points[x][z].y, transformed_points[x][z].z);
			glEnd();
		}
		// break;
	}
}