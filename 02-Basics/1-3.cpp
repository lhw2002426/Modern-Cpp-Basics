#include<bits/stdc++.h>
/* 
设操作BitEquiv表示两个数在二进制表示上相同, i32表示32位整数，f32表示32位浮点数。
   f32 GetInvSqrt(f32 num)
   {
       i32 a <- BitEquiv(num);
       i32 b <- 0x5f3759df - (a >> 1);
       f32 y <- BitEquiv(b);
       return y * (1.5f - (num * 0.5f * y * y));
   }
*/
float GetInvSqrt(float num)
{
    int a = std::bit_cast<int>(num);
    int b = 0x5f3759df - (a >> 1);
    float y = std::bit_cast<float>(b);
    return y * (1.5f - (num * 0.5f * y * y));
}
int main()
{
    float num = 2.0f;
    float invSqrt = GetInvSqrt(num);
    std::cout << "Inverse square root of " << num << " is approximately " << invSqrt <<" use cmath" << 1.0/std::sqrt(num) << std::endl;
    //Inverse square root of 2 is approximately 0.70693 use cmath0.707107 精度是0.01
    return 0;
}