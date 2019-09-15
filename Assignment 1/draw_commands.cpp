#include <GL/glut.h>
#include <time.h> 
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdlib.h>

#include "matrix.h"
#include "structs.h"
#include "draw_commands.h"

#define EPSILON 0.000001

using namespace std;

/**
 * Takes in 1 co-ordinates and a colour value
 * Draws a line made of small boxs representing pixels to the screen
 * \param p: struct with 2 integers between representing x and y
 * \param RGB: struct with 3 doubles between 0 and 0.256
*/
void setPixel(point p, colour RGB) {
    glBegin(GL_QUADS);
        glColor3d(RGB.R, RGB.G, RGB.B); // Set colour
        // Define vertices
        glVertex3f((p.x - 1) * SCALE, (p.y - 1) * SCALE,0.0);
        glVertex3f(p.x * SCALE, (p.y - 1) * SCALE, 0.0);
        glVertex3f(p.x * SCALE, p.y * SCALE,0.0);
        glVertex3f((p.x - 1) * SCALE, p.y * SCALE,0.0);
    glEnd();
}

/**
 * Draws 100 pixels in random locations and random colours to the screen
*/
void randomPixels() {
    srand(time(NULL));
    for (int i = 0; i < 100; i++) {
		point random_location = {(rand()%MAX_X), (rand()%MAX_Y)};
		colour randomColour = {RAND_COLOUR(), RAND_COLOUR(), RAND_COLOUR()};
        setPixel(random_location, randomColour);
    }

}

/**
 * Takes in 4 co-ordinates and 3 colour values.
 * Sets a pointer to point to a line made of small boxs representing pixels. Does not draw to screen.
 * \param p1, p2: struct with 2 integers between representing x and y
 * \param x_at_y: pointer to an array of integers
*/
void drawLineDDA(point p1, point p2, int* x_at_y) {
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    int steps;
    
    if (abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);
    double x_inc = dx / (double) steps;
    double y_inc = dy / (double) steps;

	point p;
    double x = p1.x;
    double y = p1.y;
	p.x = ROUND(x);
	p.y = ROUND(y);
	x_at_y[0] = p.x;

	int bottom_y = (p1.y < p2.y) ? p1.y : p2.y;

    for (int i = 0; i < steps; i++) {
        x += x_inc;
        y += y_inc;
		p.x = ROUND(x);
		p.y = ROUND(y);
		x_at_y[p.y - bottom_y] = p.x;
    }
    return;
}

/**
 * Takes in 4 co-ordinates and 3 colour values.
 * Draws a line made of small boxs representing pixels to the screen
 * \param p1, p2: struct with 2 integers between representing x and y
 * \param RGB: struct with 3 doubles between 0 and 0.256
*/
void drawLineDDA(point p1, point p2, colour RGB) {
	int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    int steps;
    
    if (abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);
    double x_inc = dx / (double) steps;
    double y_inc = dy / (double) steps;

	point p;
    double x = p1.x;
    double y = p1.y;
	p.x = ROUND(x);
	p.y = ROUND(y);

    setPixel(p, RGB);
    for (int i = 0; i < steps; i++) {
        x += x_inc;
        y += y_inc;
		p.x = ROUND(x);
		p.y = ROUND(y);
        setPixel(p, RGB);
    }
    return;
}

/**
 * Draws 10 random lines in random locations and random colours to the screen
 */
void randomLines() {
    srand(time(NULL));
	point p1, p2;

    for (int i = 0; i <= 10; i ++) {
        p1.x = (rand()%MAX_X);
        p1.y = (rand()%MAX_Y);
        p2.x = (rand()%MAX_X);
        p2.y = (rand()%MAX_Y);

		colour randomColour = {RAND_COLOUR(), RAND_COLOUR(), RAND_COLOUR()};
        drawLineDDA(p1, p2, randomColour);
    }
    return;
}

/**
 * Takes in 3 co-ordinate points and 3 colour values.
 * Draws a triangle using small boxs representing a pixel to the screen and fills them with given colour
 * \param p1, p2, p3: structs with 2 integers between representing x and y
 * \param RGB: struct with 3 doubles between 0 and 0.256
 */
