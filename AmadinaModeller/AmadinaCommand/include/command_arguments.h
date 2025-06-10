#ifndef COMMAND_ARGUMENTS_H_INCLUDED
#define COMMAND_ARGUMENTS_H_INCLUDED

#include "command_token.h"
#include <vector>

namespace cad::command::interpreter
{
    class CommandArguments
    {
        public:
            CommandArguments(const std::vector<CommandToken> &tokens)
            {
                for (size_t i=1, max_tok = tokens.size(); i<max_tok; i++)
                    m_tokens.push_back(tokens[i]);
            }

            CommandArguments(CommandArguments &&args) noexcept
                : m_tokens(std::move(args.m_tokens))
            { }

            CommandToken GetArg(size_t pos)
            {
                return pos < m_tokens.size() ? m_tokens[pos] : CommandToken{};
            }

            size_t GetSize() const
            {
                return m_tokens.size();
            }

        private:
            std::vector<CommandToken> m_tokens;
    };
}

#endif // COMMAND_ARGUMENTS_H_INCLUDED