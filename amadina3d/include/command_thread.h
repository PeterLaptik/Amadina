#ifndef COMMANDTHREAD_H
#define COMMANDTHREAD_H

#include "command_abstract.h"
#include "point.h"
#include <atomic>

namespace cad
{
    namespace modeller
    {
        namespace command
        {
            class InputReceiver
            {
                virtual void SetPoint(const Point &point) = 0;
                virtual void SetNumber(double number) = 0;
                virtual void SetString(double number) = 0;
            };

            class CommandThread: public CommandAbstract, public InputReceiver
            {
                public:
                    CommandThread();
                    virtual ~CommandThread();
                    virtual void Draw(void) = 0;
            //        virtual bool IsMultiple(void) const;

                    virtual void SetPoint(const Point &point);
                    virtual void SetNumber(double number);

                protected:
                    Point InputPoint(void);
                    double InputNumber(void);
                    inline bool IsBusy(void) const;

                private:
                    std::atomic<bool> is_waiting_for_point;
                    std::atomic<bool> is_waiting_for_number;
                    Point m_point;
                    double m_number;
            };
        }
    }
}

#endif // COMMANDTHREAD_H
