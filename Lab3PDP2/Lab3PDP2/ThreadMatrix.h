#pragma once
#include <vector>
#include <utility>
#include "Matrix.h"
class ThreadMatrix 
{
protected:
    std::vector<std::pair<int, int>> elems;
    int startRow, startColumn, positionsToFill;
    Matrix &matrix1, &matrix2, &result;
    int K;
public:
    ThreadMatrix(int startRow, int startColumn, int positionsToFill, Matrix& matrix1, Matrix& matrix2, Matrix& result);
    ThreadMatrix(int startRow, int startColumn, int positionsToFill, Matrix& matrix1, Matrix& matrix2, Matrix& result,int K);
    virtual ~ThreadMatrix() = default;
    virtual void computeElements()=0;
    void run();



};

