#include "Approach.h"
#include "TaskType.h"
#include "Matrix.h"
#include "ThreadMatrix.h"
#include <future>
#include "TaskInit.h"
#include <vector>
#include <iostream>
#include "ThreadPool.h"
const int rowMatrix1 = 500;
const int rowMatrix2 = 500;
const int colMatrix1 = 500;
const int colMatrix2 = 500;
const int THREAD_COUNT = 10;
const Approach THREAD_APPROACH = Approach::CLASSIC;
const TaskType TASK_TYPE = TaskType::KTH;

void ThreadPoolCase(Matrix& matrix1, Matrix& matrix2, Matrix& result)
{
	ThreadPool pool(THREAD_COUNT);
	for (int i = 0; i < THREAD_COUNT; i++)
	{
		switch (TASK_TYPE)
		{
		case TaskType::ROWS:
			
			pool.enqueue([i, &matrix1, &matrix2, &result]() {
				TaskInit::initRowTask(i, matrix1, matrix2, result, THREAD_COUNT);
				});
			
			break;
		case TaskType::COLUMNS:
			pool.enqueue([i, &matrix1, &matrix2, &result]() {
				TaskInit::initColumnTask(i, matrix1, matrix2, result, THREAD_COUNT);
				});
			break;
		case TaskType::KTH:
			pool.enqueue([i, &matrix1, &matrix2, &result]() {
				TaskInit::initKTask(i, matrix1, matrix2, result, THREAD_COUNT);
				});
			break;
		default:
			std::cerr << "Invalid Task Type!" << std::endl;
			return;
		}
	}
	pool.close();
	std::cout << "Matrix 1:\n" << matrix1.ToString();
	std::cout << "Matrix 2:\n" << matrix2.ToString();
	std::cout << "Resulted matrix:\n" << result.ToString();
}

void ClassicCase(Matrix& matrix1, Matrix& matrix2, Matrix& result)
{
	std::vector<std::thread> threads;
	for (int i = 0; i < THREAD_COUNT; i++)
	{
		switch (TASK_TYPE)
		{
		case TaskType::ROWS:
			threads.emplace_back(TaskInit::initRowTask, i, std::ref(matrix1), std::ref(matrix2), std::ref(result), THREAD_COUNT);
			break;
		case TaskType::COLUMNS:
			threads.emplace_back(TaskInit::initColumnTask, i, std::ref(matrix1), std::ref(matrix2), std::ref(result), THREAD_COUNT);
			break;
		case TaskType::KTH:
			threads.emplace_back(TaskInit::initKTask, i, std::ref(matrix1), std::ref(matrix2), std::ref(result), THREAD_COUNT);
			break;
		default:
			std::cerr << ("InvalidTask Type!");
			return;
		}
		
	}

	

	for (auto& t : threads)
	{
		if (t.joinable())
			t.join();
	}
	std::cout << "Matrix 1:\n" << matrix1.ToString();
	std::cout << "Matrix 2:\n" << matrix2.ToString();
	std::cout << "Resulted matrix:\n" << result.ToString();

}

int main()
{
	if (colMatrix1 != rowMatrix2)
	{
		std::cerr << "Can't multiply the matrices! the columns of the first matrix must be equal with the rows of the second!";
		return 1;
	}

	Matrix matrix1(rowMatrix1, colMatrix1);
	Matrix matrix2(rowMatrix2, colMatrix2);
	Matrix result(rowMatrix1, colMatrix2);

	matrix1.generateMatrix();
	matrix2.generateMatrix();

	auto startTime = std::chrono::high_resolution_clock::now();

	switch (THREAD_APPROACH) {
	case Approach::CLASSIC:
		ClassicCase(matrix1, matrix2, result);
		break;
	case Approach::THREADPOOL:
		ThreadPoolCase(matrix1, matrix2, result);
		break;
	default:
		std::cerr << "Invalid thread approach!\n";
		return 1;
	}
	auto stopTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> time = stopTime - startTime;

	std::cout << "Time:" << time.count();

	return 0;

}
