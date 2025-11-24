#include<bits/stdc++.h>
int main()
{
    std::uint64_t v = 0x1122334455667788ull;
    std::array<std::uint8_t, 8> out;
    if (std::endian::native == std::endian::big) {
        std::cout<< "big endian\n";
        // 大端机：内存字节序已经是网络序
        // 直接按内存顺序拷到 out
        std::memcpy(out.data(), &v, 8);
    } else if (std::endian::native == std::endian::little) {
        std::cout<< "little endian\n";
        // 小端机：内存里是低位在前，需要反转成大端
        std::uint8_t tmp[8];
        std::memcpy(tmp, &v, 8);        // tmp[0] 是最低字节，tmp[7] 是最高字节
        for (int i = 0; i < 8; ++i) {
            out[i] = tmp[7 - i];        // 反转得到大端序：最高字节放在 out[0]
        }
    } else {
        // 罕见：既非小端也非大端
        static bool warned = false;
        if (!warned) {
            std::cerr << "[warn] Unknown endianness (neither little nor big). "
                         "Falling back to portable packing.\n";
            warned = true;
        }
    }
    for (auto by : out) {
        std::cout << std::hex << std::uppercase << std::setw(2) << std::setfill('0')
                  << static_cast<unsigned>(by) << ' ';
    }
}