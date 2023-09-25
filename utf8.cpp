#include <cstdio>
#include <iostream>

#include <string>
#include <locale>

namespace utf8
{
    bool process_utf8_byte(unsigned char c, int &bytes2skip, size_t &length)
    {
        if (bytes2skip) {
            if ((c & 0xC0) != 0x80)
                return false;
            --bytes2skip;
            return true;
        }

        ++length; // Count a new Unicode code point
        if ((c & 0x80) == 0)
            return true; // ASCII

        if ((c & 0xE0) == 0xC0)
            bytes2skip = 1;
        else if ((c & 0xF0) == 0xE0)
            bytes2skip = 2;
        else if ((c & 0xF8) == 0xF0)
            bytes2skip = 3;
        else
            return false; // Invalid UTF-8

        return true;
    }

    bool is_valid_utf8(const std::string &str)
    {
        int bytesToSkip = 0;
        size_t dummyLength = 0;
        for (unsigned char c : str) {
            if (!process_utf8_byte(c, bytesToSkip, dummyLength))
                return false;
        }
        return bytesToSkip == 0;
    }

    size_t length(const std::string &str)
    {
        size_t length = 0;
        int bytesToSkip = 0;
        for (unsigned char c : str) {
            if (!process_utf8_byte(c, bytesToSkip, length))
                return 0; // Invalid UTF-8
        }
        if (bytesToSkip)
            return 0; // Incomplete UTF-8 sequence
        return length;
    }

    void test()
    {
        std::string test1 = "Hello";
        std::string test2 = "\xC3\xA9";      // 'é' in UTF-8
        std::string test3 = "Hello\xC3\xA9"; // "Helloé"

        std::cout << utf8::is_valid_utf8(test1) << std::endl; // Output: 1
        std::cout << utf8::is_valid_utf8(test2) << std::endl; // Output: 1
        std::cout << utf8::length(test1) << std::endl;        // Output: 5
        std::cout << utf8::length(test2) << std::endl;        // Output: 1
        std::cout << utf8::length(test3) << std::endl;        // Output: 6
    }
} // namespace utf8
