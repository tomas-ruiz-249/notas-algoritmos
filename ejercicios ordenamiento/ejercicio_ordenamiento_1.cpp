#include <iostream>
#include <string>
#include "../linked_list.h"

using namespace std;

double randomDouble(double min, double max){
    double f = (double)rand() / RAND_MAX;
    return min + f * (max - min);
}

class Libro{
public:
    Libro(string titulo, string categoria, double puntuacion){
        this->titulo = titulo;
        this->categoria = categoria;
        this->puntuacion = puntuacion;
    }

    Libro(){
        titulo = string();
        categoria = string();
        puntuacion = 0;
    }

    string getTitulo() const{
        return titulo;
    }

    string getCategoria() const{
        return categoria;
    }

    double getPuntuacion() const{
        return puntuacion;
    }

    string to_string() const {
        return titulo + ", " + categoria + ", " + std::to_string(puntuacion);
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
    string categoria;
    double puntuacion;
};

class Biblioteca{
public:
    void initLista(int numLibros){
        cout << "=======lista de libros generados aleatoriamente======\n";
        for(int i = 0; i < numLibros; i++){
            string titulo("Libro ");
            titulo += to_string(i+1);
            string categoria("categoria");
            double calificacion = randomDouble(0, 5);
            Libro l(titulo, categoria, calificacion);
            libros.append(l);
        }
        mostrarLista();
    }

    void ordenarLista(){
        libros.sort("mergeSort");
        cout << "\n======lista ordenada:=======\n";
        mostrarLista();
    }

    void mostrarLista(){
        libros.print();
    }
private:
    LinkedList<Libro> libros;
};

int main(){
    srand(time(0));
    Biblioteca b;
    b.initLista(20);
    b.ordenarLista();
};