//
// Created by dop on 2/17/21.
//

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


