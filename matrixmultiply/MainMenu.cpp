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
	execute_ = false;
}

matrixm::menu::MainMenu::MainMenu() : Menu(MAIN_MENU, STARTED_OPTION)
{
	execute_ = false;
}

matrixm::menu::MainMenu::~MainMenu()
{
}

void matrixm::menu::MainMenu::show()
{
	execute_ = true;
	int key;

	while(execute_)
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

void matrixm::menu::MainMenu::close()
{
	execute_ = false;
}
