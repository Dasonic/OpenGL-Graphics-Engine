#ifndef draw_commands_h
#define draw_commands_h
	#include <vector>
	#include "structs.h"

	#define SCALE 0.5
	#define MAX_X 160
	#define MAX_Y 160
	#define RAND_COLOUR() (double)(rand()%256)/100
	#define ROUND(x) ((int)(x + 0.5))
	
	bool same_side(point a, point b, point I1, point I2);
	bool inside(point p, point a, point b, point c);
	bool check_inside_polygon(std::vector<point> points, point vertex_a, point vertex_b, point vertex_c);
	bool intersects(point p1, point p2, point p3, point p4);

	void setPixel(point p, colour RGB);
	void randomPixels();
	void drawLineDDA(point p1, point p2, colour RGB, int* x_at_y);
	void drawLineDDA(point p1, point p2, colour RGB);
	void randomLines();
	void fillTriangle(point p1, point p2, point p3, colour RGB);
	void drawPolygon(std::vector<point> points, colour RGB);
			
	int find_max_point(std::vector<point> points, char type);
	int find_min_point(std::vector<point> points, char type);
	
#endif