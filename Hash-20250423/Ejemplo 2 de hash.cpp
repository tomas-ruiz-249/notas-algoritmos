//Hash polinómico con base 27 (solo 3 caracteres)


#include <iostream>
#include <string>
using namespace std;


int Hash_2(const string &key, int tableSize) {
    // Protección por si la clave tiene menos de 3 caracteres
    char c1 = (key.length() > 0) ? key[0] : 0;
    char c2 = (key.length() > 1) ? key[1] : 0;
    char c3 = (key.length() > 2) ? key[2] : 0;

    return (c1 + 27 * c2 + 729 * c3) % tableSize;
}

int main() {
    string key;
    int tableSize = 10007;

    cout << "Ingrese una clave: ";
    getline(cin, key);

    // Usamos la función renombrada
    int index = Hash_2(key, tableSize);

    cout << "El índice para la clave '" << key << "' es: " << index << endl;

    return 0;
}

// Se usa una función polinómica
// Eso genera valores entre 0 y ~92,000 
// El número 10,007 es el primo más cercano mayor que 10,000
