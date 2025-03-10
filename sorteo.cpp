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
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size - i - 1; j++){
            if(arr[j] > arr[j + 1]){
                swap(arr[j], arr[j+1]);
            }
        }
    }
}


void selectionSort(int* arr, int size){
    int minIndex;
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

void insertionSort(int* arr, int size){
    int temp;
    int previous;
    for(int i = 1; i < size; i++){
        temp = arr[i];
        previous = i - 1;
        while(previous >= 0 && arr[previous] > temp){
            arr[previous + 1] = arr[previous];
            previous--;
        }
        arr[previous + 1] = temp;
    }
}

void shellSort(int* arr, int size){
    int anterior;
    int temp;
    for(int intervalo = size/2; intervalo > 0; intervalo /= 2){
        for(int i = intervalo; i < size; i++){
            temp = arr[i];
            anterior = i - intervalo;
            while(anterior >= 0 && arr[anterior] > temp){
                arr[anterior + intervalo] = arr[anterior];
                anterior -= intervalo;
            }
            arr[anterior + intervalo] = temp;
        }
    }
}

int partition(int* arr, int low, int high){
    int pivot = arr[high];
    int swapped = low-1;
    for(int compare = low; compare < high; compare++){
        if(pivot >= arr[compare]){
            swapped++;
            swap(arr[compare], arr[swapped]);
        }
    }
    swap(arr[swapped + 1], arr[high]);
    return swapped + 1;
}

void quickSort(int* arr, int low, int high){
    if(low < high){
        int pivot = partition(arr, low, high);
        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}


int main(){
    srand(time(0));
    const int SIZE = 5;
    int arr[SIZE] = {7,-2,4,-8,3};
    int correcto[SIZE];
    for(int i = 0; i < SIZE; i++){
        // arr[i] = rand() % 10 + 1;
        correcto[i] = arr[i];
    }
    
    cout << "arreglo original:\n";
    printArray(arr, SIZE);
    cout << "\narreglo sorteado\n";
    quickSort(arr, 0, SIZE-1);
    printArray(arr, SIZE);
    cout << "\narreglo correcto\n";
    bubbleSort(correcto, SIZE);
    printArray(correcto, SIZE);
    return 0;
}