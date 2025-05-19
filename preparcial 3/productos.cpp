#include <iostream>
#include <string>
#include <type_traits>
#include <math.h>

using std::cout;
using std::string;
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

template<typename K, typename V>
struct Pair{
    K key;
    V value;
    bool empty;

    Pair(){
        key = K();
        value = V();
        empty = true;
    }

    Pair(K key, V value){
        this->key = key;
        this->value = value;
        this->empty = false;
    }
    
    bool operator== (Pair<K,V>& p) const{
        return key == p.key && value == p.value;
    }

    bool operator!= (Pair<K,V>& p){
        return key != p.key && value != p.value;
    }
};

template<typename K, typename V>
class HashMap{
public:
    HashMap(int tableSize = 11, float loadFactor = 0.75f){
        table = Vector<Pair<K,V>>(tableSize);
        this->loadFactor = loadFactor;
        this->size = 0;
    }

    bool insert(K key, V value){
        Pair<K,V> p(key, value);
        int hashIndex = hash(key);
        int index;
        int i = 0;
        while(i < table.getCapacity()){
            index = (hashIndex + i * i) % table.getCapacity();
            if(table[index] == p){
                return false;
            }
            if(table[index].empty){
                table[index] = p;
                size++;
                if(size > table.getCapacity() * loadFactor){
                    expand();
                }
                return true;
            }
            i++;
        }
        return false;
    }

    int getSize(){
        return size;
    }

    bool containsKey(K& key){
    int hashIndex = hash(key);
    int index;
    int i = 0;
    do{
        index = (hashIndex + i * i) % table.getCapacity();
        if (table[index].empty) return false;
        if (table[index].key == key && !table[index].empty) return true;
        i++;
    } while(i < table.getCapacity());
    return false;
    }

    bool remove(K key){
        int hashIndex = hash(key);
        int index;
        int i = 0;
        do{
            index = (hashIndex + i * i) % table.getCapacity();
            if(table[index].empty){
                return false;
            }
            if(table[index].key == key){
                table[index] = Pair<K,V>();
                table[index].empty = true;
                size--;
                return true;
            }
            i++;
        }
        while(i < table.getCapacity());
        return false;
    }

    bool isEmpty(){
        return size == 0;
    }

    V& operator[](const K& key){
        int hashIndex = hash(key);
        int index = 0;
        int i = 0;
        int capacity = table.getCapacity();
        int firstEmpty = -1;
        while (i < capacity) {
            index = (hashIndex + i * i) % capacity;
            if (!table[index].empty){
                if(table[index].key == key) {
                    return table[index].value;
                }
            }
            else if(firstEmpty == -1) {
                firstEmpty = index;
            }
            i++;
        }
        table[firstEmpty].key = key;
        table[firstEmpty].value = V();
        table[firstEmpty].empty = false;
        size++;

        if(size > table.getCapacity() * loadFactor){
            expand();
            return (*this)[key];
        }
        return table[firstEmpty].value;
    }

    void print(){
        cout << "---HASHMAP----\n";
        for(int i = 0; i < table.getCapacity(); i++){
            if (!table[i].empty){
                cout << "map[" << table[i].key << "]: " << table[i].value << "\n";
            }
        }
        cout << "--------------\n";
    }

    int hash(K key){
        string str;
        if constexpr (std::is_same<K,string>::value){
            str = key;
        }
        else if constexpr (std::is_arithmetic<K>::value){
            str = std::to_string(key);
        }
        else{
            str = key.to_string();
        }
        unsigned int hashVal = 0;
        for (char ch : str) {
            hashVal = 37 * hashVal + ch;
        }
        return hashVal % table.getCapacity();
    }

    class Iterator {
    private:
        Pair<K,V>* ptr;
        Pair<K,V>* end;
    public:
        Iterator(Pair<K,V>* p, Pair<K,V>*e) : ptr(p), end(e) {}
        
        Pair<K,V>& operator*() const { return *ptr; }

        Iterator& operator++() {
            ++ptr;
            while(ptr->empty and ptr != end){
                ptr++;
            }
            return *this; 
        }

        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
    };
    
    Iterator begin() { return Iterator(&table[0], &table[table.getCapacity()]); }
    Iterator end()   { return Iterator(&table[table.getCapacity()], &table[table.getCapacity()]); }
private:
    Vector<Pair<K,V>> table;
    double loadFactor;
    int size;

    bool isPrime(int n){
        if(n < 2){
            return false;
        }
        if(n == 2 || n == 3){
            return true;
        }
        if (n % 2 == 0 || n % 3 == 0){
            return false;
        }
        for (int i = 5; i * i <= n; i += 6){
            if (n % i == 0 || n % (i + 2) == 0){
                return false;
            }
        }
        return true;
    }

    int nextPrime(int n){
        while(!isPrime(n)){
            n++;
        }
        return n;
    }

    void expand(){
        Vector<Pair<K,V>> oldTable = table;
        int newCapacity = nextPrime(2 * table.getCapacity());
        table = Vector<Pair<K,V>>(newCapacity);
        size = 0;

        for(int i = 0; i < oldTable.getCapacity(); i++){
            if(!oldTable[i].empty){
                insert(oldTable[i].key, oldTable[i].value);
            }
        }
    }
};