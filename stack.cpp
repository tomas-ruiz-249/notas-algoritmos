#include<iostream>
#include "linked_list.h"

using namespace std;

template <typename T>
class Stack{
public:
    void push(T value){
        list.append(value);
    }

    T pop(){
        int size = list.getSize();
        T element = list.get(size - 1);
        list.remove(size - 1);
        return element;
    }

    T peek(){
        int size = list.getSize();
        T element = list.get(size - 1);
        return element;
    }

    bool isEmpty(){
        return list.getSize() == 0;
    }

    void print(){
        int size = list.getSize();
        if (size == 0){
            cout << "empty heap\n";
            return;
        }
        T element;
        for(int i = size - 1; i >= 0; i--){
            element = list.get(i);
            cout << "(" << element << ")\n";
        }
        cout << "-----------------------------------------\n";
        cout << "size: " << list.getSize() << "\n";
        cout << "bottom: " << list.get(0) << "\n";
        cout << "top: " << peek() << "\n";
        cout << "-----------------------------------------\n";
    }

private:
    LinkedList<T> list;
};

int main(){
    Stack<const char*> h;
    h.push("a");
    h.push("b");
    h.push("c");
    h.push("d");
    h.push("e");
    h.push("f");
    h.print();
    for(int i = 0; i < 10; i++){
        h.pop();
        h.print();
    }
}