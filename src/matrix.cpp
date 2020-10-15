#include "matrix.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

Matrix::Matrix()
: num_rows_(0)
, num_columns_(0)
{}

Matrix::Matrix(int num_rows, int num_columns) {
	Reset(num_rows, num_columns);
}

void Matrix::Reset(int num_rows, int num_columns) {
	if (num_rows < 0) {
		throw out_of_range("num_rows must be >= 0");
	}
	if (num_columns < 0) {
		throw out_of_range("num_columns must be >= 0");
	}
	if (num_rows == 0 || num_columns == 0) {
		num_rows = num_columns = 0;
	}

	num_rows_    = num_rows;
	num_columns_ = num_columns;
	elements_.assign(num_rows, vector<double>(num_columns));
}

double& Matrix::At(int row, int column) {
	return elements_.at(row).at(column);
}

double Matrix::At(int row, int column) const {
    return elements_.at(row).at(column);
}

vector<double>& Matrix::operator[](size_t row)
{
	return elements_[row];
}
const vector<double>& Matrix::operator[](size_t row) const
{
	return elements_[row];
}

size_t Matrix::NumRows() const {
    return num_rows_;
  }

size_t Matrix::NumColumns() const {
    return num_columns_;
}

bool operator==(const Matrix& one, const Matrix& two) {
  if ((one.NumRows() != two.NumRows()) && (one.NumColumns() != two.NumColumns())) {
    return false;
  }

  for (int row = 0; row < one.NumRows(); ++row) {
    for (int column = 0; column < one.NumColumns(); ++column) {
      if (one.At(row, column) != two.At(row, column)) {
        return false;
      }
    }
  }

  return true;
}

Matrix operator+(const Matrix& one, const Matrix& two) {
  if (one.NumRows() != two.NumRows()) {
    throw invalid_argument("Mismatched number of rows");
  }

  if (one.NumColumns() != two.NumColumns()) {
    throw invalid_argument("Mismatched number of columns");
  }

  Matrix result(one.NumRows(), one.NumColumns());
  for (int row = 0; row < result.NumRows(); ++row) {
    for (int column = 0; column < result.NumColumns(); ++column) {
      result.At(row, column) = one.At(row, column) + two.At(row, column);
    }
  }

  return result;
}

istream& operator>>(istream& in, Matrix& matrix) {
  int num_rows, num_columns;
  in >> num_rows >> num_columns;

  matrix.Reset(num_rows, num_columns);
  for (int row = 0; row < num_rows; ++row) {
    for (int column = 0; column < num_columns; ++column) {
      in >> matrix.At(row, column);
    }
  }

  return in;
}

ostream& operator<<(ostream& out, const Matrix& matrix) {
  out << matrix.NumRows() << " " << matrix.NumColumns() << endl;
  for (int row = 0; row < matrix.NumRows(); ++row) {
    for (int column = 0; column < matrix.NumColumns(); ++column) {
      if (column > 0) {
        out << " ";
      }
      out << matrix.At(row, column);
    }
    out << endl;
  }

  return out;
}

