#include "ChoiceMenu.h"

#include "Msg.h"
#include "Configure.h"

#include <string>

#define CHOICE_MENU(x) { x, MSG_YES, MSG_NO }
matrixm::menu::ChoiceMenu::ChoiceMenu(const std::string& _ask) : ChoiceMenu(_ask, nullptr)
{
}

matrixm::menu::ChoiceMenu::ChoiceMenu(const std::string& _ask, Options* parent) : Menu(parent)
{
	Menu::add_option(new Option(_ask, TITLE_OPTIONS_POS_X, TITLE_OPTIONS_POS_Y, 7, false));

	std::string yes(MSG_YES);
	std::string no(MSG_NO);

	Menu::add_option(new Option(yes, TITLE_OPTIONS_POS_X + _ask.length()/2 - yes.length(), TITLE_OPTIONS_POS_Y + 1));
	Menu::add_option(new Option(no, TITLE_OPTIONS_POS_X + _ask.length()/2 + 1, TITLE_OPTIONS_POS_Y + 1));

	Menu::select(1);
	Menu::show_selected_option(false);
}

void matrixm::menu::ChoiceMenu::select(const int& _key, const int& _min_value, const int& _max_value)
{
	switch(_key)
	{
	case KEY_LEFT:
		select_up(_min_value, _max_value);
		break;
	case KEY_RIGHT:
		select_down(_min_value, _max_value);
		break;

	default:
		if (_key == 'y' || _key == 'Y' || _key == 't' || _key == 'T')
			Menu::select(1);
		else if (_key == 'n' || _key == 'N')
			Menu::select(2);
	}

	Menu::select(_key, _min_value, _max_value);
}
