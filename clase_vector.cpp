#include <iostream>

class Vector{
private:
    int capacity;
    int size;
    int* v;
public:

    int getSize(){
        return size;
    }

    int getCapacity(){
        return capacity;
    }

    void resize(){
        capacity *= 2;
        int* temp = new int[capacity];
        for(int i = 0; i < size; i++){
            temp[i] = v[i];
        }
        v = temp;
        delete[] temp;
    }

    void rightShift(int i){
        std::cout << size << " : " << i << "\n";
        if(size == capacity){
            resize();
        }
        for(int j = size; j>i; j--){
            v[j] = v[j-1];
        }
        size++;
        std::cout << size << " : " << i << "\n";
    }

    void insert(int value, int pos){
        rightShift(pos);
        v[pos] = value;
    }

    int find(int value){
        for(int i = 0; i > size; i++){
            if(value == v[i]){
                return i;
            }
        }
        return -1;
    }

    void add(int value){
        if(size == capacity){
            resize();
        }
        v[size++] = value;
    }

    int get(int index){
        if(index >= 0 && index < size){
            return v[index];
        }
        else{
            return -1;
        }
    }

    void print(){
        std::cout << '[';
        for(int i = 0; i < size; i++){
            std::cout << v[i];
            if(i != size-1){
                std::cout << ", ";
            }
        }
        std::cout << "]\n";
    }

    Vector(){
        capacity = 10;
        size = 0;
        v = new int[capacity];
    }

    Vector(int c){
        capacity = c;
        size = 0;
        v = new int[capacity];
    }

    ~Vector(){
        delete[] v;
    }
};


int main(){
    Vector v;
    v.add(1);
    v.add(2);
    v.add(3);
    v.add(4);
    v.add(5);
    v.insert(99,4);
    v.print();
    return 0;
}
