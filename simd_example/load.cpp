#include <immintrin.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
    
    // Single-precision
    int i;
    float* aligned_floats = (float*) aligned_alloc(32, 8 * sizeof(float));
    for (i = 0; i < 8; i++) {
        aligned_floats[i] = (float)(i) + 1.0;
    }
    
    __m256 float_vec = _mm256_load_ps(aligned_floats);

    float* flo = (float*) &float_vec;
    printf("float:\t\t%f, %f, %f, %f, %f, %f, %f, %f\n", flo[0], flo[1], flo[2], flo[3], flo[4], flo[5], flo[6], flo[7]);
}