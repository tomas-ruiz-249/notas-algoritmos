#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

struct Mensaje{
    vector<int> reacciones;
}

struct NodoCiudadanos{
    vector<Mensaje> mensajes;
};

template <typename T>
class Grafo{
public:
    void insertarNodo(){}
private:
    vector<vector<int>> matriz;
    map<int, T> nodos;
};