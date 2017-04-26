#include "ReadMenu.h"

#include <conio.h>

#include "Msg.h"
#include "Configure.h"

#define READ_MENU { MSG_READMENU_TITLE, MSG_READMENU_OPTION_1, MSG_READMENU_OPTION_2, MSG_MENU_BACK }

matrixm::menu::ReadMenu::ReadMenu() : Menu(READ_MENU, STARTED_OPTION)
{
	
}

matrixm::menu::ReadMenu::~ReadMenu()
{
	
}


void matrixm::menu::ReadMenu::show()
{
	int key;

	while (true)
	{
		color_selected(SELECTED_OPTION_COLOR, NO_SELECTED_COLOR);
		draw();

		key = _getch();

		if (key != KEY_RETURN)
			select(key, 1, size());
		else
			break;
	}
}

