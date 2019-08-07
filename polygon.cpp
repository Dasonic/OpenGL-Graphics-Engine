#include <vector>
#include <iostream>

#include "polygon.h"
#include "structs.h"
#include "draw_commands.h"

Polygon::Polygon(std::vector<point> points) {
	point_list = points;
}

void Polygon::set_colour(colour RGB) {
	fill_colour = RGB;
}
void Polygon::draw() {
	drawPolygon(point_list, fill_colour);
}
void Polygon::scale() {

}
void Polygon::rotate() {

}
void Polygon::translate() {
	
}
