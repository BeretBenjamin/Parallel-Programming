#include "KTask.h"
#include "ThreadMatrix.h"
#include <iostream>

KTask::KTask(int startRow, int startColumn, int positionsToFill, Matrix& matrix1, Matrix& matrix2, Matrix& result, int K)
	:ThreadMatrix(startRow,startColumn,positionsToFill,matrix1,matrix2,result,K)
{
	
}

void KTask::computeElements()
{
	int currentRow = startRow;
	int currentCol = startColumn;
	int cntPosToFill = positionsToFill;
	int rows = result.getRows();
	int cols = result.getCols();

	while (cntPosToFill > 0 && currentRow < rows && currentCol < cols)
	{
		elems.emplace_back(currentRow, currentCol);
		cntPosToFill--;
		currentRow = currentRow + (currentCol +K) / cols;
		currentCol =(currentCol + K) % cols;
	}
}
