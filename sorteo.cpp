#include <iostream>

using namespace std;

void printArray(int arr[], int size){
    cout << "[";
    for(int i = 0; i < size; i++){
        cout << arr[i];
        if(i != size-1){
            cout << ", ";
        }
    }
    cout << "]\n";
}

void swap(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
}

void bubbleSort(int* arr, int size){
    for(int i = 0; i < size-1; i++){
        for(int j = i+1; j < size; j++){
            if(arr[i] > arr[j]){
                swap(arr[i], arr[j]);
            }
        }
    }
}

void insertionSort(int* arr, int size){

}


int main(){
    const int SIZE = 5;
    int arr[SIZE] = {30,83,-4,-91,7};
    cout << "arreglo original:\n";
    printArray(arr, SIZE);
    cout << "---------------------\n";
    bubbleSort(arr, SIZE);
    printArray(arr, SIZE);
    return 0;
}