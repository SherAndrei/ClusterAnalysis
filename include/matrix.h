#pragma once

#include <iostream>
#include <vector>

class Matrix {
public:

	Matrix();
	Matrix(int num_rows, int num_columns);

 	void Reset(int num_rows, int num_columns);

  	double& At(int row, int column);
  	double At(int row, int column) const;
	
  	std::vector<double>& operator[](size_t row);
  	const std::vector<double>& operator[](size_t row) const;

  	size_t NumRows() const;
  	size_t NumColumns() const;
private:
  	size_t num_rows_;
  	size_t num_columns_;

  	std::vector<std::vector<double>> elements_;
};

bool operator==(const Matrix& one, const Matrix& two);
Matrix operator+(const Matrix& one, const Matrix& two);

std::istream& operator>>(std::istream& in, Matrix& matrix);
std::ostream& operator<<(std::ostream& out, const Matrix& matrix);