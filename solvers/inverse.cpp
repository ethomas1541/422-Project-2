/*
 *	Author: Kaylee Thomas
 *
 * 	Description
 * 		Defines dependent Class InverseSolver functions
 *
 *	Functions:
 *		solve(Matrix)
 *			Finds inverse and saves intermediary matrices and step descriptions
 *			returns vector
 *
 *		verify(Matrix)
 *			Determines if inputted matrix is invertible
 *			returns bool
 *
 *	History
 *		5/28/24	Kaylee Thomas	Initial Creation
 *		5/31/24	Kaylee Thomas	Implemented ability to solve 1x1 and 2x2 matrices
 *		6/1/24	Kaylee Thomas	Implemented ability to solve 3x3 matrices
 *
 * */
#include "solvers.hpp"
#include <iostream>


using namespace Eigen;
using namespace std;


vector<tuple<Matrix<float, Dynamic, Dynamic>, string>> InverseSolver::solve(Matrix<float, Dynamic, Dynamic> inp_Mat){
	/* Finds and describes the steps taken to get the inverse of a matrix */

	// create holder for steps
	vector<tuple<Matrix<float, Dynamic, Dynamic>, string>> steps;
	
	string description;
	//description = "Inputted Matrix";
	//steps.emplace_back(inp_Mat, description);
	
	// Not Invertible
	if(!verify(inp_Mat)){
	
		description = "Matrix is not invertible";
		steps.emplace_back(inp_Mat, description);
	
	}
	
	// Invertible and Identity matrix
	else if(inp_Mat.isIdentity()){

		// no further steps need, inverse of identity is identity
		description = "The inverse of an identity matrix is itself";
		steps.emplace_back(inp_Mat, description);
	
	}
	// Invertible and Not Identity Matix
	else{

		// Get dimensions of inputted matrix
		int dim = inp_Mat.rows();

		// Create holder for inverse matrix filled with zeros
		Matrix<float, Dynamic, Dynamic> inverse = Matrix<float, Dynamic, Dynamic>::Zero(inp_Mat.rows(), inp_Mat.cols());
			
		// Testing fill with zeros
		//description = "Matrix filled with zeros";
		//steps.emplace_back(inverse, description);


		// 1x1 Case
		if(dim == 1){
			
			// Formula:	[a] -> [1/a]
			float a = inp_Mat(0,0);	
			string a_str = to_string(a);
			
			// It shouldn't if verified worked but just in case
			if(a != 0){
				inverse(0,0) = 1/a;
				
				// Convert floats to string
				string rep_a = to_string(1/a);
			
				// Document Step
				description = "The inverse of a 1x1 matrix is the recipical of the entry " 
						+ a_str + " -> 1/" + a_str + " = " + rep_a;
				steps.emplace_back(inverse, description);
		

			}else{
				description = "Matrix is not invertible";
				steps.emplace_back(inp_Mat, description);
			}
				
				
		}
			
		// 2x2 Case
		else if(dim == 2){
				
			// Formula:	[a, b ; c, d] -> 1/(ad-bc)[d, -b; -c, a]

			// Get individual values
			float a = inp_Mat(0,0);
			float b = inp_Mat(0,1);
			float c = inp_Mat(1,0);
			float d = inp_Mat(1,1);

			// Document Step				
			description = "Let a bet the top-left, b be the top-right, c be bottom-left, and d be bottom-left";
			steps.emplace_back(inp_mat, description);
			

			// calculate det (ad-bc)
			float det = (a*d) - (b*c);
	
			// Create strings of the values
			string str_a = to_string(a);
			string str_b = to_string(b);
			string str_c = to_string(c);
			string str_d = to_string(d);
			string det_str = to_string(det);

			description = "Find the determinant by calculating ad-bc = " 
							+ str_a + "*" + str_b + "-" + str_d + "*" + str_c + " = " + det_str;
			steps.emplace_back(inverse, description);
				
			// input values into inverse
			if(det != 0){
				//float scalar = 1/det;
				inverse(0,0) = (1/det) * d;
				inverse(0,1) = (1/det) * (-b);
				inverse(1,0) = (1/det) * (-c);
				inverse(1,1) = (1/det) * a;
			}
				
			// Document Step
			description = "Swap a and d, negate b and c, and then muliply each entry with 1/"+ det_str;
			steps.emplace_back(inverse, description);
				
		}
			
		
		// 3x3 Case 
		else if(dim == 3){	
			// row reduce with unit vectors [m | e1] , [m | e2] , [m | e3]	
			
			// Create matrix to save steps, initially filled with zeros
			Matrix<float, Dynamic, Dynamic> stepMatrix;
			stepMatrix = Matrix<float, Dynamic, Dynamic>::Zero(inp_Mat.rows(), inp_Mat.cols()+1);
			

			// Copy input to fill in stepMatrix leaving last column as zeros
			for(int i = 0; i < dim; i++){
				for(int j = 0; j < dim; j++){
					stepMatrix(i,j) = inp_Mat(i,j);
				}
			}
			
			// Create Matrix to hold row reduced step mattix
			Matrix<float, Dynamic, Dynamic> rr_stepMatrix;
		

			// Create object from sibling class
			RowReductionSolver rrsolver;


			// Holder for steps from rowReductionSolver
			vector<tuple<Matrix<float, Dynamic, Dynamic>>, string> rowReduce_steps;
			tuple<Matrix<float, Dynamic, Dynamic>, string> last_rr_step;
			

			for(int i = 0; i < dim; i++){
				// Make last column unit vector
				stepMatrix(i,dim) = 1;
				
				// Document step
				description = "Create an augmented matrix with given matrix and unit vector e"
								+ to_string(i+1) + " as right-most column";
				steps.emplace_back(stepMatrix, description);

				// Row reduce to reduce echelon form
				rowReduce_steps = rrsolver.solve(stepMatrix);

				// Get final matrix from the last step of rowReduce_steps
				last_step = rowReduce_steps.back();
				rr_stepMatrix = get<0>(last_step);
				

				// Document step
				description = "Convert augmented matrix to reduced echelon form using row operations";
				steps.emplace_back(rr_stepMatrix, description);
				
				
				// Fill inverse matrix col k with last column of rr_stepMatrix
				for(int j = 0; j < dim; j++){
					inverse(j,i) = rr_stepMatrix(j,dim);

				}
				
				// Document step
				description = "Take right-most column of the augmented reduced form matrix and place it in column "
								+ to_string(i+1);
				steps.emplace_back(inverse, description);


				// Zero out last column
				stepMatrix(i, dim) = 0;

			}
		}
			

	}	
	
	// Return vector containg steps to find inverse
	return steps;
}

bool InverseSolver::verify(Matrix<float, Dynamic, Dynamic> m){
	/* 
	 * Determines if inputted matrix is invertible by checking
	 * the dimensions and the determinant of the matrix 
	 */

	bool invertible = true;
	
	// Must be a square matrix
	if(m.cols() != m.rows()){
		invertible = false;
	}

	// Determinant cannot be zero 
	else{
		int det = m.determinant();
		if(det == 0){
			invertible = false;
		}
	}
	return invertible;
}

