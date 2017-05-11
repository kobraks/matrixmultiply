#include "WriteMenu.h"

#include "Msg.h"
#include "Configure.h"

#define WRITE_MENU { MSG_WRITEMENU_TITLE, MSG_WRITEMENU_OPTION_1, MSG_WRITEMENU_OPTION_2, MSG_MENU_BACK }

matrixm::menu::WriteMenu::WriteMenu(Options* _parent) : Menu(_parent, WRITE_MENU, STARTED_OPTION)
{
}

matrixm::menu::WriteMenu::WriteMenu() : Menu(WRITE_MENU, STARTED_OPTION)
{
}

matrixm::menu::WriteMenu::~WriteMenu()
{
	
}
