#include "Menu.h"

#include <conio.h>
#include <iostream>
#include <iomanip>

#include "Configure.h"
#include "exceptions.h"
#include "Msg.h"
#include "Console.h"

matrixm::menu::Menu::Menu(Options* _parent)
{
	parent_ = _parent;
	execute_ = false;
	selected_ = 0;
	show_selected_ = true;
}

matrixm::menu::Menu::Menu(Options* _parent, std::initializer_list<std::string> _options, const sys::uint& _start_selected) :
Menu(_options, _start_selected)
{
	parent_ = _parent;
	execute_ = false;
	show_selected_ = true;
}

matrixm::menu::Menu::Menu(std::initializer_list<std::string> _options, const sys::uint& _start_selected)
: selected_(_start_selected), show_selected_(true)
{
	execute_ = false;

	try
	{
		std::string space = "";
		for (auto i = 0; i < BREAK_AFTER_NUBMER; ++i)
			space += " ";

		for (sys::uint i = 0; i < _options.size(); ++i)
		{
			if (i == 0)
				options_.push_back(new Option(*(_options.begin() + i), TITLE_OPTIONS_POS_X, TITLE_OPTIONS_POS_Y));
			else
				options_.push_back(new Option(std::to_string(i) + space + *(_options.begin() + i), OPTIONS_POSITION_X, OPTIONS_POSITION_Y(i)));
		}

		if(show_selected_)
		{
			options_.push_back(new Option(MSG_CHOICE_OPTION + std::to_string(selected()), SELECTED_STRING_POSITION_X, SELECTED_STRING_POSITION_Y(options_.size() - 1)));
			options_[options_.size() - 1]->is_selectable(false);
		}

	}
	catch (std::bad_alloc)
	{
		throw exceptions::MenuBadAllocException();
	}

}


matrixm::menu::Menu::~Menu()
{
	close();
	for (auto element : options_)
		delete element;
}

int matrixm::menu::Menu::selected() const
{
	return selected_;
}

int matrixm::menu::Menu::count() const
{
	return options_.size() - 1;
}

void matrixm::menu::Menu::select(const int& _key, const int& _min_value, const int& _max_value)
{
	switch(_key)
	{
	case KEY_UP:
		select_up(_min_value, _max_value);

		break;
	case KEY_DOWN:
		select_down(_min_value, _max_value);
		break;
	default:
		if (_key - KEY_0 >= _min_value && _key - KEY_0 <= _max_value )
		{
			if (get_option(_key - KEY_0)->is_selectable())
				selected_ = _key - KEY_0;
		}
	}

	if (show_selected_) options_[options_.size() - 1]->set_name(MSG_CHOICE_OPTION + std::to_string(selected()));
}

void matrixm::menu::Menu::draw() const
{
	if (options_.empty())
		return;

	for (auto current = options_.begin(); current != options_.end(); ++current)
		(*current)->wirte();

	console::Console::swap();
}

void matrixm::menu::Menu::color_selected(const sys::ushort& _selected_color, const sys::ushort& _unselected_color)
{
	if (options_.empty())
		return;

	sys::uint b = 0;

	for (auto current = options_.begin(); current != options_.end(); ++current)
	{
		if (b == selected())
			(*current)->set_color(_selected_color);
		else
			(*current)->set_color(_unselected_color);

		b++;
	}
}

std::vector<matrixm::menu::Option*> matrixm::menu::Menu::get_options() const
{
	return options_;
}

matrixm::menu::Option* matrixm::menu::Menu::get_selected()
{
	return options_[selected_];
}

matrixm::menu::Option* matrixm::menu::Menu::get_option(int _index)
{
	if (_index < 0 || _index > options_.size() - 1)
		return nullptr;

	return options_[_index];
}


matrixm::menu::Options* matrixm::menu::Menu::parent()
{
	return parent_;
}

void matrixm::menu::Menu::show()
{
	execute_ = true;

	int key;

	while (execute_)
	{
		color_selected(SELECTED_OPTION_COLOR, NO_SELECTED_COLOR);
		draw();

		key = _getch();

		if (key != KEY_RETURN)
			select(key, 0, count());
		else
			get_selected()->on_click();
	}
}

void matrixm::menu::Menu::close()
{
	execute_ = false;
}

void matrixm::menu::Menu::add_option(Option* option)
{
	options_.push_back(option);
}

void matrixm::menu::Menu::remove_option(int _index)
{
	if (_index > 0 && _index < count())
	{
		delete options_[_index];
		options_[_index] = nullptr;

		options_.erase(options_.begin() + _index);
	}
}

void matrixm::menu::Menu::select(const int& _index)
{
	if (_index > 0 && _index < options_.size() && options_[_index]->is_selectable())
		selected_ = _index;
}

bool matrixm::menu::Menu::show_selected_option() const
{
	return show_selected_;
}

void matrixm::menu::Menu::show_selected_option(bool _show)
{
	show_selected_ = _show;
}

void matrixm::menu::Menu::select_up(const int& _min_value, const int& _max_value)
{
	if (selected_ > _min_value)
		selected_--;

	if (!options_[selected_]->is_selectable())
		if (selected_ > _min_value)
			selected_--;
		else
			selected_++;
}

void matrixm::menu::Menu::select_down(const int& _min_value, const int& _max_value)
{
	if (selected_ < _max_value)
		selected_++;

	if (!options_[selected_]->is_selectable())
		if (selected_ < _max_value)
			selected_++;
		else
			selected_--;
}
