#include "ReadMenu.h"

#include <conio.h>

#include "Msg.h"
#include "Configure.h"

#define READ_MENU { MSG_READMENU_TITLE, MSG_READMENU_OPTION_1, MSG_READMENU_OPTION_2, MSG_MENU_BACK }

matrixm::menu::ReadMenu::ReadMenu(Options *_parent) : Menu(_parent, READ_MENU, STARTED_OPTION)
{
	execute_ = false;
}

matrixm::menu::ReadMenu::ReadMenu() : Menu(READ_MENU, STARTED_OPTION)
{
	execute_ = false;
}

matrixm::menu::ReadMenu::~ReadMenu()
{
	
}


void matrixm::menu::ReadMenu::show()
{
	int key;
	execute_ = true;

	while (execute_)
	{
		color_selected(SELECTED_OPTION_COLOR, NO_SELECTED_COLOR);
		draw();

		key = _getch();

		if (key != KEY_RETURN)
			select(key, 1, count());
		else
			get_selected()->on_click();
	}
}

void matrixm::menu::ReadMenu::close()
{
	execute_ = false;
}