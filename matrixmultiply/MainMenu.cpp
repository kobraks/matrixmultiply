#include "MainMenu.h"

#include <new>
#include <string>
#include <conio.h>

#include "Exceptions.h"
#include "Msg.h"
#include "Configure.h"

#define MAIN_MENU { MSG_MAINMENU_TITLE, MSG_MAINMENU_OPTION_1, MSG_MAINMENU_OPTION_2, MSG_MAINMENU_OPTION_3, MSG_MAINMENU_OPTION_4, MSG_MAINMENU_OPTION_5 }

matrixm::menu::MainMenu::MainMenu() : Menu(MAIN_MENU, STARTED_OPTION)
{
}

matrixm::menu::MainMenu::~MainMenu()
{
}

void matrixm::menu::MainMenu::show()
{
	int key;

	while(true)
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
