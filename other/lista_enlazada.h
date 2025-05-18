#pragma once
#include <iostream>

using namespace std;

template <typename T>
class NodoLista{
public:
    NodoLista(){
        this->next = nullptr;
    }
    NodoLista(T data){
        this->data = data;
        this->next = nullptr;
    }
    NodoLista(T data, NodoLista<T>* next){
        this->data = data;
        this->next = next;
    }
    NodoLista<T>* getNext(){
        return next;
    }
    void setNext(NodoLista<T>* node){
        next = node;
    };
    T getData(){
        return data;
    }
    T* getDataPtr(){
        return &data;
    }
    void setData(T data){
        this->data = data;
    }
    private:
    T data;
    NodoLista<T>* next;
};

template <typename T>
class ListaEnlazada{
public:
    ListaEnlazada(){
        head = nullptr;
        tail = head;
        size = 0;
    }

    ListaEnlazada(NodoLista<T>* head){
        this->head = head;
        tail = this->head;
        size = 0;
    }

    void print(){
        if (size <= 0){
            cout << "------------\n";
            cout << "Empty list\n";
            cout << "------------\n";
            return;
        }
        cout << "[HEAD]";
        NodoLista<T>* current = head;
        while(current != nullptr){
            cout << "(" << current->getData() << ")--->\n";
            current = current->getNext();
        }
        cout << "NULL\n";
        cout << "-----------------------------------------\n";
        cout << "size: " << size << "\n";
        cout << "head: " << head->getData() << "\n";
        cout << "tail: " << tail->getData() << "\n";
        cout << "-----------------------------------------\n";
    }

    string to_string(){
        string str;
        NodoLista<T>* current = head;
        while(current != nullptr){
            str += current->getData().to_string();
            if(current->getNext())
                str +=  "--->";
            current = current->getNext();
        }
        return str;
    }

    T get(int index) const{
        if(index >= size || index < 0){
            return T();
        }
        NodoLista<T>* current = head;
        for(int i = 0; i < index; i++){
            current = current->getNext();
        }
        return current->getData();
    }

    T* getPtr(int index){
        if(index >= size || index < 0){
            return nullptr;
        }
        NodoLista<T>* current = head;
        for(int i = 0; i < index; i++){
            current = current->getNext();
        }
        return current->getDataPtr();
    }

    void set(int index, T value){
        if(index >= size || index < 0){
            return;
        }
        NodoLista<T>* current = head;
        for(int i = 0; i < index; i++){
            current = current->getNext();
        }
        current->setData(value);
    }

    NodoLista<T>* getNode(int index){
        if(index >= size || index < 0){
            return nullptr;
        }
        if(index == 0){
            return head;
        }
        NodoLista<T>* current = head;
        for(int i = 0; i < index; i++){
            current = current->getNext();
        }
        return current;
    }

