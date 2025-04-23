//Hash polinómico general con base 37 (todos los caracteres)


#include <iostream>
#include <string>
using namespace std;

unsigned int hash_3(const string &key, int tableSize) {
    unsigned int hashValue = 0;

    for (char ch : key) {
        hashValue = 37 * hashValue + ch;
    }

    return hashValue % tableSize;
}

int main() {
    string key;
    int tableSize = 10007; // Primo grande para buena dispersión

    cout << "Ingrese una clave: ";
    getline(cin, key);

    unsigned int index = hash_3(key, tableSize);

    cout << "El índice para la clave '" << key << "' es: " << index << endl;

    return 0;
}