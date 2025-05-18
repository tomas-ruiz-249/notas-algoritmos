#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Grafo{
public:
    void añadirNodo(string key, string value){
        if(adyacentes.find(key) == adyacentes.end()){
            adyacentes[key] = vector<string>();
        }
        adyacentes[key].push_back(value);
    }

    void print(){
        cout << "------GRAFO-----\n";
        for(auto n : adyacentes){
            cout << n.first << ": ";
            for(auto vecino : n.second){
                cout << vecino << ", ";
            }
            cout << "\n";
        }
    }

    void printValue(string value){
        vector<string> origenes;
        for(auto n : adyacentes){
            for(auto vecinos : n.second){
                if(vecinos == value){
                    origenes.push_back(n.first);
                }
            }
        }
        for(auto origen : origenes){
            printKey(origen);
        }
    }

    void printKey(string key){
        if(adyacentes.find(key) == adyacentes.end()){
            cout << "no se encontro la ciudad " << key << "\n";
            return;
        }
        cout << "desde " << key << "se puede llegar a" << ": ";
        for(auto vecino : adyacentes[key]){
            cout << vecino << ", ";
        }
        cout << "\n";
    }
private:
    map<string, vector<string>> adyacentes;
};

void printMenu(){
    cout << "-------Opciones-------\n";
    cout << "1.Mostrar destinos desde una ciudad\n";
    cout << "2.Mostrar origenes hacia una ciudad\n";
    cout << "3.Salir\n";
}

int main(){
    Grafo g;
    bool running = true;
    int option;
    string origen, destino;

    cout << "ingrese el numero de rutas que desea ingresar: ";
    cin >> option;
    cin.ignore();
    cout << "ingrese las rutas como pares de ciudades (origen, destino)\n";
    for(int i = 0; i < option; i++){
        cout << "Ruta #" << i + 1 << " - Origen: ";
        getline(cin, origen);
        cout << "Ruta #" << i + 1 << " - Destino: ";
        getline(cin, destino);
        g.añadirNodo(origen, destino);
    }

    while(running){
        printMenu();
        if(!(cin >> option)){
            cout << "FAIL\n";
            return 0;
        }
        cin.ignore();
        switch(option){
        case 1:{
            cout << "ingrese el nombre de una ciudad: ";
            string ciudad;
            getline(cin, ciudad);
            g.printKey(ciudad);
            break;
        }
        case 2:{
            cout << "ingrese el nombre de una ciudad: ";
            string ciudad;
            getline(cin, ciudad);
            g.printValue(ciudad);
            break;
        }
        case 3:
            running = false;
            break;
        }
    }
    return 0;
}