#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "../../kernel/command/uicommands.h"
#include "exceptions.h"
#include <map>
#include <wx/menu.h>

///\brief Keeps menu-commands mapping.
/// There is no need to work with the class directly.
/// See the description of interface ui::UiCommands
class AmadinMenu: public ui::UiCommands
{
    public:
        AmadinMenu();
        ~AmadinMenu();

        virtual void AppendFileMenuItem(const std::string &menu_name,
                                const std::string &command_name);
        virtual void AppendEditMenuItem(const std::string &menu_name,
                                const std::string &command_name);
        virtual void AppendViewMenuItem(const std::string &menu_name,
                                const std::string &command_name);
        virtual void AppendDrawMenuItem(const std::string &menu_name,
                                const std::string &command_name);
        virtual void AppendSettingsMenuItem(const std::string &menu_name,
                                const std::string &command_name);
        virtual void AppendAboutMenuItem(const std::string &menu_name,
                                const std::string &command_name);

        virtual std::string GetMenuCommand(int id);

    private:
        // Throws exception if the command name exists in th emap
        void CheckCommand(const std::string &command) const throw(CommandExists);
        // Generates new wxId for the menu item
        inline int GenerateMenuId(void) const;

        wxMenu *menu_file;
        wxMenu *menu_edit;
        wxMenu *menu_view;
        wxMenu *menu_draw;
        wxMenu *menu_settings;
        wxMenu *menu_about;
        // UI menu id - command map
        std::map<int,std::string> menu_command_mapping;
};

#endif // MENU_H_INCLUDED
