#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <assert.h>

void write()
{
    FILE * fp;

    
    fp = fopen ("file.txt", "w+");
    int n = 1<<30;

    for(int i=0; i<n; i++){

        fprintf(fp, "%s", "HELLO");

    }
    fclose(fp);
}


size_t read()
{
    FILE* fp = fopen ("file.txt", "r");

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    // printf("size: %ld\n", size);    

    char *buf = (char *)malloc(size+1);
    printf("%p\n", buf);
    // for (int i = 0; i < 10; i++){
    //     size_t res = fread(buf, sizeof(char), size/10, fp);
    //     buf = &buf[size/10];
    // }
    size_t res = fread(buf, sizeof(char), size, fp);

    assert(res == size);

    fclose(fp);

    return size;
}

int main()
{
    // write();
    // struct timespec start, end;
    // clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    
    size_t size = read();

    // clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    // double delta_s = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;

    // printf("time: %lf\n", delta_s);
    // printf("%f MB/s\n", ((size/(1<<20)/delta_s)));
//    #pragma omp parallel for num_threads(2) private(j)
//    for(j=0;j<size;j++){
//        fread(&buf[j], sizeof(char), 1, fp);
//    }
//     fread(buf, sizeof(char), size, fp);
//     for (int i=0; i< size; i++){
//         //int tid = omp_get_thread_num();
//         printf("%c", buf[i]);
//     }
    

}
 