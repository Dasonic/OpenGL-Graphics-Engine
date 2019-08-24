#ifndef structs_h
#define structs_h
	struct point {
		int x, y;
	};

	struct colour {
		double R, G, B;
	};

	struct rectangle {
		point top_left, bottom_right;
	};
#endif