#include "Matrix.h"
#include <stdexcept>
#include <sstream>

Matrix::Matrix(int rows, int cols)
{
	this->rows = rows;
	this->cols = cols;
	this->matrix.resize(rows, std::vector<int>(cols));
}

int Matrix::getRows()
{
	return this->rows;
}

int Matrix::getCols()
{
	return this->cols;
}

std::vector<std::vector<int>> Matrix::getMatrix()
{
	return this->matrix;
}

int Matrix::getElem(int row, int col)
{
	if (row >= this->rows || col >= this->cols || row < 0 || col < 0) {
		throw std::out_of_range("Invalid position!");
	}
	return this->matrix[row][col];
}

void Matrix::setElem(int row, int col, int elem)
{

	if (row >= this->rows || col >= this->cols || row < 0 || col < 0) {
		throw std::out_of_range("Invalid position!");
	}
	this->matrix[row][col] = elem;
}

void Matrix::generateMatrix()
{
	for (int i = 0; i < this->rows; i++)
		for (int j = 0; j < this->cols; j++)
			this->matrix[i][j] = i + j+1;
}
std::string Matrix::ToString() const {
	std::ostringstream builder;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			builder << matrix[i][j] << " ";
		}
		builder << "\n";
	}

	return builder.str();
}
