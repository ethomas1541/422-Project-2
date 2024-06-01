#include <eigen/Eigen/Dense>
#include <vector>
#include <tuple>
#include <string>

using namespace Eigen;

typedef std::vector<std::tuple<Matrix<float, Dynamic, Dynamic>, std::string>> result_vector;

//abstract solver class
class Solver{
    public:
        virtual result_vector solve(Matrix <float, Dynamic, Dynamic> a, Matrix <float, Dynamic, Dynamic> b);
        virtual bool verify(Matrix <float, Dynamic, Dynamic> matrix) = 0;
};

//sample solver declaration
class DerivedSolver: public Solver{
    public:
        result_vector solve(Matrix <float, Dynamic, Dynamic> a, Matrix <float, Dynamic, Dynamic> b);
        bool verify(Matrix <float, Dynamic, Dynamic> matrix);
};

// Matrix multiplication solver
class MatrixMultiplicationSolver : public Solver {
    public: 
        result_vector solve(Matrix<float, Dynamic, Dynamic> a, Matrix<float, Dynamic, Dynamic> b);
        bool verify(Matrix<float, Dynamic, Dynamic> a, Matrix<float, Dynamic, Dynamic> b, Matrix<float, Dynamic, Dynamic> result);
};

class DeterminantSolver : public Solver{
    public:
        result_vector solve(Matrix<float, Dynamic, Dynamic> a, Matrix<float, Dynamic, Dynamic> b);
        bool verify(Matrix<float, Dynamic, Dynamic> m);
};

class RowReductionSolver : public Solver {
    public: 
        result_vector solve(Matrix<float, Dynamic, Dynamic> a, Matrix<float, Dynamic, Dynamic> b);
        bool verify(Matrix<float, Dynamic, Dynamic> mat);
};

// Inverse Solver
class InverseSolver : public Solver {
    public: 
        result_vector solve(Matrix<float, Dynamic, Dynamic> a, Matrix<float, Dynamic, Dynamic> b);
        bool verify(Matrix<float, Dynamic, Dynamic> mat);
};
