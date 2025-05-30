#include <iostream>
#include <string>
#include "lista_enlazada.h"

using namespace std;

template <typename T>
class Pila{
public:
    Pila(){
        size = 0;
        capacity = 5;
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
        size--;
        T value = arr[size];
        arr[size] = T();
        return value;
    }

    void print(){
        cout << "----PILA---\n";
        for(int i = 0; i < capacity; i++){
            cout << i << ": ";
            if(arr[i] == T()){
                cout << "vacio";
            }
            else{
                cout << arr[i];
            }
            cout << ", ";
        }
    }

    bool canPush(){
        return size < capacity;
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
        list.append(value);
        size++;
    }

    T dequeue(){
        T first = list.get(0);
        list.remove(0);
        size--;
        return first;
    }

    void print(){
        cout << "    Vehiculos en cola:\n";
        if(size == 0){
            cout << "    ninguno\n";
            return;
        }
        for(auto value : list){
            cout << "    " << value << "\n";
        }
    }

    int getSize(){
        return size;
    }
private:
    ListaEnlazada<T> list;
    int size;
};

struct Zona{
    string nombre;
    Zona* next;
    Pila<string> vehiculos;
    Cola<string> fila;

    Zona(){
        nombre = "";
        next = nullptr;
        vehiculos = Pila<string>();
        fila = Cola<string>();
    }

    Zona(string n){
        nombre = n;
        next = nullptr;
        vehiculos = Pila<string>();
        fila = Cola<string>();
    }
};

struct Parqueadero{
    string nombre;
    ListaEnlazada<Zona>* zonas;
    Parqueadero* next;

    Parqueadero(){
        nombre = "";
        next = nullptr;
        zonas = new ListaEnlazada<Zona>;
    }

    Parqueadero(string n){
        nombre = n;
        next = nullptr;
        zonas = new ListaEnlazada<Zona>;
    }
};

struct Ciudad{
    string nombre;
    ListaEnlazada<Parqueadero>* parqueaderos;
    Ciudad* next;

    Ciudad(string n){
        nombre = n;
        next = nullptr;
        parqueaderos = new ListaEnlazada<Parqueadero>;
    }
};
class Programa{
public:
    Programa(){
        head = nullptr;
    }

    void agregarCiudad(string n){
        if(!head){
            head = new Ciudad(n);
        }
        else{
            Ciudad* current = head;
            while(current->next){
                current = current->next;
            }
            current->next = new Ciudad(n);
        }
    }

    void agregarParqueadero(string nombreCiudad, string nombreParqueadero){
        auto current = head;
        while(current){
            if(current->nombre == nombreCiudad){
                break;
            }
            current = current->next;
        }

        if(!current){
            cout << "no se pudo encontrar la ciudad " + nombreCiudad + "\n";
            return;
        }
        current->parqueaderos->append(Parqueadero(nombreParqueadero));
    }

    void agregarZona(string nombreCiudad, string nombreParqueadero, string nombreZona){
        auto current = head;
        while(current){
            if(current->nombre == nombreCiudad){
                break;
            }
            current = current->next;
        }

        if(!current){
            cout << "no se pudo encontrar la ciudad " + nombreCiudad + "\n";
            return;
        }

        for(auto parqueadero : *current->parqueaderos){
            if(parqueadero.nombre == nombreParqueadero){
                parqueadero.zonas->append(Zona(nombreZona));
                return;
            }
        }
    }

    void buscarCiudad(string ciudad){
        Ciudad* current = head;
        int index = 0;
        while(current){
            if(current->nombre == ciudad){
                cout << "la ciudad " + ciudad + " esta en la posición " << index << " de la lista de ciudades\n";
                return;
            }
            current = current->next;
            index++;
        }
        cout << "no se pudo encontrar la ciudad " + ciudad + "\n";
    }