void fillTriangle(point p1, point p2, point p3, colour RGB) {
	colour white = {1, 1, 1};
    // Find out top and bottom points
    point top, bot;
    if (p1.y >= p2.y && p1.y >= p3.y) {
        top = p1;
        if (p2.y > p3.y) {
            bot = p3;
        } else {
            bot = p2;
        }
    } else if (p2.y >= p1.y && p2.y >= p3.y) {
        top = p2;
        if (p1.y > p3.y) {
            bot = p3;
        } else {
            bot = p1;
        }
    } else {
        top = p3;
        if (p2.y > p1.y) {
            bot = p1;
        } else {
            bot = p2;
        }
    }
    point points[3] = {p1, p2, p3};

    int size_of_array = (top.y - bot.y);
    vector<vector<int>> x_at_y(size_of_array);
    for (int i = 0; i < 3; i++) {
        int next_i = i + 1;
		// If next i is out of index, then loop around to 0
        if (i == 2)
            next_i = 0;

        if (points[i].x == points[next_i].x) { // If vertical line (x is same)
            int lower = (points[i].y < points[next_i].y) ? points[i].y : points[next_i].y;
            int higher = (points[i].y > points[next_i].y) ? points[i].y : points[next_i].y;
            for (int j = lower - bot.y; j < higher - bot.y; j++) { // Add x value to vector for values starting at the bottom to the top
                x_at_y[j].push_back(points[i].x);
            }
        } else if (points[i].y != points[next_i].y) { // Not horizontal (so at an angle)
			point lower;
            lower.y = (points[i].y < points[next_i].y) ? points[i].y : points[next_i].y;
            lower.x = (points[i].y < points[next_i].y) ? points[i].x : points[next_i].x;

			point higher;
            higher.y = (points[i].y > points[next_i].y) ? points[i].y : points[next_i].y;
            higher.x = (points[i].y > points[next_i].y) ? points[i].x : points[next_i].x;

            // Calculate gradient
			int xy[higher.y - lower.y] = {0};
            drawLineDDA(lower, higher, xy);
            int k = 0;
            for (int j = lower.y - bot.y; j < higher.y - bot.y; j++) { // Add x value to vector for values starting at the bottom to the top
                x_at_y[j].push_back(xy[k]);
                k++;
            }
        } // Horizontal lines do nothing
    }
    // Draw the lines for filling triangle
    for (int y = 0; y < top.y - bot.y; y++) {
        if (x_at_y[y][0] != x_at_y[y][1]) {
			point fp = {x_at_y[y][0], y + bot.y}; // First point
			point sp = {x_at_y[y][1], y + bot.y}; // Second point
            drawLineDDA(fp, sp, RGB);
		}
    }
    // Draw lines for outline
    drawLineDDA(p1, p2, white);
    drawLineDDA(p2, p3, white);
    drawLineDDA(p3, p1, white);
}

/**
 * Takes in 4 co-ordinate points
 * Returns true if points a and b are on the same side
 * \param a, b, I1, I2: struct with 2 integers between representing x and y
 */
bool same_side(point a, point b, point I1, point I2) {
    // I1 and I2 are ends of the line
    int apt = (a.x - I1.x) * (I2.y - I1.y) - (I2.x - I1.x) * (a.y - I1.y);
    int bpt = (b.x - I1.x) * (I2.y - I1.y) - (I2.x - I1.x) * (b.y - I1.y);
    // Returns true if both a and b are on the same side
    return ((apt * bpt) > 0);
}

/**
 * Takes in 4 co-ordinate points
 * Returns true if a point p is inside a triangle formed out of points a, b and c
 * \param p, a, b, c: struct with 2 integers representing x and y
 */
bool inside(point p, point a, point b, point c) {
	return same_side(p, a, b, c) && same_side(p, b, a, c) && same_side(p, c, a, b);
    // return same_side(p, a, b, c) && same_side(p, b, c, a) && same_side(p, c, a, b);
}

/**
 * Finds either the maximum x or y value given a list of points
 * \param points: vector of points
 * \param type: either 'x' or 'y' depending on which maximum is to be found
 */
int find_max_point(vector<point> points, char type) {
	int max = -999999;
	for (int i = 0; i < points.size(); i ++) {
		if (type == 'x') {
			if (points[i].x > max)
				max = points[i].x;
		} else if (type == 'y') {
			if (points[i].y > max)
				max = points[i].y;
		} else {
			cerr << "ERROR: Invalid type given to find_max_point" << endl;
			exit(3);
		}
	}
	return max;
}

/**
 * Finds either the minimum x or y value given a list of points
 * \param points: vector of points
 * \param type: either 'x' or 'y' depending on which minimum is to be found
 */
int find_min_point(vector<point> points, char type) {
	int min = 99999999;
	for (int i = 0; i < points.size(); i ++) {
		if (type == 'x') {
			if (points[i].x < min)
				min = points[i].x;
		} else if (type == 'y') {
			if (points[i].y < min)
				min = points[i].y;
		} else {
			cerr << "ERROR: Invalid type given to find_min_point" << endl;
			exit(3);
		}
	}
	return min;
}

