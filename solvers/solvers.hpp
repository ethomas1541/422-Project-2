#include <eigen/Eigen/Dense>
using namespace Eigen;
//abstract solver class
class Solver{
    public:
        virtual Matrix <int, Dynamic, Dynamic> solve(Matrix <int, Dynamic, Dynamic> a, Matrix <int, Dynamic, Dynamic> b) = 0;
        virtual bool verify(Matrix <int, Dynamic, Dynamic> matrix) = 0;
};

//sample solver declaration
class DerivedSolver: public Solver{
    public:
        Matrix <int, Dynamic, Dynamic> solve(Matrix <int, Dynamic, Dynamic> a, Matrix <int, Dynamic, Dynamic> b);
        bool verify(Matrix <int, Dynamic, Dynamic> matrix);
};