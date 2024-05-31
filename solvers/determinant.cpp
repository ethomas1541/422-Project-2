#include <eigen/Eigen/Dense>
#include <iostream>

using namespace Eigen;
using namespace std;

typedef vector<tuple<Matrix<float, Dynamic, Dynamic>, string>> result_vector;

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

float det(Matrix<float, Dynamic, Dynamic> m, result_vector* v) {
    float determinant = 0;
    if(m.rows() == m.cols()){
        if(m.rows() == 2){
            determinant =  m(0, 0) * m(1, 1) - m(0, 1) * m(1,0);
            (*v).emplace_back(make_tuple(m, "Determinant of 2x2 matrix is " + to_string(determinant) + " by formula det = ad-bc"));
        }else if(m.rows() > 2){
            short int coefficient_sign = 1;
            for(unsigned int i = 0; i < m.rows(); i++){
                determinant += coefficient_sign * m(0, i) * det(minor(m, 0, i), v);
                coefficient_sign *= -1;
            }
            (*v).emplace_back(make_tuple(m, "Determinant of larger matrix is " + to_string(determinant) + " by cofactor expansion"));
        }
    }else{
        cout << "CANNOT TAKE DETERMINANT OF NON-SQUARE MATRIX\n";
        exit(EXIT_FAILURE);
    }
    return determinant;
}

bool verify(Matrix<float, Dynamic, Dynamic> m){
    return m.rows() == m.cols();
}

result_vector solve(Matrix<float, Dynamic, Dynamic> m){
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