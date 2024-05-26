//abstract solver class
class Solver{
    public:
        virtual int solve(int a, int b) = 0;
        virtual bool verify(int a) = 0;
};
//sample solver declaration
class DerivedSolver: public Solver{
    public:
        int solve(int a, int b);
        bool verify(int a);
};
