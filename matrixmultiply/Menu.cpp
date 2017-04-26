#include "Menu.h"

#include <iostream>
#include <iomanip>

#include "Configure.h"
#include "exceptions.h"
#include "Msg.h"
#include "Console.h"

matrixm::menu::Menu::Menu(std::initializer_list<std::string> _options, const sys::uint& _start_selected)
: options_(new Option[_options.size() + 1]), amount_options_(_options.size() + 1), selected_(_start_selected)
{
	try
	{
		std::string space = "";
		for (auto i = 0; i < BREAK_AFTER_NUBMER; ++i)
			space += " ";

		for (sys::uint i = 0; i < amount_options_ - 1; ++i)
		{
			if (i == 0)
				options_[i] = Option(*(_options.begin() + i), TITLE_OPTIONS_POS_X, TITLE_OPTIONS_POS_Y);
			else
				options_[i] = Option(std::to_string(i) + space + *(_options.begin() + i), OPTIONS_POSITION_X, OPTIONS_POSITION_Y(i));
		}

		options_[amount_options_ - 1] = Option(MSG_CHOICE_OPTION + std::to_string(get_selected()), SELECTED_STRING_POSITION_X, SELECTED_STRING_POSITION_Y(amount_options_ - 1));
	}
	catch (std::bad_alloc)
	{
		throw exceptions::MenuBadAllocException();
	}

}


matrixm::menu::Menu::~Menu()
{
	delete[] options_;
}

int matrixm::menu::Menu::get_selected() const
{
	return selected_;
}

int matrixm::menu::Menu::size() const
{
	return amount_options_ - 2;
}


void matrixm::menu::Menu::select(const int& _key, const int& _min_value, const int& _max_value)
{
	switch(_key)
	{
	case KEY_UP:
		if (selected_ > _min_value)
			selected_--;
		break;
	case KEY_DOWN:
		if (selected_ < _max_value)
			selected_++;
		break;
	default:
		if (_key - KEY_0 >= _min_value && _key - KEY_0 <= _max_value )
			selected_ = _key - KEY_0;
	}

	options_[amount_options_ - 1] = Option(MSG_CHOICE_OPTION + std::to_string(get_selected()), SELECTED_STRING_POSITION_X, SELECTED_STRING_POSITION_Y(amount_options_ - 1));
}

void matrixm::menu::Menu::draw() const
{
	for (auto current = options_; current != options_ + amount_options_; current++)
		current->wirte();

	console::Console::swap();
}

void matrixm::menu::Menu::color_selected(const sys::ushort& _selected_color, const sys::ushort& _unselected_color)
{
	sys::uint b = 0;

	for (auto current = options_; current != options_ + amount_options_; current++)
	{
		if (b == get_selected())
			current->set_color(_selected_color);
		else
			current->set_color(_unselected_color);

		b++;
	}
}