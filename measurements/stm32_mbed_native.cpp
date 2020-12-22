#include <stdlib.h>
#include <string.h>
#include "mbed.h"
using namespace std::chrono;

int fib(int n) {
    if (n <= 1)
        return n;
    return fib(n - 1) + fib(n - 2);
}

int main() {
    Timer t;
    printf("Starting native calculation\n");
    t.start();

    printf("fib(24) = %d\n", fib(24));

    t.stop();
    printf("Finished native calculation\n");
    printf("The time taken was %llu milliseconds\n",
           duration_cast<milliseconds>(t.elapsed_time()).count());
}