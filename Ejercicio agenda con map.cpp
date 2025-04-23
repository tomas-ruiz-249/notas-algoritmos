#include <iostream>
#include <string>

using namespace std;

// -------------------- Nodo para Map --------------------

template <typename K, typename V>
struct PairNode {
    K key;
    V value;
    PairNode* next;

    PairNode(K k, V v) : key(k), value(v), next(nullptr) {}
};

// -------------------- Clase Map --------------------

template <typename K, typename V>
class Map {
private:
    PairNode<K, V>* head;

    PairNode<K, V>* findNode(K key) const {
        PairNode<K, V>* current = head;
        while (current) {
            if (current->key == key)
                return current;
            current = current->next;
        }
        return nullptr;
    }

public:
    Map() : head(nullptr) {}

    ~Map() {
        PairNode<K, V>* current = head;
        while (current) {
            PairNode<K, V>* next = current->next;
            delete current;
            current = next;
        }
    }

    void insert(K key, V value) {
        PairNode<K, V>* node = findNode(key);
        if (node) {
            node->value = value; // actualizar
        } else {
            PairNode<K, V>* newNode = new PairNode<K, V>(key, value);
            newNode->next = head;
            head = newNode;
        }
    }

    bool get(K key, V& value) const {
        PairNode<K, V>* node = findNode(key);
        if (node) {
            value = node->value;
            return true;
        }
        return false;
    }

    void remove(K key) {
        PairNode<K, V>* current = head;
        PairNode<K, V>* prev = nullptr;

        while (current) {
            if (current->key == key) {
                if (prev)
                    prev->next = current->next;
                else
                    head = current->next;
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    void print() const {
        PairNode<K, V>* current = head;
        std::cout << "{\n";
        while (current) {
            std::cout << "  " << current->key << " → " << current->value << "\n";
            current = current->next;
        }
        std::cout << "}\n";
    }
};

void printMenu(){
    cout << "1.registrar nueva nota\n";
    cout << "2.actualizar nota de estudiante\n";
    cout << "3.eliminar registro por carnet\n";
    cout << "4.consultar nota de estudiante\n";
    cout << "5.mostrar listado completo de estudiantes y notas\n";
    cout << "6.salir\n";
}

int main() {
    Map<string, double> registroNotas;
    bool running = true;
    int option;
    string carnet;
    double nota;
    while(running){
        printMenu();
        cin >> option;
        switch(option){
        case 1:
            cout << "ingrese carnet del estudiante\n";
            cin >> carnet;
            cout << "ingrese nota\n";
            cin >> nota;
            registroNotas.insert(carnet, nota);
            break;
        case 2:
            cout << "ingrese carnet del estudiante\n";
            cin >> carnet;
            cout << "ingrese nueva nota\n";
            cin >> nota;
            registroNotas.remove(carnet);
            registroNotas.insert(carnet, nota);
            break;
        case 3:
            cout << "ingrese carnet del estudiante\n";
            cin >> carnet;
            registroNotas.remove(carnet);
            break;
        case 4:{
            cout << "ingrese carnet del estudiante\n";
            cin >> carnet;
            bool found = registroNotas.get(carnet, nota);
            if(found){
                cout << "la nota del estudiante con carnet " + carnet + " es de " << nota << "\n";
            }
            else{
                cout << "el estudiante con el carnet " + carnet + " no fue encontrado\n";
            }
            break;
        }
        case 5:
            cout << "registro de notas:\n";
            registroNotas.print();
            break;
        case 6:
            running = false;
            break;
        }
    }
    return 0;
}