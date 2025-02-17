#include <iostream>

const int LENGTH = 4;
const int WIDTH = 5;
const int ARRAY_SIZE = LENGTH * WIDTH;

using namespace std;

void initMatrix(int mat[LENGTH][WIDTH]){
    for(int i = 0; i < LENGTH; i++){
        for(int j = 0; j < WIDTH; j++){
            mat[i][j] = rand() % 11;
            std::cout << "m[" << i << "][" << j <<"]: " << mat[i][j] << "\n";
        }
    }
}

void initArray(int arr[ARRAY_SIZE]){
    for(int i = 0; i < ARRAY_SIZE; i++){
        arr[i] = -1; 
    }
}

bool isPrime(int n){
    if(n == 0 || n == 1){
        return false;
    }
    else{
        for(int i = 2; i < n; i++){
            if( n % i == 0){
                return false;
            }
        }
        return true;
    }
}

void findValues(int matrix[LENGTH][WIDTH], int nonPrimes[ARRAY_SIZE], int mult5[ARRAY_SIZE]){
    int indexA = 0;
    int indexB = 0;
    for(int i = 0; i < LENGTH; i++){
        for(int j = 0; j < WIDTH; j++){
            if(!isPrime(matrix[i][j])){
                nonPrimes[indexA] = matrix[i][j];
                indexA++;
            }
            if(matrix[i][j] % 5 == 0){
                mult5[indexB] = matrix[i][j];
                indexB++;
            }
        }
    }
}

int calculateSum(int matrix[LENGTH][WIDTH]){
    int sum = 0;
    for(int i = 0; i < LENGTH; i++){
        for(int j = 0; j < WIDTH; j++){
            sum += matrix[i][j];
        }
    }
    return sum;
}

void printArray(int arr[ARRAY_SIZE]){
    cout << "[";
    for(int i = 0; i < ARRAY_SIZE; i++){
        cout << arr[i] << ", ";
    }
    cout << "]\n";
}

int main(){
    srand(time(0));
    int M[LENGTH][WIDTH];
    int A[ARRAY_SIZE];
    int B[ARRAY_SIZE];
    initMatrix(M);
    // initArray(A);
    // initArray(B);

    cout << "---suma de los valores en la matriz---\n" << calculateSum(M) << "\n";
    findValues(M, A, B);
    cout << "---no primos encontrados---\n";
    printArray(A);
    cout << "---multiplos de 5 encontrados---\n";
    printArray(B);
    return 0;
}