    void append(T newValue){
        auto newNode = new NodoLista<T>(newValue);
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
            NodoLista<T>* current = head;
            NodoLista<T>* newNode = new NodoLista<T>(newValue);
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

    int find(T value, string option){
        mergeSort(*this, true);
        if(option == "binarySearch"){
            return binarySearch(value);
        }
        else if(option == "linearSearch"){
            return linearSearch(value);
        }
        else{
            return binarySearch(value);
        }
    }

    void remove(int index){
        if(index < 0 || index > size-1 || head == nullptr){
            return;
        }
        NodoLista<T>* prev = head;
        if(index == 0){
            head = prev->getNext();
            delete prev;
        }
        else{
            for(int i = 0; i < index-1; i++){
                prev = prev->getNext();
            }
            NodoLista<T>* current = prev->getNext();
            prev->setNext(current->getNext());
            delete current;
        }
        size--;
        tail = getNode(size - 1);
    }

    void removeValue(T value){
        int index = find(value, "binarySearch");
        if(index == -1){
            cout << "could not find value to be removed\n";
            return;
        }
        remove(index);
    }

    void reverse(){
        if(head != nullptr){
            NodoLista<T>* prev = nullptr;
            NodoLista<T>* current = head;
            NodoLista<T>* next = nullptr;
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

    int getSize() const{
        return size;
    }

    NodoLista<T>* getHead(){
        return head;
    }

    NodoLista<T>* getTail(){
        return tail;
    }

    void sort(string sort, bool ascending){
        if(sort == "bubbleSort"){
            bubbleSort(ascending);
        }
        else if (sort == "selectionSort"){
            selectionSort(ascending);
        }
        else if (sort == "insertionSort"){
            insertionSort(ascending);
        }
        else if (sort == "shellSort"){
            shellSort(ascending);
        }
        else if (sort == "quickSort"){
            quickSort(0, size - 1, ascending);
        }
        else if (sort == "heapSort"){
            heapSort(ascending);
        }
        else if (sort == "mergeSort"){
            mergeSort(*this, ascending);
        }
        else{
            quickSort(0, size - 1, ascending);
        }
    }

    bool operator==(const ListaEnlazada<T>& l){
        for(int i = 0; i < size; i++){
            if(get(i) != l.get(i)){
                return false;
            }
        }
        return true;
    }

    class Iterator {
    private:
        T* ptr;
        NodoLista<T>* current;
    public:
        Iterator(T* p, NodoLista<T>* n) : ptr(p), current(n) {}
        
        T& operator*() const { return *ptr; }

        Iterator& operator++() {
            current = current->getNext();
            ptr = current->getDataPtr();
            return *this; 
        }

        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
    };
    
    Iterator begin() { return Iterator(head->getDataPtr(), head); }
    Iterator end()   { return Iterator(nullptr, nullptr); }

private:    
// ---------------------------------sorting------------------------------
    void swap(int a, int b){
        if(a == b){
            return;
        }
        NodoLista<T>* nodeA = getNode(a);
        NodoLista<T>* nodeB = getNode(b);
        NodoLista<T>* prevA = getNode(a - 1);
        NodoLista<T>* prevB = getNode(b - 1);

        if(nodeA == nullptr || nodeB == nullptr){
            return;
        }

        if(prevA != nullptr){
            prevA->setNext(nodeB);
        }
        else{
            head = nodeB;
        }

        if(prevB != nullptr){
            prevB->setNext(nodeA);
        }
        else{
            head = nodeA;
        }

        NodoLista<T>* temp = nodeA->getNext();
        nodeA->setNext(nodeB->getNext());
        nodeB->setNext(temp);
        tail = getNode(size - 1);
    }

    void bubbleSort(bool ascending){
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size - i - 1; j++){
                if(ascending){
                    if(get(j) > get(j + 1)){
                        swap(j, j + 1);
                    }
                }
                else{
                    if(get(j) < get(j + 1)){
                        swap(j, j + 1);
                    }
                }
            }
        }
    }

    void selectionSort(bool ascending){
        if(ascending){
            int minIndex;
            for(int i = 0; i < size - 1; i++){
                minIndex = i;
                for(int j = i + 1; j < size; j++){
                    if(get(j) < get(minIndex)){
                        minIndex = j;
                    }
                }
                if(minIndex != i){
                    swap(i, minIndex);
                }
            }
        }
        else{
            int maxIndex;
            for(int i = 0; i < size - 1; i++){
                maxIndex = i;
                for(int j = i + 1; j < size; j++){
                    if(get(j) > get(maxIndex)){
                        maxIndex = j;
                    }
                }
                if(maxIndex != i){
                    swap(i, maxIndex);
                }
            }
        }
    }

    void insertionSort(bool ascending){
        T temp;
        int previous;
        for(int i = 1; i < size; i++){
            temp = get(i);
            previous = i - 1;
            bool comparison;
            if(ascending){
                while(previous >= 0 && get(previous) > temp){
                    set(previous + 1, get(previous));
                    previous--;
                }
            }
            else{
                while(previous >= 0 && get(previous) < temp){
                    set(previous + 1, get(previous));
                    previous--;
                }
            }
            set(previous + 1, temp);
        }
    }

    void shellSort(bool ascending){
        int anterior;
        T temp;
        for(int intervalo = size/2; intervalo > 0; intervalo/=2){
            for(int i = intervalo; i < size; i++){
                temp = get(i);
                anterior = i - intervalo;
                if(ascending){
                    while(anterior >= 0 && get(anterior) > temp){
                        set(anterior + intervalo, get(anterior));
                        anterior -= intervalo;
                    }
                }
                else{
                    while(anterior >= 0 && get(anterior) < temp){
                        set(anterior + intervalo, get(anterior));
                        anterior -= intervalo;
                    }
                }
                set(anterior + intervalo, temp);
            }
        }
    }

    int partition(int low, int high, bool ascending){
        T pivot = get(high);
        int swapped = low - 1;
        for(int compare = low; compare < high; compare++){
            if constexpr (std::is_pointer<T>::value){
                if(ascending){
                    if(*pivot >= *get(compare)){
                        swapped++;
                        swap(compare, swapped);
                    }
                }
                else{
                    if(*pivot <= *get(compare)){
                        swapped++;
                        swap(compare, swapped);
                    }
                }
            }
            else{
                if(ascending){
                    if(pivot >= get(compare)){
                        swapped++;
                        swap(compare, swapped);
                    }
                }
                else{
                    if(pivot <= get(compare)){
                        swapped++;
                        swap(compare, swapped);
                    }
                }
            }
        }
        swap(swapped + 1, high);
        return swapped + 1;
    }

    void quickSort(int low, int high, bool ascending){
        if(low < high){
            int pivot = partition(low, high, ascending);
            quickSort(low, pivot - 1, ascending);
            quickSort(pivot + 1, high, ascending);
        }
    }

    void heapify(int size, int root, bool ascending){
        int left = 2 * root + 1;
        int right = 2 * root + 2;
        if(ascending){
            int largest = root;
    
            // find largest value and sort
            if(left < size && get(left) > get(largest)){
                largest = left;
            }
    
            if(right < size && get(right) > get(largest)){
                largest = right;
            }
    
            // if tree isnt sorted, put largest value on root and heapify subtree that was affected
            if(largest != root){
                swap(largest, root);
                heapify(size, largest, ascending);
            }
        }
        else{
            int smallest = root;
    
            // find smallest value and sort
            if(left < size && get(left) < get(smallest)){
                smallest = left;
            }
    
            if(right < size && get(right) < get(smallest)){
                smallest = right;
            }
    
            // if tree isnt sorted, put smallest value on root and heapify subtree that was affected
            if(smallest != root){
                swap(smallest, root);
                heapify(size, smallest, ascending);
            }
        }
    }

    void heapSort(bool ascending){
        //unsorted tree into max heap;
        for(int i = size / 2 - 1; i >= 0; i--){
            heapify(size, i, ascending);
        }

        for(int i = size - 1; i >= 0; i--){
            swap(0, i);
            heapify(i, 0, ascending);
        }
    }

    void merge(ListaEnlazada<T>& left, ListaEnlazada<T>& right, ListaEnlazada<T>& list, bool ascending){
        int leftSize = left.getSize();
        int rightSize = right.getSize();
        int leftIndex = 0;
        int rightIndex = 0;
        int originalIndex = 0;

        while(leftIndex < leftSize && rightIndex < rightSize){
            if(ascending){
                if(left.get(leftIndex) < right.get(rightIndex)){
                    list.set(originalIndex, left.get(leftIndex));
                    leftIndex++;
                }
                else{
                    list.set(originalIndex, right.get(rightIndex));
                    rightIndex++;
                }
            }
            else{
                if(left.get(leftIndex) > right.get(rightIndex)){
                    list.set(originalIndex, left.get(leftIndex));
                    leftIndex++;
                }
                else{
                    list.set(originalIndex, right.get(rightIndex));
                    rightIndex++;
                }
            }
            originalIndex++;
        }

        while(leftIndex < leftSize){
            list.set(originalIndex, left.get(leftIndex));
            leftIndex++;
            originalIndex++;
        }

        while(rightIndex < rightSize){
            list.set(originalIndex, right.get(rightIndex));
            rightIndex++;
            originalIndex++;
        }
    }

    void mergeSort(ListaEnlazada<T>& list, bool ascending){
        if(list.getSize() <= 1){
            return;
        }

        int middle = list.getSize() / 2;
        ListaEnlazada<T> left;
        ListaEnlazada<T> right;

        for(int i = 0; i < list.getSize(); i++){
            if(i < middle){
                left.append(list.get(i));
            }
            else{
                right.append(list.get(i));
            }
        }
        mergeSort(left, ascending);
        mergeSort(right, ascending);
        merge(left, right, list, ascending);
    }


// ---------------------------------- searching-------------------------------

    int linearSearch(T value){
        NodoLista<T>* current = head;
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

    int binarySearch(T value){
        int low = 0;
        int high = size - 1;
        int mid;
        bool ascending = get(0) < get(size - 1);
        while(low <= high){
            mid = low + (high - low) / 2;
            if(get(mid) == value){
                return mid;
            }
            if(ascending){
                if(get(mid) < value){
                    low = mid + 1;
                }
                else{
                    high = mid - 1;
                }
            }
            else{
                if(get(mid) > value){
                    low = mid + 1;
                }
                else{
                    high = mid - 1;
                }
            }
        }
        return -1;
    }


    NodoLista<T>* head;
    NodoLista<T>* tail;
    int size;
};