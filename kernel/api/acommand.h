#ifndef ACOMMAND_H_INCLUDED
#define ACOMMAND_H_INCLUDED

#include "exports.h"

class CommandDispatcher;

void DLL_EXPORT register_kernel_commands(CommandDispatcher *dispatcher);

#endif // ACOMMAND_H_INCLUDED