/**
 * Takes in an array of co-ordinate points and 3 co-ordinate points that form a triangle
 * Returns true if a point p is inside a triangle formed out of points a, b and c
 * \param points: vector of struct with 2 integers representing x and y
 * \param a, b, c: struct with 2 integers representing x and y
 */
bool check_inside_polygon(vector<point> points, point vertex_a, point vertex_b, point vertex_c) {
    // Find min and max points
    int min_x, min_y, max_x, max_y;
	vector<point> point_list = {vertex_a, vertex_b, vertex_c};
    min_x = find_min_point(point_list, 'x');
	max_x = find_max_point(point_list, 'x');
	min_y = find_min_point(point_list, 'y');
	max_y = find_max_point(point_list, 'y');

    // Check if point inside rectangle
    for (int i = 0; i < points.size(); i++) {
            int px = points[i].x;
			int py = points[i].y;
            if (!(px < min_x && px > max_x && py < min_y && py > max_y)) {
                // Point inside rectangle, now do inside triangle test
                if (inside(points[i], vertex_a, vertex_b, vertex_c)) {
                    // Point is inside triangle
                    return true;
                }
            }
        // }
    }
    return false;
}

/**
 * Returns true if a line between points p1 and p2 intersect a line between points p3 and p4
 * \param p1, p2, p3, p4: struct with 2 integers representing x and y
 */
bool intersects(point p1, point p2, point p3, point p4) {
	float x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
	float y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;
	
	float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	// If d is zero, there is no intersection
	if (d == 0)
		return false;	
	
	// Get the x and y
	float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
	float x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
	float y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;
	
	// Check if the x and y coordinates are within both lines
	if ( x < min(x1, x2) - EPSILON || x > max(x1, x2) + EPSILON || x < min(x3, x4) - EPSILON || x > max(x3, x4) + EPSILON ) 
		return false;
	if ( y < min(y1, y2) - EPSILON || y > max(y1, y2) + EPSILON || y < min(y3, y4) - EPSILON || y > max(y3, y4) + EPSILON )
		return false;
	
	// If the point of intersection is at any of the given points, then return false as they are allowed to intersect there
	point point_array[4] = {p1, p2, p3, p4};
	for (int i = 0; i < 4; i++) {
		if (x == point_array[i].x && y == point_array[i].y)
			return false;
	}
	return true;
}

/**
 * Takes in an array of co-ordinate points and 3 co-ordinate points that form a triangle
 * Returns true if a point p is inside a triangle formed out of points a, b and c
 * \param points: vector of struct with 2 integers between representing x and y
 * \param RGB: struct with 3 doubles between 0 and 0.256
 */
void drawPolygon(vector<point> points, colour RGB) {
	vector<vector<point>> drawn_lines;
	for (int index = 1; index < points.size(); index++) {
        point vertex_a = points[index];
        int vertex_a_index = index;
        // Form triangle with 2 adjacent vertices
        point vertex_b, vertex_c;
        if (vertex_a_index + 1 < points.size()) // Make sure the next index isn't out of bounds, if so, wrap around
            vertex_b = {points[vertex_a_index + 1].x, points[vertex_a_index + 1].y};
        else
            vertex_b = {points[0].x, points[0].y};
        if (vertex_a_index != 0) // Make sure the previous index isn't out of bounds, if so, wrap around
            vertex_c = {points[vertex_a_index - 1].x, points[vertex_a_index - 1].y};
        else
            vertex_c = {points[points.size() - 1].x, points[points.size() - 1].y};

        if (!check_inside_polygon(points, vertex_a, vertex_b, vertex_c)) { // If no of the points are in the triangle
			bool lines_intersect = false; 
			for (int i = 0; i < drawn_lines.size(); i++) {
				if (intersects(vertex_a, vertex_b, drawn_lines[i][0], drawn_lines[i][1]) || 
					intersects(vertex_a, vertex_c, drawn_lines[i][0], drawn_lines[i][1]) ||
					intersects(vertex_b, vertex_c, drawn_lines[i][0], drawn_lines[i][1])) {
						lines_intersect = true;
						break;
					}
			}
			if (!lines_intersect) { // If the lines to draw this triangle don't intersect with any previously drawn
				fillTriangle(vertex_a, vertex_b, vertex_c, RGB);
				drawn_lines.push_back({vertex_a, vertex_b});
				drawn_lines.push_back({vertex_a, vertex_c});
				drawn_lines.push_back({vertex_b, vertex_c});
			}
        }
    }
	// Puts grey pixels on each point
	for (int i = 0; i < points.size(); i++) {
		setPixel(points[i], {0.5, 0.5, 0.5});
	}
}