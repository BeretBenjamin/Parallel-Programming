#pragma once
#include "ThreadMatrix.h"
class KTask:public ThreadMatrix
{
public:
	KTask(int startRow, int startColumn, int positionsToFill, Matrix& matrix1, Matrix& matrix2, Matrix& result,int K);
protected:
	void computeElements() override;
};

