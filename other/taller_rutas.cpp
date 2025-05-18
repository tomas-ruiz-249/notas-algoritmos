#include <iostream>
#include <string>
#include <random>

using namespace std;

template <typename T>
class Node{
public:
    //tomas ruiz
    //constructor por defecto, inicializa next y el dato del nodo.
    Node(){
        this->next = nullptr;
        this->data = T();
    }

    //tomas ruiz
    //constructor que inicializa el dato del nodo al valor dado por argumento.
    Node(T data){
        this->data = data;
        this->next = nullptr;
    }
    
    //tomas ruiz
    //constructor que inicializa el dato y en puntero al siguiente por argumento.
    Node(T data, Node<T>* next){
        this->data = data;
        this->next = next;
    }

    ~Node(){
        delete next;
        delete data;
    }

    //tomas ruiz
    //getter del puntero al siguiente nodo;
    Node<T>* getNext(){
        return next;
    }

    //tomas ruiz
    //setter del puntero al siguiente nodo
    void setNext(Node<T>* node){
        next = node;
    }

    //tomas ruiz
    //getter del dato;
    T getData(){
        return data;
    }
private:
    T data;
    Node<T>* next;
};

template <typename T>
class LinkedList{
public:
    //tomas ruiz
    //constructor por defecto para la lista enlazada
    LinkedList(){
        head = nullptr;
        tail = head;
        size = 0;
    }

    //tomas ruiz
    //destructor
    ~LinkedList(){
        Node<T>* current = head;
        Node<T>* next = nullptr;
        while(current != nullptr){
            next = current->getNext();
            delete current;
            current = next;
        }
    }

    //tomas ruiz
    //metodo que imprime a la consola una representacion de la lista enlazada. imprime el tamaño, el nodo en la cabeza, y el nodo en la cola.
    void print(){
        cout << "[HEAD]";
        Node<T>* current = head;
        while(current != nullptr){
            cout << "(" << current->getData() << ")--->";
            current = current->getNext();
        }
        cout << "NULL\n";
        cout << "size: " << size << "\n";
        cout << "head: " << head->getData() << "\n";
        cout << "tail: " << tail->getData() << "\n";
    }

    //tomas ruiz
    //método que devuelve un dato en la lista en una posición dada.
    T get(int index){
        if(index > size || index < 0){
            return T();
        }
        Node<T>* current = head;
        for(int i = 0; i < index; i++){
            current = current->getNext();
        }
        return current->getData();
    }

    //tomas ruiz
    //metodo que inserta un nodo al final de la lista.
    void append(T newValue){
        auto newNode = new Node<T>(newValue);
        if(head == nullptr){
            head = newNode;
            tail = head;
            size++;
        }
        else{
            tail->setNext(newNode);
            tail = newNode;
            size++;
        }
    }

    //tomas ruiz
    //metodo que inserta un nodo en una posición dada.
    void insert(T newValue, int position){
        if(position > size || position < 0){
            cout << "can't insert in position out of bounds\n";
        }
        else{
            Node<T>* current = head;
            Node<T>* newNode = new Node<T>(newValue);
            if(position == 0){
                newNode->setNext(head->getNext());
                head = newNode;
            }
            else{
                for(int i = 0; i < position-1; i++){
                    current = current->getNext();
                }
                newNode->setNext(current->getNext());
                current->setNext(newNode);
            }
            size++;
        }
    }

    //tomas ruiz
    //método que busca un valor en la lista y devuelve su posición en la lista. En caso que no se encuentre, devuelve -1
    int find(T value){
        Node<T>* current = head;
        int index = 0;
        while(current != nullptr){
            if(current->getData() == value){
                return index;
            }
            else{
                index++;
                current = current->getNext();
            }
        }
        return -1;
    }

