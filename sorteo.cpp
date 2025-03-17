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

template<typename T>
class Tree{
private:
    T value;
    Tree<T>* left;
    Tree<T>* right;
public:
    Tree(T value, Tree<T>* left, Tree<T>* right){
        this->value = value;
        this->left = left;
        this->right = right;
    }

    Tree(){
        value = T();
        left = nullptr;
        right = nullptr;
    }

    T getValue(){
        return value;
    }

    Tree<T>* getLeft(){
        return left;
    }

    Tree<T>* getRight(){
        return right;
    }

    void setValue(T value){
        this->value = value;
    }   

    void setLeft(Tree<T>* left){
        this->left = left;
    }

    void setRight(Tree<T>* right){
        this->right = right;
    }
};

void arrToTree(int* arr, int size, Tree<int>* root, int index = 0){
    if(index < size){
        root->setValue(arr[index]);
        root->setLeft(new Tree<int>());
        root->setRight(new Tree<int>());
        arrToTree(arr, size, root->getLeft(), 2 * index + 1);
        arrToTree(arr, size, root->getRight(), 2 * index + 2);
    }
}

void heapSort(int *arr, int size){
    auto root = new Tree<int>();
    arrToTree(arr, size, root);
    cout << "finished tree\n";
}

