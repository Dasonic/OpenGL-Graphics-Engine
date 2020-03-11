#include "text.h"
#include "polygon.h"
#include "structs.h"
#include "draw_commands.h"

#include <string>
#include <iostream>

using namespace std;

/**
 * Constructor for text. Currently only supports numbers
 * \param text_to_display a string representing what text to display
 * \param bottom_left_position a point representing the bottom left position to draw the text
 * \param RGB a struct representing the RGB values of the colour to draw the text as
 */
Text::Text(std::string text_to_display, point bottom_left_position, colour RGB) {
	display_text = text_to_display;
	display_at = bottom_left_position;
	text_colour = RGB;
	rectangle tm = {{0, 13}, {7, 12}};
	rectangle tml = {{0, 13}, {1, 6}};
	rectangle tmr = {{6, 13}, {7, 6}};
	rectangle mm = {{0, 7}, {7, 6}};
	rectangle bm = {{0, 1}, {7, 0}};
	rectangle bml = {{0, 6}, {1, 0}};
	rectangle bmr = {{6, 6}, {7, 0}};
	// Define the numbers
	zero = { tm, tmr, bmr, bm, bml, tml };
	one = { tmr, bmr };
	two = { tm, tmr, mm, bml, bm };
	three = { tm, tmr, mm, bmr, bm };
	four = { tml, mm, tmr, bmr };
	five = { tm, tml, mm, bmr, bm };
	six = { tm, tml, mm, bmr, bm, bml };
	seven = {tm, tmr, bmr };
	eight = { tm, tml, tmr, mm, bml, bmr, bm };
	nine = { tm, tml, tmr, mm, bmr };
	return;
}

/**
 * Draws the text to the screen
 * \param character a vector rectangles that represent the lines of a character
 * \param shift integer representing how many spaces to shift the drawing of the character over by
 */
void Text::draw_character(vector<rectangle> character, int shift) {
	shift = shift * 9;
	for (int i = 0; i < character.size(); i++) {
		point top_left = 	{character[i].top_left.x + display_at.x + shift, character[i].top_left.y + display_at.y};
		point bottom_right = 	{character[i].bottom_right.x + display_at.x + shift, character[i].bottom_right.y + display_at.y};

		point top_right, bottom_left;
		if (character[i].top_left.y == character[i].bottom_right.y + 1) {
			top_right =   {character[i].bottom_right.x + display_at.x + shift, character[i].top_left.y + display_at.y};
			bottom_left = {character[i].top_left.x + display_at.x + shift, character[i].bottom_right.y + display_at.y};
		} else {
			top_right =   {character[i].top_left.x + display_at.x + shift, character[i].bottom_right.y + display_at.y};
			bottom_left = {character[i].bottom_right.x + display_at.x + shift, character[i].top_left.y + display_at.y};
		}
		drawLineDDA(top_left, top_right, text_colour);
		drawLineDDA(bottom_left, bottom_right, text_colour);
	}
	return;
}

/**
 * Draws the numbers to the screen
 */
void Text::draw() {
	for (int i = 0; i < display_text.size(); i++) {
		switch (display_text[i]) {
			case '0':
				draw_character(zero, i);
				break;
			case '1':
				draw_character(one, i);
				break;
			case '2':
				draw_character(two, i);
				break;
			case '3':
				draw_character(three, i);
				break;
			case '4':
				draw_character(four, i);
				break;
			case '5':
				draw_character(five, i);
				break;
			case '6':
				draw_character(six, i);
				break;
			case '7':
				draw_character(seven, i);
				break;
			case '8':
				draw_character(eight, i);
				break;
			case '9':
				draw_character(nine, i);
				break;
			default:
				cerr << "WARNING: Attempt to draw invalid character" << endl;
		}
	}
	return;
}

/**
 * Replaces the text that will be replaced
 * \param update_text string representing the new text to display
 */
void Text::update_text(std::string text_to_display) {
	display_text = text_to_display;
	return;
}