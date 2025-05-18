#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;

struct Mensaje{
    vector<int> reacciones;
    int reaccionesPositivas;
    Mensaje(vector<int> reacciones){
        this->reacciones = reacciones;
        reaccionesPositivas = 0;
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

    int most_connected(){
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

    int mostPositiveReactions(){
        vector<int> queue;
        set<int> visited;
        int start = 0;
        queue.push_back(start);
        int maxReaccionesPositivas = -1;
        int maxID = -1;

        while(!queue.empty()){
            int current = queue.at(0);
            queue.erase(queue.begin());
            visited.insert(current);

            vector<Mensaje> mensajes = nodos[current].mensajes;
            int reaccionesPositivas = 0;
            for(auto mensaje : mensajes){
                reaccionesPositivas += mensaje.reaccionesPositivas;
            }
            if(reaccionesPositivas > maxReaccionesPositivas){
                maxReaccionesPositivas = reaccionesPositivas;
                maxID = current;
            }

            for(int i = 0; i < matriz[current].size();i++){
                if(
                    i != current &&
                    matriz[current][i] != 0 &&
                    visited.find(i) == visited.end() &&
                    find(queue.begin(), queue.end(), i) == queue.end()
                ){
                    queue.push_back(i);
                }
            }
        }
        cout << "most positive reactions is ID " << maxID << "\n";
        return maxID;
    }

    int farthestNeighbor(int A){
        vector<int> queue;
        set<int> visited;
        queue.push_back(A);
        int current;

        while(!queue.empty()){
            current = queue.at(0);
            queue.erase(queue.begin());
            visited.insert(current);

            for(int i = 0; i < matriz[current].size();i++){
                if(
                    i != current &&
                    matriz[current][i] != 0 &&
                    visited.find(i) == visited.end() &&
                    find(queue.begin(), queue.end(), i) == queue.end()
                ){
                    queue.push_back(i);
                }
            }
        }
        cout << "the farthest neighbor of " << A << " is " << current;
        return current;
    }

    bool pathWithIntermediate(int A, int B, int C) {
        queue<int> q;
        set<int> visited;
        q.push(A);
        visited.insert(A);
        int saltos = 0;
        const int MAX_SALTOS = 7;

        bool visitedC = (A == C);

        while (!q.empty() && saltos < MAX_SALTOS) {
            int levelSize = q.size();
            saltos++;

            for (int j = 0; j < levelSize; ++j) {
                int current = q.front();
                q.pop();
                cout << current << " ";

                if (current == B) {
                    return visitedC;
                }

                for (int i = 0; i < matriz[current].size(); ++i) {
                    if (
                        i != current &&
                        matriz[current][i] != 0 &&
                        visited.find(i) == visited.end()
                    ) {
                        q.push(i);
                        visited.insert(i);
                        if (i == C) visitedC = true;
                    }
                }
            }
        }

        return false;
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
            int numPositivas = 0;
            for(int j = 0; j < numReacciones; j++){
                int reaccion = (rand() % 11) - 5;
                if (reaccion > 0){
                    numPositivas++;
                }
                reacciones.push_back(reaccion);
            }
            Mensaje m(reacciones);
            m.reaccionesPositivas = numPositivas;
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
        map<int, bool> intentado;
        while(numConexiones < maxConexiones){
            int B;
            int countA;
            int countB;
            do{
                if(intentado.size() == 10){
                    cout << "imposible";
                }
                B = rand() % matriz[A].size();
                intentado[B] = true;
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