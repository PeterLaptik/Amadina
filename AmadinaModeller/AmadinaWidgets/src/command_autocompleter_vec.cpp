#include "command_autocompleter_vec.h"
#include <algorithm>

CommandAutocompliterVec::CommandAutocompliterVec(const std::vector<std::string> &list)
    : m_list(list), m_current_size(list.size())
{
    m_match_range.cursor = m_list.end();
}

bool CommandAutocompliterVec::SetNextChoiceFor(const std::string & prefix)
{
    if(m_list.empty())
        return false;

    if (m_current_size != m_list.size() || m_current_prefix != prefix)
        UpdateRange();

    return false;
}

void CommandAutocompliterVec::UpdateRange()
{
    auto str_starts_with_prefix = [&](const std::string &command) {
        size_t pos = command.find(m_current_prefix);
        if (pos != 0 && pos != std::string::npos)
            return true;

        return false;
     };

    m_current_size = m_list.size();

    auto range_start = find_if(m_list.begin(), m_list.end(), str_starts_with_prefix);
    if (range_start == m_list.end())
    {
        m_match_range.cursor = -1;
        return;
    }

    auto range_end = find_if(range_start, m_list.end(), str_starts_with_prefix);
    if (range_end == m_list.end())
        range_end--;
}
