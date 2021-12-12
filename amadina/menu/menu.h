#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "../../kernel/command/uicommands.h"
#include "exceptions.h"
#include <map>
#include <wx/menu.h>

class MenuDoesNotExist;
using ui::CommandType;

static const int NO_ID = -1;

///\brief Holder for main frame menus pointers
struct AmadinaMenuList
{
    AmadinaMenuList()
        : menu_file(nullptr),
        menu_edit(nullptr),
        menu_view(nullptr),
        menu_draw(nullptr),
        menu_settings(nullptr),
        menu_about(nullptr)
    { }

    ~AmadinaMenuList()
    { }

    wxMenu *menu_file;
    wxMenu *menu_edit;
    wxMenu *menu_view;
    wxMenu *menu_draw;
    wxMenu *menu_settings;
    wxMenu *menu_about;
};


///\brief Keeps menu-commands mapping.
/// See the description of interface ui::UiCommands
/// Implementation for wxWidgets-based UI
class AmadinaMenu: public ui::UiMenuCommands
{
    public:
        AmadinaMenu();
        ~AmadinaMenu();

        virtual long AppendMenuCommand(const std::string &menu_name,
                                    const std::string &command_name,
                                    CommandType cmd_type, long id = NO_ID);

        virtual std::string GetMenuCommand(long id);

        AmadinaMenuList* GetMenuList(void);

    private:
        // Register command in 'File' menu section
        // menu_name - menu line name
        // command_name - command
        inline long AppendFileMenuItem(const std::string &menu_name,
                                const std::string &command_name,
                                long id) throw(MenuDoesNotExist);
        // Register command in 'Edit' menu section
        // menu_name - menu line name
        // command_name - command
        inline long AppendEditMenuItem(const std::string &menu_name,
                                const std::string &command_name,
                                long id) throw(MenuDoesNotExist);
        // Register command in 'Edit' menu section
        // menu_name - menu line name
        // command_name - command
        inline long AppendViewMenuItem(const std::string &menu_name,
                                const std::string &command_name,
                                long id) throw(MenuDoesNotExist);
        // Register command in 'Draw' menu section
        // menu_name - menu line name
        // command_name - command
        inline long AppendDrawMenuItem(const std::string &menu_name,
                                const std::string &command_name,
                                long id) throw(MenuDoesNotExist);
        // Register command in 'Settings' menu section
        // menu_name - menu line name
        // command_name - command
        inline long AppendSettingsMenuItem(const std::string &menu_name,
                                const std::string &command_name,
                                long id) throw(MenuDoesNotExist);
        // Register command in 'About' menu section
        // menu_name - menu line name
        // command_name - command
        inline long AppendAboutMenuItem(const std::string &menu_name,
                                const std::string &command_name,
                                long id) throw(MenuDoesNotExist);
        // Generates new wxId for the menu item
        inline long GenerateMenuId(void) const;

        AmadinaMenuList m_menu; // menu structure
        std::map<long,std::string> menu_command_mapping; // UI menu id - command map
};

#endif // MENU_H_INCLUDED
