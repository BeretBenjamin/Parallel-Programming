#include <iostream>
#include <vector>
#include <algorithm>
#include "Polynomial.h"
#include "PolynomialOperations.h"
#include <random>
#include <chrono>

void printHeader(const std::string& header) {
    std::cout << "+++++++++++++++++++++++++++++++++++++" << std::endl;
    std::cout << header << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++" << std::endl;
}

void printPolynomial(const std::string& name, const Polynomial& poly) {
    std::cout << name << ": " << poly.to_string() << std::endl;
}

std::vector<int> generateRandomCoefficients(int n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(-10, 10);

    std::vector<int> coefficients(n + 1);

    for (int i = 0; i <= n; ++i) {
        coefficients[i] = dis(gen) * dis(gen);
    }

    return coefficients;
}

int main() {
    int choice;
    std::vector<int> A, B;

    do {
        printHeader("Polynomial Coefficient Generation Menu");
        std::cout << "1. First Example" << std::endl;
        std::cout << "2. Second Example" << std::endl;
        std::cout << "3. Third Example" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            A = generateRandomCoefficients(100);
            B = generateRandomCoefficients(60);
            break;
        case 2:
            A = generateRandomCoefficients(10000);
            B = generateRandomCoefficients(5000);
            break;
        case 3:
            A = generateRandomCoefficients(25000);
            B = generateRandomCoefficients(15000);
            break;
        case 0:
            std::cout << "Exiting the program." << std::endl;
            return 0;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }

        auto m = A.size();
        auto n = B.size();
        Polynomial polyA{ static_cast<int>(m), A };
        Polynomial polyB{ static_cast<int>(n), B };

        printHeader("Polynomials");
        printPolynomial("Polynomial A", polyA);
        printPolynomial("Polynomial B", polyB);

        do {
            printHeader("Polynomial Multiplication Menu");
            std::cout << "1. Sequential Classic" << std::endl;
            std::cout << "2. Sequential Karatsuba" << std::endl;
            std::cout << "3. Parallel Classic" << std::endl;
            std::cout << "4. Parallel Karatsuba" << std::endl;
            std::cout << "0. Go Back" << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            switch (choice) {
            case 1: {
                auto start = std::chrono::high_resolution_clock::now();
                Polynomial polyProduct = PolynomialOperations::multiply_classic(polyA, polyB);
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                printHeader("Sequential Classic Result");
                printPolynomial("Result", polyProduct);
                std::cout << "Elapsed time: " << elapsed.count() << " seconds" << std::endl;
                break;
            }
            case 2: {
                auto start = std::chrono::high_resolution_clock::now();
                Polynomial polyProductKaratsuba = PolynomialOperations::multiply_karatsuba(polyA, polyB);
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                printHeader("Sequential Karatsuba Result");
                printPolynomial("Result", polyProductKaratsuba);
                std::cout << "Elapsed time: " << elapsed.count() << " seconds" << std::endl;
                break;
            }
            case 3: {
                auto start = std::chrono::high_resolution_clock::now();
                Polynomial polyProductParallel = PolynomialOperations::multiply_classic_parallel(polyA, polyB);
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                printHeader("Parallel Classic Result");
                printPolynomial("Result", polyProductParallel);
                std::cout << "Elapsed time: " << elapsed.count() << " seconds" << std::endl;
                break;
            }
            case 4: {
                auto start = std::chrono::high_resolution_clock::now();
                Polynomial polyProduct2 = PolynomialOperations::multiply_karatsuba_parallel(polyA, polyB);
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                printHeader("Parallel Karatsuba Result");
                printPolynomial("Result", polyProduct2);
                std::cout << "Elapsed time: " << elapsed.count() << " seconds" << std::endl;
                break;
            }
            case 0:
                std::cout << "Going back to the coefficient generation menu." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
        } while (choice != 0);
    } while (true);
}
