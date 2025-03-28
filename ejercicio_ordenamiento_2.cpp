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


class Pelicula{
public:
    Pelicula(string titulo, double puntuacion){
        this->titulo = titulo;
        this->puntuacion = puntuacion;
    }

    Pelicula(){
        titulo = string();
        puntuacion = 0;
    }

    string getTitulo() const{
        return titulo;
    }

    double getPuntuacion() const{
        return puntuacion;
    }

    string to_string() const {
        return titulo + ", Puntuacion promedio: " + std::to_string(puntuacion);
    }

    friend std::ostream& operator<<(std::ostream& os, const Pelicula& l) {
        return os << l.to_string();
    }

    bool operator<(const Pelicula& p){
        return this->puntuacion < p.getPuntuacion();
    }

    bool operator>(const Pelicula& p){
        return this->puntuacion > p.getPuntuacion();
    }

    bool operator<=(const Pelicula& p){
        return this->puntuacion <= p.getPuntuacion();
    }

    bool operator>=(const Pelicula& p){
        return this->puntuacion >= p.getPuntuacion();
    }

    bool operator==(const Pelicula& p){
        return this->puntuacion == p.getPuntuacion();
    }

    bool operator!=(const Pelicula& p){
        return this->puntuacion != p.getPuntuacion();
    }

private:
    string titulo;
    double puntuacion;
};

class Catalogo{
public:
    void initLista(int numPeliculas){
        cout << "=======lista de peliculas generadas aleatoriamente======\n";
        for(int i = 0; i < numPeliculas; i++){
            string titulo("Pelicula ");
            titulo += to_string(i+1);
            double calificacion = randomDouble(0, maxPuntuacion);
            Pelicula p(titulo, calificacion);
            peliculas.append(p);
        }
        mostrarLista();
    }

    void ordenarLista(){
        peliculas.sort("mergeSort", ascendiente);
        cout << "\n======lista ordenada:=======\n";
        mostrarLista();
    }

    void mostrarLista(){
        peliculas.print();
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
            i = peliculas.find((Pelicula){"", min}, "binarySearch");
            if(i == -1){
                min += double(0.01);
                min = roundDec(min, 2);
            }
        }
        if(i != -1){
            bool inRange = true;
            while(i > 0 && i < peliculas.getSize() && inRange){
                cout << peliculas.get(i) <<"\n";
                if(ascendiente){
                    i++;
                }
                else{
                    i--;
                }
                if(peliculas.get(i) > (Pelicula){"", max}){
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

    Catalogo(){
        ascendiente = false;
        maxPuntuacion = 5;
    }
private:
    LinkedList<Pelicula> peliculas;
    bool ascendiente;
    double maxPuntuacion;
};

int main(){
    srand(time(0));
    Catalogo c;
    c.initLista(20);
    c.ordenarLista();
    c.buscar();
};