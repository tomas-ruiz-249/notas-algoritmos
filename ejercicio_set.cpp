#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

int main(){
    set<string> productosVendidos;
    map<string, int> frecuencia;
    cout << "Cuantos productos fueron vendidos?\n";
    int n;
    cin >> n;
    cin.ignore();
    cout << "inserte los productos vendidos\n";
    for(int i = 0; i < n; i++){
        string nombre;
        getline(std::cin, nombre);
        productosVendidos.insert(nombre);
        frecuencia[nombre]++;
    }

    cout << "\nproductos distintos vendidos (" << productosVendidos.size() << ") :\n";
    for(auto& producto : productosVendidos){
        cout << producto << "\n";
    }

    cout << "\nfrecuencia de los productos vendidos:\n";
    for(auto& elemento : frecuencia){
        cout << elemento.first << " : " << elemento.second << "\n";
    }
}