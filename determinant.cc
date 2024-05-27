#include <iostream>

using namespace std;

typedef unsigned int uint;

class Matrix{
    private:
        float** data;
    public:
        uint rows;
        uint cols;
        bool square;
        Matrix(uint x, uint y){
            rows = x;
            cols = y;
            square = x == y;
            data = (float**)malloc(sizeof(float*) * x);
            for(uint i = 0; i < x; i++){
                data[i] = (float*)malloc(sizeof(float) * y);
                *(data[i]) = 0.0;
            }
        }
        ~Matrix(){
            for(uint i = 0; i < rows; i++){
                free(data[i]);
            }
            free(data);
        }
        void set_value(uint row, uint col, float val){
            data[row][col] = val;
        }
        void print(){
            for(uint i = 0; i < rows; i++){
                for(uint j = 0; j < cols; j++){
                    cout << data[i][j] << "\t";
                }
                cout << endl;
            }
        }
        float det(){
            if(square){
                if(rows == 2){
                    // ad-bc
                    return data[0][0] * data[1][1] - data[0][1] * data[1][0];
                }else{
                    cout << "TODO: cofactor expansion for 3x3+ matrices\n";
                    exit(EXIT_FAILURE);
                }
            }else{
                cout << "Cannot take determinant of non-square matrix!\n";
                exit(EXIT_FAILURE);
            }
        }
};

int main(){
    Matrix mtx = Matrix(2, 2);
    for(uint i = 0; i < mtx.rows; i++){
        for(uint j = 0; j < mtx.cols; j++){
            mtx.set_value(i, j, float(i * mtx.cols + j + 1));            
        }
    }
    mtx.print();
    cout << mtx.det() << endl;
}