#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Vector{
    public:
        Vector(){
            arr = nullptr;
            size = 0;
            capacity = 0;
        }

        Vector(int capacity){
            arr = new T[capacity]();
            this->capacity = capacity;
            size = 0;
        }

        int getSize() {
            return size;
        }

        int getCapacity(){
            return capacity;
        }

        void crecer(){
            T* nuevoArr = new T[capacity * 2]();
            for(int i = 0; i < size; i++){
                nuevoArr[i] = arr[i];
            }
            delete[] arr;
            arr = nuevoArr;
            capacity *= 2;
        }

        void encoger(){
            capacity = size;
            T* nuevo_arr = new T[capacity]();
            for(int i = 0; i < capacity; i++){
                nuevo_arr[i] = arr[i];
            }
            delete[] arr;
            arr = nuevo_arr;
        }

        void push(T dato){
            if (capacity == 0){
                arr = new T[1]();
                capacity = 1;
            }
            if(size == capacity){
                crecer();
            }
            arr[size] = dato;
            size++;
        }

        T pop(int indice = -1){
            if(size <= 0){
                throw std::out_of_range("pop() no puede ser llamado en vector vacio.");
            }
            if (indice == -1){
                indice = size - 1;
            }
            T dato = arr[indice];
            for(int i = indice; i < capacity-1; i++){
                arr[i] = arr[i+1];
            }
            size--;
            if(size == capacity/2){
                encoger();
            }
            return dato;
        }

        T& at(int index){
            if(index >= size)
                throw std::out_of_range("Indice fuera del rango.");
            return arr[index];
        }
        
        T& operator[](int index) {
            return arr[index];
        }

        string to_string(){
            string str;
            for(int i = 0; i < capacity; i++){
                str += std::to_string(arr[i]);
            }
            return str;
        }

        bool contains(T value){
            for(int i = 0; i < size; i++){
                if (arr[i] == value){
                    return true;
                }
            }
            return false;
        }

        class Iterator {
        private:
            T* ptr;
        public:
            Iterator(T* p) : ptr(p) {}
            
            T& operator*() const { return *ptr; }
            Iterator& operator++() { ++ptr; return *this; }
            bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
        };
        
        Iterator begin() { return Iterator(arr); }
        Iterator end()   { return Iterator(arr + size); }
        
    private:
        T* arr;
        int size;
        int capacity;
};

template<typename T>
class PriorityQueue {
public:
    void enqueue(T value) {
        minHeap.push(value);
        heapifyUp(minHeap.getSize() - 1);
    }

    T dequeue() {
        if (minHeap.getSize() == 0) {
            throw std::out_of_range("Heap is empty");
        }
        T minValue = minHeap[0];
        minHeap[0] = minHeap[minHeap.getSize() - 1];
        minHeap.pop();

        if (minHeap.getSize() > 0) {
            heapifyDown(0);
        }
        return minValue;
    }

    T peek() {
        if (minHeap.getSize() == 0) {
            throw std::out_of_range("Heap is empty");
        }
        return minHeap[0];
    }

    bool isEmpty() {
        return minHeap.getSize() == 0;
    }

    void print() {
        std::cout << "Priority Queue: [";
        for (size_t i = 0; i < minHeap.getSize(); i++) {
            std::cout << minHeap[i] << " ";
        }
        std::cout <<"]"<< std::endl;
    }

private:
    Vector<T> minHeap;

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (minHeap[index] < minHeap[parent]) {
                swap(minHeap[index], minHeap[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int left, right, smallest;
        int size = minHeap.getSize();
        
        while (true) {
            left = 2 * index + 1;
            right = 2 * index + 2;
            smallest = index;
            
            if (left < size && minHeap[left] < minHeap[smallest]) {
                smallest = left;
            }
            
            if (right < size && minHeap[right] < minHeap[smallest]) {
                smallest = right;
            }
            
            if (smallest != index) {
                swap(minHeap[index], minHeap[smallest]);
                index = smallest;
            } else {
                break;
            }
        }
    }
};

struct Paciente{
    string nombre;
    int gravedad;
    Paciente() = default;
    Paciente(string nombre, int gravedad){
        this->nombre = nombre;
        this->gravedad = gravedad;
    }
    bool operator>(Paciente& p){
        return this->gravedad > p.gravedad;
    }
    bool operator<(Paciente& p){
        return this->gravedad < p.gravedad;
    }
    bool operator==(Paciente& p){
        return this->gravedad == p.gravedad;
    }
    bool operator!=(Paciente& p){
        return this->gravedad != p.gravedad;
    }
    friend ostream& operator<<(ostream& os, Paciente& p){
        os << "(" << p.nombre << ", " << p.gravedad << ")";
        return os;
    }
};

class Urgencias{
public:
    void agregarPaciente(string nombre, int gravedad){
        if(gravedad > 5 || gravedad < 1){
            cout << "la gravedad del paciente debe estar entre 1 y 5. intenta de nuevo.\n";
            return;
        }
        Paciente p(nombre, gravedad);
        pq.enqueue(p);
    }

    void atenderPaciente(){
        if(pq.isEmpty()){
            cout << "No hay pacientes que atender\n";
            return;
        }
        Paciente atendido = pq.dequeue();
        cout << "Se ha atendido al paciente " + atendido.nombre + "\n";
    }

    void mostrar(){
        pq.print();
    }
private:
    PriorityQueue<Paciente> pq;
};

void printMenu(){
    cout << "1.Agregar Paciente\n";
    cout << "2.Atender Paciente\n";
    cout << "3.Ver pacientes\n";
    cout << "4.Salir\n";
}

int main(){
    Urgencias u;
    int option;
    bool running = true;
    while(running){
        printMenu();
        cin >> option;
        cin.ignore();
        switch(option){
        case 1:{
            string nombre;
            cout << "ingrese el nombre del paciente\n";
            getline(cin, nombre);
            int gravedad;
            cout << "ingrese la gravedad del paciente, 1-5\n";
            cin >> gravedad;
            cin.ignore();
            u.agregarPaciente(nombre, gravedad);
            break;
        }
        case 2:
            u.atenderPaciente();
            break;
        case 3:
            u.mostrar();
            break;
        case 4:
            running = false;
            break;
        }
    }
    return 0;
}