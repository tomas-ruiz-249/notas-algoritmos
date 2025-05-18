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

void heapify(int* arr, int size, int root){
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if(left < size && arr[left] > arr[largest]){
        largest = left;
    }
    if(right < size && arr[right] > arr[largest]){
        largest = right;
    }

    if(largest != root){
        swap(arr[largest], arr[root]);
        heapify(arr, size, largest);
    }
}

void heapSort(int *arr, int size){
    //create max heap
    for(int i = (size / 2) - 1; i >= 0; i--){
        heapify(arr, size, i);
    }

    for(int i = size - 1; i >= 0; i--){
        swap(arr[i], arr[0]);
        heapify(arr, i, 0);
    }
}

void merge(int* left , int* right, int* arr, int size){
    int leftSize = size / 2;
    int rightSize = size - leftSize;
    int leftIndex = 0;
    int rightIndex = 0;
    int originalIndex = 0;
    while(leftIndex < leftSize && rightIndex < rightSize){
        if(left[leftIndex] < right[rightIndex]){
            arr[originalIndex] = left[leftIndex];
            leftIndex++;
        }
        else{
            arr[originalIndex] = right[rightIndex];
            rightIndex++;
        }
        originalIndex++;
    }
    while(leftIndex < leftSize){
        arr[originalIndex] = left[leftIndex];
        originalIndex++;
        leftIndex++;
    }
    while(rightIndex < rightSize){
        arr[originalIndex] = right[rightIndex];
        originalIndex++;
        rightIndex++;
    }
}

void mergeSort(int* arr, int size){
    if(size <= 1){
        return;
    }
    int middle = size / 2;
    int* left = new int[middle];
    int* right = new int[size - middle];

    int k = 0;
    for(int i = 0; i < size; i++){
        if(i < middle){
            left[i] = arr[i];
        }
        else{
            right[k] = arr[i];
            k++;
        }
    }

    mergeSort(left, middle);
    mergeSort(right, size - middle);
    merge(left, right, arr, size);
    delete[] left;
    delete[] right;
}

int getMax(int* arr, int size){
    int max = arr[0];
    for(int i = 0; i < size; i++){
        if(arr[i] > max){
            max = arr[i];
        }
    }
    return max;
}

void placeCountingSort(int* arr, int size, int place){
    int max = getMax(arr, size);
    int* count = new int[max + 1]();
    int* output = new int[size];

    for(int i = 0; i < size; i++){
        count[(arr[i] / place) % 10]++;
    }
    for(int i = 1; i < max; i++){
        count[i] += count[i - 1];
    }
    for(int i = size - 1; i >= 0; i--){
        output[count[(arr[i] / place) % 10] - 1] = arr[i];
        count[(arr[i] / place) % 10]--;
    }
    for(int i = 0; i < size; i++){
        arr[i] = output[i];
    }
}

void radixSort(int* arr, int size){
    int max = getMax(arr, size);
    for(int place = 1; max / place > 0; place *= 10){
        placeCountingSort(arr, size, place);
    }
}

int main(){
    srand(time(0));
    const int SIZE = 5;
    int arr[SIZE];
    for(int i = 0; i < SIZE; i++){
        arr[i] = rand() % 10 + 1;
    }
    printArray(arr, SIZE);
    radixSort(arr, SIZE);
    printArray(arr, SIZE);
}