#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>

using namespace std;

struct Mensaje{
    vector<int> reacciones;
    Mensaje(vector<int> reacciones){
        this->reacciones = reacciones;
    }
    Mensaje() = default;
};

struct NodoCiudadanos{
    vector<Mensaje> mensajes;

    NodoCiudadanos(vector<Mensaje> mensajes){
        this->mensajes = mensajes;
    }

    NodoCiudadanos() = default;
    
    friend std::ostream& operator<<(std::ostream& os, NodoCiudadanos& n){
        os << n.mensajes.size();
        return os;
    }
};

class GrafoSocial{
public:
    void generarGrafo(){
        const int numNodos = 10;
        cout << "generando nodos...\n";
        for(int i = 0; i < numNodos; i++){
            generarNodo();
        }
        cout << "generando conexiones...\n";
        for(int i = 0; i < numNodos; i++){
            cout << "conexiones del nodo " << i << "\n";
            generarAristas(i);
        }
        print();
    }

    void print(){
        if(nodos.size() <= 10){
            cout << "---------------\n";
            for(auto fila : matriz){
                cout << "[ ";
                for(auto conexion : fila){
                    cout << conexion << " ";
                }
                cout << "]\n";
            }
        }
        cout << "---------------\n";
        for(auto entry : nodos){
            cout << entry.first << ": ";

            vector<int> ordered = matriz[entry.first];
            sort(ordered.begin(), ordered.end(), [](int a, int b){return a > b;});
            int count = 0;
            for(auto conexion : ordered){
                if(!conexion){
                    break;
                }
                count++;
            }

            cout << count << " conexiones\n";
        }
        cout << "---------------\n";
    }

    int searchMostConnected(){
        vector<int> stack;
        set<int> visited;

        int maxID = -1;
        int maxConnections = -1;
        int start = 0;

        stack.push_back(start);

        while(!stack.empty()){
            int current = stack.at(stack.size() - 1);
            stack.pop_back();
            visited.insert(current);

            int numConections = count(matriz[current].begin(), matriz[current].end(), 1);
            if(numConections > maxConnections){
                maxConnections = numConections;
                maxID = current;
            }

            for(int i = 0; i < matriz[current].size(); i++){
                if(
                    i != current && 
                    matriz[current][i] != 0 && 
                    visited.find(i) == visited.end() &&
                    find(stack.begin(), stack.end(), i) == stack.end()
                ){
                    stack.push_back(i);
                }
            }
        }
        cout << "most connected is ID " << maxID << '\n';
        return maxID;
    }

private:
    vector<vector<int>> matriz;
    map<int, NodoCiudadanos> nodos;

    void generarNodo(){
        int numMensajes = (rand() % 500) + 1;
        vector<Mensaje> mensajes;

        for(int i = 0; i < numMensajes; i++){
            int numReacciones = (rand() % 50) + 1;
            vector<int> reacciones;
            for(int j = 0; j < numReacciones; j++){
                int reaccion = (rand() % 11) - 5;
                reacciones.push_back(reaccion);
            }
            Mensaje m(reacciones);
            mensajes.push_back(m);
        }

        NodoCiudadanos n(mensajes);
        int numNodos = nodos.size();
        nodos[numNodos] = n;
        numNodos = nodos.size();
        vector<int> conexiones(numNodos, 0);
        matriz.push_back(conexiones);

        for(auto& row : matriz){
            while(row.size() < numNodos){
                row.push_back(0);
            }
        }
    }
    
    void generarAristas(int A){
        int numConexiones = count(matriz[A].begin(), matriz[A].end(), 1);
        int maxConexiones = (rand() % 3) + 1;
        while(numConexiones < maxConexiones){
            int B;
            int countA;
            int countB;
            do{
                B = rand() % matriz[A].size();
                countA = count(matriz[A].begin(), matriz[A].end(), 1);
                countB = count(matriz[B].begin(), matriz[B].end(), 1);
            }
            while(
                matriz[A][B] != 0 ||
                matriz[B][A] != 0 ||
                countA >= maxConexiones ||
                countB >= maxConexiones ||
                A == B
            );
            matriz[A][B] = 1;
            matriz[B][A] = 1;
            numConexiones++;
        }
    }


};