    //tomas ruiz
    //metodo que elimina un nodo en una posición.
    void remove(int index){
        if(index < 0 || index > size-1 || head == nullptr){
            cout << "can't remove node at specified index\n";
            return;
        }
        Node<T>* prev = head;
        if(index == 0){
            head = prev->getNext();
            delete prev;
        }
        else{
            for(int i = 0; i < index-1; i++){
                prev = prev->getNext();
            }
            Node<T>* current = prev->getNext();
            prev->setNext(current->getNext());
            delete current;
        }
        size--;
    }

    //tomas ruiz
    //metodo que busca un nodo por valor en la lista y lo elimina, si es posible.
    void remove(T value){
        int index = find(value);
        if(index == -1){
            cout << "could not find value to be removed\n";
            return;
        }
        remove(index);
    }

    //tomas ruiz
    //método que reversa una lista enlazada.
    void reverse(){
        if(head != nullptr){
            Node<T>* prev = nullptr;
            Node<T>* current = head;
            Node<T>* next = nullptr;
            tail = head;
    
            while(current != nullptr){
                next = current->getNext();
                current->setNext(prev);
                prev = current;
                current = next;
            }
            head = prev;
        }
        else{
            cout << "cannot reverse an empty list\n";
        }
    }

    //tomas ruiz
    //getter del tamaño de la lista
    int getSize(){
        return size;
    }

    //tomas ruiz
    //getter de la cabeza de la lista
    Node<T>* getHead(){
        return head;
    }

    //tomas ruiz
    //getter de la cola de la lista.
    Node<T>* getTail(){
        return tail;
    }
private:
    Node<T>* head;
    Node<T>* tail;
    int size;
};

class Ruta{
private:
    int codigoPasajero;
    int codigoVehiculo;
    int codigoRuta;
public:
    //tomas ruiz
    //constructor por defecto de una ruta
    Ruta(){
        codigoPasajero = -1;
        codigoVehiculo = -1;
        codigoRuta = -1;
    }

    //tomas ruiz
    //constructor parametrizado
    Ruta(int codigoPasajero, int codigoVehiculo, int codigoRuta){
        this-> codigoPasajero = codigoPasajero;
        this-> codigoRuta = codigoRuta;
        this-> codigoVehiculo = codigoVehiculo;
    }

    //tomas ruiz
    //getter del codigo del pasajero.
    int getPasajero(){
        return codigoPasajero;
    }

    //tomas ruiz
    //getter del codigo del vehiculo.
    int getVehiculo(){
        return codigoVehiculo;
    }

    //tomas ruiz
    //getter del codigo de la ruta.
    int getRuta(){
        return codigoRuta;
    }

    //tomas ruiz
    //setter del codigo del pasajero.
    void setPasajero(int codigoPasajero){
        this->codigoPasajero = codigoPasajero;
    }

    //tomas ruiz
    //setter del codigo del vehiculo
    void setVehiculo(int codigoVehiculo){
        this->codigoVehiculo = codigoVehiculo;
    }

    //tomas ruiz
    //setter del codigo de la ruta
    void setRuta(int codigoRuta){
        this->codigoRuta = codigoRuta;
    }

    //tomas ruiz
    //metodo que muestra los atributos de la clase como un string.
    string to_string() const {
        return std::to_string(codigoPasajero) + ", " + std::to_string(codigoVehiculo) + ", " + std::to_string(codigoRuta);
    }

    //tomas ruiz
    //overload del operador <<
    friend std::ostream& operator<<(std::ostream& os, const Ruta& ruta) {
        return os << ruta.to_string();
    }

    //tomas ruiz
    //overload del operador ==
    bool operator == (const Ruta& r){
        if(codigoPasajero == r.codigoPasajero && codigoVehiculo == r.codigoVehiculo && codigoRuta == r.codigoRuta){
            return true;
        }
        return false;
    }
};

//tomas ruiz
//funcion que crea una matriz dinámicamente de dimensiones x y
int** createMatrix(int y, int x){
    int** m = new int*[y];
    for (int i = 0; i < y; i++){
        m[i] = new int[x];
        for(int j = 0; j < x; j++){
            m[i][j] = 0;
        }
    }
    return m;
}

