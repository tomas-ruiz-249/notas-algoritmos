#include <iostream>
#include <string>
#include <ctime>  // Para srand(time(0))

using namespace std;

/*código para la matriz*/

// Función para crear una matriz dinámica
int** crear_mat(int f, int c) {
    int** m = new int*[f];
    for (int i = 0; i < f; i++) {
        m[i] = new int[c];
        for (int j = 0; j < c; j++) {
            m[i][j] = 0;
        }
    }
    return m;
}

// Función para destruir la matriz
void destruir_mat(int** m, int f) {
    for (int i = 0; i < f; i++) {
        delete[] m[i];
    }
    delete[] m;
}

// Función para imprimir la matriz
void print_mat(int** m, int f, int c) {
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            cout << m[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}


/*código para el arreglo*/

int* crear_arreglo(int n) {
    int* arr = new int[n];  // Crear arreglo dinámico de tamaño n
    for (int i = 0; i < n; i++) {
        arr[i] = 0;  // Inicializar con 0 (o cualquier otro valor que desees)
    }
    return arr;
}

// Función para destruir el arreglo
void destruir_arreglo(int* arr) {
    delete[] arr;  // Liberar la memoria del arreglo dinámico
}

// Función para imprimir el arreglo
void print_arreglo(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << "\t";
    }
    cout << endl;
}

// Función para llenar el arreglo con valores
void llenar_arreglo(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << "Introduce el valor para el elemento " << i << ": ";
        cin >> arr[i];
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
//elemento que devuelve la suma de los elementos de un arreglo.
int suma(int* arr, int size){
    int suma = 0;
    for(int i = 0; i < size; i++){
        suma += arr[i];
    }
    return suma;
}

//clase Venta
class Venta {
private:
    int cliente;
    int vendedor;
    int producto;
public:
    Venta() {
        cliente = -1; 
        vendedor = -1;
        producto = -1;
    }
    Venta(int c, int v, int p) {
        cliente = c;
        vendedor = v;
        producto = p;
    }
    
    //Getters y Setters
    int getCliente() const { 
        return cliente; 
    }
    void setCliente(int c) { 
        cliente = c; 
    }
    int getVendedor() const { 
        return vendedor; 
    }
    void setVendedor(int v) { 
        vendedor = v; 
    }

    int getProducto() const { 
        return producto; 
    }
    void setProducto(int p) { 
        producto = p; 
    }

    //tomas ruiz
    //sobrecarga de operador =, permite asignar los valores de un objeto venta a otro
    Venta& operator=(const Venta& f) {
        cliente = f.cliente;
        vendedor = f.vendedor;
        producto = f.producto;
        return *this;
    }

    //tomas ruiz
    //muestra los atributos de la clase en un string
    string to_string() const {
        return std::to_string(cliente) + ", " + std::to_string(vendedor) + ", " + std::to_string(producto);
    }

    //tomas ruiz
    //permite imprimir la clase por medio de cout
    friend std::ostream& operator<<(std::ostream& os, const Venta& s) {
        return os << s.to_string();
    }
};

// Clase nodo con plantilla
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

//poner aquí su código de listas con los comentarios realizados en las clases
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
    //metodo que imprime a la consola una representacion de la lista enlazada. muestra el tamaño, el nodo en la cabeza, y el nodo en la cola.
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
    //método que devuelve un dato en la lista en una posición dada. Si el indice es invalido, se devuelve el valor por defecto del tipo de dato que se almacena en la lista.
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
    //metodo que inserta un nodo al final de la lista. En lugar de iterar sobre toda la lista hasta el final, se guarda un registro del nodo en la cola y de ahi se inserta el nuevo nodo.
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
    //metodo que inserta un nodo en una posición dada, iterando sobre la lista hasta que encuentra la posicion donde insertar. En caso de que la posicion sea invalida, no se inserta nada
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
    //metodo que elimina un nodo en una posición dada. si el indice es invalido, no se elimina nada.
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
    //método que invierte una lista enlazada. Si la lista es vacia, se especifica por la consola que no se puede invertir
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
    //tomas ruiz
    //puntero a la cabeza de la lista
    Node<T>* head;
    //tomas ruiz
    //puntero a la cola de la lista
    Node<T>* tail;
    //tomas ruiz
    //tamaño de la lista
    int size;
};



