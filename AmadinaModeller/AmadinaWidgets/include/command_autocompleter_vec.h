#ifndef COMMAND_AUTOCOMPLETER_VEC_H_INCLUDED
#define COMMAND_AUTOCOMPLETER_VEC_H_INCLUDED

#include "command_autocompleter.h"

///\brief Basic autocomplete util implementation
/// For every input (string begining) methods SetNextChoiceFor and GetNextChoice should be
/// sequently called. GetNextChoice call without SetNextChoiceFor returns the same proposal.
///\see CommandAutocompleter
///\see CommandPanel how to use
class CommandAutocompleterVec: public CommandAutocompleter
{
    public:
        CommandAutocompleterVec() = default;
        ~CommandAutocompleterVec() override  = default;

        void SetCommandList(const std::vector<std::string> *list) override;

        /// Find next autocomplete proposal for the string input.
        /// A proposal list is looped: after the last proposal goes to the initial string input.
        ///\param prefix - initial string input / last proposal from GetNextChoice
        ///\returns true if autocomplete proposals exist, otherwise false
        bool SetNextChoiceFor(const std::string &prefix) override;

        /// Returns next autocomplete proposal. 
        /// Should be called only after SetNextChoiceFor,
        /// and if the result of SetNextChoiceFor is true
        ///\returns next proposal, or last valid proposal for wrong cases
        std::string& GetNextChoice() override;

    private:
        void UpdateRange(const std::string &prefix);

        // Result range and current cursor value (vector indices)
        struct
        {
            int start = -1;
            int end = -1;
            int cursor = -1;
        } m_match_range;
        
        const std::vector<std::string> *m_list; // sorted list of command names
        std::string m_current_proposal;         // current proposal
        std::string m_initial_prefix;           // initial prefix
        size_t m_current_list_size;             // list size
};

#endif // !COMMAND_AUTOCOMPLETER_VEC_H_INCLUDED