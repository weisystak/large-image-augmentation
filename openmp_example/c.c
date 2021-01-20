#include <stdio.h>
#include <omp.h>
#include <time.h>

#define n 2<<15



int main(int argc, char** argv){
    int thread_id;
    long long sum=0;
    long long res=0;
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    #pragma omp parallel for reduction(+:res) 
    for( int i = 0; i < n; i++){
            for(int j = 0; j < n; j++)
                res++;
    }

    printf("%lld\n", res);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    double dur = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
    dur /= 1000000;
    printf("elapsed: %f\n", dur);
    return 0;
}