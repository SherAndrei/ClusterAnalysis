#pragma once

#include <iostream>
#include <vector>

template<class T>
class Matrix {
public:

	Matrix() : num_rows_(0u), num_columns_(0u) {}
	Matrix(size_t num_rows, size_t num_columns); 

 	void Reset(size_t num_rows, size_t num_columns);

  	T& At(size_t row, size_t column);
  	T At(size_t row, size_t column) const;
	
  	std::vector<T>& operator[](size_t row);
  	const std::vector<T>& operator[](size_t row) const;

  	size_t NumRows() const;
  	size_t NumColumns() const;
private:
  	size_t num_rows_;
  	size_t num_columns_;

  	std::vector<std::vector<T>> elements_;
};

template<class T>
Matrix<T>::Matrix(size_t num_rows, size_t num_columns) {
	Matrix::Reset(num_rows, num_columns);
}

template<class T>
void Matrix<T>::Reset(size_t num_rows, size_t num_columns) {
	if (num_rows == 0 || num_columns == 0) {
		num_rows = num_columns = 0;
	}

	num_rows_    = num_rows;
	num_columns_ = num_columns;
	elements_.assign(num_rows, std::vector<T>(num_columns));
}

template<class T>
T& Matrix<T>::At(size_t row, size_t column) { return elements_.at(row).at(column); }
template<class T>
T  Matrix<T>::At(size_t row, size_t column) const { return elements_.at(row).at(column); }

template<class T>
std::vector<T>& Matrix<T>::operator[](size_t row) { return elements_[row]; }
template<class T>
const std::vector<T>& Matrix<T>::operator[](size_t row) const { return elements_[row]; }

template<class T>
size_t Matrix<T>::NumRows() const { return num_rows_; }
template<class T>
size_t Matrix<T>::NumColumns() const { return num_columns_; }

template<class T>
Matrix<T> operator+(const Matrix<T>& one, const Matrix<T>& two)
{
    if (one.NumRows() != two.NumRows()) {
        throw std::invalid_argument("Mismatched number of rows");
    }

    if (one.NumColumns() != two.NumColumns()) {
        throw std::invalid_argument("Mismatched number of columns");
    }

    Matrix<T> result(one.NumRows(), one.NumColumns());
    size_t row, column;
    for (row = 0u; row < result.NumRows(); ++row) {
        for (column = 0u; column < result.NumColumns(); ++column) {
            result.At(row, column) = one.At(row, column) + two.At(row, column);
        }
    }

  return result;
}

template<class T>
std::istream& operator>>(std::istream& in, Matrix<T>& matrix)
{
  size_t num_rows, num_columns;
  in >> num_rows >> num_columns;

  matrix.Reset(num_rows, num_columns);
  for (size_t row = 0u; row < num_rows; ++row) {
    for (size_t column = 0u; column < num_columns; ++column) {
      in >> matrix.At(row, column);
    }
  }

  return in;
}
template<class T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& matrix)
{
  out << matrix.NumRows() << " " << matrix.NumColumns() << std::endl;
  size_t row, column;
  for (row = 0u; row < matrix.NumRows(); ++row) {
    for (column = 0u; column < matrix.NumColumns(); ++column) {
      if (column > 0) {
        out << " ";
      }
      out << matrix.At(row, column);
    }
    out << std::endl;
  }

  return out;
}