// for x86_64:
// g++ avx2_test.cpp -mavx2 -O3 -o avx2_test

#include <stdio.h>
#include <immintrin.h>


int main()
{

    float data[8] = {
        1.0f,
        2.0f,
        3.0f,
        4.0f,
        5.0f,
        6.0f,
        7.0f,
        8.0f
    };


    float result[8];


    float scale = 10.0f;


    // 加载8个float
    __m256 vdata =
        _mm256_loadu_ps(data);


    // 广播scale到8个元素
    __m256 vscale =
        _mm256_set1_ps(scale);


    // AVX2乘法
    __m256 vresult =
        _mm256_mul_ps(
            vdata,
            vscale
        );


    // 保存
    _mm256_storeu_ps(
        result,
        vresult
    );


    for(int i=0;i<8;i++)
    {
        printf("%.1f\n",
               result[i]);
    }


    return 0;
}
