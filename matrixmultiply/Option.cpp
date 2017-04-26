#include "Option.h"

#include <windows.h>

#include "Console.h"

using namespace matrixm;
using namespace matrixm::menu;

Option::Option() : name_(""), color_(7), position_(sys::Vector2i(0, 0))
{
}

Option::Option(const std::string& _option_name) : Option(_option_name, sys::Vector2i(0, 0))
{
	
}

Option::Option(const sys::Vector2i& _position, const sys::ushort& _color) : position_(_position), color_(_color)
{
}

Option::Option(const std::string& _option_name, const sys::Vector2i& _position, const sys::ushort& _color) : Option(_position, _color)
{
	name_ = _option_name;
}

Option::Option(const std::string& _option_name, const int& _x, const int& _y, const sys::ushort& _color) : Option(_option_name, sys::Vector2i(_x, _y), _color)
{
}

Option::Option(const int& _x, const int& _y, const sys::ushort& _color) : Option(sys::Vector2i(_x, _y), _color)
{	
}

Option::~Option()
{
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
