#include <cstdio>
#include <string>
#include <locale>
#include <iostream>

// printf format specifiers
// https://en.cppreference.com/w/cpp/io/c/fwprintf

namespace stdstr
{
    // encoding: UTF-8
    void test_string(const std::string &str)
    {
        // byte-size
        std::printf("str byte-size = %zu\n", str.length());

        // char
        std::printf("sizeof(char) = %zu\n", sizeof(str[0]));
        std::printf("str[0]str[1]str[2] = 0x%hhX%hhX%hhX\n", str[0], str[1], str[2]);

        std::printf("literal = %s\n", str.c_str());
        std::cout << str << std::endl;
    }

    // encoding:
    // - Windows: UTF-16, but always 2-byte
    // - Linux: UTF-32
    // Goals of wstring:
    // - wide enough to hold the characters
    // - fast enough to get the length
    void test_wstring(const std::wstring &wstr)
    {
        // length
        std::wprintf(L"wstr length = %zu\n", wstr.length());

        std::printf("sizeof(wchar_t) = %zu\n", sizeof(wstr[0]));
        std::printf("wstr[0] = 0x%X\n", wstr[0]);

        // https://en.cppreference.com/w/cpp/locale/setlocale
        std::setlocale(LC_ALL, "en_US.UTF-8");

        std::wprintf(L"literal = %s\n", wstr.c_str());
        std::wcout << wstr << std::endl;
    }

    void test()
    {
        // "我"
        // U+6211
        // UTF-8 (hex)	0xE6 0x88 0x91 (e68891)
        // UTF-16 (hex)	0x6211 (6211)
        // https://www.fileformat.info/info/unicode/char/6211/index.htm

        const auto str = std::string{"我和我"};
        test_string(str);

        std::cout << std::endl;

        const auto wstr = std::wstring{L"我和我"};
        test_wstring(wstr);
    }
} // namespace stdstr
