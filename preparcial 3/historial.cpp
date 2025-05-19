#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Pila{
public:
    Pila(){
        size = 0;
        capacity = 50;
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
        for(int i = 0; i < capacity; i++){
            if(arr[i] != T()){
                cout << i << ": ";
                cout << arr[i];
                cout << "\n";
            }
        }
    }

    bool canPush(){
        return size < capacity;
    }

    int getSize(){
        return size;
    }
private:
    T* arr;
    int capacity;
    int size;
};

class Historial{
public:
    void visitar(string url){
        if (actual != ""){
            visitadas.push(actual);
        }
        actual = url;
        print();
    }

    void atras(){
        if(visitadas.getSize() > 0){
            volver.push(actual);
            actual = visitadas.pop();
            print();
        }
        else{
            cout << "-----no hay paginas para ir adelante------\n";
        }
    }

    void adelante(){
        if(volver.getSize() > 0){
            visitadas.push(actual);
            actual = volver.pop();
            print();
        }
        else{
            cout << "-----no hay paginas para ir adelante------\n";
        }
    }

    void print(){
        cout << "--------pagina actual: " + actual << "---------\n";
        cout << "atras: \n";
        visitadas.print();
        cout << "adelante: \n";
        volver.print();
    }
private:
    string actual;
    Pila<string> visitadas;
    Pila<string> volver;
};

void printMenu(){
    cout << "1.Visitar url\n";
    cout << "2.Ir a la pagina anterior\n";
    cout << "3.Ir a la pagina siguiente\n";
    cout << "4.Salir\n";
}

int main(){
    Historial h;
    int option;
    bool running = true;
    while(running){
        printMenu();
        cin >> option;
        cin.ignore();
        switch(option){
        case 1:{
            string url;
            cout << "escriba la url que desea visitar\n";
            getline(cin, url);
            h.visitar(url);
            break;
        }
        case 2:
            h.atras();
            break;
        case 3:
            h.adelante();
            break;
        case 4:
            running = false;
            break;
        }
    }
    return 0;
}