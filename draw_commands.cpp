#include <GL/glut.h>
#include <time.h> 
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdlib.h>

#include "matrix.h"
#include "structs.h"
#include "draw_commands.h"

using namespace std;


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

/*
    Draws 100 pixels in random locations and random colours to the screen
 */
void randomPixels() {
    srand(time(NULL));
    for (int i = 0; i < 100; i++) {
		point random_location = {(rand()%MAX_X), (rand()%MAX_Y)};
		colour randomColour = {RAND_COLOUR(), RAND_COLOUR(), RAND_COLOUR()};
        setPixel(random_location, randomColour);
    }

}

/*
    Takes in 4 co-ordinates and 3 colour values.
    Draws a line made of small boxs representing pixels to the screen
    \param x and y: integer between 1 and 20
    \param r, g and b: double between 0 and 0.256
 */
vector<int> drawLineDDA(point p1, point p2, colour RGB) {
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
    double y = p2.y;
	p.x = ROUND(x);
	p.y = ROUND(y);

    vector<int> x_at_y;
    setPixel(p, RGB);
    for (int i = 0; i < steps; i++) {
        x += x_inc;
        y += y_inc;
        x_at_y.push_back(ROUND(x));
		p.x = ROUND(x);
		p.y = ROUND(y);
        setPixel(p, RGB);
    }
    return x_at_y;
}

/*
    Draws 10 random lines in random locations and random colours to the screen
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

/*
    Takes in 3 co-ordinate points and 3 colour values.
    Draws a triangle using small boxs representing a pixel to the screen and fills them with given colour
    \param p: struct with 2 integers between 1 and 20 representing x and y
    \param r, g and b: double between 0 and 0.256
 */
void fillTriangle(point p1, point p2, point p3, colour RGB) {
	colour white = {1, 1, 1};
    // Find out top and bottom points
    int topx, topy, botx, boty;
    if (p1.y >= p2.y && p1.y >= p3.y) {
        topx = p1.x;
        topy = p1.y;
        if (p2.y > p3.y) {
            botx = p3.x;
            boty = p3.y;
        } else {
            botx = p2.x;
            boty = p2.y;
        }
    } else if (p2.y >= p1.y && p2.y >= p3.y) {
        topx = p2.x;
        topy = p2.y;
        if (p1.y > p3.y) {
            botx = p3.x;
            boty = p3.y;
        } else {
            botx = p1.x;
            boty = p1.y;
        }
    } else {
        topx = p3.x;
        topy = p3.y;
        if (p2.y > p1.y) {
            botx = p1.x;
            boty = p1.y;
        } else {
            botx = p2.x;
            boty = p2.y;
        }
    }
    point points[3] = {p1, p2, p3};

    int size_of_array = (topy - boty);
    vector<vector<int>> x_at_y(size_of_array);
    for (int i = 0; i < 3; i++) {
        int warp_i = i + 1;
        if (i == 2)
            warp_i = 0;
        if (points[i].x == points[warp_i].x) { // If vertical line (x is same)
            int bottom = (points[i].y < points[warp_i].y) ? points[i].y : points[warp_i].y;
            int top = (points[i].y > points[warp_i].y) ? points[i].y : points[warp_i].y;
            for (int j = bottom - boty; j < top - boty; j++) { // Add x value to vector for values starting at the bottom to the top
                x_at_y[j].push_back(points[i].x);
            }
        } else if (points[i].y != points[warp_i].y) { // Not horizontal (so at an angle)
			point bottom;
            bottom.y = (points[i].y < points[warp_i].y) ? points[i].y : points[warp_i].y;
            bottom.x = (points[i].y < points[warp_i].y) ? points[i].x : points[warp_i].x;

			point top;
            top.y = (points[i].y > points[warp_i].y) ? points[i].y : points[warp_i].y;
            top.x = (points[i].y > points[warp_i].y) ? points[i].x : points[warp_i].x;

            // Calculate gradient
            vector<int> xy = drawLineDDA(bottom, top, white);
            int k = 0;
            for (int j = bottom.y - boty; j < top.y - boty; j++) { // Add x value to vector for values starting at the bottom to the top
                x_at_y[j].push_back(xy[k]);
                k++;
            }
        } // Horizontal lines do nothing
    }
    // Draw the lines for filling triangle
    for (int y = 0; y < topy - boty; y++) {
        if (x_at_y[y][0] != x_at_y[y][1]) {
			point fp = {x_at_y[y][0], y + boty + 1}; // First point
			point sp = {x_at_y[y][1], y + boty + 1}; // Second point
            drawLineDDA(fp, sp, RGB);
		}
    }
    // Draw lines for outline
    drawLineDDA(p1, p2, white);
    drawLineDDA(p2, p3, white);
    drawLineDDA(p3, p1, white);
}

