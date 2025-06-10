#ifndef UI_COMMAND_H_INCLUDED
#define UI_COMMAND_H_INCLUDED

namespace cad::command
{
    class SheetContext;

    class UiCommand
    {
        
        public:

            virtual UiCommand* Clone(SheetContext *ctx) = 0;

        protected:
            
    };
}

#endif
