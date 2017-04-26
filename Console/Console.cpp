// Console.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Console.h"
#include "ConsoleBadAllocException.h"
#include "ConsoleNoHandlerException.h"

using namespace console;


Console::Console()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info))
		throw console::exception::ConsoleNoHandlerException();

	try
	{
		buffer_ = new Buffer(info.dwMaximumWindowSize.X, info.dwMaximumWindowSize.Y);
	}
	catch (std::bad_alloc)
	{
		throw console::exception::ConsoleBadAllocException();
	}
}

Console::~Console()
{
	delete buffer_;
}

unsigned short Console::color()
{
	return Console::get_instance().buffer_->color();
}

void Console::color(const ushort& _color)
{
	Console::get_instance().buffer_->color(_color);
}

void Console::gotoxy(const int& _x, const int _y)
{
	get_instance().buffer_->gotoxy(_x, _y);
}

void Console::gotox(const int& _x)
{
	get_instance().buffer_->gotox(_x);
}

void Console::gotoy(const int& _y)
{
	get_instance().buffer_->gotoy(_y);
}

int Console::wherex()
{
	return get_instance().buffer_->wherex();
}

int Console::wherey()
{
	return get_instance().buffer_->wherey();
}

Vector2i Console::wherexy()
{
	return get_instance().buffer_->wherexy();
}

bool Console::print(const char& _c)
{
	return get_instance().buffer_->print(_c);
}

bool Console::print(const char* _str)
{
	return get_instance().buffer_->print(_str);
}

bool Console::print(const std::string& _str)
{
	return get_instance().buffer_->print(_str);
}

bool Console::println(const char& _c)
{
	return get_instance().buffer_->println(_c);
}

bool Console::println(const char* _str)
{
	return get_instance().buffer_->println(_str);
}

bool Console::println(const std::string& _str)
{
	return get_instance().buffer_->println(_str);
}

void Console::clear()
{
	get_instance().buffer_->clear_buffers();
}

void Console::swap()
{
	get_instance().buffer_->swap();
}


Console& Console::get_instance()
{
	static Console console;
	return console;
}

