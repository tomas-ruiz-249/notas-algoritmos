#include <iostream>
#include <string.h>
#include <map>

using namespace std;

int main(){
    map<string, int> precioFrutas;
    precioFrutas["manzana"] = 50;
    precioFrutas["banana"] = 30;
    precioFrutas["naranja"] = 40;

    cout << "el precio de una manzana es " << precioFrutas["manzana"] << " centavos\n";
    precioFrutas["manzana"] = 55;
    cout << "el nuevo precio de una manzana es " << precioFrutas["manzana"] << " centavos\n";

    cout << "lista de precios:\n";

    for(auto& precio : precioFrutas){
        cout << "precio de " << precio.first << " es " << precio.second << " centavos.\n";
    }
    
    return 0;
}