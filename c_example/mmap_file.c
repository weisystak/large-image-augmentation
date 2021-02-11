#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/io.h>
#include <sys/mman.h>
#include <time.h>


int main(int argc, char const *argv[])
{
    unsigned char *f;
    long long size;
    struct stat s;
    const char * file_name = argv[1];
    int fd = open (argv[1], O_RDONLY);

    /* Get the size of the file. */
    int status = fstat (fd, & s);
    size = s.st_size;
    printf("size: %lld\n", size);
struct timespec start, end;
clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    
    
    f = (char *) mmap (0, size, PROT_READ, MAP_PRIVATE, fd, 0);

    for (long long i = 0; i < size; i++) {
        char c;

        c = f[i];
        // putchar(c);
    }


clock_gettime(CLOCK_MONOTONIC_RAW, &end);

double delta_s = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;

printf("time: %lf\n", delta_s);
printf("%f MB/s\n", ((size/(1<<20)/delta_s)));
    return 0;
}