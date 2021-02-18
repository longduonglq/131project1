// Long Duong 
// 02/18/2020
// Description: Provides an input function that look for input of a particular type.

#ifndef PROJ1_INPUTTYPE_H
#define PROJ1_INPUTTYPE_H

#include <iostream>
#include <string>

/// Credit: Based largely on Prof. Hester Tools.cpp

// Preconditions: A well formed prompt and an inputable type parameter represents the expected input type.
// Postconditions: The user input is returned in type provided.
template <typename T>
T inputType(std::string prompt)
{
    while (true)
    {
        T input;
        std::cout << prompt;
        std::cin >> input;
        std::cin.ignore(999, '\n');
        if (!std::cin.fail())
            return input;
        std::cin.clear();
        std::cin.ignore(999, '\n');
        std::cout << "Input Failure! Try again" << std::endl;
    }
}

#endif //PROJ1_INPUTTYPE_H
