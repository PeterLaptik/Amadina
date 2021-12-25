#ifndef CALLABLE_H_INCLUDED
#define CALLABLE_H_INCLUDED

class CallableFrame
{
    public:
        virtual void PrintMessage(const std::string &msg) = 0;
        virtual void SetUndoRedoState(bool can_undo, bool can_redo) = 0;
};

#endif // CALLABLE_H_INCLUDED
