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

    SolverRequest(string opcode, string a_rows, string a_cols, string a_entires, string b_rows, string b_cols, string b_entries){
        this->opcode = opcode;

        Matrix<float, Dynamic, Dynamic> matrix_a;
        matrix_a.resize(stoi(a_rows), stoi(a_cols));

        Matrix<float, Dynamic, Dynamic> matrix_b; 
        matrix_a.resize(stoi(b_rows), stoi(b_cols));
		
        this->matricies.push_back(matrix_a);
        this->matricies.push_back(matrix_b);

		//parse entry string
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

void printVectorTuple(result_vector vt){
	/* Prints out the contents of a vector filled with tuples to standard output*/
	for(auto& tuple: vt){
        cout << "\n" << get<0>(tuple) << "\t" << get<1>(tuple) << endl;
	}
}

int main(int argc, char **argv){
	SolverRequest request(argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
	printVectorTuple(CombinedCalc(&request));
}

//return for a 2x2 matrix should look like: 1,2,3,4 instructions-1,2,3,4 instructions-1,2,3,4 instructions-1,2,3,4 instructions...
//if returning 2 matricies use $ to separate the strings ...-1,2,3,4 instructions$5,6,7,8 instructions-...
//- is used to divide steps