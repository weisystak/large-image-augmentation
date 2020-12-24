#include <iostream>
#include <immintrin.h>

using namespace std;

void lscale(__v4sf *out, const __v4sf *in) {
    __m128 v10 = _mm_set_ps1(10.0f), v09 = _mm_set_ps1(0.9f);
    for (unsigned i = 0; i < N / 4; ++i) {
        __m128 cmp = _mm_cmp_gt(in[i], v10);
        __m128 tmp = _mm_add_ps(v10, _mm_mul_ps(_mm_sub_ps(in[i], v10),
        V09));
        out[i] = _mm_blendv_ps(in[i], tmp, cmp);
    }
}

int main()
{

}


