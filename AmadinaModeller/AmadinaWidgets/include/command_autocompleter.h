#ifndef COMMAND_AUTOCOMPLETER_VEC_H_INCLUDED
#define COMMAND_AUTOCOMPLETER_VEC_H_INCLUDED

#include "command_autocompleter.h"
#include <string>
#include <vector>

///\brief Basic autocomplete util implementation
/// For every input (string begining) methods SetNextChoiceFor and GetNextChoice should be
/// sequently called. GetNextChoice call without SetNextChoiceFor returns the same proposal.
///\see CommandAutocompleter
///\see CommandPanel how to use
class CommandAutocompleter
{
    public:
        CommandAutocompleter() = default;
        ~CommandAutocompleter() = default;

        void SetCommandList(const std::vector<std::string> *list);

        /// Find next autocomplete proposal for the string input.
        /// A proposal list is looped: after the last proposal goes to the initial string input.
        ///\param prefix - initial string input / last proposal from GetNextChoice
        ///\returns true if autocomplete proposals exist, otherwise false
        bool SetNextChoiceFor(const std::string &prefix);

        /// Returns next autocomplete proposal. 
        /// Should be called only after SetNextChoiceFor,
        /// and if the result of SetNextChoiceFor is true
        ///\returns next proposal, or initial text after last proposal, or last valid proposal for wrong cases
        std::string& GetNextChoice();

    private:
        void UpdateRange(const std::string &prefix);

        // Result range and current cursor value (vector indices)
        struct
        {
            int start = -1;
            int end = -1;
            int cursor = -1; // current proposal
        } m_match_range;
        
        const std::vector<std::string> *m_list = nullptr; // sorted list of command names
        std::string m_current_proposal;
        std::string m_initial_prefix;
        size_t m_current_list_size = 0;
};

#endif // !COMMAND_AUTOCOMPLETER_VEC_H_INCLUDED