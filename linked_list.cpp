#include <iostream>

using namespace std;

template <typename T>
class Node{
public:
    Node(){
        this->next = nullptr;
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
    void setData(T data){
        this->data = data;
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
        if(index >= size || index < 0){
            return T();
        }
        Node<T>* current = head;
        for(int i = 0; i < index; i++){
            current = current->getNext();
        }
        return current->getData();
    }

    Node<T>* getNode(int index){
        if(index >= size || index < 0){
            return nullptr;
        }
        if(index == size - 1){
            return tail;
        }
        if(index == 0){
            return head;
        }
        Node<T>* current = head;
        for(int i = 0; i < index; i++){
            current = current->getNext();
        }
        return current;

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
        return binarySearch(value);
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

    void removeValue(T value){
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

    void sort(){
        bubbleSort();
    }

private:    
    void swap(int a, int b){
        Node<T>* A = getNode(a);
        Node<T>* B = getNode(b);
        T temp = A->getData();
        A->setData(B->getData());
        B->setData(temp);
    }

    void bubbleSort(){
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size - i - 1; j++){
                if(get(j) > get(j + 1)){
                    swap(j, j + 1);
                }
            }
        }
    }

    int linearSearch(T value){
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

    int binarySearch(T value){
        int low = 0;
        int high = size - 1;
        int mid;
        while(low <= high){
            mid = low + (high - low) / 2;
            if(get(mid) == value){
                return mid;
            }
            if(get(mid) < value){
                low = mid + 1;
            }
            else{
                high = mid - 1;
            }
        }
        return -1;
    }

    Node<T>* head;
    Node<T>* tail;
    int size;
};