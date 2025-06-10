#ifndef AMADINA_APPLICATION_CONTEXT_H_INCLUDED
#define AMADINA_APPLICATION_CONTEXT_H_INCLUDED

#include "sheet_context.h"
#include "base_command.h"
#include "command_dispatcher.h"

namespace cad::app
{
    class ApplicationContext
    {
        public:
            ApplicationContext() = default;
            virtual ~ApplicationContext() = default;

            //void AppendSheet(SheetContext *sheet);
            //void RemoveSheet(SheetContext *sheet);
            //void ActivateSheet(SheetContext *sheet);

            bool AddCommand(const std::string &name, BaseCommand *cmd);
            BaseCommand* GetCommand(std::string alias);
            void RemoveCommand(const std::string &name);

            static const int kMaxSheetsInApp = 8;

        private:
            SheetContext *m_sheet_ctx[kMaxSheetsInApp];
            SheetContext *m_active_sheet = nullptr;
            cad::command::CommandDispatcher m_cmd_dispatcher;
    };
}

#endif // AMADINA_APPLICATION_CONTEXT_H_INCLUDED
