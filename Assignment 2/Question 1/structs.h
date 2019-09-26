#ifndef structs_h
#define structs_h

	struct Point {
		double x, y, z;
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
#endif