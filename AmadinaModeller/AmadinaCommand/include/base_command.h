#ifndef BASE_COMMAND_H_INCLUDED
#define BASE_COMMAND_H_INCLUDED

#include <string>

namespace cad::command
{
    class BaseCommand
    {
        public:
            BaseCommand() = default;
            virtual ~BaseCommand() = default;

        protected:
            void GetPoint();
            void GetText();
            void GetString();
            void GetNumber();

        private:
            // Token or value

    };
}

#endif // !BASE_COMMAND_H_INCLUDED

