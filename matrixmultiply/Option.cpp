#include "Option.h"

#include <windows.h>

#include "Console.h"

using namespace matrixm;
using namespace matrixm::menu;

Option::Option() : selectable_(true), name_(""), position_(sys::Vector2i(0, 0)), color_(7), on_click_(nullptr)
{
}

Option::Option(const std::string& _option_name, bool _selectable, std::function<void()> _on_click)
: Option(_option_name, sys::Vector2i(0, 0), 7, _selectable, _on_click)
{	
}

Option::Option(const sys::Vector2i& _position, const sys::ushort& _color, bool _selectable, std::function<void()> _on_click)
: selectable_(_selectable), position_(_position), color_(_color), on_click_(_on_click)
{
}

Option::Option(const std::string& _option_name, const sys::Vector2i& _position, const sys::ushort& _color, bool _selectable, std::function<void()> _on_click)
: Option(_position, _color, _selectable, _on_click)
{
	name_ = _option_name;
}

Option::Option(const std::string& _option_name, const int& _x, const int& _y, const sys::ushort& _color, bool _selectable, std::function<void()> _on_click)
: Option(_option_name, sys::Vector2i(_x, _y), _color, _selectable, _on_click)
{
}

Option::Option(const int& _x, const int& _y, const sys::ushort& _color, bool _selectable, std::function<void()> _on_click)
: Option(sys::Vector2i(_x, _y), _color, _selectable, _on_click)
{	
}

Option::~Option()
{
	on_click_ = nullptr;
}

matrixm::sys::Vector2i Option::get_position() const
{
	return position_;
}

void Option::set_position(const int& _x, const int& _y)
{
	set_position(sys::Vector2i(_x, _y));
}

void Option::set_position(const sys::Vector2i& _position)
{
	position_ = _position;
}

int Option::get_color() const
{
	return color_;
}

void Option::set_color(int _color)
{
	color_ = _color;
}

std::string Option::get_name() const
{
	return name_;
}

void Option::set_name(const std::string& _option_name)
{
	name_ = _option_name;
}

Option& Option::operator=(const sys::Vector2i& _vector)
{
	position_ = _vector;
	return *this;
}

std::ostream& Option::write(std::ostream& _out) const
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(console, &info);

	COORD coords;
	coords.X = position_.x;
	coords.Y = position_.y;

	SetConsoleCursorPosition(console, coords);
	SetConsoleTextAttribute(console, color_);
	_out << name_;

	SetConsoleTextAttribute(console, info.wAttributes);
	SetConsoleCursorPosition(console, info.dwCursorPosition);
	return _out;
}

Option& Option::wirte()
{
	console::Console::gotoxy(position_.x, position_.y);
	console::Console::color(color_);
	console::Console::print(get_name());

	return *this;
}

void Option::delete_on_click_action()
{
	on_click_ = nullptr;
}

std::function<void()> Option::get_on_click_action() const
{
	return on_click_;
}

void Option::set_on_click_action(std::function<void()> _on_click)
{
	on_click_ = _on_click;
}

void Option::on_click()
{
	if (on_click_)
		on_click_();
}

bool Option::is_selectable()
{
	return selectable_;
}

void Option::is_selectable(bool _selectable)
{
	selectable_ = _selectable;
}

