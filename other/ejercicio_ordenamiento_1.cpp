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

class Libro{
public:
    Libro(string titulo, int categoria, double puntuacion){
        this->titulo = titulo;
        this->categoria = categoria;
        this->puntuacion = puntuacion;
    }

    Libro(){
        titulo = string();
        categoria = int();
        puntuacion = 0;
    }

    string getTitulo() const{
        return titulo;
    }

    int getCategoria() const{
        return categoria;
    }

    double getPuntuacion() const{
        return puntuacion;
    }

    string to_string() const {
        return titulo + ", categoria: " + std::to_string(categoria) + ", puntuacion: " + std::to_string(puntuacion);
    }

    friend std::ostream& operator<<(std::ostream& os, const Libro& l) {
        return os << l.to_string();
    }

    bool operator<(const Libro& l){
        return this->puntuacion < l.getPuntuacion();
    }

    bool operator>(const Libro& l){
        return this->puntuacion > l.getPuntuacion();
    }

    bool operator<=(const Libro& l){
        return this->puntuacion <= l.getPuntuacion();
    }

    bool operator>=(const Libro& l){
        return this->puntuacion >= l.getPuntuacion();
    }

    bool operator==(const Libro& l){
        return this->puntuacion == l.getPuntuacion();
    }

    bool operator!=(const Libro& l){
        return this->puntuacion != l.getPuntuacion();
    }

private:
    string titulo;
    int categoria;
    double puntuacion;
};

class Biblioteca{
public:
    void initLista(int numLibros){
        cout << "=======lista de libros generados aleatoriamente======\n";
        for(int i = 0; i < numLibros; i++){
            string titulo("Libro ");
            titulo += to_string(i+1);
            int categoria = rand() % numCategorias;
            double calificacion = randomDouble(0, maxPuntuacion);
            Libro l(titulo, categoria, calificacion);
            libros.append(l);
        }
        mostrarLista();
    }

    void ordenarLista(){
        libros.sort("quickSort", ascendiente);
        cout << "\n======lista ordenada:=======\n";
        mostrarLista();
    }

    void mostrarLista(){
        libros.print();
    }

    void buscar(){
        cout << "\n======Busqueda en un rango=======\n";
        cout << "Seleccione la puntuacion minima en el rango que desea buscar:\n";
        double min;
        cin >> min;
        cout << "Seleccione la puntuacion maxima en el rango que desea buscar:\n";
        double max;
        cin >> max;

        if(max < min){
            cout << "rango invalido, intente de nuevo.\n";
            buscar();
            return;
        }

        int i = -1;
        while(i == -1 && min < maxPuntuacion){
            i = libros.find((Libro){"", 0, min}, "binarySearch");
            if(i == -1){
                min += double(0.01);
                min = roundDec(min, 2);
            }
        }
        if(i != -1){
            bool inRange = true;
            while(i > 0 && i < libros.getSize() && inRange){
                cout << libros.get(i) <<"\n";
                if(ascendiente){
                    i++;
                }
                else{
                    i--;
                }
                if(libros.get(i) > (Libro){"", 0, max}){

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

    Biblioteca(){
        ascendiente = false;
        numCategorias = 3;
        maxPuntuacion = 5;
    }
private:
    LinkedList<Libro> libros;
    bool ascendiente;
    int numCategorias;
    double maxPuntuacion;
};

int main(){
    srand(time(0));
    Biblioteca b;
    b.initLista(20);
    b.ordenarLista();
    b.buscar();
};