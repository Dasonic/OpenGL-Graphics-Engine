#ifndef matrix_h
#define matrix_h
	#include <vector>

	class matrix {
		std::vector<std::vector<int>> pm;
		int num_rows, num_cols;

		public:
			void set_row(int row_number, std::vector<int> row);
			void set_col(int col_number, std::vector<int> col);
			void set_val(int row_number, int col_number, int val);
			void add_val(int row_number, int col_number, int val);
			int get_val(int row_number, int col_number);
			int get_rows();
			int get_cols();
			void print();
			matrix multiply(matrix other_matrix);
			matrix(int num_rows, int num_cols);
	};
#endif