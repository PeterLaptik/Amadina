#ifndef AMADINA_SKETCH_COMMAND_H_INCLUDED
#define AMADINA_SKETCH_COMMAND_H_INCLUDED

#include "base_command.h"

namespace cad::command
{
    class CreateSketch: public BaseCommand
    {
        public:
            bool Execute(SheetContext *ctx, CommandArguments &args) override;

            BaseCommand *Clone() override;
    };
}

#endif // AMADINA_SKETCH_COMMAND_H_INCLUDED