//tomas ruiz
//función que elimina una matriz de la memoria.
void deleteMatrix(int** matrix, int y){
    for(int i = 0; i < y; i++){
        delete [] matrix[i];
    }
    delete matrix;
}

//tomas ruiz
//función que muestra una matríz en consola.
void printMatrix(int** matrix, int y, int x){
    for(int i = 0; i < y; i++){
        cout << "[ ";
        for(int j = 0; j < x; j++){
            cout << (int)matrix[i][j];
            if(j != x - 1){
                cout << ", ";
            }
        }
        cout << " ]\n";
    }
}

//tomas ruiz
//función que devuelve la posicion del elemento más grande de un arreglo
int maxPos(int* arr, int size){
    int max = -1;
    int indice = 0;
    for(int i = 0; i < size; i++){
        if(arr[i] > max){
            max = arr[i];
            indice = i;
        }
    }
    return indice;
}

//tomas ruiz
//función que devuelve la posicion del elemento mas pequeño de un arreglo.
int minPos(int* arr, int size){
    int min = INT32_MAX;
    int indice = 0;
    for(int i = 0; i < size; i++){
        if(arr[i] < min){
            min = arr[i];
            indice = i;
        }
    }
    return indice;
}

//tomas ruiz
//elemento que devuelve la suma de los elementos de un arreglo.
int suma(int* arr, int size){
    int suma = 0;
    for(int i = 0; i < size; i++){
        suma += arr[i];
    }
    return suma;
}

class Plataforma{
private:
    int np;
    int nv;
    int nr;
    int nt;
    int** matriz;
    LinkedList<Ruta> rutas;
public:
    //tomas ruiz
    //constructor por defecto.
    Plataforma(){
        np = 1;
        nv = 10;
        nr = 10;
        nt = 100;
        matriz = createMatrix(nr, nv);
    }

    //tomas ruiz
    //constructor parametrizado
    Plataforma(int np, int nv, int nr, int nt){
        this->np = np;
        this->nv = nv;
        this->nr = nr;
        this->nt = nt;
        matriz = createMatrix(nr, nv);
    }

    //tomas ruiz
    //método que inicializa la lista enlazada con valores aleatorios, los codigos de cada nodo estan entre 0 y np, nv, o nr respectivamente. Se generan nt nodos en la lista.
    void inicializarLista(){
        for(int i = 0; i < nt; i++){
            int codigoPasajero = rand() % np;
            int codigoVehiculo = rand() % nv;
            int codigoRuta = rand() % nr;
            Ruta ruta(codigoPasajero, codigoVehiculo, codigoRuta);
            rutas.append(ruta);
        }
        rutas.print();
    }

    //tomas ruiz
    //se toma el codigo de ruta y el codigo del vehiculo como el 'y' y el 'x' respectivamente de una matriz, y le suma 1 a esa posición. Hace esto para cada viaje en la lista enlazada.
    void llenarMatriz(){
        Node<Ruta>* ptr = rutas.getHead();
        for (int i = 0; i < nt; i++) {
            matriz[ptr->getData().getRuta()][ptr->getData().getVehiculo()]++;
            ptr = ptr->getNext();
        }
        cout << "Matriz de vehiculos x por rutas y : \n";
        printMatrix(matriz, nr, nv);
    }

    //tomas ruiz
    //método que calcula la ruta más popular al guardar en un arreglo los numeros de viajes de cada ruta y escoger el máximo.
    int calcRutaMasPopular(){
        int* rutas = new int[nr]();
        for(int i = 0; i < nr; i++){
            int numViajes = suma(matriz[i], nv);
            rutas[i] = numViajes;
        }
        int rutaMasPopular = maxPos(rutas, nr);
        delete[] rutas;
        return rutaMasPopular;
    }

