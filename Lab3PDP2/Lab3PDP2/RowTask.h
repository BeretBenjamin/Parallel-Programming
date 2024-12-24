#pragma once
#include "ThreadMatrix.h"
#include"Matrix.h"
class RowTask: public ThreadMatrix
{
public:
	RowTask(int startRow, int startColumn, int positionsToFill, Matrix& matrix1, Matrix& matrix2, Matrix& result);
protected:
	void computeElements() override;
};

