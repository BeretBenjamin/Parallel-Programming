#pragma once
#include "ThreadMatrix.h"
class TaskInit
{
public:
    static ThreadMatrix* initRowTask(int index, Matrix &matrix1, Matrix &matrix2, Matrix &result, int threadsNumber);
    static ThreadMatrix* initColumnTask(int index, Matrix& matrix1, Matrix& matrix2, Matrix& result, int threadsNumber);
    static ThreadMatrix* initKTask(int index, Matrix& matrix1, Matrix& matrix2, Matrix& result, int threadsNumber);
    static int computeMatrixElement( Matrix &matrix1,  Matrix &matrix2, int row, int column);

};

