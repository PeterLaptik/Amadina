#include "menu.h"

AmadinMenu::AmadinMenu()
    : menu_file(nullptr),
        menu_edit(nullptr),
        menu_view(nullptr),
        menu_draw(nullptr),
        menu_settings(nullptr),
        menu_about(nullptr)
{ }

AmadinMenu::~AmadinMenu()
{ }

void AmadinMenu::CheckCommand(const std::string &command) const throw(CommandExists)
{
    for(std::map<int,std::string>::const_iterator it=menu_command_mapping.begin();
            it!=menu_command_mapping.end(); ++it)
    {
        if(it->second==command)
            throw CommandExists(command);
    }
}

int AmadinMenu::GenerateMenuId(void) const
{
    return wxNewId();
}

void AmadinMenu::AppendFileMenuItem(const std::string &menu_name,
                        const std::string &command_name)
{
    CheckCommand(command_name);
    int id = GenerateMenuId();
    menu_file->Append(id, menu_name);
    menu_command_mapping.insert(std::pair<int,std::string>(id, command_name));
}

void AmadinMenu::AppendEditMenuItem(const std::string &menu_name,
                        const std::string &command_name)
{
    CheckCommand(command_name);
    int id = GenerateMenuId();
    menu_edit->Append(id, menu_name);
    menu_command_mapping.insert(std::pair<int,std::string>(id, command_name));
}

void AmadinMenu::AppendViewMenuItem(const std::string &menu_name,
                        const std::string &command_name)
{
    CheckCommand(command_name);
    int id = GenerateMenuId();
    menu_view->Append(id, menu_name);
    menu_command_mapping.insert(std::pair<int,std::string>(id, command_name));
}

void AmadinMenu::AppendDrawMenuItem(const std::string &menu_name,
                        const std::string &command_name)
{
    CheckCommand(command_name);
    int id = GenerateMenuId();
    menu_draw->Append(id, menu_name);
    menu_command_mapping.insert(std::pair<int,std::string>(id, command_name));
}

void AmadinMenu::AppendSettingsMenuItem(const std::string &menu_name,
                            const std::string &command_name)
{
    CheckCommand(command_name);
    int id = GenerateMenuId();
    menu_settings->Append(id, menu_name);
    menu_command_mapping.insert(std::pair<int,std::string>(id, command_name));
}

void AmadinMenu::AppendAboutMenuItem(const std::string &menu_name,
                         const std::string &command_name)
{
    CheckCommand(command_name);
    int id = GenerateMenuId();
    menu_about->Append(id, menu_name);
    menu_command_mapping.insert(std::pair<int,std::string>(id, command_name));
}

std::string AmadinMenu::GetMenuCommand(int id)
{
    std::string result = "";
    std::map<int,std::string>::const_iterator it = menu_command_mapping.find(id);
    if(it!=menu_command_mapping.end())
        result = it->second;

    return result;
}
