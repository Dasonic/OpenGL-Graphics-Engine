#include "matrix.h"
#include <vector>
#include <iostream>

using namespace std;


matrix::matrix(int rows, int cols) {
	std::vector<std::vector<double>> m(rows, std::vector<double>(cols, 0));
	pm = m;
	num_rows = rows;
	num_cols = cols;
	return;
}

void matrix::print() {
	for(int row = 0; row < num_rows; row++) {
		for (int col = 0; col < num_cols; col++) {
			cout << pm[row][col] << " ";
		}
		cout << endl;
	}
	return;
}

void matrix::set_row(int row_number, std::vector<double> row) {
	if (row_number >= num_rows || row_number < 0) {
		cerr << "ERROR: Invalid row index to set" << endl;
		exit(2);
	}

	pm[row_number] = row;
	return;
}

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

void matrix::set_val(int row_number, int col_number, double val) {
	pm[row_number][col_number] = val;
	return;
}

void matrix::add_val(int row_number, int col_number, double val) {
	pm[row_number][col_number] += val;
	return;
}

double matrix::get_val(int row_number, int col_number) {
	return pm[row_number][col_number];
}

int matrix::get_rows() {
	return num_rows;
}

int matrix::get_cols() {
	return num_cols;
}

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

void matrix::set_up_transformation() {

	set_row(0, {1, 0, 0, 0});
	set_row(1, {0, 1, 0, 0});
	set_row(2, {0, 0, 1, 0});
	set_row(3, {0, 0, 0, 1});

	return;
}