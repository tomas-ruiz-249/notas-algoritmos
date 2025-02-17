#include <iostream>

using namespace std;
const int width = 4;
const int height = 3;

void printMatrix(int m[height][width]){
    cout << "\n-------------------------\n";
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            cout << " | " <<  m[i][j] << " | ";
        }
        cout << "\n-------------------------\n";
    }
};

void inicializarMatriz(int m[height][width]){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            cout << "m[" << i << "][" << j << "] : ";
            cin >> m[i][j];
        }
    }
};

double promedioPares(int m[height][width]){
    int suma = 0;
    int numPares = 0;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(m[i][j] % 2 == 0){
                suma += m[i][j];
                numPares++;
            }
        }
    }
    double promedio = suma / numPares;
    cout << "el promedio de los numeros pares es " << promedio << "\n";
    return promedio;
}

int sumaImpares(int m[height][width]){
    int suma = 0;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(m[i][j] % 2 != 0){
                suma += m[i][j];
            }
        }
    }
    cout << "la suma de los numeros impares es " << suma << "\n";
    return suma;
}

int main(){
    int m[height][width];
    inicializarMatriz(m);
    printMatrix(m);
    sumaImpares(m);
    promedioPares(m);
    return 0;
}