#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

class wxOccPanel;

namespace modeller {
    namespace command {

        class Command
        {
            virtual void Execute(wxOccPanel *panel) = 0;
        };

        class ClonableCommand: public Command
        {
            virtual Command* Clone(void) = 0;
        };

    }
}

#endif // COMMAND_H_INCLUDED
