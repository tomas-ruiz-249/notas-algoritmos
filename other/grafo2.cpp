#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

const int NUM_NODOS = 6;

void printAdyacencyList(map<string, vector<string>> grafo){
    cout << "\n--LISTA DE ADYACENCIA--\n";
    for(auto& entry : grafo){
        cout << entry.first << ": ";
        for(auto& vecino : entry.second){
            cout << vecino + ", ";
        }
        cout << "\n";
    }
    cout << "-----------------------\n";
}

void printAdyacencyMatrix(bool matr[NUM_NODOS][NUM_NODOS], int size){
    cout << "\n--MATRIZ DE ADYACENCIA--\n";
    for(int i = 0; i < size; i++){
        cout << "[ ";
        for(int j = 0; j < size; j++){
            cout << matr[i][j];
            if(j < size-1){
                cout << ", ";
            }
        }
        cout << " ]\n";
    }
    cout << "------------------------\n";
}

void printMenu(){
    cout << "1.Mostrar lista de adyacencia\n";
    cout << "2.Mostrar matriz de adyacencia\n";
    cout << "3.Salir\n";
}

int main(){
    bool matrizAdyacencia[NUM_NODOS][NUM_NODOS] = {
        {0,1,0,0,1,0},
        {1,0,1,0,1,0},
        {0,1,0,1,0,0},
        {0,0,1,0,1,1},
        {1,1,0,1,0,0},
        {0,0,0,1,0,0}
    };

    map<string, vector<string>> listaAdyacencia;
    listaAdyacencia["1"] = {"5","2"};
    listaAdyacencia["2"] = {"1","3","5"};
    listaAdyacencia["3"] = {"4","2"};
    listaAdyacencia["4"] = {"3","5","6"};
    listaAdyacencia["5"] = {"4","2","1"};
    listaAdyacencia["6"] = {"4"};

    bool running = true;
    int option;
    while(running){
        printMenu();
        cin >> option;
        switch(option){
        case 1:
            printAdyacencyList(listaAdyacencia);
            break;
        case 2:
            printAdyacencyMatrix(matrizAdyacencia, NUM_NODOS);
            break;
        case 3:
            running = false;
            break;
        }
    }
    return 0;
}