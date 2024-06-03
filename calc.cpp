#include "solvers/solvers.hpp"
#include <stdlib.h>
#include <iostream>


using namespace std;

void printVectorTuple(result_vector vt){
	
	for(auto& tuple: vt){
        cout << get<0>(tuple) << "\t" << get<1>(tuple) << endl;
	}
}


int main(){
    // ELIJAH'S TEST CODE
    DeterminantSolver detsolv;
    Matrix<float, 4, 4> sample4x4 = Matrix<float, 4, 4>::Zero();
    sample4x4 << 9, 10, 11, 10, 11, 9, 4, 2, 8, 4, 6, 9, 22, 33, 11, 22;
    result_vector det_result = detsolv.solve(sample4x4, sample4x4);
	printVectorTuple(det_result);

    MatrixMultiplicationSolver multsolv;
    Matrix<float, 2, 2> sample2x2a = Matrix<float, 2, 2>::Zero(), sample2x2b = Matrix<float, 2, 2>::Zero();
    sample2x2a << 4, 0, 0, 4;
    sample2x2b << 2, 2, 2, 2;
    result_vector mul_result = multsolv.solve(sample2x2a, sample2x2b);
	printVectorTuple(mul_result);

    return 0;
}
