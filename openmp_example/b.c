#include <stdio.h>
#include <time.h>

#define n 2<<15

int main(int argc, char** argv){
    long long a = 0;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    for (int i = 0; i < n; i++)
        // printf("Hello from process: %lld\n", i);
        for(int j = 0; j < n; j++)
            a++;

    printf("%lld\n", a);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    double dur = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
    dur /= 1000000;
    printf("elapsed: %f\n", dur);
    return 0;
}

// real    0m9.576s
// user    0m9.575s
// sys     0m0.000s

// real    0m1.081s
// user    0m16.145s
// sys     0m0.004s