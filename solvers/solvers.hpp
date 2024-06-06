/*
 *	Authors: All group members
 *      
 *      Gus Cochran, Jerin Spencer, Elijah Thomas, Kaylee Thomas, Drew Tweedale
 *
 * 	Description
 * 		Defines a base solver class with virtual methods and several derived solver classes with distinct behaviors.
 *
 *	Functions:
 *		solve(Matrix, Matrix)
 *			Abstract base class, inherited by derived classes that make specific determinations on what "solve" means.
 *          Has "slots" for two matrices, though not all operations require both of these. Some solvers leave one matrix
 *          unused at their discretions.
 *			returns result_vector object
 *
 *		verify(Matrix)
 *			Determines if operation is possible and viable with given arguments
 *          returns bool
 *
 *	History
 *		5/25/24	Gus Cochran	    Initial Creation
 *		5/27/24	Drew Tweedale	Matrix multiplication derived class
 *		5/29/24	Jerin Spencer	Row reduction derived class
 *      5/30/24 Elijah Thomas   Determinant derived class
 *      5/30/24 Kaylee Thomas   Inverse matrices derived class
 *      6/1/24  Elijah Thomas   Fixed base class function signature conflict with derived classes
 *      6/1/24  Kaylee Thomas   Changed a function signature for compatibility with row-reduction module
 *
 * */

#include "../eigen/Eigen/Dense"
#include <vector>
#include <tuple>
#include <string>

using namespace Eigen;

typedef std::vector<std::tuple<Matrix<float, Dynamic, Dynamic>, std::string>> result_vector;

//abstract solver class
// class Solver{
//     public:
//         virtual result_vector solve(Matrix <float, Dynamic, Dynamic> a, Matrix <float, Dynamic, Dynamic> b);
//         virtual bool verify(Matrix <float, Dynamic, Dynamic> matrix);
// }

// Matrix multiplication solver
class MatrixMultiplicationSolver{
    public: 
        result_vector solve(Matrix<float, Dynamic, Dynamic> a, Matrix<float, Dynamic, Dynamic> b);
        bool verify(Matrix<float, Dynamic, Dynamic> a, Matrix<float, Dynamic, Dynamic> b);
};

class DeterminantSolver{
    public:
        result_vector solve(Matrix<float, Dynamic, Dynamic> a, Matrix<float, Dynamic, Dynamic> b);
        bool verify(Matrix<float, Dynamic, Dynamic> m);
};

class RowReductionSolver{
    public: 
        result_vector solve(Matrix<float, Dynamic, Dynamic> a, Matrix<float, Dynamic, Dynamic> b);
        bool verify(Matrix<float, Dynamic, Dynamic> mat);
};

// Inverse Solver
class InverseSolver{
    public: 
        result_vector solve(Matrix<float, Dynamic, Dynamic> a, Matrix<float, Dynamic, Dynamic> b);
        bool verify(Matrix<float, Dynamic, Dynamic> mat);
};
