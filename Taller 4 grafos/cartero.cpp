#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <queue>
#include <set>
#include <algorithm>


using namespace std;


class GrafoCartero{
public:
    GrafoCartero(){
        generarGrafo();
        // print();
    }

    void crearConexion(string inicio, string final, int costo){
        adyacencia[inicio].push_back({final, costo});
        adyacencia[final].push_back({inicio, costo});
    }

    void generarGrafo(){
        crearConexion("bogota", "cartagena", 1030);
        crearConexion("bogota", "barranquilla", 1000);
        crearConexion("bogota", "santa marta", 960);
        crearConexion("medellin", "cartagena", 640);
        crearConexion("medellin", "barranquilla", 700);
        crearConexion("medellin", "santa marta", 740);
        crearConexion("cali", "bucaramanga", 860);
        crearConexion("cali", "cucuta", 980);
        crearConexion("cartagena", "bucaramanga", 615);
        crearConexion("cartagena", "cucuta", 750);
        crearConexion("pereira", "cucuta", 810);
        crearConexion("manizales", "cucuta", 830);
        crearConexion("barranquilla", "bucaramanga", 560);
        crearConexion("santa marta", "bucaramanga", 490);
        crearConexion("manizales", "cartagena", 850);
        crearConexion("manizales", "barranquilla", 910);
    }

    void print(){
        for(auto [nodo, vecinos] : adyacencia){
            cout << "[" << nodo << "] : ";
            for(auto vecino : vecinos){
                cout << vecino.first << ", ";
            }
            cout << "\n";
        }
    }

    bool esEuleriano(string nodo){
        return adyacencia[nodo].size() % 2 == 0;
    }

    vector<string> nodosImpares(){
        vector<string> impares;
        for(auto [nodo, vecinos] : adyacencia){
            if(!esEuleriano(nodo)){
                impares.push_back(nodo);
            }
        }
        return impares;
    }

    struct DijkstraPath{
        vector<string> path;
        int totalCost;
        DijkstraPath(vector<string> path, int totalCost){
            this->path = path;
            this->totalCost = totalCost;
        }
        DijkstraPath() = default;
    };

    DijkstraPath dijkstra(string A, string B) {
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;
        map<string, pair<int, string>> dist;

        for (auto [nodo, _] : adyacencia) {
            dist[nodo] = {__INT_MAX__, ""};
        }
        dist[A] = {0, ""};
        pq.push({0, A});

        while (!pq.empty()) {
            auto [currentDist, current] = pq.top();
            pq.pop();

            for (auto [vecino, costo] : adyacencia[current]) {
                int newDist = currentDist + costo;
                if (dist[vecino].first > newDist) {
                    dist[vecino] = {newDist, current};
                    pq.push({newDist, vecino});
                }
            }
        }

        vector<string> path;
        string current = B;
        while (current != "") {
            path.push_back(current);
            current = dist[current].second;
        }
        reverse(path.begin(), path.end());

        return DijkstraPath(path, dist[B].first);
    }


    struct EmparejamientoMinimo{
        vector<pair<string,string>> pares;
        int costoTotal;
    };

    void emparejamientosMenorCosto(vector<string>& impares, EmparejamientoMinimo& emparejamiento){
        if(impares.empty()){
            return;
        }
        else{
            string A = impares[0];
            map<string, map<string , DijkstraPath>> costos;
            int minCost = __INT_MAX__;
            string minNode = "";
            for(auto B : impares){
                if(B != A){
                    costos[A][B] = dijkstra(A,B);
                }
            }
            for(auto [vecino, costo] : costos[A]){
                if(costo.totalCost < minCost){
                    minCost = costo.totalCost;
                    minNode = vecino;
                }
            }
            emparejamiento.pares.push_back(pair<string, string>(A, minNode));
            impares.erase(find(impares.begin(), impares.end(), A));
            impares.erase(find(impares.begin(), impares.end(), minNode));
            auto camino = costos[A][minNode].path;
            for(int i = 1; i < camino.size(); i++){
                int cost;
                for(auto [vecino ,peso] : adyacencia[camino[i]]){
                    if(vecino == camino[i-1]){
                        cost = peso;
                        break;
                    }
                }
                crearConexion(camino[i], camino[i - 1], cost * 1.3);
            }
            emparejamientosMenorCosto(impares, emparejamiento);
        }
    }

private:
    map<string, vector<pair<string, int>>> adyacencia;
    const string inicio = "bogota";
};