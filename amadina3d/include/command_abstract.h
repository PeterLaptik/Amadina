#ifndef COMMAND_ABSTRACT_H_INCLUDED
#define COMMAND_ABSTRACT_H_INCLUDED

#include "context.h"

namespace cad
{
    namespace modeller
    {
        namespace command
        {
            class CommandAbstract
            {
                public:
                    virtual ~CommandAbstract(void)
                    {}

                    virtual void Execute() = 0;
                    virtual CommandAbstract* Clone(Context *context) = 0;
            };
        }
    }
}


#endif // COMMAND_ABSTRACT_H_INCLUDED
