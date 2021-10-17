#ifndef SCREEN_COMUNICATOR_H_INCLUDED
#define SCREEN_COMUNICATOR_H_INCLUDED

class Command;
///
class StatefulScreen
{
    public:
        void PickScreenPoint(Command *callback);
        void PickScreenEntity(Command *callback);
        void PickScreenEntities(Command *callback);

    private:
        // State
};

#endif // SCREEN_COMUNICATOR_H_INCLUDED
