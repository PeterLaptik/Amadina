#ifndef UI_COMMUNICATOR_H_INCLUDED
#define UI_COMMUNICATOR_H_INCLUDED

class AbstractCommunicator
{
    public:
        AbstractCommunicator():
            is_waiting(false)
        { }

        ~AbstractCommunicator()
        { }

        void SetFinished() {is_waiting = false;}
        bool GetFinished(void) {return !is_waiting;}

        virtual Point EnterPoint(void) = 0;
        virtual Entity* SelectEntity(void) = 0;
        virtual std::vector<Entity*>& SelectEntities(void) = 0;
        virtual void ShowModalWindow(void *dlg) = 0;

    protected:
        volatile is_waiting;

    private:
        std::vector<Entity*> selected;
};

#endif // UI_COMMUNICATOR_H_INCLUDED
