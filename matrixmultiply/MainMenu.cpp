#include "MainMenu.h"

#include <new>
#include <string>
#include <conio.h>

#include "Exceptions.h"
#include "Msg.h"
#include "Configure.h"

#define MAIN_MENU { MSG_MAINMENU_TITLE, MSG_MAINMENU_OPTION_1, MSG_MAINMENU_OPTION_2, MSG_MAINMENU_OPTION_3, MSG_MAINMENU_OPTION_4, MSG_MAINMENU_OPTION_5 }

matrixm::menu::MainMenu::MainMenu(Options* _parent) : Menu(_parent, MAIN_MENU, STARTED_OPTION)
{
	Menu::get_option(0)->is_selectable(false);
}

matrixm::menu::MainMenu::MainMenu() : Menu(MAIN_MENU, STARTED_OPTION)
{
	Menu::get_option(0)->is_selectable(false);
}

matrixm::menu::MainMenu::~MainMenu()
{
}