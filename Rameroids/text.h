#ifndef text_h
#define text_h
	#include <vector>
	#include <string>
	#include "polygon.h"
	#include "structs.h"

	class Text {
		private:
			std::string display_text;
			point display_at;
			colour text_colour;
			std::vector<rectangle> zero, one, two, three, four, five, six, seven, eight, nine, a;
			void draw_character(std::vector<rectangle> character, int shift);
		public:
			Text(std::string text_to_display, point bottom_left_position, colour RBG);
			void draw();
			void update_text(std::string text_to_display);
	};
#endif