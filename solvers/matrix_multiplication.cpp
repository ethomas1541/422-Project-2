#include <solvers.hpp>
#include <sstream>
#include <stdexcept>

using namespace Eigen;

std::vector<std::tuple<Matrix<int, Dynamic, Dynamic>, std::string>> MatrixMultiplicationSolver::solve(Matrix<int, Dynamic, Dynamic> a, Matrix<int, Dynamic, Dynamic> b) {
    std::vector<std::tuple<Matrix<int, Dynamic, Dynamic>, std::string>> steps;
    
    // Ensure matrices can be multiplied
    if (a.cols() != b.rows()) {
        throw std::invalid_argument("Matrix dimensions do not match for multiplication.");
    }

    int rowsA = a.rows();
    int colsA = a.cols();
    int colsB = b.cols();

    Matrix<int, Dynamic, Dynamic> result = Matrix<int, Dynamic, Dynamic>::Zero(rowsA, colsB);

    // Perform matrix multiplication manually to record each step
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            for (int k = 0; k < colsA; ++k) {
                result(i, j) += a(i, k) * b(k, j);

                // Record the step
                Matrix<int, Dynamic, Dynamic> stepMatrix = result;
                std::ostringstream description;
                description << "Multiplying row " << i << " of matrix A by column " << j << " of matrix B. ";
                description << "Added " << a(i, k) << " * " << b(k, j) << " to result(" << i << ", " << j << ").";
                steps.emplace_back(stepMatrix, description.str());
            }
        }
    }

    return steps;
}

bool MatrixMultiplicationSolver::verify(Matrix<int, Dynamic, Dynamic> a, Matrix<int, Dynamic, Dynamic> b, Matrix<int, Dynamic, Dynamic> result) {
    // Perform matrix multiplication using Eigen's built-in function
    Matrix<int, Dynamic, Dynamic> expected = a * b;

    // Compare the expected result with the given result
    return expected == result;
}