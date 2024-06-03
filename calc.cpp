#include "solvers/solvers.hpp"
#include <stdlib.h>
#include <iostream>

int main(){
    // ELIJAH'S TEST CODE
    using namespace std;
    DeterminantSolver detsolv;
    Matrix<float, 4, 4> sample4x4 = Matrix<float, 4, 4>::Zero();
    sample4x4 << 9, 10, 11, 10, 11, 9, 4, 2, 8, 4, 6, 9, 22, 33, 11, 22;
    result_vector det_result = detsolv.solve(sample4x4, sample4x4);
    for(unsigned int i = 0; i < det_result.size(); i++){
        cout << get<0>(det_result[i]) << "\t" << get<1>(det_result[i]) << endl;
    }

    MatrixMultiplicationSolver multsolv;
    Matrix<float, 2, 2> sample2x2a = Matrix<float, 2, 2>::Zero(), sample2x2b = Matrix<float, 2, 2>::Zero();
    sample2x2a << 4, 0, 0, 4;
    sample2x2b << 2, 2, 2, 2;
    result_vector mul_result = multsolv.solve(sample2x2a, sample2x2b);
    for(unsigned int i = 0; i < mul_result.size(); i++){
        cout << get<0>(mul_result[i]) << "\t" << get<1>(mul_result[i]) << endl;
    }

    return 0;
}