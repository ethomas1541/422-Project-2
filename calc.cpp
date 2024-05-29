#include "solvers/solvers.hpp"
#include <stdlib.h>
#include <iostream>

int main(){
    using namespace std;
    DerivedSolver test;
    Eigen::Matrix<int, 3, 3> a;
    Eigen::Matrix<int, 3, 3> b;
    cout << test.solve(a, b) << endl;
    cout << test.verify(a);
    return 0;
}