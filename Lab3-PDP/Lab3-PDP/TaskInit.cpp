#include "TaskInit.h"
#include "Matrix.h"
#include "RowTask.h"
#include "ColumnTask.h"
#include "KTask.h"
#include "ThreadMatrix.h"
#include <stdexcept>

ThreadMatrix* TaskInit::initRowTask(int index, Matrix& matrix1, Matrix& matrix2, Matrix& result, int threadsNumber)
{
    int positions = result.getRows() * result.getCols();
    int defaultNumberOfPositionsPerThread = positions / threadsNumber;
    int numberOfThreadsWithExtraPos = positions % threadsNumber;
    int positionsToBeFilled = defaultNumberOfPositionsPerThread;

    int startRow = (positionsToBeFilled * index) / result.getCols();
    int startCol = (positionsToBeFilled * index) % result.getCols();

    if (index == threadsNumber - 1) {
        positionsToBeFilled += numberOfThreadsWithExtraPos;
    }

    RowTask* task = new RowTask(startRow, startCol, positionsToBeFilled, matrix1, matrix2, result);
    task->run();  
    return task;
}

ThreadMatrix* TaskInit::initColumnTask(int index, Matrix& matrix1, Matrix& matrix2, Matrix& result, int threadsNumber)
{
    int positions = result.getRows() * result.getCols();
    int defaultNumberOfPositionsPerThread = positions / threadsNumber;
    int numberOfThreadsWithExtraPos = positions % threadsNumber;
    int positionsToBeFilled = defaultNumberOfPositionsPerThread;

    int startRow = (positionsToBeFilled * index) % result.getRows();
    int startCol = (positionsToBeFilled * index) / result.getRows();

    if (index == threadsNumber - 1) {
        positionsToBeFilled += numberOfThreadsWithExtraPos;
    }
    ColumnTask* task = new ColumnTask(startRow, startCol, positionsToBeFilled, matrix1, matrix2, result);
    task->run();  
    return task;
}

ThreadMatrix* TaskInit::initKTask(int index, Matrix& matrix1, Matrix& matrix2, Matrix& result, int threadsNumber)
{
    int positions = result.getRows() * result.getCols();
    int defaultNumberOfPositionsPerThread = positions / threadsNumber;

    if (index < positions % threadsNumber) {
        defaultNumberOfPositionsPerThread++;
    }

    int startRow = index / result.getCols();
    int startColumn = index % result.getCols();
    KTask* task = new KTask(startRow, startColumn, defaultNumberOfPositionsPerThread, matrix1, matrix2, result, threadsNumber);
    task->run();  
    return task;
}

int TaskInit::computeMatrixElement(Matrix &matrix1,  Matrix &matrix2, int row, int column)
{
    int res = 0;
    if(row<matrix1.getRows() && column < matrix2.getCols()){
        for (int i = 0; i < matrix1.getCols(); ++i) {
            res += matrix1.getElem(row, i) * matrix2.getElem(i, column);
        }
    }
    else {
     throw std::invalid_argument("Invalid row or column for matrix multiplication.");
    }

    return res;
}
