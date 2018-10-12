#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime> 

typedef std::vector< std::vector<int> > matrix;

// печать матрицы
void printMatrix(const matrix& vec){
    for (auto i : vec) {
        for (auto j : i) {
            std::cout << j << " ";
        }
        std::cout << '\n';
    }  
    std::cout << "&";
}

// генерация матрицы
void matrixGen(int n, int m, matrix& matr) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        std::vector<int> tmp;
        for (int j = 0; j < m; j++) {
            int num = rand() % 10;
            tmp.push_back(num);
        }
        matr.push_back(tmp);
    }
}

// a b c d - размерности двух матриц
matrix commonMultiply(const matrix& m1, const matrix& m2, int a, int b, int c, int d) {
    matrix result;
    for (int i = 0; i < a; i++){
        std::vector<int> tmp;
        for (int j = 0; j < c; j++){
            tmp.push_back(0);
        }
        result.push_back(tmp);
    }
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < c; j++) {
            for (int k = 0; k < b; k++) {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
    return result;
}

matrix vinogradMultiply(const matrix& m1, const matrix& m2, int a, int b, int c, int d) {
    matrix result;
    for (int i = 0; i < a; i++){
        std::vector<int> tmp;
        for (int j = 0; j < c; j++){
            tmp.push_back(0);
        }
        result.push_back(tmp);
    }

    std::vector<int> rowFactor;
    for (int i = 0; i < a; i++) {
        rowFactor.push_back(0);
    }
    for (int i = 0; i < a; i++) {
        // rowFactor[i] = m1[i][1] * m1[i][2];
        for (int j = 0; j < b/2; j++) {
            rowFactor[i] += m1[i][2*j] * m1[i][2*j+1];
        }
    }

    std::vector<int> columnFactor;
    for (int i = 0; i < a; i++) {
        columnFactor.push_back(0);
    }

    for (int i = 0; i < c; i++) {
        // columnFactor[i] = m2[1][i] * m2[2][i];
        for (int j = 0; j < b/2; j++) {
            columnFactor[i] += m2[2*j][i] * m2[2*j+1][i];
        }
    }

    for (int i = 0; i < a; i++) {
        for (int j = 0; j < c; j++) {
            result[i][j] = -rowFactor[i] - columnFactor[j];
            for (int k = 0; k < b/2; k++) {
                // result[i][j] += ( m1[i][2*k-1] + m2[2*k][j]) * 
                //                     (m1[i][2*k] + m2[2*k-1][j]);
                result[i][j] += ( m1[i][2*k] + m2[2*k + 1][j]) * 
                                    (m1[i][2*k + 1] + m2[2*k][j]);
            }
        }
    }

    if (b % 2) {
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < c; j++) {
                result[i][j] += m1[i][b-1] * m2[b-1][j];
            }
        }
    }
    return result;
}


int main(int argc, char const *argv[])
{   
    matrix m1; 
    matrix m2;
    matrix rCommon;
    matrix rVin;
    matrixGen(3,3,m1);
    std::cout << "\nfirst matrix" << "\n";
    printMatrix(m1);

    matrixGen(3,3,m2);
    std::cout << "\nsecond matrix" << "\n";
    printMatrix(m2);

    rCommon = commonMultiply(m1,m2,3,3,3,3);

    std::cout << "\ncommon matrix" << "\n";
    printMatrix(rCommon);

    rVin = vinogradMultiply(m1,m2,3,3,3,3);

    std::cout << "\nVinograd matrix" << "\n";
    printMatrix(rVin);

    return 0;
}