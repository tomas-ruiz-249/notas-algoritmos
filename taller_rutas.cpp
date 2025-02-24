#include <iostream>
#include <string>
#include <random>

using namespace std;

template <typename T>
class Node{
public:
    Node(){
        this->next = nullptr;
    }
    Node(T data){
        this->data = data;
        this->next = nullptr;
    }
    Node(T data, Node<T>* next){
        this->data = data;
        this->next = next;
    }
    Node<T>* getNext(){
        return next;
    }
    void setNext(Node<T>* node){
        next = node;
    };
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
    LinkedList(){
        head = nullptr;
        tail = head;
        size = 0;
    }

    LinkedList(Node<T>* head){
        this->head = head;
        tail = this->head;
        size = 0;
    }

    ~LinkedList(){
        Node<T>* current = head;
        Node<T>* next = nullptr;
        while(current != nullptr){
            next = current->getNext();
            delete current;
            current = next;
        }
    }

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

    void remove(T value){
        int index = find(value);
        if(index == -1){
            cout << "could not find value to be removed\n";
            return;
        }
        remove(index);
    }

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

    int getSize(){
        return size;
    }

    Node<T>* getHead(){
        return head;
    }

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
    Ruta(){
        codigoPasajero = -1;
        codigoVehiculo = -1;
        codigoRuta = -1;
    }

    Ruta(int codigoPasajero, int codigoVehiculo, int codigoRuta){
        this-> codigoPasajero = codigoPasajero;
        this-> codigoRuta = codigoRuta;
        this-> codigoVehiculo = codigoVehiculo;
    }

    int getPasajero(){
        return codigoPasajero;
    }

    int getVehiculo(){
        return codigoVehiculo;
    }

    int getRuta(){
        return codigoRuta;
    }

    void setPasajero(int codigoPasajero){
        this->codigoPasajero = codigoPasajero;
    }

    void setVehiculo(int codigoVehiculo){
        this->codigoVehiculo = codigoVehiculo;
    }

    void setRuta(int codigoRuta){
        this->codigoRuta = codigoRuta;
    }

    string to_string() const {
        return std::to_string(codigoPasajero) + ", " + std::to_string(codigoVehiculo) + ", " + std::to_string(codigoRuta);
    }

    friend std::ostream& operator<<(std::ostream& os, const Ruta& ruta) {
        return os << ruta.to_string();
    }

    bool operator == (const Ruta& r){
        if(codigoPasajero == r.codigoPasajero && codigoVehiculo == r.codigoVehiculo && codigoRuta == r.codigoRuta){
            return true;
        }
        return false;
    }
};

int** createMatrix(int y, int x){
    int ** m = new int*[y];
    for (int i = 0; i < y; i++){
        m[i] = new int[x];
        for(int j = 0; j < x; j++){
            m[i][j] = 0;
        }
    }
    return m;
}

void deleteMatrix(int** matrix, int y){
    for(int i = 0; i < y; i++){
        delete [] matrix[i];
    }
    delete matrix;
}

void printMatrix(int** matrix, int y, int x){
    for(int i = 0; i < y; i++){
        cout << "[ ";
        for(int j = 0; j < x; j++){
            cout << matrix[i][j];
            if(j != x - 1){
                cout << ", ";
            }
        }
        cout << " ]\n";
    }
}

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
    Plataforma(){
        np = 1;
        nv = 10;
        nr = 10;
        nt = 100;
        matriz = createMatrix(nr, nv);
    }

    Plataforma(int np, int nv, int nr, int nt){
        this->np = np;
        this->nv = nv;
        this->nr = nr;
        this->nt = nt;
        matriz = createMatrix(nr, nv);
    }

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

    void llenarMatriz(){
        Node<Ruta>* ptr = rutas.getHead();
        for (int i = 0; i < nt; i++) {
            matriz[ptr->getData().getRuta()][ptr->getData().getVehiculo()]++;
            ptr = ptr->getNext();
        }
        cout << "Matriz de vehiculos x por rutas y : " << endl;
        printMatrix(matriz, nr, nv);
    }

    int calcRutaMasPopular(){
        int* rutas = new int[nr];
        for(int i = 0; i < nr; i++){
            int numViajes = suma(matriz[i], nv);
            rutas[i] = numViajes;
        }
        int rutaMasPopular = maxPos(rutas, nr);
        delete[] rutas;
        return rutaMasPopular;
    }

    int calcRutaMenosPopular(){
        int* rutas = new int[nr];
        for(int i = 0; i < nr; i++){
            int numViajes = suma(matriz[i], nv);
            rutas[i] = numViajes;
        }
        int rutaMenosPopular = minPos(rutas, nr);
        delete[] rutas;
        return rutaMenosPopular;
    }

};

int main(){
    Plataforma p(10,10,10,5);
    p.inicializarLista();
    p.llenarMatriz();
    cout << p.calcRutaMenosPopular();
    return 0;
}