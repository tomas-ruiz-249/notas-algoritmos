#include <iostream>

using namespace std;

int sumArray(int *ptr, int length){
    int sum = 0;
    for(int i = 0; i < length; i++){
        sum += *(ptr + i);
    }
    return sum;
}

double avgMultiples3(int *ptr, int length){
    int sum = 0;
    int count = 0;
    for(int i = 0; i < length; i++){
        if(*(ptr + i) % 3 == 0){
            sum += *(ptr + i);
            count++;
        }
    }
    if(count == 0){
        return -1;
    }
    return sum / count;
}

bool isPrime(int n){
    if(n == 0 || n == 1){
        return false;
    }
    for(int i = 2; i < n; i++){
        if(n % i == 0){
            return false;
        }
    }
    return true;
}

int sumPrimes(int* ptr, int length){
    int sum = 0;
    for(int i = 0; i < length; i++){
        if(isPrime(*(ptr + i))){
            sum += *(ptr + i);
        }
    }
    return sum;
}


int sumComposite(int* ptr, int length){
    int sum = 0;
    for(int i = 0; i < length; i++){
        if(!isPrime(*(ptr + i))){
            sum += *(ptr + i);
        }
    }
    return sum;
}

int main(){
    const int LENGTH = 10;
    int nums[LENGTH] = {1,2,3,4,5,6,7,8,9,10};
    cout << sumComposite(nums, LENGTH);
    return 0;
}