// Clase Distribuidora
class Distribuidora {
private:
    //max codigo clientes
    int nc; 
    //max codigo vendedor
    int nv;
    //max codigo producto
    int np;
    //numero de ventas
    int ns;
    int** matriz;
    int* arreglo;
    LinkedList<Venta> ventas;
public:
    //tomas ruiz
    // constructor
    Distribuidora(int c = 100, int v = 100, int p = 100, int s = 1000): nc(c), nv(v), np(p), ns(s) {
        matriz = crear_mat(nv, np);
        arreglo = crear_arreglo(nv);
    }

    //tomas ruiz
    // destructor
    ~Distribuidora() {
        destruir_mat(matriz, nv);
        destruir_arreglo(arreglo);
    }
    
    //crear el método init_lista()

    //tomas ruiz
    // metodo que inicializa la lista de ventas con valores aleatorios y la imprime
    void init_lista() {
        for(int i = 0; i < ns; i++){
            int cliente = rand() % nc;
            int vendedor = rand() % nv;
            int producto = rand() % np;
            Venta venta(cliente, vendedor, producto);
            ventas.append(venta);
        }
        print();
    }

    //tomas ruiz
    //metodo que imprime la lista de ventas
    void print() {
        cout << "Se han generado " << ns << " ventas\n";
        ventas.print();
    }
    
    //tomas ruiz
    //metodo que genera un arreglo del total de ventas de cada vendedor. El indice es el codigo del vendedor y el valor es su total
    void generar_arreglo() {
        Node<Venta>* ptr = ventas.getHead();
        while (ptr != nullptr) {
            arreglo[ptr->getData().getVendedor()]++;  // Incrementar el vendedor correspondiente en el arreglo Si la lista es vacia, se especifica por la consola que no se puede invertir
            ptr = ptr->getNext();
        }
        cout << "Arreglo de vendedores: " << endl;
        print_arreglo(arreglo, nv);  // Imprimir el arreglo con los vendedores y sus ventas
    }
    
    //tomas ruiz
    //metodo que genera un arreglo de vendedores x productos segun los datos en la lista de ventas, donde las filas son los productos y las columnas son los vendedores
    void calcular_matriz(){
        Node<Venta>* ptr = ventas.getHead();
        while (ptr != nullptr) {
            matriz[ptr->getData().getProducto()][ptr->getData().getVendedor()]++;  
            ptr = ptr->getNext();
        }
        cout << "Matriz de vendedores x productos: " << endl;
        print_mat(matriz, np, nv);
    }
    

    //tomas ruiz
    //metodo que calcula el vendendor con mas ventas en un producto dado, al escoger el valor maximo de la fila correspondiente al producto, y devolver su indice
   int vendedor_con_mas_ventas_por_producto(int indice){
        int* vendedores;
        vendedores = matriz[indice];
        return maxPos(vendedores, nv);
    }
   
    
    //crear el método calcular_promedio_ventas
    //tomas ruiz
    //metodo que calcula el promedio de ventas por vendedor al sumar todas las ventas de cada vendedor y dividir por el numero de vendedores.
    double calcular_promedio_ventas(){
        double promedio = suma(arreglo, nv) / (double)nv;
        cout << "el promedio de las ventas por vendedor es: " << promedio << "\n";
        return promedio;
    }
};

int main() {
    srand(time(0));  // Inicialización del generador de números aleatorios con el tiempo actual
    int c = 10;
    int v = 10;
    int p = 10;
    int s = 100;
    Distribuidora dis = Distribuidora(c, v, p, s);
    dis.init_lista();
    cout << endl;
    dis.calcular_matriz();
    for (int i = 0; i < p; i++) {
        cout << "El vendedor con más ventas en el producto " << i << " es: " 
             << dis.vendedor_con_mas_ventas_por_producto(i) << endl;
    }
    cout << "-------------datos del arreglo-------------" << endl;
    dis.generar_arreglo();
    dis.calcular_promedio_ventas();
    return 0;
}