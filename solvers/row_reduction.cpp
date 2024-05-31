#include <solvers.hpp>
#include <stdexcept>

using namespace Eigen;
using namespace std;

vector<tuple<Matrix<float, Dynamic, Dynamic>, string>> RowReductionSolver::solve(Matrix<float, Dynamic, Dynamic> mat) {
    //initial set up 
    r = mat.rows();
    vector<tuple<Matrix<float, Dynamic, Dynamic>, string>> steps;
    string cur_step = ""

    //for each row
    for(int row = 0; row < r; row++)
    {   //for each row below this row
        string cur_row = to_string(row);
        string cur_piv = to_string(mat(row,row));

        for(int brow = row; brow < brow++ )
        {
            string bel_row = to_string(brow);
            string bel_piv = to_string(mat(brow,row));
            if(mat(row,row) != 0)
            {
                float factor = -1*(mat(brow,row)/mat(row,row));
                //multiply it by factor, then add to brow
                mat.row(brow) += factor * mat.row(row);
                //multiply row "row" by "-(row,row)/(brow,row)" and add it to row "brow"
                cur_step = "multply row " + cur_row + " by " + bel_piv + "/" + cur_piv + " and add to " + bel_row;
                steps.push_back((mat,cur_step));
            }
            else
            {
                cur_step = "a pivot position is 0, thefore this matrix can not be reduced further."
                steps.push_back((mat,cur_step));
                return steps;
            }
        }
    }
    return steps;
}

bool RowReductionSolver::verify(Matrix<float, Dynamic, Dynamic> a) {
    // this program can only reduce square matrices
    return (a.rows() == a.col());
}