#include <eigen/Eigen/Dense>
#include "solvers.hpp"
#include <iostream>

using namespace Eigen;
using namespace std;

typedef vector<tuple<Matrix<float, Dynamic, Dynamic>, string>> result_vector;

// Take the minor matrix, as given by a matrix and row, col coordinate pair.
// https://en.wikipedia.org/wiki/Minor_(linear_algebra)
Matrix<float, Dynamic, Dynamic> minor(Matrix<float, Dynamic, Dynamic> m, int row, int col){
    // Minor matrices of square matrices are always square and always of 1 less size than the parent matrix
    unsigned int minordim = m.rows() - 1;
    // Return value
    Matrix<float, Dynamic, Dynamic> ret(minordim, minordim);
    for(unsigned int i = 0; i < m.rows(); i++){
        // Ignore the row we want to remove. Don't even iterate through it.
        if(i == row){continue;}
        for(unsigned int j = 0; j < m.cols(); j++){
            // Same with the column to remove
            if(j == col){continue;}
            unsigned int ret_row = i, ret_col = j;
            // If i's row is "lower" than the removal row index, move it up by 1 position
            if(i > row){ret_row -= 1;}
            // If j's column is "further to the right" than the removal column index so move left by 1 position
            if(j > col){ret_col -= 1;}
            // Manually emplace the value at the 2-dimensional index it should be at
            ret(ret_row, ret_col) = m(i, j);
        }
    }
    return ret;
}

// Take the determinant of a matrix, using recursion if needed. Send EVERY detail to the result_vector* v parameter
float det(Matrix<float, Dynamic, Dynamic> m, result_vector* v) {
    // Return value
    float determinant = 0;
    // MATRIX MUST BE SQUARE!
    if(m.rows() == m.cols()){
        if(m.rows() == 2){
            // 2x2 matrix determinants are very easy.
            // https://en.wikipedia.org/wiki/Determinant
            determinant =  m(0, 0) * m(1, 1) - m(0, 1) * m(1,0);
            // Send data for this step
            (*v).emplace_back(make_tuple(m, "Determinant of 2x2 matrix is " + to_string(determinant) + " by formula det = ad-bc"));
        }else if(m.rows() > 2){
            // If the matrix is larger, we can use recurion to "break" it into 2x2 matrices for which the determinant
            // is easy.

            // The sign alternates in a checkerboard pattern.
            short int coefficient_sign = 1;
            for(unsigned int i = 0; i < m.rows(); i++){
                // This summation gives the determinant of a larger matrix
                // A 3x3 matrix has three relevant 2x2 minors
                // A 4x4 matrix has four relevant 3x3 minors which each have three relevant 2x2 minors, and so on
                determinant += coefficient_sign * m(0, i) * det(minor(m, 0, i), v);
                // Flip the sign
                coefficient_sign *= -1;
            }
            // Send data for this step
            (*v).emplace_back(make_tuple(m, "Determinant of larger matrix is " + to_string(determinant) + " by cofactor expansion"));
        }
    }else{
        cout << "CANNOT TAKE DETERMINANT OF NON-SQUARE MATRIX\n";
        exit(EXIT_FAILURE);
    }
    return determinant;
}

bool DeterminantSolver::verify(Matrix<float, Dynamic, Dynamic> m){
    return m.rows() == m.cols();
}

result_vector DeterminantSolver::solve(Matrix<float, Dynamic, Dynamic> m, Matrix<float, Dynamic, Dynamic> unused){
    result_vector ret;
    det(m, &ret);
    return ret;
}

/*
int main(){
    Matrix<float, 2, 2> sample2x2 = Matrix<float, 2, 2>::Zero();
    Matrix<float, 3, 3> sample3x3 = Matrix<float, 3, 3>::Zero();
    Matrix<float, 4, 4> sample4x4 = Matrix<float, 4, 4>::Zero();
    sample2x2 << 1, 2, 3, 4;
    sample3x3 << 4, 9, 8, 6, 7, 99, 22, 33, 44;
    sample4x4 << 9, 10, 11, 10, 11, 9, 4, 2, 8, 4, 6, 9, 22, 33, 11, 22;
    result_vector v, w, x;
    cout << det(sample2x2, &v) << endl;
    for(unsigned int i = 0; i < v.size(); i++){
        cout << get<0>(v[i]) << "\t" << get<1>(v[i]) << endl;
    }
    cout << det(sample3x3, &w) << endl;
    for(unsigned int i = 0; i < w.size(); i++){
        cout << get<0>(w[i]) << "\t" << get<1>(w[i]) << endl;
    }
    cout << det(sample4x4, &x) << endl;
    for(unsigned int i = 0; i < x.size(); i++){
        cout << get<0>(x[i]) << "\t" << get<1>(x[i]) << endl;
    }
}
*/