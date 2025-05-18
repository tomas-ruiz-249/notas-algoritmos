#include <iostream>
#include "linked_list.cpp"
#include "sorteo.cpp"

using namespace std;

int linearSearch(int* arr, int size, int value){
    for(int i = 0; i < size; i++){
        if(arr[i] == value){
            return i;
        }
    }
    return -1;
}

int binarySearch(int* arr, int size, int value){
    int low = 0;
    int high = size - 1;
    int mid;
    while(low <= high){
        mid = low + (high - low) / 2;
        if(arr[mid] == value){
            return mid;
        }
        if(arr[mid] < value){
            low = mid + 1;
        }
        else{
            high = mid - 1;
        }
    }
    return -1;
}

int indexedSearch(int* arr, int size, int value){
    
}

int main(){
    srand(time(0));
    const int SIZE = 20;
    LinkedList<int> list;
    for(int i = 0; i < SIZE; i++){
        list.append(rand() % 10);
    }
    list.sort();
    list.print();
    int val;
    cout << "escoja un valor para buscar\n";
    cin >> val;
    cout << "value " << val << " found at position " << list.find(val);
    
    return 0;
}