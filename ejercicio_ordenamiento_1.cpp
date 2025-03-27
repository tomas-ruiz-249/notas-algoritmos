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
    return min + f * (max - min);
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
            double calificacion = randomDouble(0, 5);
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
        cout << "\n======Busqueda por categoria=======\n";
        cout << "Seleccione una categoria\n";
        int categoria;
        cin >> categoria;
        if(categoria >= numCategorias || categoria < 0){
            cout << "categoria invalida, intente de nuevo\n";
            buscar();
            return;
        }
        for(int i = 0; i < libros.getSize(); i++){
            Libro libro = libros.get(i);
            if(libro.getCategoria() == categoria){
                cout << libro << "\n";
            }
        }
    }

    Biblioteca(){
        ascendiente = false;
        numCategorias = 3;
    }
private:
    LinkedList<Libro> libros;
    bool ascendiente;
    int numCategorias;
};

int main(){
    srand(time(0));
    Biblioteca b;
    b.initLista(20);
    b.ordenarLista();
    b.buscar();
};