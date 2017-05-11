#include "ReadMenu.h"

#include <conio.h>

#include "Msg.h"
#include "Configure.h"

#define READ_MENU { MSG_READMENU_TITLE, MSG_READMENU_OPTION_1, MSG_READMENU_OPTION_2, MSG_MENU_BACK }

matrixm::menu::ReadMenu::ReadMenu(Options *_parent) : Menu(_parent, READ_MENU, STARTED_OPTION)
{
}

matrixm::menu::ReadMenu::ReadMenu() : Menu(READ_MENU, STARTED_OPTION)
{
}

matrixm::menu::ReadMenu::~ReadMenu()
{
	
}