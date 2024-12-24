#include "ThreadMatrix.h"
#include "TaskInit.h"
#include <iostream>

ThreadMatrix::ThreadMatrix(int startRow, int startColumn, int positionsToFill, Matrix& matrix1, Matrix& matrix2, Matrix& result)
    : startRow(startRow), startColumn(startColumn), positionsToFill(positionsToFill), matrix1(matrix1), matrix2(matrix2), result(result), K(0) {
    
}

ThreadMatrix::ThreadMatrix(int startRow, int startColumn, int positionsToFill, Matrix& matrix1, Matrix& matrix2, Matrix& result, int K)
    :startRow(startRow),startColumn(startColumn), positionsToFill(positionsToFill),matrix1(matrix1), matrix2(matrix2), result(result), K(K)
{
   

}
void ThreadMatrix::run() {
 
    computeElements();
    for (const auto& elem : elems) {
        int row = elem.first;
        int col = elem.second;
        result.setElem(row, col, TaskInit::computeMatrixElement(matrix1, matrix2, row, col));
    }
}
