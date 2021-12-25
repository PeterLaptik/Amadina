#ifndef ACOMMAND_H_INCLUDED
#define ACOMMAND_H_INCLUDED

#include "exports.h"

class CommandDispatcher;

// The function should be called to register all kernel commands
// in existing command dispatcher or its custom implementation
void DLL_EXPORT register_kernel_commands(CommandDispatcher *dispatcher);

#endif // ACOMMAND_H_INCLUDED
