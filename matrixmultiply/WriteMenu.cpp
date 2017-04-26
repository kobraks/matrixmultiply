#include "WriteMenu.h"

#include <conio.h>

#include "Msg.h"
#include "Configure.h"

#define READ_MENU { MSG_READMENU_TITLE, MSG_READMENU_OPTION_1, MSG_READMENU_OPTION_2, MSG_MENU_BACK }

matrixm::menu::WriteMenu::WriteMenu() : Menu(READ_MENU, STARTED_OPTION)
{
	
}

matrixm::menu::WriteMenu::~WriteMenu()
{
	
}


void matrixm::menu::WriteMenu::show()
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

