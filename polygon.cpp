#include <vector>
#include <iostream>

#include "polygon.h"
#include "structs.h"
#include "matrix.h"
#include "draw_commands.h"

using namespace std;

Polygon::Polygon(std::vector<point> points, point coordinates) {
	point_list = points;
	fill_colour = {1, 1, 1};

	transform_matrix = new matrix(4, 4);
	transform_matrix->set_row(0, {1, 0, 0, coordinates.x});
	transform_matrix->set_row(1, {0, 1, 0, coordinates.y});
	transform_matrix->set_row(2, {0, 0, 1, 0});
	transform_matrix->set_row(3, {0, 0, 0, 1});

	scale_matrix = new matrix(4, 4);

	// coords = new matrix(4, 1);
	// coords->set_col(0, {coordinates.x, coordinates.y, 1, 1});
	return;
}

void Polygon::set_colour(colour RGB) {
	fill_colour = RGB;
	return;
}
void Polygon::draw() {
	matrix ts(4, 4);
	if (scale_matrix->get_val(0, 0) != 0) {
		int x = transform_matrix->get_val(0, 3);
		int y = transform_matrix->get_val(1, 3);
		// Define negative matrix
		matrix neg_transform_matrix(4, 4);
		neg_transform_matrix.set_row(0, {1, 0, 0, -x});
		neg_transform_matrix.set_row(1, {0, 1, 0, -y});
		neg_transform_matrix.set_row(2, {0, 0, 1, 0});
		neg_transform_matrix.set_row(3, {0, 0, 0, -1});
		ts = neg_transform_matrix.multiply(scale_matrix->multiply(*transform_matrix));
	}


	std::vector<point> new_points;
	for (int i = 0; i < point_list.size(); i++) {
		// Convert point to matrix
		matrix temp_point(4, 1);
		temp_point.set_col(0, {point_list[i].x, point_list[i].y, 1, 1});
		// Apply transformation to co-ords
		matrix use_point(4, 1);
		if (scale_matrix->get_val(0, 0) == 0) // If no scale values
			use_point = transform_matrix->multiply(temp_point);
		else {
			use_point = ts.multiply(temp_point);
			// use_point.print();
			// cout << endl;
		}
		// Add transformed points to vector
		new_points.push_back({use_point.get_val(0, 0), use_point.get_val(1, 0)});
	}
	// Draw polygon using transformed points
	drawPolygon(new_points, fill_colour);
	return;
}
void Polygon::scale(int x_scale, int y_scale) {
	int x = transform_matrix->get_val(0, 3);
	int y = transform_matrix->get_val(1, 3);

	scale_matrix->set_row(0, {x_scale, 0, 0, (1 - x_scale) * x});
	scale_matrix->set_row(1, {0, y_scale, 0, (1 - y_scale) * y});
	scale_matrix->set_row(2, {0, 0, 1, 0});
	scale_matrix->set_row(3, {0, 0, 0, 1});

	return;
}
void Polygon::rotate() {

}
void Polygon::translate(int x_offset, int y_offset) {
	transform_matrix->set_col(3, {x_offset, y_offset, 1, 1});
	return;
}
