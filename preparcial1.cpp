#include <iostream>
#include <string>
#include <random>

using namespace std;

template <typename T>
class Node{
public:
    Node(){
        this->next = nullptr;
        this->data = T();
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

class Prestamo{
private:
    int codigoUsuario;
    int codigoLibro;
    int codigoGenero;
public:
    Prestamo(){
        codigoUsuario = -1;
        codigoLibro = -1;
        codigoGenero = -1;
    }

    Prestamo(int codigoUsuario, int codigoLibro, int codigoGenero){
        this->codigoUsuario = codigoUsuario;
        this->codigoLibro = codigoLibro;
        this->codigoGenero = codigoGenero;
    }

    int getUsuario(){
        return codigoUsuario;
    }

    int getLibro(){
        return codigoLibro;
    }

    int getGenero(){
        return codigoGenero;
    }

    void setUsuario(int codigoPasajero){
        this->codigoUsuario = codigoPasajero;
    }

    void setLibro(int codigoVehiculo){
        this->codigoLibro = codigoVehiculo;
    }

    void setGenero(int codigoRuta){
        this->codigoGenero = codigoRuta;
    }

    string to_string() const {
        return std::to_string(codigoUsuario) + ", " + std::to_string(codigoLibro) + ", " + std::to_string(codigoGenero);
    }

    friend std::ostream& operator<<(std::ostream& os, const Prestamo& ruta) {
        return os << ruta.to_string();
    }

    bool operator == (const Prestamo& p){
        if(codigoUsuario == p.codigoUsuario && codigoLibro == p.codigoLibro && codigoGenero == p.codigoGenero){
            return true;
        }
        return false;
    }
};

int* crearArreglo(int x){
    int* m = new int[x];
    for (int i = 0; i < x; i++){
        m[i] = 0;
    }
    return m;
}

void imprimirArreglo(int* arreglo, int x){
    cout << "[ ";
    for(int i = 0; i < x; i++){
        cout << arreglo[i];
        if(i != x - 1){
            cout << ", ";
        }
    }
    cout << " ]\n";
}


class Biblioteca{
private:
    int nu;
    int nl;
    int ng;
    int np;
    int* arreglo;
    LinkedList<Prestamo> prestamos;
public:
    Biblioteca(){
        nu = 1;
        nl = 10;
        ng = 10;
        np = 100;
        arreglo = crearArreglo(nl);
    }

    Biblioteca(int nu, int nl, int ng, int np){
        this->nu = nu;
        this->nl = nl;
        this->ng = ng;
        this->np = np;
        arreglo = crearArreglo(nl);
    }

    void inicializarLista(){
        cout << "------Lista de prestamos(usuario, libro, genero)------- \n";
        for(int i = 0; i < np; i++){
            int codigoUsuario = rand() % nu;
            int codigoLibro = rand() % nl;
            int codigoGenero = rand() % ng;
            Prestamo prestamo(codigoUsuario, codigoLibro, codigoGenero);
            prestamos.append(prestamo);
        }
        prestamos.print();
    }

    void llenarArreglo(){
        Node<Prestamo>* ptr = prestamos.getHead();
        for (int i = 0; i < np; i++) {
            arreglo[ptr->getData().getLibro()]++;
            ptr = ptr->getNext();
        }
        cout << "Prestamos por libro: \n";
        imprimirArreglo(arreglo, nl);
    }

};

int main(){
    const int NUM_PRESTAMOS = 10;
    const int MAX_CODIGO_USUARIO = 10;
    const int MAX_CODIGO_LIBRO = 10;
    const int MAX_CODIGO_GENERO = 10;
    Biblioteca p(MAX_CODIGO_USUARIO, MAX_CODIGO_LIBRO, MAX_CODIGO_GENERO, NUM_PRESTAMOS);
    p.inicializarLista();
    p.llenarArreglo();
    return 0;
}