// aarch64-linux-gnu-g++ neon_test.cpp -O3 -o neon_test

#include <stdio.h>
#include <arm_neon.h>


int main()
{
    float data[4] = {
        1.0f,
        2.0f,
        3.0f,
        4.0f
    };

    float result[4];

    float scale = 10.0f;


    // 加载4个float到NEON寄存器
    float32x4_t vdata = vld1q_f32(data);

    // 设置缩放因子
    float32x4_t vscale = vdupq_n_f32(scale);

    // SIMD乘法
    float32x4_t vresult =
        vmulq_f32(vdata, vscale);

    // 保存结果
    vst1q_f32(result, vresult);


    for(int i = 0; i < 4; i++)
    {
        printf("%.1f\n", result[i]);
    }


    return 0;
}
