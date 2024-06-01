#include "solvers.hpp"
#include "row_reduction.cpp"
#include "matrix_multiplication.cpp"
#include "determinant.cpp"
#include "inverse.cpp"

//it returns a vector cause there are 2 matricies in the solver
vector<Matrix <float, Dynamic, Dynamic>> matToEigen(SolverRequest req)
{
	//a fucntion to convert the solver request matricies to eigen matracies
	vector<Matrix <float, Dynamic, Dynamic>> ret; //the return
	//needs to be filled in

	return ret;

}

vector<tuple<Matrix<float, Dynamic, Dynamic>, string>> CombinedCalc(SolverRequest req)
{
	//Takes a solver request and parses it for the appropriate solver

	/*
	1) get matrix from solver
	2) use code to find which solver to use from request
	3) put matrix into solver, then return
	*/
	//1)
	vector<Matrix <float, Dynamic, Dynamic>> mats = matToEigen(req);
	vector<tuple<Matrix<float, Dynamic, Dynamic>, string>> ret;

	//2 and 3 in if elif chain)
	if(req.opcode == "row")
	{
		RowReductionSolver tool;
		ret = tool.solve(mats[0]);
	}
	else if(req.opcode == "mult")
	{
		MatrixMultiplicationSolver tool;
		ret = tool.solve(mats[0], mats[1]);
	}
	else if(req.opcode == "det")
	{
		DeterminantSolver tool;
		ret = tool.solve(mats[0]);
	}
	else if(req.opcode == "inv")
	{
		InverseSolver tool;
		ret = tool.solve(mats[0]);
	}
	return ret;
}