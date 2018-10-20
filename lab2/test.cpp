#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime> 

unsigned long long tick(void)
{
 unsigned long long d;
 __asm__ __volatile__ ("rdtsc" : "=A" (d) );
 return d;
}


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
matrix matrixGen(int n, int m) {
    matrix matr;
    srand(time(0));
    for (int i = 0; i < n; i++) {
        std::vector<int> tmp;
        for (int j = 0; j < m; j++) {
            
            int num = rand() % 10;
            tmp.push_back(num);
        }
        matr.push_back(tmp);
    }
    return matr;
}

// a b c d - размерности двух матриц
matrix commonMultiply(const matrix& m1, const matrix& m2, int a, int b, int c) {
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

matrix vinogradMultiply(const matrix& m1, const matrix& m2, int a, int b, int c) {
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
        for (int j = 0; j < b/2; j++) {
            rowFactor[i] = rowFactor[i] + m1[i][2*j] * m1[i][2*j+1];
        }
    }
    std::vector<int> columnFactor;
    for (int i = 0; i < a; i++) {
        columnFactor.push_back(0);
    }
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < b/2; j++) {
            columnFactor[i] = columnFactor[i] + m2[2*j][i] * m2[2*j+1][i];
        }
    }
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < c; j++) {
            result[i][j] = -rowFactor[i] - columnFactor[j];
            for (int k = 0; k < b/2; k++) {
                result[i][j] = result[i][j] + ( m1[i][2*k] + m2[2*k + 1][j]) * 
                                    (m1[i][2*k + 1] + m2[2*k][j]);
            }
        }
    }
    if (b % 2) {
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < c; j++) {
                result[i][j] = result[i][j] + m1[i][b-1] * m2[b-1][j];
            }
        }
    }
    return result;
}


matrix betterVinogradMultiply(const matrix& m1, const matrix& m2, int a, int b, int c) {
    matrix result;
    for (int i = 0; i < a; i++){
        std::vector<int> tmp;
        for (int j = 0; j < c; j++){
            tmp.push_back(0);
        }
        result.push_back(tmp);
    }

    int half = b/2; // оптимизация 1
    std::vector<int> rowFactor;
    for (int i = 0; i < a; i++) {
        rowFactor.push_back(0);
    }
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < half; j++) {
            // оптимизация 2
            rowFactor[i] += m1[i][j << 1] * m1[i][(j << 1)+1]; // оптимизация 4 (+=)
        }
    }
    std::vector<int> columnFactor;
    for (int i = 0; i < a; i++) {
        columnFactor.push_back(0);
    }
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < half; j++) {
             // оптимищация 3 (вместо 2 умножений будет один побитовый сдвиг)
            columnFactor[i] += m2[j << 1][i] * m2[(j << 1)+1][i];
        }
    }
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < c; j++) {
            result[i][j] = -rowFactor[i] - columnFactor[j];
            for (int k = 0; k < half; k++) {
                result[i][j] += ( m1[i][k << 1] + m2[(k << 1) + 1][j]) * 
                                    (m1[i][(k << 1) + 1] + m2[k << 1][j]);
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
    int tb1, te1, result1;
    int tb2, te2, result2;
    int tb3, te3, result3;
    matrix m1; 
    matrix m2;
    matrix m3;
    matrix rCommon;
    matrix rVin;
    matrix better_rVin;

    // четные 100-1000
    int k;
    for (int i = 1; i <= 10; i++) {
        k = i*100;
        m1 = matrixGen(k,k);
        m2 = matrixGen(k,k);


        tb1= clock();
        rCommon = commonMultiply(m1,m2,k,k,k);
        te1= clock();
        result1 = te1 - tb1 ;
        std::cout << "COMMON " << k <<"х" << k << " time:" << result1 << "\n";  

        tb2= clock();
        rVin = vinogradMultiply(m1,m2,k,k,k);
        te2= clock();
        result2 = te2 - tb2 ;
        std::cout << "VINOGRAD " << k <<"х" << k << " time:" << result2 << "\n";

        tb3= clock();
        better_rVin = betterVinogradMultiply(m1,m2,k,k,k);
        te3= clock();
        result3 = te3 - tb3 ;
        std::cout << "BETTER " << k <<"х" << k << " time:" << result3 << "\n";
        std::cout << "\n";
    }


    // нечетные 101-1001
    std::cout << "\n\n\n";
    for (int i = 1; i <= 10; i++) {
        k = i*100 + 1;
        m1 = matrixGen(k,k);
        m2 = matrixGen(k,k);


        tb1 = clock();
        rCommon = commonMultiply(m1,m2,k,k,k);
        te1 = clock();
        result1 = te1 - tb1 ;
        std::cout << "COMMON " << k <<"х" << k << " time:" << result1 << "\n";  

        tb2= clock();
        rVin = vinogradMultiply(m1,m2,k,k,k);
        te2= clock();
        result2 = te2 - tb2;
        std::cout << "VINOGRAD " << k <<"х" << k << " time:" << result2 << "\n";

        tb3 = clock();
        better_rVin = betterVinogradMultiply(m1,m2,k,k,k);
        te3= clock();
        result3 = te3 - tb3 ;
        std::cout << "BETTER " << k <<"х" << k << " time:" << result3 << "\n";
        std::cout << "\n";
    }
    return 0;
}