/*
    Takes in 4 co-ordinate points
    Returns true if points a and b are on the same side
    \param a, b, I1, I2: struct with 2 integers between 1 and 20 representing x and y
 */
bool same_side(point a, point b, point I1, point I2) {
    // I1 and I2 are ends of the line
    int apt = (a.x - I1.x) * (I2.y - I1.y) - (I2.x - I1.x) * (a.y - I1.y);
    int bpt = (b.x - I1.x) * (I2.y - I1.y) - (I2.x - I1.x) * (b.y - I1.y);
    // Returns true if both a and b are on the same side
    return ((apt * bpt) > 0);
}

/*
    Takes in 4 co-ordinate points
    Returns true if a point p is inside a triangle formed out of points a, b and c
    \param p, a, b, c: struct with 2 integers between 1 and 20 representing x and y
 */
bool inside(point p, point a, point b, point c) {
    return same_side(p, a, b, c) && same_side(p, b, a, c) && same_side(p, c, b, a);
}

/*
    Takes in an array of co-ordinate points and 3 co-ordinate points that form a triangle
    Returns true if a point p is inside a triangle formed out of points a, b and c
    \param points: vector of struct with 2 integers between 1 and 20 representing x and y
    \param a, b, c: struct with 2 integers between 1 and 20 representing x and y
 */
bool check_inside_polygon(vector<point> points, point vertex_a, point vertex_b, point vertex_c) {
    // Find min and max points
    point min, max;
    if (vertex_a.x < vertex_b.x && vertex_a.x < vertex_c.x) {
        min.x = vertex_a.x;
        min.y = vertex_a.y;
        if (vertex_b.x > vertex_c.x) {
            max.x = vertex_b.x;
            max.y = vertex_b.y;
        }
        else {
            max.x = vertex_c.x;
            max.y = vertex_c.y;
        }
    } else if (vertex_b.x < vertex_a.x && vertex_b.x < vertex_c.x) {
        min.x = vertex_b.x;
        min.y = vertex_b.y;
        if (vertex_a.x > vertex_c.x) {
            max.x = vertex_a.x;
            max.y = vertex_a.y;
        }
        else {
            max.x = vertex_c.x;
            max.y = vertex_c.y;
        }
    } else {
        min.x = vertex_c.x;
        min.y = vertex_c.y;
        if (vertex_a.x > vertex_b.x) {
            max.x = vertex_a.x;
            max.y = vertex_a.y;
        }
        else {
            max.x = vertex_b.x;
            max.y = vertex_b.y;
        }
    }
    
    // Check if point inside rectangle
    for (int y = 0; y < points.size(); y++) {
        if (y != vertex_a.y && y != vertex_b.y && y != vertex_c.y) {
            int px = points[y].y;
            if (!(px < min.x && px > max.x && y < min.y && y > max.y)) {
                // Point inside rectangle, now do inside triangle test
                point p;
                p.x = px;
                p.y = y;
                if (inside(p, vertex_a, vertex_b, vertex_c)) {
                    // Point is inside triangle
                    return true;
                }
            }
        }
    }
    return false;
}

/*
    Takes in an array of co-ordinate points and 3 co-ordinate points that form a triangle
    Returns true if a point p is inside a triangle formed out of points a, b and c
    \param points: vector of struct with 2 integers between 1 and 20 representing x and y
    \param r, g and b: double between 0 and 0.256
 */
void drawPolygon(vector<point> points, colour RGB) {
    vector<int> used = {}; // stores index of used points
    while (used.size() < points.size()) {
        // Find leftmost vertex
        point vertex_a = {999999999, -1};
        int vertex_a_index = -1;
        for (int i = 0; i < points.size(); i++) {
            if (find(used.begin(), used.end(), i) == used.end() && points[i].x < vertex_a.x) {
                vertex_a = points[i];
                vertex_a_index = i;
            }
        }
    
        if (vertex_a_index == -1)
            exit(1);

        used.push_back(vertex_a_index);
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
			colour randomColour = {RAND_COLOUR(), RAND_COLOUR(), RAND_COLOUR()};
            fillTriangle(vertex_a, vertex_b, vertex_c, randomColour);
        }
    }

}