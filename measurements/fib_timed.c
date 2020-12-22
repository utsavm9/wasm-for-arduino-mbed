// To be compiled into WASM module

#include <stdio.h>

void startTimer();
void endTimer();

int fib(int n) {
    if (n <= 1)
        return n;
    return fib(n - 1) + fib(n - 2);
}

int main() {
    startTimer();
    printf("fib(24) = %d\n", fib(24));
    endTimer();
    return 0;
}
