#include <eigen/Eigen/Dense>
#include <vector>
#include <tuple>
#include <string>

using namespace Eigen;

//abstract solver class
class Solver{
    public:
        virtual Matrix <float, Dynamic, Dynamic> solve(Matrix <float, Dynamic, Dynamic> a, Matrix <float, Dynamic, Dynamic> b) = 0;
        virtual bool verify(Matrix <float, Dynamic, Dynamic> matrix) = 0;
};

//sample solver declaration
class DerivedSolver: public Solver{
    public:
        Matrix <float, Dynamic, Dynamic> solve(Matrix <float, Dynamic, Dynamic> a, Matrix <float, Dynamic, Dynamic> b);
        bool verify(Matrix <float, Dynamic, Dynamic> matrix);
};

// Matrix multiplication solver
class MatrixMultiplicationSolver : public Solver {
    public: 
        std::vector<std::tuple<Matrix<float, Dynamic, Dynamic>, std::string>> solve(Matrix<float, Dynamic, Dynamic> a, Matrix<int, Dynamic, Dynamic> b);
        bool verify(Matrix<float, Dynamic, Dynamic> a, Matrix<float, Dynamic, Dynamic> b, Matrix<float, Dynamic, Dynamic> result);
}