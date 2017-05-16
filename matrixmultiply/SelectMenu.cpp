#include "SelectMenu.h"
#include <conio.h>

#include "Msg.h"
#include "Configure.h"

#define SELECT_MENU { MSG_SELECTMENU_TITLE, MSG_SELECTMENU_OPTION_1, MSG_SELECTMENU_OPTION_2, MSG_SELECTMENU_OPTION_3, MSG_MENU_BACK }

matrixm::menu::SelectMenu::SelectMenu(Options *_parent) : Menu(_parent, SELECT_MENU, STARTED_OPTION)
{
	Menu::get_option(0)->is_selectable(false);
}

matrixm::menu::SelectMenu::SelectMenu() : Menu(SELECT_MENU, STARTED_OPTION)
{
	Menu::get_option(0)->is_selectable(false);
}

matrixm::menu::SelectMenu::~SelectMenu()
{

}