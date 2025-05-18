#include <iostream>
#include <math.h>

using namespace std;

void inicializarArregloRand(int vec[], int largo){
    for(int i = 0; i < largo; i++){
        vec[i] = rand() % 10 + 1;
        cout << "v[" << i << "] = " << vec[i] << "\n"; 
    }
    cout << "-----------\n";
}

void inicializarArregloVacio(int vec[], int largo){
    for(int i = 0; i < largo; i++){
        vec[i] = -1;
        cout << "v[" << i << "] = " << vec[i] << "\n"; 
    }
    cout << "-----------\n";
}

void buscarValor(int vec[], int largo){
    int valor;
    cout << "ingrese el valor que desea buscar: ";
    cin >> valor;
    int contador = 0;
    bool encontrado = false;
    for(int i = 0; i < largo; i++){
        if(vec[i] == valor){
            cout << "el valor " << valor << " se encuentra en v[" << i << "]\n";
            encontrado = true;
        }
    }
    if(!encontrado){
        cout << "el valor " << valor << " no ha sido encontrado";
    }
}

bool esPrimo(int num){
    if (num == 1){
        return false;
    }
    int div = 2;
    while(num % div != 0){
        div++;
    }
    if(div == num){
        return true;
    }
    return false;
}

void encontrarPrimos(int vec[], int primos[], int largo){
    int index = 0;
    for(int i = 0; i < largo; i++){
        if(esPrimo(vec[i])){
            cout << "vec[" << i << "] = " << vec[i] << " es primo\n";
            primos[index] = vec[i];
            index++;
        }
    }
}

void imprimirArreglo(int vec[], int largo){
    for(int i = 0; i < largo; i++){
        cout << "v[" << i << "] = " << vec[i] << "\n";
    }
}

int main(){
    const int largo = 10;
    srand(time(0));
    int v[largo];
    int primos[largo];
    inicializarArregloRand(v, largo);
    inicializarArregloVacio(primos, largo);
    encontrarPrimos(v, primos, largo);
    imprimirArreglo(primos, largo);
    return 0;
}