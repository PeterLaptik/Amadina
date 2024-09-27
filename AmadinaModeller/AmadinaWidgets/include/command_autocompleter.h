#ifndef COMMAND_AUTOCOMPLETER_H_INCLUDED
#define COMMAND_AUTOCOMPLETER_H_INCLUDED

#include <string>
#include <vector>

///\brief Autocomplete util for a command line widgets.
/// Contains pointer to a command list (vector).
/// The command list has to satisfy following requirements:
///\li list has to be sorted
///\li all command names should contain lower case characters only
class CommandAutocompleter
{
    public:
        CommandAutocompleter() = default;
        virtual ~CommandAutocompleter() = default;

        /// Assign pointer for a sorted command list
        virtual void SetCommandList(const std::vector<std::string> *list) = 0;
        
        /// Find next autocomplete proposal for the string input.
        ///\param prefix - string input / last proposal from GetNextChoice
        ///\returns true if any autocomplete proposals exist, otherwise false
        virtual bool SetNextChoiceFor(const std::string &prefix) = 0;

        /// Returns next autocomplete proposal. 
        virtual std::string& GetNextChoice() = 0;
};

#endif // !COMMAND_AUTOCOMPLETER_H_INCLUDED
