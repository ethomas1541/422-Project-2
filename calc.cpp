#include "solvers/solvers.hpp"
#include <stdlib.h>
#include <iostream>

int main(){
    using namespace std;
    DerivedSolver test;
    cout << test.solve(1, 2) << endl;
    cout << test.verify(1);
    return 0;
}