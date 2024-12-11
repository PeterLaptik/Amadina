#include "command_autocompleter.h"
#include <algorithm>
#include <iterator>

// Autocomplete util shows ptopositions only if its quantity is not higher than this value
const int MAX_CHOICE_NUMBER = 5;


void CommandAutocompleter::SetCommandList(const std::vector<std::string> *list)
{
    m_list = list;
}

bool CommandAutocompleter::SetNextChoiceFor(const std::string &prefix)
{
    if(!m_list || m_list->empty())
        return false;

    // List has been changed / invalidated, or a new prefix is retyped
    if (m_current_list_size != m_list->size() || m_current_proposal != prefix)
        UpdateRange(prefix);

    // There are no choices / too many choices
    if (m_match_range.cursor == -1 || (m_match_range.end - m_match_range.start > MAX_CHOICE_NUMBER))
        return false;

    // Last value was shown. Set up initial string as a proposition, and go to begin
    if (m_match_range.cursor > m_match_range.end)
    {
        m_current_proposal = m_initial_prefix;
        m_match_range.cursor = m_match_range.start;
    }
    else // Get next proposition
    {
        m_current_proposal = (*m_list)[m_match_range.cursor];
        m_match_range.cursor++;
    }

    return true;
}

std::string& CommandAutocompleter::GetNextChoice()
{
    return m_current_proposal;
}

void CommandAutocompleter::UpdateRange(const std::string &prefix)
{
    m_current_list_size = m_list->size();
    m_initial_prefix = prefix;

    // TODO REMOVE
    // Lower case copy: lower case letters only are expected in a command list
    std::string lower_case_prefix;
    std::transform(m_initial_prefix.begin(), m_initial_prefix.end(), 
        std::back_insert_iterator<std::string>(lower_case_prefix),
        [](char ch) {
            return std::tolower(ch);
        });

    // Is the command name begins with the prefix
    auto str_starts_with_prefix = [&](const std::string_view &command) {
        size_t pos = command.find(lower_case_prefix);
        if (pos == 0 && pos != std::string::npos)
            return true;

        return false;
        };

    // First matching command occurence
    auto range_start = find_if(m_list->begin(), m_list->end(), str_starts_with_prefix);
    if (range_start == m_list->end())
    {
        m_match_range.cursor = -1;
        return;
    }

    // Last matching command occurence
    auto range_end = find_if_not(range_start, m_list->end(), str_starts_with_prefix);
    range_end--;

    // Transorm found diapason to indeces
    m_match_range.start = std::distance(m_list->begin(), range_start);
    m_match_range.end = std::distance(m_list->begin(), range_end);
    m_match_range.cursor = m_match_range.start;
}
