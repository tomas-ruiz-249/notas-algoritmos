#include <iostream>

using namespace std;

int fib(int n){
    if(n == 0){
        return 0;
    }
    else if(n == 1){
        return 1;
    }
    else{
        return fib(n-1) + fib(n-2);
    }
}

// fib(5) = fib(4) + fib(3)
// fib(5) = (fib(3) + fib(2)) + (fib(2) + fib(1))
// fib(5) = ((fib(2) + fib(1)) + (fib(1) + fib(0))) + ((fib(1) + fib(0)) + 1)
// fib(5) = (((fib(1) + fib(0)) + 1) + (1 + 0)) + ((1 + 0) + 1)
// fib(5) = (((1 + 0) + 1) + (1 + 0)) + ((1 + 0) + 1)
// fib(5) = 1 + 1 + 1 + 1 + 1
// fib(5) = 5


int main(){
    for(int i = 0; i < 11; i++){
        cout << i << " " << fib(i) << "\n";
    }
}