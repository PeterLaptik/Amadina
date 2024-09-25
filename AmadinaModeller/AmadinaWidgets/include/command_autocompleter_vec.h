#ifndef COMMAND_AUTOCOMPLETER_VEC_H_INCLUDED
#define COMMAND_AUTOCOMPLETER_VEC_H_INCLUDED

#include "command_autocompleter.h"
#include <vector>

class CommandAutocompliterVec: public CommandAutocompliter
{
    public:
        CommandAutocompliterVec() = delete;
        explicit CommandAutocompliterVec(const std::vector<std::string> &list);

        ~CommandAutocompliterVec() override  = default;

        bool SetNextChoiceFor(const std::string &prefix) override;

    private:
        void UpdateRange();

        struct
        {
            std::vector<std::string>::const_iterator start;
            std::vector<std::string>::const_iterator end;
            std::vector<std::string>::const_iterator cursor;
        } m_match_range;
        
        const std::vector<std::string> &m_list;
        std::string m_current_prefix;
        size_t m_current_size;
};

#endif // !COMMAND_AUTOCOMPLETER_VEC_H_INCLUDED