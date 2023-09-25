#include <Windows.h>

#include <locale>
#include <string>
#include <iostream>
#include <format>

namespace gb2312
{
    std::string utf8_to_gb2312(const std::string &utf8_str)
    {
        // Convert UTF-8 to Unicode (UTF-16)
        int wlen = MultiByteToWideChar(CP_UTF8, 0, utf8_str.c_str(), -1, nullptr, 0);
        if (wlen == 0) {
            return "";
        }
        wchar_t *wstr = new wchar_t[wlen];
        MultiByteToWideChar(CP_UTF8, 0, utf8_str.c_str(), -1, wstr, wlen);

        // Convert Unicode (UTF-16) to GB2312
        int len = WideCharToMultiByte(936, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
        if (len == 0) {
            delete[] wstr;
            return "";
        }
        char *str = new char[len];
        WideCharToMultiByte(936, 0, wstr, -1, str, len, nullptr, nullptr);

        std::string gb2312_str(str);
        delete[] wstr;
        delete[] str;

        return gb2312_str;
    }

    void test()
    {
        std::string utf8_str = "你好";
        std::string gb2312_str = utf8_to_gb2312(utf8_str);

        if (gb2312_str.empty()) {
            std::cout << "Conversion failed.\n";
            return;
        }

        std::cout << std::format("GB2312 string length: {}\n", gb2312_str.length());
    }
} // namespace gb2312
