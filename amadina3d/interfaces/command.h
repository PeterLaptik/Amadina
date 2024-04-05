#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

class wxOccPanel;

namespace modeller
{
    namespace command
    {
        ///\brief Common interface for commands
        /// Only one command can be executed at the same time
        /// (the only exception are instant commands).
        ///\see InstantCommand
        class Command
        {
            public:
                virtual void Execute(wxOccPanel *drawing) = 0;
        };

        ///\brief Command which can be executed during execution of another command
        /// (while another command is waiting for input, screen pick, etc.).
        /// The implementation of InstantCommand should not use direct screen/widgets interactions,
        /// showing input windows, etc.
        /// Possible examples: commands for change view direction, zoom in / zoom out
        /// and other additional routines that may be used during input data for commands.
        /// Command executor uses RTTI to distinguish instant commands.
        class InstantCommand: public Command {};
    }
}

#endif // COMMAND_H_INCLUDED
