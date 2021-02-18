// Name : Long Duong 
// Date: 02/18/2020
// Description: Provides a standardized way to add pre-checks for each option in OptionUI.

#ifndef PROJ1_PREREQUISITE_H
#define PROJ1_PREREQUISITE_H


#include <map>
#include <vector>
#include <optional>
#include <functional>

class AbstractPrerequisite
{
public:
    // Preconditions: Expect an error message
    // Postconditions: Instance initialized
    AbstractPrerequisite(const std::string& _errorMsg): errorMsg {_errorMsg}
    {}
    virtual ~AbstractPrerequisite() {} ;

    // Preconditions: None
    // Postconditions: Depends on derived class
    virtual bool isSatisfied() = 0;

    // Preconditions: None
    // Postconditions: Return errorMsg given.
    virtual const std::string getErrorMsg()
    {
        return errorMsg;
    }

private:
    std::string errorMsg;
};

class InvokeMethodRequirement : public AbstractPrerequisite
{
public:
    typedef std::function<bool(void)> CheckFunc_t;
    // Preconditions: expect a boolean checkFunction and an errorMessage
    // Postconditions: Instance initialized.
    InvokeMethodRequirement(CheckFunc_t&& _checkFunc,
                            const std::string& _errorMsg)
        :
        AbstractPrerequisite (_errorMsg),
        checkFunc {_checkFunc}
    {}
    ~InvokeMethodRequirement() override = default;

    // Preconditions: Instance was initialized with proper check function.
    // Postconditions: Return whether the conditions checked by CheckFunc is met.
    bool isSatisfied() override
    {
        return std::invoke(checkFunc);
    }
private:
    CheckFunc_t checkFunc;
};

template <typename OptionalType>
class RequireValuedOptional : public InvokeMethodRequirement
{
public:
    // Preconditions: Expect a reference wrapper to the optional needed watching and an errorMsg
    // Postconditions: Instance is initialized
    explicit RequireValuedOptional(std::reference_wrapper<OptionalType> _target,
                                   const std::string& _errorMsg) :
        InvokeMethodRequirement([_target]() { return _target.get().has_value(); }, _errorMsg ) {}
    virtual ~RequireValuedOptional() override {};
};

template <typename VecType>
class RequireNonEmptyVector : public InvokeMethodRequirement
{
public:
    // Preconditions: Expect a reference wrapper to the vector needed watching and an errorMsg
    // Postconditions: Instance is initialized
    explicit RequireNonEmptyVector(std::reference_wrapper<VecType> _target,
                                   const std::string& _errorMsg) :
        InvokeMethodRequirement([_target]() { return !_target.get().empty(); }, _errorMsg) {}
    virtual ~RequireNonEmptyVector() override {};
};

template <typename StringType>
class RequireNonEmptyString : public InvokeMethodRequirement
{
public:
    // Preconditions: Expect a reference wrapper to the string needed watching and an errorMsg
    // Postconditions: Instance is initialized
    explicit RequireNonEmptyString(std::reference_wrapper<StringType> _target,
                                   const std::string& _errorMsg) :
        InvokeMethodRequirement([_target] () { return !_target.get().empty() ;}) {}
    virtual ~RequireNonEmptyString() override {};
};

#endif //PROJ1_PREREQUISITE_H
