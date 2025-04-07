#include <iostream>
#include "linked_list.h"

using namespace std;

template <typename T>
class Queue{
public:
    void enqueue(T value){
        list.append(value);
    }

    T dequeue(){
        T element = list.get(0);
        list.remove(0);
        return element;
    }

    T peek(){
        T element = list.get(0);
        return element;
    }

    bool isEmpty(){
        return list.getSize() == 0;
    }

    void print(){
        int size = list.getSize();
        if (size == 0){
            cout << "empty queue\n";
            return;
        }
        T element;
        for(int i = 0; i < list.getSize(); i++){
            element = list.get(i);
            cout << "(" << element << ")\n";
        }
        cout << "-----------------------------------------\n";
        cout << "size: " << list.getSize() << "\n";
        cout << "top: " << peek() << "\n";
        cout << "bottom: " << list.get(list.getSize() - 1) << "\n";
        cout << "-----------------------------------------\n";
    }

private:
    LinkedList<T> list;
};

int main(){
    Queue<const char*> h;
    h.enqueue("a");
    h.enqueue("b");
    h.enqueue("c");
    h.enqueue("d");
    h.enqueue("e");
    h.enqueue("f");
    h.print();
    for(int i = 0; i < 10; i++){
        h.dequeue();
        h.print();
    }
}