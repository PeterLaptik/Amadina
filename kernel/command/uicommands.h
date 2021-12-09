#ifndef UICOMMANDS_H_INCLUDED
#define UICOMMANDS_H_INCLUDED

#include <string>

namespace ui
{
    static const int NO_ID = -1;

    /// Menu section for command
    enum CommandType
    {
        CMD_NO_MENU,
        CMD_FILE,
        CMD_EDIT,
        CMD_VIEW,
        CMD_DRAW,
        CMD_SETTINGS,
        CMD_ABOUT
    };

    ///\brief Main interface for the UI-menu items registration class.
    /// Appends commands (string command value) and menu aliases into a main menu.
    /// Main goal of the class is to provide UI-library independent interface
    /// for command registration in UI-menus.
    class UiMenuCommands
    {
        public:
            ///\brief Appends appropriate menu choice for the defined command.
            /// The command name can be got from storage by menu id.
            /// For this method menu id generation should be implemented in sub-classes
            ///\param menu_name - menu section name
            ///\param cmd_name - exact command name
            ///\param cmd_type - command type enumeration value
            ///\param id - menu id
            ///\returns menu id
            virtual long AppendMenuCommand(const std::string &menu_name,
                                        const std::string &cmd_name,
                                        CommandType cmd_type, long id=NO_ID) = 0;

            /// Returns command name for defined menu id
            virtual std::string GetMenuCommand(long id) = 0;
    };
}

#endif // UICOMMANDS_H_INCLUDED
