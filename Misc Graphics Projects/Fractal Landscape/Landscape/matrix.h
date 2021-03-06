#ifndef matrix_h
#define matrix_h
	#include <vector>

	class matrix {
		std::vector<std::vector<double>> pm;
		int num_rows, num_cols;

		public:
			matrix(int num_rows, int num_cols);
			matrix();
			void set_row(int row_number, std::vector<double> row);
			void set_col(int col_number, std::vector<double> col);
			void set_val(int row_number, int col_number, double val);
			void add_val(int row_number, int col_number, double val);
			double get_val(int row_number, int col_number);
			int get_rows();
			int get_cols();
			void print();
			matrix multiply(matrix other_matrix);
			void set_up_transformation();
	};
#endif