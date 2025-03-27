#include <iostream>
#include <string>
#include <cmath>
#include "linked_list.h"

using namespace std;

double roundDec(double num, int places){
    double multiplier = pow(10, places);
    return ceil(num * multiplier) / multiplier;
}

double randomDouble(double min, double max){
    double f = (double)rand() / RAND_MAX;
    return roundDec(min + f * (max - min), 2);
}


class Producto{
public:
    Producto(string nombre, int stock, double precio){
        this->nombre = nombre;
        this->stock = stock;
        this->precio = precio;
    }

    Producto(){
        nombre = string();
        stock = 0;
        precio = 0;
    }

    string getNombre() const{
        return nombre;
    }

    int getStock() const{
        return stock;
    }

    double getPrecio() const{
        return precio;
    }

    string to_string() const {
        return nombre + ", stock: " + std::to_string(stock) + ", $" + std::to_string(precio);
    }

    friend std::ostream& operator<<(std::ostream& os, const Producto& l) {
        return os << l.to_string();
    }

    bool operator<(const Producto& p){
        return this->precio < p.getPrecio();
    }

    bool operator>(const Producto& p){
        return this->precio > p.getPrecio();
    }

    bool operator<=(const Producto& p){
        return this->precio <= p.getPrecio();
    }

    bool operator>=(const Producto& p){
        return this->precio >= p.getPrecio();
    }

    bool operator==(const Producto& p){
        return this->precio == p.getPrecio();
    }

    bool operator!=(const Producto& p){
        return this->precio != p.getPrecio();
    }

private:
    string nombre;
    int stock;
    double precio;
};

class Inventario{
public:
    void initLista(int numProductos){
        cout << "=======lista de productos generadas aleatoriamente======\n";
        for(int i = 0; i < numProductos; i++){
            string nombre("Producto ");
            nombre += to_string(i+1);
            int stock = rand() % 10;
            double precio = randomDouble(0, maxPrecio);
            Producto p(nombre, stock, precio);
            productos.append(p);
        }
        mostrarLista();
    }

    void ordenarLista(){
        productos.sort("heapSort", ascendiente);
        cout << "\n======lista ordenada:=======\n";
        mostrarLista();
    }

    void mostrarLista(){
        productos.print();
    }

    void buscar(){
        cout << "\n======Busqueda en un rango=======\n";
        cout << "Seleccione el precio minimo en el rango que desea buscar:\n";
        double min;
        cin >> min;
        cout << "Seleccione el precio maximo en el rango que desea buscar:\n";
        double max;
        cin >> max;

        if(max < min){
            cout << "rango invalido, intente de nuevo.\n";
            buscar();
            return;
        }

        int i = -1;
        while(i == -1 && min < maxPrecio){
            i = productos.find((Producto){"", 0, min}, "binarySearch");
            if(i == -1){
                min += double(0.01);
                min = roundDec(min, 2);
            }
        }
        if(i != -1){
            bool inRange = true;
            while(i < productos.getSize() && inRange){
                cout << productos.get(i) << "\n";
                if(ascendiente){
                    i++;
                }
                else{
                    i--;
                }
                if(productos.get(i) > (Producto){"", 0, max}){
                    inRange = false;
                }
            }
        }
        else{
            cout << "no se han encontrado elementos en este rango...\n";
            int repetir = 0;
            cout << "desea buscar de nuevo? (1 = si, 0 = no)\n";
            cin >> repetir;
            if(repetir > 0){
                buscar();
            }
        }
    }

    Inventario(){
        ascendiente = false;
        maxPrecio = 100;
    }
private:
    LinkedList<Producto> productos;
    bool ascendiente;
    double maxPrecio;
};

int main(){
    srand(time(0));
    Inventario i;
    i.initLista(20);
    i.ordenarLista();
    i.buscar();
};