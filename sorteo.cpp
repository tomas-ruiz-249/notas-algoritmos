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
    int temp;
    int previous;
    for(int i = 1; i < size; i++){
        temp = arr[i];
        previous = i - 1;
        while(previous >= 0 && arr[previous] > temp){
            arr[previous + 1] = arr[previous];
            previous--;
            printArray(arr, size);
            cout << previous << "\n";
        }
        arr[previous + 1] = temp;
    }
}

void selectionSort(int* arr, int size){
    int minIndex;
    int temp;
    for(int i = 0; i < size - 1; i++){
        minIndex = i;
        for(int j = i + 1; j < size; j++){
            if(arr[j] < arr[minIndex]){
                minIndex = j;
            }
        }
        if(minIndex != i){
            swap(arr[i], arr[minIndex]);
        }
    }
}

void shellSort(int* arr, int size){
    int intervalo = size / 2;
}


int main(){
    const int SIZE = 5;
    int arr[SIZE] = {14,9,-5,3,-6};
    cout << "arreglo original:\n";
    printArray(arr, SIZE);
    cout << "---------------------\n";
    bubbleSort(arr, SIZE);
    printArray(arr, SIZE);
    return 0;
}