    void buscarParqueadero(string ciudad, string parqueadero){
        Ciudad* current = head;
        int ciudadIndex = 0;
        int parqueaderoIndex = 0;
        while(current){
            if(current->nombre == ciudad){
                for(auto p : *current->parqueaderos){
                    if(p.nombre == parqueadero){
                        cout << "el parqueadero " + parqueadero + " ocupa la posicion " << parqueaderoIndex;
                        cout << " en la ciudad " + ciudad + " con posicion " << ciudadIndex << "\n";
                        return;
                    }
                    parqueaderoIndex++;
                }
                cout << "no se pudo encontrar el parqueadero " + parqueadero + " en la ciudad " + ciudad + "\n";
            }
            ciudadIndex++;
            current = current->next;
        }
        cout << "no se pudo encontrar el parqueadero " + parqueadero + " en la ciudad " + ciudad + "\n";
    }

    void buscarZona(string ciudad, string parqueadero, string zona){
        Ciudad* current = head;
        int ciudadIndex = 0;
        int parqueaderoIndex = 0;
        int zonaIndex = 0;
        while(current){
            if(current->nombre == ciudad){
                for(auto p : *current->parqueaderos){
                    if(p.nombre == parqueadero){
                        for(auto z : *p.zonas){
                            if(z.nombre == zona){
                                cout << "la zona " + zona + " se encuentra en la posicion " << zonaIndex;
                                cout << " en el parqueadero " + parqueadero + " en la posicion " << parqueaderoIndex;
                                cout << " en la ciudad " + ciudad + " en la posicion " << ciudadIndex;
                            }
                            zonaIndex++;
                        }
                        cout << "no se pudo encontrar la zona " + zona + " en el parqueadero " + parqueadero;
                        cout << " en la ciudad " + ciudad + "\n";
                    }
                    parqueaderoIndex++;
                }
                cout << "no se pudo encontrar la zona " + zona + " en el parqueadero " + parqueadero;
                cout << " en la ciudad " + ciudad + "\n";
            }
            ciudadIndex++;
            current = current->next;
        }
        cout << "no se pudo encontrar la zona " + zona + " en el parqueadero " + parqueadero;
        cout << " en la ciudad " + ciudad + "\n";
    }

    void registrarVehiculo(string ciudad, string parqueadero, string zona, string placa){
        Ciudad* current = head;
        while(current){
            if(current->nombre == ciudad){
                for(auto& p : *current->parqueaderos){
                    if(p.nombre == parqueadero){
                        for(auto& z : *p.zonas){
                            if(z.nombre == zona){
                                if(!z.vehiculos.push(placa)){
                                    z.fila.enqueue(placa);
                                }
                                return;
                            }
                        }
                        cout << "no se pudo encontrar la zona " << zona << '\n';
                    }
                }
                cout << "no se pudo encontrar el parqueadero " + parqueadero + "\n";
            }
            current = current->next;
        }
        cout << "no se pudo encontrar la ciudad " + ciudad + "\n";
    }

    string deshacerRegistro(string ciudad, string parqueadero, string zona){
        Ciudad* current = head;
        while(current){
            if(current->nombre == ciudad){
                for(auto& p : *current->parqueaderos){
                    if(p.nombre == parqueadero){
                        for(auto& z : *p.zonas){
                            if(z.nombre == zona){
                                return z.vehiculos.pop();
                            }
                        }
                        cout << "no se pudo encontrar la zona " << zona << '\n';
                    }
                }
                cout << "no se pudo encontrar el parqueadero " + parqueadero + "\n";
            }
            current = current->next;
        }
        cout << "no se pudo encontrar la ciudad " + ciudad + "\n";
    }


    void atenderVehiculo(string ciudad, string parqueadero, string zona){
        Ciudad* current = head;
        while(current){
            if(current->nombre == ciudad){
                for(auto& p : *current->parqueaderos){
                    if(p.nombre == parqueadero){
                        for(auto& z : *p.zonas){
                            if(z.nombre == zona){
                                if(z.fila.getSize()){
                                    auto placa = z.fila.dequeue();
                                    if(!z.vehiculos.push(placa)){
                                        z.fila.enqueue(placa);
                                    }
                                    return;
                                }
                            }
                        }
                        cout << "no se pudo encontrar la zona " << zona << '\n';
                    }
                }
                cout << "no se pudo encontrar el parqueadero " + parqueadero + "\n";
            }
            current = current->next;
        }
        cout << "no se pudo encontrar la ciudad " + ciudad + "\n";
    }

