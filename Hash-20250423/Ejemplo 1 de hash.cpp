//Suma de caracteres simples

#include <iostream>
#include <string>

using namespace std;

// Función hash que calcula el índice basado en la clave (key)
int hash_1(const string& key, int tableSize) {
    int hashValue = 0;

    // Sumar los valores ASCII de los caracteres de la clave
    for (char ch : key) {
        hashValue += ch;  // Suma el valor ASCII de cada carácter
    }

    // Asegura que el valor de hashValue esté dentro del tamaño de la tabla
    return hashValue % tableSize;  // Devuelve el índice final dentro del tamaño de la tabla
}

int main() {
    string key = "Hola";
    int tableSize = 10;  // Ejemplo de tamaño de la tabla

    // Llamada a la función hash
    int index = hash_1(key, tableSize);

    // Mostrar el índice calculado
    cout << "El índice para la clave '" << key << "' es: " << index << endl;

    return 0;
}