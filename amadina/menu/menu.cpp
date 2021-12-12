#include "menu.h"

AmadinaMenu::AmadinaMenu()
{ }

AmadinaMenu::~AmadinaMenu()
{ }


long AmadinaMenu::AppendMenuCommand(const std::string &menu_name,
                                    const std::string &cmd_name,
                                    CommandType cmd_type, long id)
{
    using ui::CommandType;
    switch(cmd_type)
    {
        case CommandType::CMD_FILE:
            return AppendFileMenuItem(menu_name, cmd_name, id);
        case CommandType::CMD_VIEW:
            return AppendViewMenuItem(menu_name, cmd_name, id);
        case CommandType::CMD_EDIT:
            return AppendEditMenuItem(menu_name, cmd_name, id);
        case CommandType::CMD_DRAW:
            return AppendDrawMenuItem(menu_name, cmd_name, id);
        case CommandType::CMD_SETTINGS:
            return AppendSettingsMenuItem(menu_name, cmd_name, id);
        case CommandType::CMD_ABOUT:
            return AppendAboutMenuItem(menu_name, cmd_name, id);
    }
}

long AmadinaMenu::AppendFileMenuItem(const std::string &menu_name,
                        const std::string &command_name,
                        long id) throw(MenuDoesNotExist)
{
    if(!m_menu.menu_file)
        throw MenuDoesNotExist("File");

    if(id==NO_ID)
        id = GenerateMenuId();

    m_menu.menu_file->Append(id, menu_name);
    menu_command_mapping.insert(std::pair<int,std::string>(id, command_name));
    return id;
}

long AmadinaMenu::AppendEditMenuItem(const std::string &menu_name,
                        const std::string &command_name,
                        long id) throw(MenuDoesNotExist)
{
    if(!m_menu.menu_file)
        throw MenuDoesNotExist("Edit");

    if(id==NO_ID)
        id = GenerateMenuId();

    m_menu.menu_edit->Append(id, menu_name);
    menu_command_mapping.insert(std::pair<int,std::string>(id, command_name));
    return id;
}

long AmadinaMenu::AppendViewMenuItem(const std::string &menu_name,
                        const std::string &command_name,
                        long id) throw(MenuDoesNotExist)
{
    if(!m_menu.menu_file)
        throw MenuDoesNotExist("View");

    if(id==NO_ID)
        id = GenerateMenuId();

    m_menu.menu_view->Append(id, menu_name);
    menu_command_mapping.insert(std::pair<int,std::string>(id, command_name));
    return id;
}

long AmadinaMenu::AppendDrawMenuItem(const std::string &menu_name,
                        const std::string &command_name,
                        long id) throw(MenuDoesNotExist)
{
    if(!m_menu.menu_file)
        throw MenuDoesNotExist("Draw");

    if(id==NO_ID)
        id = GenerateMenuId();

    m_menu.menu_draw->Append(id, menu_name);
    menu_command_mapping.insert(std::pair<int,std::string>(id, command_name));
    return id;
}

long AmadinaMenu::AppendSettingsMenuItem(const std::string &menu_name,
                            const std::string &command_name,
                            long id) throw(MenuDoesNotExist)
{
    if(!m_menu.menu_file)
        throw MenuDoesNotExist("Settings");

    if(id==NO_ID)
        id = GenerateMenuId();

    m_menu.menu_settings->Append(id, menu_name);
    menu_command_mapping.insert(std::pair<int,std::string>(id, command_name));
    return id;
}

long AmadinaMenu::AppendAboutMenuItem(const std::string &menu_name,
                         const std::string &command_name,
                         long id) throw(MenuDoesNotExist)
{
    if(!m_menu.menu_file)
        throw MenuDoesNotExist("About");

    if(id==NO_ID)
        id = GenerateMenuId();

    m_menu.menu_about->Append(id, menu_name);
    menu_command_mapping.insert(std::pair<int,std::string>(id, command_name));
    return id;
}

std::string AmadinaMenu::GetMenuCommand(long id)
{
    std::string result = "";
    std::map<long,std::string>::const_iterator it = menu_command_mapping.find(id);
    if(it!=menu_command_mapping.end())
        result = it->second;

    return result;
}

long AmadinaMenu::GenerateMenuId(void) const
{
    return wxNewId();
}

AmadinaMenuList* AmadinaMenu::GetMenuList()
{
    return &m_menu;
}
