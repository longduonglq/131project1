// Name : Long Duong 
// Date: 02/18/2020
// Description: Provide a convenient class for creating a choice-based UI.

#ifndef PROJ1_OPTIONUI_H
#define PROJ1_OPTIONUI_H

#include <optional>
#include <cassert>
#include "Prerequisite.h"
#include "Parameter.h"
#include "UIExcept.h"

class SingularOption
{
public:
    std::function<void(std::ostream&)> invokeOption;


    // Preconditions: None
    // Postconditions: Instance created.
    SingularOption() = default;
    

    // Preconditions: OptionHandler_t is a callable and a list of parameters of type AbstractParameter
    // Postconditions: Public member InvokeOption is created and will call optionHandler with parameters given upon invokcation.
    template<typename OptionHandler_t, typename ...AbstractParameter>
    SingularOption(OptionHandler_t optionHandler, AbstractParameter... requiredParams)
    {
        bindHandler(optionHandler, requiredParams...);
    }

    // Preconditions: OptionHandler_t is a callable and a list of parameters of type AbstractParameter
    // Postconditions: Public member InvokeOption is created and will call optionHandler with parameters given upon invokcation.
    template <typename OptionHandler_t, typename ...AbstractParameters>
    void bindHandler(OptionHandler_t optionHandler, AbstractParameters... requiredParams)
    {
        invokeOption = [this, optionHandler, requiredParams...] ( std::ostream& os )
        {
            for (auto& prerequisite: prerequisites)
            {
                if (!prerequisite->isSatisfied())
                {
                    os << prerequisite->getErrorMsg() << std::endl;
                    return;
                }
            }
            try
            {
                optionHandler(requiredParams.collectParam()...);
            }
            catch (UIExcept& e)
            {
                os << e.what() << std::endl;
                return;
            }
        };
    }

    // Preconditions: Expect a shared_ptr to a prerequisite
    // Postconditions: Prerequisite is added to the list of prechecks for before invoking this option.
    SingularOption& require(std::shared_ptr<AbstractPrerequisite> condition)
    {
        prerequisites.push_back(condition);
        return *this;
    }

private:
    std::vector<std::shared_ptr<AbstractPrerequisite>> prerequisites;
};

class OptionUI
{
public:
    OptionUI() :
        choiceCollector("Option: ")
    {}

    // Preconditions: Instance was initialize properly.
    // Postconditions: Added optionCharacter -> optionHandler into a map.
    template<typename ...AbstractParameter, typename OptionHandler_t>
    SingularOption& addOption(char optionCharacter,
                              OptionHandler_t optionHandler,
                              AbstractParameter... requiredParams)
    {
        assert (options.find(optionCharacter) == options.end());

        auto singularOptionIt = options.insert(
            std::make_pair(
                optionCharacter,
                std::make_unique<SingularOption>(
                    optionHandler,
                    requiredParams...
                )
            )
        );
        return *(singularOptionIt.first->second);
    }
    
    // Preconditions: Expect an optionCharacter that is present in the map
    // Postconditions: Invoke the function associated with the optionCharacter
    void processOption(char optionCharacter)
    {
        auto option = options.find(optionCharacter);
        option->second->invokeOption(std::cout);
    }
    
    // Preconditions: None
    // Postconditions: Depends on derived class.
    virtual void init() = 0;

    // Preconditions: None
    // Postconditions: Depends on derived class.
    virtual void showCurrentState() = 0;
    
    // Preconditions: choiceCollect and options map initialized
    // Postconditions: Continously collect user's options until terminateCharacter was entered. 
    void run()
    {
        this->init();
        this->showCurrentState();

        char userChoice;
        while (userChoice = tolower(choiceCollector.collectParam()),
               userChoice != terminateCharacter)
        {
            if (options.find(userChoice) == options.end())
            {
                std::wcout << "Option was not registered" << std::endl;
            }
            else
            {
                processOption(userChoice);
            }
            this->showCurrentState();
        }
    }

protected:
    CharParameter choiceCollector;
    std::optional<char> terminateCharacter;
    std::map<char, std::unique_ptr<SingularOption>> options;
};

#endif //PROJ1_OPTIONUI_H
