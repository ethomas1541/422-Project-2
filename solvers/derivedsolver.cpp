#include "solvers.hpp"
//sample solver implementation
int DerivedSolver::solve(int a, int b){
    return a + b;
}

bool DerivedSolver::verify(int a){
    return true ? a > 0 : false;
}