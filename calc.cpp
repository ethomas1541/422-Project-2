#include "solvers/solvers.hpp"
#include <stdlib.h>
#include <iostream>


using namespace std;

void printVectorTuple(result_vector vt){
	/* Prints out the contents of a vector filled with tuples to standard output*/

	for(auto& tuple: vt){
        cout << "\n" << get<0>(tuple) << "\t" << get<1>(tuple) << endl;
	}
}


int main(){
	
	// Testing Determinant Solver
    cout << "\nTesting Determinant Solver\n";
	DeterminantSolver detsolv;
    Matrix<float, 4, 4> sample4x4 = Matrix<float, 4, 4>::Zero();
    sample4x4 << 9, 10, 11, 10, 11, 9, 4, 2, 8, 4, 6, 9, 22, 33, 11, 22;
    result_vector det_result = detsolv.solve(sample4x4, sample4x4);
	printVectorTuple(det_result);

	// Testing MatrixMultiplcationSolver
    cout << "\nTesting Matrix Multiplication Solver\n";
    MatrixMultiplicationSolver multsolv;
    Matrix<float, 2, 2> sample2x2a = Matrix<float, 2, 2>::Zero(), sample2x2b = Matrix<float, 2, 2>::Zero();
    sample2x2a << 4, 0, 0, 4;
    sample2x2b << 2, 2, 2, 2;
    result_vector mul_result = multsolv.solve(sample2x2a, sample2x2b);
	printVectorTuple(mul_result);


    // Testing RowReductionSolver
    cout << "\nTesting Row Reduction Solver\n";
	RowReductionSolver rowredsolv;
    Matrix<float, 3, 3> rr_sample3x3 = Matrix<float, 3, 3>::Zero();
    rr_sample3x3 << 1, 2, 0, 2,-1,2,-1,3,-2;
    result_vector rr_result = rowredsolv.solve(rr_sample3x3, rr_sample3x3);
	printVectorTuple(rr_result);
	// Final matrix should be 	1, 0,  0.8
	// 							0, 1, -0.4
	// 							0, 0,  0
	

    // Testing InverseSolver
    cout << "\nTesting Inverse Solver\n";
	InverseSolver invsolv;
    Matrix<float, 3, 3> inv_sample3x3 = Matrix<float, 3, 3>::Zero();
    inv_sample3x3 << 2, 0, -1, 5, 1, 0, 0, 1, 3;
    result_vector inv_result = invsolv.solve(inv_sample3x3, inv_sample3x3);
	printVectorTuple(inv_result);
	// Final matrix shoulde be	  3, -1,  1
	//							-15,  6, -5
	//							  5, -2,  2

    return 0;
}
