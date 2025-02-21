#include <iostream>

using namespace std;

template<typename T>
class NodeDouble{
public:
    NodeDouble(){
        next = nullptr;
        prev = nullptr;
        data = T();
    }

    NodeDouble(T data){
        next = nullptr;
        prev = nullptr;
        this->data = data;
    }

    NodeDouble<T>* getNext(){
        return next;
    };

    NodeDouble<T>* getPrev(){
        return prev;
    };

    void setNext(NodeDouble<T>* next){
        this->next = next;
    }

    void setPrev(NodeDouble<T>* prev){
        this->prev = prev;
    }

    T getData(){
        return data;
    }

private:
    NodeDouble<T>* next;
    NodeDouble<T>* prev;
    T data;
};

template<typename T>
class DoublyLinkedList{
public:
    DoublyLinkedList(){
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    void append(T value){
        NodeDouble<T>* newNode = new NodeDouble<T>(value);
        if(head == nullptr){
            head = newNode;
            tail = head;
        }
        else{
            tail->setNext(newNode);
            tail->setPrev(newNode);
            tail = newNode;
        }
        size++;
    }

    void insert(T value, int position){
        if(position < 0 || position > size){
            cout << "invalid position for node insertion.\n";
            return;
        }

        if(position == 0){
            if(head == nullptr){
                append(value);
            }
            else{
                NodeDouble<T>* newNode = new NodeDouble<T>(value);
                newNode->setNext(head);
                head = newNode;
                size++;
            }
        }
        else if(position == size){
            append(value);
        }
        else{
            NodeDouble<T>* current = head;
            for(int i = 0; i < position - 1; i++){
                current = current->getNext();
            }
            NodeDouble<T>* newNode = new NodeDouble<T>(value);
            newNode->setNext(current->getNext());
            current->getNext()->setPrev(newNode);
            current->setNext(newNode);
            newNode->setPrev(current);
            size++;
        }
    }

    void remove(int index){
        NodeDouble<T>* current = head;
        if(index < 0 || index > size-1 || head == nullptr){
            cout << "can't remove node at specified index\n";
            return;
        }
        Node<T>* prev = head;
        if(index == 0){
            head = prev->getNext();
            delete prev;
        }
        for(int i = 0; i < index; i++){

        }
    }

    void remove(T value){
        int index = find(T);
        if(index == -1){
            cout << "could not find node with that value\n";
            return;
        }
        remove(index);
    }

    int find(T value){
        int index = 0;
        NodeDouble<T>* current = head;
        while(current != nullptr){
            if(current->getData == value){
                return index;
            }
            current = current->getNext();
            index++;
        }
        return -1;
    }
    
    void print(){
        cout << "---------------------\n";
        if(head == nullptr){
            cout << "empty list\n";
        }
        else{
            cout << "NULL";
            NodeDouble<T>* current = head;
            int count = 0;
            while(current != nullptr){
                cout << "<---(" << current->getData() << ")--->";
                current = current->getNext();
                count++;
            }
            cout << "NULL\n";
            cout << "size: " << size << "\n";
            cout << "head: " << head->getData() << "\n";
            cout << "tail: " << tail->getData() << "\n";
        }
        cout << "---------------------\n";
    }
private:
    NodeDouble<T>* head;
    NodeDouble<T>* tail;
    int size;
};


int main(){
    DoublyLinkedList<const char*> list;
    list.print();
    list.append("tomas");
    list.append("jaime");
    list.append("felipe");
    list.print();
    list.insert("el pepe", 3);
    list.print();
}