#include "RowTask.h"
#include "ThreadMatrix.h"
#include <iostream>

RowTask::RowTask(int startRow, int startColumn, int positionsToFill, Matrix& matrix1, Matrix& matrix2, Matrix& result)
	:ThreadMatrix(startRow,startColumn,positionsToFill, matrix1,matrix2,result)
{
	
}

void RowTask::computeElements()
{
	int currentRow = startRow;
	int currentCol = startColumn;
	int cntPosToFill = positionsToFill;
	int rows = result.getRows();
	int cols = result.getCols();

	while (cntPosToFill > 0 && currentRow < rows && currentCol < cols)
	{
		elems.emplace_back(currentRow, currentCol);
		currentCol++;
		cntPosToFill--;
		

		if (currentCol == cols)
		{
			currentRow++;
			currentCol = 0;
		}
	}
}
