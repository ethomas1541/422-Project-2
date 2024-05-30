#include <eigen/Eigen/Dense>
#include <iostream>

using namespace Eigen;
using namespace std;

// Matrix<float, Dynamic, Dynamic>
Matrix<float, Dynamic, Dynamic> minor(Matrix<float, Dynamic, Dynamic> m, int row, int col){
    unsigned int minordim = m.rows() - 1;
    Matrix<float, Dynamic, Dynamic> ret(minordim, minordim);
    for(unsigned int i = 0; i < m.rows(); i++){
        if(i == row){continue;}
        for(unsigned int j = 0; j < m.cols(); j++){
            if(j == col){continue;}
            unsigned int ret_row = i, ret_col = j;
            if(i > row){ret_row -= 1;}
            if(j > col){ret_col -= 1;}
            ret(ret_row, ret_col) = m(i, j);
        }
    }
    return ret;
}

float solve(Matrix<float, Dynamic, Dynamic> m) {
    float det = 0;
    if(m.rows() == m.cols()){
        if(m.rows() == 2){
            det =  m(0, 0) * m(1, 1) - m(0, 1) * m(1,0);
        }else if(m.rows() > 2){
            short int coefficient_sign = 1;
            for(unsigned int i = 0; i < m.rows(); i++){
                det += coefficient_sign * m(0, i) * solve(minor(m, 0, i));
                coefficient_sign *= -1;
            }
        }
    }else{
        cout << "CANNOT TAKE DETERMINANT OF NON-SQUARE MATRIX\n";
        exit(EXIT_FAILURE);
    }
    return det;
}

bool verify(Matrix<float, Dynamic, Dynamic> m){
    return m.rows() == m.cols();
}

int main(){
    Matrix<float, 2, 2> sample2x2 = Matrix<float, 2, 2>::Zero();
    Matrix<float, 3, 3> sample3x3 = Matrix<float, 3, 3>::Zero();
    Matrix<float, 4, 4> sample4x4 = Matrix<float, 4, 4>::Zero();
    sample2x2 << 1, 2, 3, 4;
    sample3x3 << 4, 9, 8, 6, 7, 99, 22, 33, 44;
    sample4x4 << 9, 10, 11, 10, 11, 9, 4, 2, 8, 4, 6, 9, 22, 33, 11, 22;
    cout << solve(sample2x2) << endl;
    cout << solve(sample3x3) << endl;
    cout << solve(sample4x4) << endl;
}