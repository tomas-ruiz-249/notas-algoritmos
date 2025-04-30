#include <iostream>
#include <string>
#include "linked_list.h"

using namespace std;

template <typename T>
class Pila{
public:
    Pila(){
        size = 0;
        capacity = 10;
        arr = new T[capacity]();
    }

    Pila(int capacity){
        this->size = 0;
        this->capacity = capacity;
        arr = new T[capacity]();
    }

    bool push(T value){
        if(size < capacity){
            arr[size] = value;
            size++;
            return true;
        }
        return false;
    }

    T pop(){
        if(size == 0){
            throw std::out_of_range("Pila vacia.");
        }
        T value = arr[size];
        size--;
        return value;
    }

    void print(){
        cout << "PILA\n";
        for(int i = 0; i < capacity; i++){
            cout << i << ": " << arr[i] << '\n';
        }
    }
private:
    T* arr;
    int capacity;
    int size;
};

template <typename T>
class Cola{
public:
    Cola(){
        size = 0;
    }

    void enqueue(T value){
        list.append(value)
        size++;
    }

    void dequeue(){
        list.remove(0);
        size--;
    }
private:
    LinkedList<T> list;
    int size;
};

struct Zona{
    string nombre;
    Zona* next;
};

struct Parqueadero{
    string nombre;
    LinkedList<Zona>* zonas;
    Parqueadero* next;
};

struct Ciudad{
    string nombre;
    LinkedList<Parqueadero>* parquaderos;
    Ciudad* next;
};


int main(){
    return 0;
}