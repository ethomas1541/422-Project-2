#include "solvers.hpp"
//sample solver implementation
Matrix <int, Dynamic, Dynamic> DerivedSolver::solve(Matrix <int, Dynamic, Dynamic> a, Matrix <int, Dynamic, Dynamic> b){
    //matrices wont be undefined when they come from the solver request
    a.setZero();
    b.setZero();
    return a * b;
}

bool DerivedSolver::verify(Matrix <int, Dynamic, Dynamic> matrix){
    return true;
}