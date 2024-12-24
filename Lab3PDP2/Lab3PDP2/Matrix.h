#pragma once
#include <vector>
#include <string>
class Matrix
{
private:
	int rows;
	int cols;
	std::vector<std::vector<int>> matrix;
	const int Max_Init_Val = 1;
	const int Min_Init_Val = 0;
public:
	Matrix(int rows,int cols);
	int getRows();
	int getCols();
	std::vector<std::vector<int>> getMatrix();
	int getElem(int row,int col);
	void setElem(int row, int col, int elem);
	void generateMatrix();

	 std::string ToString() const;

};

