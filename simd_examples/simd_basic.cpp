#include <iostream>
#include <immintrin.h>


int main()
{
    __m256 float_vec1 = _mm256_set1_ps(1.0);
    __m256 float_vec2 = _mm256_set1_ps(2.0);
    __m256 float_result = _mm256_add_ps(float_vec1, float_vec2);

    float* flo = (float*) &float_vec1;
    printf("float:\t\t%f, %f, %f, %f, %f, %f, %f, %f\n", flo[0], flo[1], flo[2], flo[3], flo[4], flo[5], flo[6], flo[7]);
    flo = (float*) &float_vec2;
    printf("float:\t\t%f, %f, %f, %f, %f, %f, %f, %f\n", flo[0], flo[1], flo[2], flo[3], flo[4], flo[5], flo[6], flo[7]);
    flo = (float*) &float_result;
    printf("float:\t\t%f, %f, %f, %f, %f, %f, %f, %f\n", flo[0], flo[1], flo[2], flo[3], flo[4], flo[5], flo[6], flo[7]);
} 