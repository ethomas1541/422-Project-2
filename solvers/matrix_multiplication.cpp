/*
 *	Author: Drew Tweedale
 *
 * 	Description
 * 		Defines dependent Class Matrix Multiplication functions
 *
 *	Functions:
 *		solve(Matrix, Matrix)
 *			Find the matrix product and returns intermediary matricies.
 *			returns vector
 *
 *		verify(Matrix)
 *			Determines if inputted matrices are multipliable.
 *			returns bool
 *
 *	History
 *		5/28/24	Drew Tweedale	Initial Creation
 *		5/30/24 Drew Tweedale   Finished implementation.
 *
 * */

#include <iostream>
#include "solvers.hpp"
#include <stdexcept>
#include <iomanip>
#include <cmath>

using namespace Eigen;
using namespace std;

vector<tuple<Matrix<float, Dynamic, Dynamic>, string>> MatrixMultiplicationSolver::solve(Matrix<float, Dynamic, Dynamic> a, Matrix<float, Dynamic, Dynamic> b) {
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
                // Format numbers properly
                auto formatNumber = [](float num) {
                    if (fabs(num - round(num)) < 1e-6) {
                        return to_string(static_cast<int>(num));
                    } else {
                        ostringstream oss;
                        oss << fixed << setprecision(6) << num;
                        return oss.str();
                    }
                };
                description += "Added " + formatNumber(a(i, k)) + " * " + formatNumber(b(k, j)) + " to result(" + to_string(i) + ", " + to_string(j) + ").";
                steps.emplace_back(stepMatrix, description);
            }
        }
    }

    return steps;
}

bool MatrixMultiplicationSolver::verify(Matrix<float, Dynamic, Dynamic> a, Matrix<float, Dynamic, Dynamic> b) {
    // Ensure matrices can be multiplied
    if (a.cols() != b.rows()) {
        throw invalid_argument("Matrix dimensions do not match for multiplication.");
        return false;
    }
    return true;
}