    void mostrarEstructura(){
        auto current = head;
        while(current){
            cout << current->nombre + ":\n";
            if(!current->parqueaderos->getSize()){
                cout << "- no hay parqueaderos registrados\n";
            }
            else{
                for (auto p : *current->parqueaderos){
                    cout << "- " + p.nombre + "\n";
                    if(!p.zonas->getSize()){
                        cout << "    no hay zonas registradas\n";
                    }
                    else{
                        for(auto z : *p.zonas){
                            cout << "  - " + z.nombre + "\n";
                            z.vehiculos.print();
                            z.fila.print();
                        }
                    }
                }
            }
            current = current->next;
        }
    }
private:
    Ciudad* head;
};

void printMenu(){
    cout << "1.Agregar ciudad\n";
    cout << "2.Agregar parqueadero\n";
    cout << "3.Agregar zona\n";
    cout << "4.Registrar vehiculo\n";
    cout << "5.Mostrar estructura\n";
    cout << "6.Deshacer último registro\n";
    cout << "7.Atender vehiculo de la cola\n";
    cout << "8.Salir\n";
}

int main(){
    Programa p;
    bool running = true;
    int option;

    while(running){
        printMenu();
        cin >> option;
        cin.ignore();

        switch(option){
            case 1:{
                cout << "ingrese el nombre de la ciudad que busca añadir\n";
                string nombre;
                getline(cin, nombre);
                
                p.agregarCiudad(nombre);
                break;
            }
            case 2:{
                cout << "ingrese el nombre de la ciudad en la que desea ingresar el parqueadero\n";
                string ciudad;
                getline(cin, ciudad);
                cout << "ingrese el nombre del parqueadero que desea añadir\n";
                string parqueadero;
                getline(cin, parqueadero);
                p.agregarParqueadero(ciudad, parqueadero);
                break;
            }
            case 3:{
                string ciudad;
                string parqueadero;
                string zona;
                cout << "ingrese el nombre de la ciudad en la que desea ingresar la zona\n";
                getline(cin, ciudad);
                cout << "ingrese el nombre del parqueadero en el que desea añadir la zona\n";
                getline(cin, parqueadero);
                cout << "ingrese el nombre de la zona que desea añadir\n";
                getline(cin, zona);
                p.agregarZona(ciudad, parqueadero, zona);
                break;
            }
            case 4:{
                string ciudad;
                string parqueadero;
                string zona;
                string placa;
                cout << "ingrese la ciudad donde va a registrar el vehiculo\n";
                getline(cin, ciudad);
                cout << "ingrese el parqueadero donde va a registrar el vehiculo\n";
                getline(cin, parqueadero);
                cout << "ingrese la zona donde va a registrar el vehiculo\n";
                getline(cin, zona);
                cout << "ingrese la placa del vehiculo\n";
                getline(cin, placa);
                p.registrarVehiculo(ciudad, parqueadero, zona, placa);
                break;
            }
            case 5:
                p.mostrarEstructura();
                break;
            case 6:{
                string ciudad;
                string parqueadero;
                string zona;
                cout << "ingrese la ciudad donde va a deshacer el registro\n";
                getline(cin, ciudad);
                cout << "ingrese el parqueadero donde va a deshacer el registro\n";
                getline(cin, parqueadero);
                cout << "ingrese la zona donde va a deshacer el registro\n";
                getline(cin, zona);
                p.deshacerRegistro(ciudad, parqueadero, zona);
                break;
            }
            case 7:{
                string ciudad;
                string parqueadero;
                string zona;
                cout << "ingrese la ciudad donde va a atender el vehiculo\n";
                getline(cin, ciudad);
                cout << "ingrese el parqueadero donde va a atender el vehiculo\n";
                getline(cin, parqueadero);
                cout << "ingrese la zona donde va a atender el vehiculo\n";
                getline(cin, zona);
                p.atenderVehiculo(ciudad, parqueadero, zona);
                break;
            }
            case 8:
                running = false;
                break;
        }
    }
    return 0;
}