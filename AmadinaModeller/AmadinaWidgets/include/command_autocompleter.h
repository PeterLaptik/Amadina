#ifndef COMMAND_AUTOCOMPLETER_H_INCLUDED
#define COMMAND_AUTOCOMPLETER_H_INCLUDED

#include <string>

class CommandAutocompliter
{
    public:
        CommandAutocompliter() = default;
        virtual ~CommandAutocompliter() = default;
        
        virtual bool SetNextChoiceFor(const std::string &prefix) = 0;
};

#endif // !COMMAND_AUTOCOMPLETER_H_INCLUDED
