#include "matrix.h"
#include <vector>
#include <iostream>

using namespace std;


/**
 * Constructor for a matrix when given and number of rows and columns
 * \param rows an integer representing the number of rows the matrix should have
 * \param cols an integer representing the number of columns the matrix should have
 */
matrix::matrix(int rows, int cols) {
	std::vector<std::vector<double>> m(rows, std::vector<double>(cols, 0));
	pm = m;
	num_rows = rows;
	num_cols = cols;
	return;
}

/**
 * Constructor for a matrix if not given a size. Makes a 4 by 4 matrix
 */
matrix::matrix()
:	matrix(4, 4)
{}

/**
 * Prints out the matrix to stdout in a formatted way
 */
void matrix::print() {
	for(int row = 0; row < num_rows; row++) {
		for (int col = 0; col < num_cols; col++) {
			cout << pm[row][col] << " ";
		}
		cout << endl;
	}
	return;
}

/**
 * Replaces a row in the matrix with the given vector
 * \param row_number integer representing which row to replace
 * \param row vector of doubles representing the new row values
 */
void matrix::set_row(int row_number, std::vector<double> row) {
	if (row_number >= num_rows || row_number < 0) {
		cerr << "ERROR: Invalid row index to set" << endl;
		exit(2);
	}

	pm[row_number] = row;
	return;
}

/**
 * Replaces a col in the matrix with the given vector
 * \param col_number integer representing which column to replace
 * \param col vector of doubles representing the new col values
 */
void matrix::set_col(int col_number, std::vector<double> col) {
	if (num_rows < col.size()) {
		cerr << "ERROR: Too many rows to set col" << endl;
		exit(2);
	}
	else if (col_number >= num_cols || col_number < 0) {
		cerr << "ERROR: Invalid column index to set" << endl;
		exit(2);
	}

	for (int row_num = 0; row_num < num_rows; row_num++) {
		pm[row_num][col_number] = col[row_num];
	}
	return;
}

/**
 * Replaces a value at the given row and column with the given value
 * \param row_number integer representing which row to replace
 * \param col_number integer representing which column to replace
 * \param val double representing the value to use in the matrix
 */
void matrix::set_val(int row_number, int col_number, double val) {
	pm[row_number][col_number] = val;
	return;
}

/**
 * Adds a value at the given row and column with the given value
 * \param row_number integer representing which row to replace
 * \param col_number integer representing which column to replace
 * \param val double representing the value to add in the matrix
 */
void matrix::add_val(int row_number, int col_number, double val) {
	pm[row_number][col_number] += val;
	return;
}

/**
 * Returns a value at the given row and column
 * \param row_number integer representing which row to replace
 * \param col_number integer representing which column to replace
 */
double matrix::get_val(int row_number, int col_number) {
	return pm[row_number][col_number];
}

/**
 * Returns the number of rows the matrix has
 */
int matrix::get_rows() {
	return num_rows;
}

/**
 * Returns the number of columns the matrix has
 */
int matrix::get_cols() {
	return num_cols;
}

/**
 * Performs matrix dot multiplication between this matrix and a given matrix
 * \param other_matrix the matrix to multiply with
 */
matrix matrix::multiply(matrix other_matrix) {
	matrix product_matrix(num_rows, other_matrix.get_cols());

	for(int i = 0; i < num_rows; i++) {
		for (int j = 0; j < other_matrix.get_cols(); j++) {
            for(int k = 0; k < num_cols; k++) {
            	product_matrix.add_val(i, j, pm[i][k] * other_matrix.get_val(k, j));
            } 
		}
	}
	return product_matrix;
}

/**
 * Sets up the matrix as a blank transformation matrix
 */
void matrix::set_up_transformation() {
	if (num_rows == 4 && num_cols == 4) {
		set_row(0, {1, 0, 0, 0});
		set_row(1, {0, 1, 0, 0});
		set_row(2, {0, 0, 1, 0});
		set_row(3, {0, 0, 0, 1});
	} else {
		cerr << "ERROR: Matrix incorrect size to use set_up_transformation" << endl;
		exit(6);
	}

	return;
}