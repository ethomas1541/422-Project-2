#include <iostream>
#include <vector>

using namespace std;

class Matrix{
    private:
        float** data;
    public:
        int rows;
        int cols;
        bool square;
        Matrix(unsigned int x, unsigned int y){
            rows = x;
            cols = y;
            square = rows == cols;
            data = (float**)malloc(sizeof(float*) * x);
            for(unsigned int i = 0; i < x; i++){
                data[i] = (float*)malloc(sizeof(float) * y);
                *(data[i]) = 0.0;
            }
        }
        ~Matrix(){
            for(unsigned int i = 0; i < rows; i++){
                free(data[i]);
            }
            free(data);
        }
        void set_value(unsigned int row, unsigned int col, float val){
            data[row][col] = val;
        }
        void print(){
            for(unsigned int i = 0; i < rows; i++){
                for(unsigned int j = 0; j < cols; j++){
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
    for(unsigned int i = 0; i < mtx.rows; i++){
        for(unsigned int j = 0; j < mtx.cols; j++){
            mtx.set_value(i, j, float(i * mtx.cols + j + 1));            
        }
    }
    mtx.print();
    cout << mtx.det() << endl;
}