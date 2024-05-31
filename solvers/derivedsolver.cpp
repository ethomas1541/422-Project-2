#include "solvers.hpp"
//sample solver implementation
Matrix <float, Dynamic, Dynamic> DerivedSolver::solve(Matrix <float, Dynamic, Dynamic> a, Matrix <float, Dynamic, Dynamic> b){
    //matrices wont be undefined when they come from the solver request
    a.setZero();
    b.setZero();
    return a * b;
}

bool DerivedSolver::verify(Matrix <float, Dynamic, Dynamic> matrix){
    return true;
}