    //tomas ruiz
    //método que hace lo mismo que el anterior pero busca el mínimo del arreglo en vez del máximo.
    int calcRutaMenosPopular(){
        int* rutas = new int[nr]();
        for(int i = 0; i < nr; i++){
            int numViajes = suma(matriz[i], nv);
            rutas[i] = numViajes;
        }
        int rutaMenosPopular = minPos(rutas, nr);
        delete[] rutas;
        return rutaMenosPopular;
    }

    //tomas ruiz
    //método que acumula el numero de viajes de cada vehiculo en un arreglo, y escoge el máximo elemento.
    int calcVehiculoMasPopular(){
        int* vehiculos = new int[nv]();
        for(int i = 0; i < nv; i++){
            for(int j = 0; j < nr; j++){
                vehiculos[i] += matriz[j][i];
            }
        }
        int vehiculoMasPopular = maxPos(vehiculos, nv);
        delete[] vehiculos;
        return vehiculoMasPopular;
    }

    //tomas ruiz
    //método que hace lo mismo que el anterior pero escoge el mínimo elemento del arreglo.
    int calcVehiculoMenosPopular(){
        int* vehiculos = new int[nv]();
        for(int i = 0; i < nv; i++){
            for(int j = 0; j < nr; j++){
                vehiculos[i] += matriz[j][i];
            }
        }
        int vehiculoMenosPopular = minPos(vehiculos, nv);
        delete[] vehiculos;
        return vehiculoMenosPopular;
    }

    //tomas ruiz
    //método que guarda en un arreglo el promedio de viajes de cada vehiculo y los muestra por pantalla.
    void mostrarPromedioViajesPorVehiculo(){
        float* promedios = new float[nv]();
        int count = 0;
        for(int i = 0; i < nv; i++){
            for(int j = 0; j < nr; j++){
                promedios[i] += matriz[j][i];
                count++;
            }
            promedios[i] /= (float)count;
            count = 0;
        }
        cout << "promedios por vehiculo:\n" << "[ ";
        for(int i = 0; i < nv; i++){
            cout << promedios[i];
            if(i != nv - 1){
                cout << ", ";
            }
        }
        cout << " ]\n";
        delete[] promedios;
    }

    //tomas ruiz
    //método que dado una ruta, calcula el vehiculo que tiene mas viajes. si es una ruta invalida, se devuelve -1.
    int vehiculoConMasViajes(int ruta){
        if(ruta < 0 || ruta >= nr){
            return -1;
        }
        int* vehiculos = matriz[ruta];
        return maxPos(vehiculos, nv);
    }
};

int main(){
    //tomas ruiz
    //se llaman todas las funcionalidades de la clase.
    const int maxCodigoPasajero = 100;
    const int maxCodigoVehiculo = 10;
    const int maxCodigoRuta = 10;
    const int totalViajes = 5;
    Plataforma p(maxCodigoPasajero, maxCodigoVehiculo, maxCodigoRuta,totalViajes);
    p.inicializarLista();
    p.llenarMatriz();
    cout << "la ruta con mas pasajeros transportados es la ruta: " << p.calcRutaMasPopular() << "\n";
    cout << "la ruta con menos pasajeros transportados es la ruta: " << p.calcRutaMenosPopular() << "\n";
    cout << "el vehiculo con mas viajes es el vehiculo: " << p.calcVehiculoMasPopular() << "\n";
    cout << "el vehiculo con menos viajes es el vehiculo: " << p.calcVehiculoMenosPopular() << "\n";
    p.mostrarPromedioViajesPorVehiculo();
    int ruta;
    cout << "ingrese una ruta\n";
    cin >> ruta;
    if(p.vehiculoConMasViajes(ruta) == -1){
        cout << "ruta invalida\n";
    }
    else{
        cout << "el vehiculo con mas viajes en la ruta " << ruta << " es el vehiculo: " << p.vehiculoConMasViajes(ruta) << "\n";
    }
    return 0;
}