/*
 *	Author: Gus Coochran & Jerin Spencer
 *
 *	Description:
 *		Processes solver requests to call the appropriate solver
 *		
 *
 *	Functions:
 *		matToEigen(SolverRequest)
 *			converts the matrix, or matricies, in a solver to the matrix in the Eigen Library
 *
 *			returns vector<Matrix <float, Dynamic, Dynamic>>
 *		CombinedCalc(SolverRequest)
 *			The namesake of the module; processes a solver request to call the correct solver
 *
 *			returns vector<tuple<Matrix<float, Dynamic, Dynamic>, string>> 
 * 
 *
 *	History
 *		5/31/24		Initial creation
 *		6/3/24
 *
 * */
#include "solvers.hpp"
#include <iostream>

using namespace std;

class SolverRequest{
public:
    string opcode;
    vector<Matrix<float, Dynamic, Dynamic>> matricies;

    SolverRequest(string opcode, char **argv){
		int a_rows = stoi(argv[2]);
		int a_cols = stoi(argv[3]);
		string a_entries = argv[4];
		int b_rows = stoi(argv[a_rows * a_cols + 1]);
		int b_cols = stoi(argv[a_rows * a_cols + 2]);
		string b_entries = argv[a_rows * a_cols + 3];

        this->opcode = opcode;

        Matrix<float, Dynamic, Dynamic> matrix_a;
        matrix_a.resize(a_rows, a_cols);

        Matrix<float, Dynamic, Dynamic> matrix_b; 
        matrix_a.resize(b_rows, b_cols);
		
        matrix_a << 1,2,3,4,5,6,7,8,9;
		matrix_b << 1,2,3,4,5,6,7,8,9;

        this->matricies.push_back(matrix_b);
		this->matricies.push_back(matrix_a);
		cout << matrix_a;
		cout << matrix_b;
		//idk
		// string bbuffer[100];
		// int bindex = 0;
		// splitString(b_entries, ',', bbuffer, bindex);
		// for(int i = 0; i < stoi(b_rows) - 1; i++){
		// 	for(int j = 0; j < stoi(b_cols) - 1; j++){
		// 		matrix_b(i,j) = stoi(bbuffer[i + j]);
		// 	}
			
		// }
    };
};

vector<tuple<Matrix<float, Dynamic, Dynamic>, string>> CombinedCalc(SolverRequest *req)
{
	//Takes a solver request and parses it for the appropriate solver

	/*
	1) get matrix from solver
	2) use code to find which solver to use from request
	3) put matrix into solver, then return
	*/
	//1)
	// vector<Matrix <float, Dynamic, Dynamic>> mats = matToEigen(req);
	vector<tuple<Matrix<float, Dynamic, Dynamic>, string>> ret;

	vector<Matrix<float, Dynamic, Dynamic>> mats = req->matricies;

	//2 and 3 in if elif chain)
	if(req->opcode == "row")
	{
		RowReductionSolver tool;
		ret = tool.solve(mats[0], mats[1]);
	}
	else if(req->opcode == "mult")
	{
		MatrixMultiplicationSolver tool;
		ret = tool.solve(mats[0], mats[1]);
	}
	else if(req->opcode == "det")
	{
		DeterminantSolver tool;
		ret = tool.solve(mats[0], mats[1]);
	}
	else if(req->opcode == "inv")
	{
		InverseSolver tool;
		ret = tool.solve(mats[0], mats[1]);
	}
	return ret;
}

void unfoldMatrix(Matrix<float, Dynamic, Dynamic> m){
	for(unsigned int i = 0; i < m.rows(); i++){
		for(unsigned int j = 0; j < m.cols(); j++){
			float pos_i_j = m(i, j);
			if(!i && !j){
				cout << pos_i_j;
			}else{
				cout << "," << pos_i_j;
			}
		}
	}
	cout << " ";
}

void printVectorTuple(result_vector vt){
	/* Prints out the contents of a vector filled with tuples to standard output*/
	for(auto& tuple: vt){
    	unfoldMatrix(get<0>(tuple));
		cout << get<1>(tuple) << "&";
	}
}

int main(int argc, char **argv){
	SolverRequest request(argv[1], argv);
	printVectorTuple(CombinedCalc(&request));
}

//return for a 2x2 matrix should look like: 1,2,3,4 instructions-1,2,3,4 instructions-1,2,3,4 instructions-1,2,3,4 instructions...
//if returning 2 matricies use $ to separate the strings ...-1,2,3,4 instructions$5,6,7,8 instructions-...
//& is used to divide steps