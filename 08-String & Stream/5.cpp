#include <algorithm>
#include <array>
#include <iostream>
#include <locale>

struct CtypeWithChineseNum : std::ctype<wchar_t>
{
private:
    using Base = std::ctype<wchar_t>;
    static const std::size_t s_digitNpos = 13;
    static inline const std::array<wchar_t, 13> s_upperChineseNumbers{
        L'壹', L'贰', L'叁', L'肆', L'伍', L'陆', L'柒',
        L'捌', L'玖', L'拾', L'佰', L'仟', L'萬'
    };
    static inline const std::array<wchar_t, 13> s_lowerChineseNumbers{
        L'一', L'二', L'三', L'四', L'五', L'六', L'七',
        L'八', L'九', L'十', L'百', L'千', L'万'
    };

protected:
    static auto GetChineseLowerDigitIdx(wchar_t c)
    {
        return std::ranges::find(s_lowerChineseNumbers, c) -
                s_lowerChineseNumbers.begin();
    }

    static auto GetChineseUpperDigitIdx(wchar_t c)
    {
        return std::ranges::find(s_upperChineseNumbers, c) -
                s_upperChineseNumbers.begin();
    }

    static bool IsChineseDigit(wchar_t c)
    {
        return GetChineseLowerDigitIdx(c) != s_digitNpos ||
                GetChineseUpperDigitIdx(c) != s_digitNpos;
    }

    bool do_is(mask m, char_type c) const override
    {
        if ((m & digit) && IsChineseDigit(c))
        {
            return true;
        }

        if ((m & upper) && GetChineseUpperDigitIdx(c) != s_digitNpos)
        {
            return true;
        }

        if ((m & lower) && GetChineseLowerDigitIdx(c) != s_digitNpos)
        {
            return true;
        }

        return Base::do_is(m, c);
    }

    char_type do_toupper(char_type c) const override
    {
        if (auto pos = GetChineseLowerDigitIdx(c); pos != s_digitNpos)
        {
            return s_upperChineseNumbers[pos];
        }
        return Base::do_toupper(c);
    }

    char_type do_tolower(char_type c) const override
    {
        if (auto pos = GetChineseUpperDigitIdx(c); pos != s_digitNpos)
        {
            return s_lowerChineseNumbers[pos];
        }
        return Base::do_tolower(c);
    }
};

int main()
{
    // std::locale chs{ std::locale("zh-CN") };
    // std::cout << std::isupper(L'壹', chs) << ' ' << std::islower(L'一', chs)
    //             << '\n'; // 输出什么？
    // chs = std::locale{ chs, new CtypeWithChineseNum{} };
    std::locale chs{ std::locale::classic(), new CtypeWithChineseNum{} };
    std::cout << std::isupper(L'壹', chs) << ' ' << std::islower(L'一', chs)
        << '\n'; // 输出什么？

    std::wcout.imbue(chs);
    std::ranges::transform(
        L"壹捌玖捌", std::ostream_iterator<wchar_t, wchar_t>{ std::wcout },
        [](wchar_t c) {
            return std::use_facet<std::ctype<wchar_t>>(std::wcout.getloc())
                .tolower(c);
        }); // 输出什么？
    return 0;
}