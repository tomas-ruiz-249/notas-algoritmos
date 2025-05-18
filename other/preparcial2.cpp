#include <iostream>
#include <string>
#include "linked_list.h"

using namespace std;

class Calificacion{
public:
    Calificacion(int grupo, int puntaje){
        this->grupo = grupo;
        this->puntaje = puntaje;
    }

    Calificacion(){
        grupo = -1;
        puntaje = -1;
    }

    int getPuntaje() const{
        return puntaje;
    }

    string to_string() const {
        return "" + std::to_string(grupo) + ", "  + std::to_string(puntaje);
    }

    friend std::ostream& operator<<(std::ostream& os, const Calificacion& c) {
        return os << c.to_string();
    }

    bool operator<(const Calificacion& p){
        return this->puntaje < p.getPuntaje();
    }

    bool operator>(const Calificacion& p){
        return this->puntaje > p.getPuntaje();
    }

    bool operator<=(const Calificacion& p){
        return this->puntaje <= p.getPuntaje();
    }

    bool operator>=(const Calificacion& p){
        return this->puntaje >= p.getPuntaje();
    }

    bool operator==(const Calificacion& p){
        return this->puntaje == p.getPuntaje();
    }

    bool operator!=(const Calificacion& p){
        return this->puntaje != p.getPuntaje();
    }

private:
    int grupo;
    int puntaje;
};

class Evaluador{
public:
    Evaluador(int numCalificaciones, int indice){
        this->indice = indice;
        if(!numCalificaciones){
            puntos = 0;
            return;
        }
        for(int i = 0; i < numCalificaciones; i++){
            int grupo = rand() % 4;
            int puntaje = rand() % 10;
            puntos += puntaje;
            Calificacion a (grupo, puntaje);
            lista.append(a);
        }
    }

    int getPuntos() const{
        return puntos;
    }

    int getIndice() const{
        return indice;
    }

    bool esVacio(){
        return !lista.getSize();
    }

    void sort(){
        lista.sort("mergeSort", true);
    }

    Evaluador(){
        puntos = -1;
    }
    
    void mostrar(){
        lista.print();
    }

    string to_string() const {
        string str;
        int size = lista.getSize();
        for(int i = 0; i < size; i++){
            str += "(" + lista.get(i).to_string() + ")";
            if(i != size-1){
                str += ", ";
            }
        }
        return str;
    }

    friend std::ostream& operator<<(std::ostream& os, const Evaluador& e) {
        return os << e.to_string();
    }

    bool operator<(const Evaluador& e){
        return this->puntos < e.getPuntos();
    }

    bool operator>(const Evaluador& e){
        return this->puntos > e.getPuntos();
    }

    bool operator<=(const Evaluador& e){
        return this->puntos <= e.getPuntos();
    }

    bool operator>=(const Evaluador& e){
        return this->puntos >= e.getPuntos();
    }

    bool operator==(const Evaluador& e){
        return this->puntos == e.getPuntos();
    }

    bool operator!=(const Evaluador& e){
        return this->puntos != e.getPuntos();
    }

private:
    LinkedList<Calificacion> lista;
    int puntos;
    int indice;
};

class Sistema{
public:
    Sistema(int numEvaluadores){
        int numCalificaciones;
        for(int i = 0; i < numEvaluadores; i++){
            if(i != 2){
                numCalificaciones = rand() % 3 + 10;
            }
            else{
                numCalificaciones = 0;
            }
            Evaluador e(numCalificaciones, i);
            evaluadores.append(e);
        }
        cout << "Resultado por evaluador (grupo, calificacion) ordenado por grupo:\n";
        mostrar();
    }

    void mostrar(){
        for(int i = 0; i < evaluadores.getSize(); i++){
            cout << evaluadores.get(i).getIndice() << " -> " ;
            if (evaluadores.get(i).esVacio()){
                cout << "la lista de registros esta vacia\n";
            }
            else{
                cout << evaluadores.get(i) << "\n";
            }
        }
    }

    void mostrarTotalCalificaciones(){
        cout << "\n";
        cout << "Resultado con la suma de calificaciones por evaluador\n";
        Evaluador e;
        for(int i = 0; i < evaluadores.getSize(); i++){
            e = evaluadores.get(i);
            cout << "Evaluador " << e.getIndice() << " tiene " << e.getPuntos() << " puntos\n";
        }
    }

    void mostrarTotalOrdenado(){
        cout << "\n";
        evaluadores.sort("mergeSort", true);
        cout << "Resultado de puntos por evaluador ordenados de menor a mayor:\n";
        Evaluador e;
        for(int i = 0; i < evaluadores.getSize(); i++){
            e = evaluadores.get(i);
            cout << "Evaluador " << e.getIndice() << " tiene " << e.getPuntos() << " puntos\n";
        }
    }

    void mostrarEvaluadoresOrdenados(){
        for(int i = 0; i < evaluadores.getSize(); i++){
            evaluadores.get(i).sort();
        }
        cout << "\nResultado por evaluador (grupo, calificacion) ordenado por calificacion:\n";
        mostrar();
    }


private:
private:
    LinkedList<Evaluador> evaluadores;
};

int main(){
    int numEvaluadores;
    cout << "ingrese el numero de evaluadores (minimo 3, maximo 6): ";
    cin >> numEvaluadores;
    if(numEvaluadores > 6 || numEvaluadores < 3){
        cout << "numero invalido, seleccione un numero entre 3 y 6\n";
        main();
        return 0;
    }
    Sistema s(numEvaluadores);
    s.mostrarTotalCalificaciones();
    s.mostrarTotalOrdenado();
    s.mostrarEvaluadoresOrdenados();
}