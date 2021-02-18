// Name : Long Duong 
// Date: 02/18/2020
// Description:  Provides a convenient class for collecting user input with validator.

#ifndef PROJ1_PARAMETER_H
#define PROJ1_PARAMETER_H

#include <string>
#include <optional>
#include "inputType.h"

template <typename T>
class AbstractParameter
{
public:
    // Preconditions:  Expect a prompt
    // Postconditions: Instance created with prompt.
    explicit AbstractParameter(std::string&& _prompt) :
        prompt {_prompt},
        validator {std::nullopt}
    {}

    // Preconditions:  Expect prompt and input validator
    // Postconditions: Instance created with prompt and input validator
    AbstractParameter(std::string&& _prompt,
                      std::function<bool(const T&)> _validator) :
        prompt {_prompt},
        validator {_validator}
    {}

    ~AbstractParameter() = default;

    // Preconditions: Instance was properly initialized.
    // Postconditions: Continuously ask the user for data of the type given and validate if validator was provided.
    T collectParam() const
    {
        T input;
        do
        {
            input = inputType<T>(prompt);
            if (validator.has_value() && !validator.value()(input))
                std::cout << "ERROR: Input did not pass validator\'s check." << std::endl;
            else
                return input;
        } while (true);
    }
private:
    std::string prompt;
    std::optional<std::function<bool(const T&)>> validator;
};

using LongParameter = AbstractParameter<long>;
using DoubleParameter = AbstractParameter<double>;
using CharParameter = AbstractParameter<char>;
using StringParameter = AbstractParameter<std::string>;

#endif //PROJ1_PARAMETER_H
