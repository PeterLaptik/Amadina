#ifndef MAIN_COMMAND_FILE_NEW_INCLUDED_H
#define MAIN_COMMAND_FILE_NEW_INCLUDED_H

#include "abstract_command.h"
#include <wx/msgdlg.h>

class FileNew: public AbstractCommand
{
    public:
        using AbstractCommand::AbstractCommand;

        void Execute() override
        {
            wxMessageBox("File new");
        }
};

#endif
