#ifndef UICOMMANDS_H_INCLUDED
#define UICOMMANDS_H_INCLUDED

#include <string>

namespace ui
{
    ///\brief Main interface for the UI-menu items registration class.
    /// Appends commands (string command value) and menu aliases into main menu.
    /// Main goal of the class is to provide UI-library independent interface
    /// for command registration in UI-menus.
    class UiCommands
    {
        /// Register command in 'File' menu section
        ///\param menu_name - menu line name
        ///\param command_name - command
        virtual void AppendFileMenuItem(const std::string &menu_name,
                                    const std::string &command_name) = 0;

        /// Register command in 'Edit' menu section
        ///\param menu_name - menu line name
        ///\param command_name - command
        virtual void AppendEditMenuItem(const std::string &menu_name,
                                    const std::string &command_name) = 0;

        /// Register command in 'View' menu section
        ///\param menu_name - menu line name
        ///\param command_name - command
        virtual void AppendViewMenuItem(const std::string &menu_name,
                                    const std::string &command_name) = 0;

        /// Register command in 'Draw' menu section
        ///\param menu_name - menu line name
        ///\param command_name - command
        virtual void AppendDrawMenuItem(const std::string &menu_name,
                                    const std::string &command_name) = 0;

        /// Register command in 'Settings' menu section
        ///\param menu_name - menu line name
        ///\param command_name - command
        virtual void AppendSettingsMenuItem(const std::string &menu_name,
                                    const std::string &command_name) = 0;

        /// Register command in 'About' menu section
        ///\param menu_name - menu line name
        ///\param command_name - command
        virtual void AppendAboutMenuItem(const std::string &menu_name,
                                    const std::string &command_name) = 0;

        /// Returns command for defined menu id
        virtual std::string GetMenuCommand(int id) = 0;
    };
}

#endif // UICOMMANDS_H_INCLUDED
