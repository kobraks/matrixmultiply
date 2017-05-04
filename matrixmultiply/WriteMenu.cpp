#include "WriteMenu.h"

#include <conio.h>

#include "Msg.h"
#include "Configure.h"

#define WRITE_MENU { MSG_WRITEMENU_TITLE, MSG_WRITEMENU_OPTION_1, MSG_WRITEMENU_OPTION_2, MSG_MENU_BACK }

matrixm::menu::WriteMenu::WriteMenu(Options* _parent) : Menu(_parent, WRITE_MENU, STARTED_OPTION)
{
	execute_ = false;
}

matrixm::menu::WriteMenu::WriteMenu() : Menu(WRITE_MENU, STARTED_OPTION)
{
	execute_ = false;
}

matrixm::menu::WriteMenu::~WriteMenu()
{
	
}


void matrixm::menu::WriteMenu::show()
{
	execute_ = true;

	int key;

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


void matrixm::menu::WriteMenu::close()
{
	execute_ = false;
}
