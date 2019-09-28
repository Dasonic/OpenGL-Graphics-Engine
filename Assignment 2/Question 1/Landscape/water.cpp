#include "water.h"
#include <GL/glut.h>
#include <iostream>

void water::set_water_level(int level) {
	for (int x = 0; x < all_points.size(); x++) {
		for (int z = 0; z < all_points[0].size(); z++) {
			all_points[x][z].y = level;
		}
	}
	// apply_transformations();
}

colour water::get_colour(double height) {
	return {0, 0.5, 1};
}

void water::set_lowest_point(int point) {
	lowest_point = point;
	return;
}

void water::draw() {
	// Draw polygon using transformed points
	for (int x = 0; x < all_points.size() - 1; x++) {
		for (int z = 0; z < all_points[0].size() - 1; z++) {
			colour RGB = get_colour(transformed_points[x + 1][z].y);
			glColor4d(0, 0.5, 1, 0.5); // Set colour
			glBegin(GL_TRIANGLES);
				// Top
				glVertex3d(transformed_points[x][z].x, transformed_points[x][z].y, transformed_points[x][z].z);
				glVertex3d(transformed_points[x + 1][z].x, transformed_points[x + 1][z].y, transformed_points[x + 1][z].z);
				glVertex3d(transformed_points[x][z+1].x, transformed_points[x][z+1].y, transformed_points[x][z+1].z);

				glVertex3d(transformed_points[x + 1][z].x, transformed_points[x + 1][z].y, transformed_points[x + 1][z].z);
				glVertex3d(transformed_points[x][z + 1].x, transformed_points[x][z + 1].y, transformed_points[x][z + 1].z);
				glVertex3d(transformed_points[x + 1][z + 1].x, transformed_points[x + 1][z + 1].y, transformed_points[x + 1][z + 1].z);
				// Side
				glVertex3d(transformed_points[x][z].x, transformed_points[x][z].y, transformed_points[x][z].z);
				glVertex3d(transformed_points[x + 1][z].x, transformed_points[x + 1][z].y, transformed_points[x + 1][z].z);
				glVertex3d(transformed_points[x][z].x, lowest_point, transformed_points[x][z].z);

				glVertex3d(transformed_points[x][z].x, lowest_point, transformed_points[x][z].z);
				glVertex3d(transformed_points[x + 1][z].x, transformed_points[x + 1][z].y, transformed_points[x + 1][z].z);
				glVertex3d(transformed_points[x + 1][z].x, lowest_point, transformed_points[x + 1][z].z);

				// Side
				glVertex3d(transformed_points[x][z].x, transformed_points[x][z].y, transformed_points[x][z].z);
				glVertex3d(transformed_points[x][z + 1].x, transformed_points[x][z + 1].y, transformed_points[x][z + 1].z);
				glVertex3d(transformed_points[x][z].x, lowest_point, transformed_points[x][z].z);

				glVertex3d(transformed_points[x][z].x, lowest_point, transformed_points[x][z].z);
				glVertex3d(transformed_points[x][z + 1].x, transformed_points[x][z + 1].y, transformed_points[x][z + 1].z);
				glVertex3d(transformed_points[x][z + 1].x, lowest_point, transformed_points[x][z + 1].z);

				// Side
				glVertex3d(transformed_points[x + 1][z].x, transformed_points[x + 1][z].y, transformed_points[x + 1][z].z);
				glVertex3d(transformed_points[x + 1][z + 1].x, transformed_points[x + 1][z + 1].y, transformed_points[x + 1][z + 1].z);
				glVertex3d(transformed_points[x + 1][z].x, lowest_point, transformed_points[x + 1][z].z);

				glVertex3d(transformed_points[x + 1][z].x, lowest_point, transformed_points[x + 1][z].z);
				glVertex3d(transformed_points[x + 1][z + 1].x, transformed_points[x + 1][z + 1].y, transformed_points[x + 1][z + 1].z);
				glVertex3d(transformed_points[x + 1][z + 1].x, lowest_point, transformed_points[x + 1][z + 1].z);

				// Side
				glVertex3d(transformed_points[x][z + 1].x, transformed_points[x][z + 1].y, transformed_points[x][z + 1].z + 1);
				glVertex3d(transformed_points[x + 1][z + 1].x, transformed_points[x + 1][z + 1].y, transformed_points[x + 1][z + 1].z + 1);
				glVertex3d(transformed_points[x][z + 1].x, lowest_point, transformed_points[x][z + 1].z + 1);

				glVertex3d(transformed_points[x][z + 1].x, lowest_point, transformed_points[x][z + 1].z + 1);
				glVertex3d(transformed_points[x + 1][z + 1].x, transformed_points[x + 1][z + 1].y, transformed_points[x + 1][z + 1].z + 1);
				glVertex3d(transformed_points[x + 1][z + 1].x, lowest_point, transformed_points[x + 1][z + 1].z + 1);
			glEnd();


			// glColor3d(0, 0, 0);
			// glBegin(GL_LINES);
			// 	glVertex3f(transformed_points[x][z].x, transformed_points[x][z].y, transformed_points[x][z].z);
			//  	glVertex3f(transformed_points[x + 1][z].x, transformed_points[x + 1][z].y, transformed_points[x + 1][z].z);
				
			// 	glVertex3f(transformed_points[x + 1][z].x, transformed_points[x + 1][z].y, transformed_points[x + 1][z].z);
			// 	glVertex3f(transformed_points[x][z+1].x, transformed_points[x][z+1].y, transformed_points[x][z+1].z);

			// 	glVertex3f(transformed_points[x][z+1].x, transformed_points[x][z+1].y, transformed_points[x][z+1].z);
			// 	glVertex3f(transformed_points[x][z].x, transformed_points[x][z].y, transformed_points[x][z].z);
			// glEnd();
		}
	}
}