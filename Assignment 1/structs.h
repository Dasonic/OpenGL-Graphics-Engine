#ifndef structs_h
#define structs_h
	/**
	 * Two integers representing a pixel on the screen
	 * \param x x co-ordinate of pixel
	 * \param y y co-ordinate of pixel
	 */
	struct point {
		int x, y;
	};

	/**
	 * Three doubles representing values for red, green and blue respectively
	 * \param R red value
	 * \param G green value
	 * \param B blue value
	 */
	struct colour {
		double R, G, B;
	};

	/**
	 * Two points representing the top left and bottom right corners to form a rectangle
	 * \param top_left point where the top left of the rectangle is located
	 * \param bottom_right point where the bottom right of the recatngle is located
	 */
	struct rectangle {
		point top_left, bottom_right;
	};

	/**
	 * Three doubles representing velocity as both x and y components and the magnitude of a vector
	 * \param x x component of the velocity
	 * \param y y component of the velocity
	 * \param speed the magnitude of the velocity vector
	 */
	struct velocity {
		double x, y, speed;
	};
#endif