/*
 *	Author: Kaylee Thomas & Jerin Spencer
 *
 *	Description:
 *		Defines functions for dependent class RowReductionSolver.
 *		
 *		Apart of the Matrix Solver project which aims to give a
 *		step-by-step on how to solve linear algebra matrix problems.
 *
 *
 *	Functions:
 *		solve(Matrix)
 *			Through a series of row operations, reduces the matrix into redcued echelon form
 *			while saving intermediate matrices and step descriptions
 *			
 *			returns vector
 *
 * 		verify(Matrix)
 * 			Determines if inputted matrix can be roe reduced
 * 			
 * 			returns bool
 *
 *	History
 *		5/28/24		Jerin Spencer 	Initial file created
 *		5/30/24		Jerin Spencer	Reduces to echeclon form, stops if hits a zero. Inputs limited to square matrices. 
 *		6/1/24		Kaylee Thomas	Implemented further reduction to reduced echelon form. Allowed for non-square matrix inputs.
 *
 * */


#include "solvers.hpp"
#include <stdexcept>
#include <iostream>

using namespace Eigen;
using namespace std;

vector<tuple<Matrix<float, Dynamic, Dynamic>, string>> RowReductionSolver::solve(Matrix<float, Dynamic, Dynamic> mat) {

	// Create holder of to contain steps
    vector<tuple<Matrix<float, Dynamic, Dynamic>, string>> steps;
    
	// Inputted Matrix
	string cur_step = "";
	steps.emplace_back(mat, cur_step);
	
	// Get dimension of matrice
    int numRows = mat.rows();
	int numCols = mat.cols();

	// Starting position is top left corner
	int cur_rowi = 0; 
	int cur_coli = 0; 

	bool nonZeroFound;
	
	// String holders for documenting steps
	string entry;
	string entry_rowi;
	string entry_coli;
	string piv_rowi;
	string piv_coli;
	string pivot;

	// Document Step
	cur_step = "Begin with left-most nonzero column and choose a pivot. Pivots must be to the right and below previous pivot";
	steps.emplace_back(mat, cur_step);		
	
	// Traverse matrix diagonally from top-left to bottom-right
	while(cur_rowi != numRows && cur_coli != numCols){
		
		// Reset bool
		nonZeroFound = false;

		// Current position is zero and cannot be pivot 
		if(mat(cur_rowi, cur_coli) == 0){
			
			// Search entries below within column for nonzero
			for(int i = cur_rowi + 1; i < numRows; i++){
				
				// Found a non zero entry
				if(mat(i, cur_coli) != 0){
					
					nonZeroFound = true;
					
					// Convert values to string for documenting
					entry_rowi = to_string(i + 1);
					entry_coli = to_string(cur_rowi + 1);
					piv_rowi = to_string(cur_rowi + 1);
				
					// Document Steps
					cur_step = "Select nonzero entry to become pivot: ("+entry_rowi+","+entry_coli+")";
					steps.emplace_back(mat, cur_step);
					
					
					// Swap rows so that pivot position is on top
					mat.row(i).swap(mat.row(cur_rowi));

					
					// Documnet Step
					cur_step = "Move entry in row" + entry_rowi +" into pivot position in row"
								+ piv_rowi +" by swapping the rows";
					steps.emplace_back(mat, cur_step);
					
					break;
				}
			
			}
			
			// Non-zero entry was not found
			if(!nonZeroFound){
				
				// Move to next column but same row
				cur_coli++;
				continue;
			}

		}
		// Current position is nonzero and can be pivot 
		else{
			
			// Convert values to string to document step
			pivot = to_string(mat(cur_rowi, cur_coli));
			piv_rowi = to_string(cur_rowi + 1);
			piv_coli = to_string(cur_coli + 1);

			// Document Step
			cur_step = "Selected pivot is " +pivot+" in position ("+piv_rowi+","+piv_coli+")";
			steps.emplace_back(mat, cur_step);		


			// Convert pivot to 1 by dividing whole row by pivot	
			if (mat(cur_rowi, cur_coli) != 1){

				float scalar = 1/mat(cur_rowi, cur_coli);;
				mat.row(cur_rowi) *= scalar;
				
				//Document Step	
				cur_step = "Convert pivot " + pivot +" into 1 by multiplying row"
							+ piv_rowi +" by (1/pivot) = " +to_string(scalar);
				steps.emplace_back(mat, cur_step);
			}
			
			// Document Step
			cur_step = "Within column"+piv_coli+" convert the entries below the pivot into zeroes";
			steps.emplace_back(mat, cur_step);

			// Zero out entries below the pivot 
			for(int i = cur_rowi + 1; i < numRows; i++){
				
				if(mat(i, cur_coli) != 0){
					
					// Convert values to string to document step
					entry = to_string(mat(i, cur_coli));
					entry_rowi = to_string(i+1);
					entry_coli = to_string(cur_coli + 1);

					// Multiple pivot row with entry below and subtract from row
					mat.row(i) -= mat.row(cur_rowi) * mat(i, cur_coli);
					
				
					// Document Step
					cur_step = "Convert entry (" +entry_rowi+","+entry_coli+") into zero by replacing row"+entry_rowi+
								" with [row"+entry_rowi+" - (row"+piv_rowi+" * "+entry+")]";
					steps.emplace_back(mat, cur_step);
					
				}
			}

		}

		// Move right and down form current position
		cur_rowi++; 
		cur_coli++; 
	}

		
	// Go back to previous position within scope of matrix
	cur_rowi--; 
	cur_coli--; 


	// Zero out above pivot entries until position is outside the matrix
	// Traverse matrix diagonally from bottom-right to top-left
	while(cur_rowi != -1 && cur_coli != -1){
	

		// Current position is not a pivot, 
		if(mat(cur_rowi, cur_coli) != 1){
			
			// Move to left column same row
			cur_coli--;
			continue;
		}	


		// Current position is a pivot
		else if(mat(cur_rowi, cur_coli) == 1){

			// Document Step
			cur_step = "Within column"+piv_coli+" convert the entries below the pivot into zeroes";
			steps.emplace_back(mat, cur_step);

			// Zero out above entries within Column
			for(int i = cur_rowi - 1; i >= 0; i--){
				
				if(mat(i, cur_coli) != 0){
					
					// Convert values to string to document step
					entry = to_string(mat(i, cur_coli));
					entry_rowi = to_string(i+1);
					entry_coli = to_string(cur_coli + 1);
					
					// Multiple pivot row with entry below and subtract from row
					mat.row(i) -= mat.row(cur_rowi) * mat(i, cur_coli);
					
					// Document Step
					cur_step = "Convert entry (" +entry_rowi+","+entry_coli+") into zero by replacing row"+entry_rowi+
								" with [row"+entry_rowi+" - (row"+piv_rowi+" * "+entry+")]";
					steps.emplace_back(mat, cur_step);
					
				}
			}

		}

		// Move left and up (diagonal)
		cur_rowi--;
		cur_coli--;
	}

    return steps;
}

bool RowReductionSolver::verify(Matrix<float, Dynamic, Dynamic> a) {
    // Can row reduce any matrix
    return true;
}
