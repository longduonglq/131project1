// Name : Long Duong 
// Date: 02/18/2020
// Description: Implementation of various non-templated functions that output the display width of various types.

#include "MixedColumn.h"

std::size_t displayLength(const char* cStr)
{
    return strlen(cStr);
}

std::size_t displayLength(const wchar_t* cStr)
{
    return wcslen(cStr);
}

std::size_t displayLength(std::wstring WideStr)
{
    return WideStr.size();
}

std::size_t displayLength(char)
{
    return 1;
}


