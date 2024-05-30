#include <solvers.hpp>
#include <stdexcept>

using namespace Eigen;
using namespace std;

vector<tuple<Matrix<float, Dynamic, Dynamic>, string>> RowReductionSolver::solve(Matrix<float, Dynamic, Dynamic> mat) {
    vector<tuple<Matrix<float, Dynamic, Dynamic>, string>> steps;

    Matrix<float, Dynamic, Dynamic> result = Matrix<float, Dynamic, Dynamic>::Zero(rowsA, colsB);

    return steps;
}

bool RowReductionSolver::verify(Matrix<float, Dynamic, Dynamic> a) {
    // A matrix can always be Reduced
    return true
}