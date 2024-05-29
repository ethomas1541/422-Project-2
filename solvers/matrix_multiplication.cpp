#include <solvers.hpp>
#include <stdexcept>

using namespace Eigen;
using namespace std;

vector<tuple<Matrix<float, Dynamic, Dynamic>, string>> MatrixMultiplicationSolver::solve(Matrix<float, Dynamic, Dynamic> a, Matrix<int, Dynamic, Dynamic> b) {
    vector<tuple<Matrix<float, Dynamic, Dynamic>, string>> steps;

    int rowsA = a.rows();
    int colsA = a.cols();
    int colsB = b.cols();

    Matrix<float, Dynamic, Dynamic> result = Matrix<float, Dynamic, Dynamic>::Zero(rowsA, colsB);

    // Perform matrix multiplication manually to record each step
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            bool firstIteration = true;
            for (int k = 0; k < colsA; ++k) {
                result(i, j) += a(i, k) * b(k, j);

                // Record the step
                Matrix<float, Dynamic, Dynamic> stepMatrix = result;
                string description;
                if (firstIteration) {
                    description = "Multiplying row " + to_string(i) + " of matrix A by column " + to_string(j) + " of matrix B. ";
                    firstIteration = false;
                }
                description += "Added " + to_string(a(i, k)) + " * " + to_string(b(k, j)) + " to result(" + to_string(i) + ", " + to_string(j) + ").";
                steps.emplace_back(stepMatrix, description);
            }
        }
    }

    return steps;
}

bool MatrixMultiplicationSolver::verify(Matrix<float, Dynamic, Dynamic> a, Matrix<float, Dynamic, Dynamic> b, Matrix<float, Dynamic, Dynamic> result) {
    // Ensure matrices can be multiplied
    if (a.cols() != b.rows()) {
        throw invalid_argument("Matrix dimensions do not match for multiplication.");
    }
}