#ifndef COMMAND_INTERPRETER_H
#define COMMAND_INTERPRETER_H

#include <string>
#include <vector>

namespace cad
{
    namespace command
    {
        class Interpreter
        {
            public:
                Interpreter();
                virtual ~Interpreter();

                void ParseExpression(std::string expr);

            private:
                void PurgeDelimiters(std::string &expr);
                void ReadSubExpressions(std::string &line,std::vector<std::string> &tokens);

                void TrimSpacesAfterCommas(std::string &expr);
        };
    }
}
#endif // COMMAND_INTERPRETER_H
