#include<bits/stdc++.h>
#include<locale>
#include<fstream>
class WcharFacet
    : public std::codecvt<wchar_t, char, std::char_traits<wchar_t>::state_type>
{
    using Base =
        std::codecvt<wchar_t, char, std::char_traits<wchar_t>::state_type>;
    using state_type = Base::state_type;
    using result = Base::result;

    result do_in(state_type &state, const char *from, const char *from_end,
                const char *&from_next, wchar_t *to, wchar_t *to_limit,
                wchar_t *&to_next) const override
    {
        // 我们不妨不进行Unicode的合法性校验了。
        std::size_t outSize = (to_limit - to) * sizeof(wchar_t),
                    inSize = from_end - from;
        std::size_t copySize = std::min(inSize, outSize) / sizeof(wchar_t) *
                            sizeof(wchar_t); // 算一下完整的wchar_t有多大

        std::memcpy(to, from, copySize);
        from_next = from + copySize, to_next = to + copySize / sizeof(wchar_t);
        return copySize == inSize ? partial : ok;
    }

    result do_out(state_type &state, const wchar_t *from,
                const wchar_t *from_end, const wchar_t *&from_next, char *to,
                char *to_limit, char *&to_next) const override
    {
        std::size_t outSize = to_limit - to,
                    inSize = (from_end - from) * sizeof(wchar_t);
        std::size_t copySize =
            std::min(inSize, outSize) / sizeof(wchar_t) * sizeof(wchar_t);

        std::memcpy(to, from, copySize);
        from_next = from + copySize / sizeof(wchar_t), to_next = to + copySize;
        return copySize == inSize ? partial : ok;
    }
};

int main()
{
    std::wofstream fout{ "test.txt" };
    fout.imbue(std::locale{ fout.getloc(), new WcharFacet });
    // Unicode要写一下BOM
    if (std::endian::native == std::endian::little)
    {
        wchar_t bom = static_cast<wchar_t>(0xFEFF);
        fout.write(&bom, 1);
    }
    else
    {
        wchar_t bom = static_cast<wchar_t>(0xFFFE);
        fout.write(&bom, 1);
    }
    fout << L"眼底未名水，胸中黄河月";
}