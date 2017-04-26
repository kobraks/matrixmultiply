#include "Console.h"

#include <windows.h>
#include <new>

#include "exceptions.h"

matrixm::sys::Console::Console()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info))
		throw console::exception::ConsoleNoHandlerException();

	try
	{
		buffer = new Buffer(info.dwMaximumWindowSize.X, info.dwMaximumWindowSize.Y);
	}
	catch(std::bad_alloc)
	{
		throw console::exception::ConsoleBadAllocException();
	}
}


matrixm::sys::Console::~Console()
{
	delete buffer;
}

void matrixm::sys::Console::set_color(const matrixm::sys::ushort& _color)
{
	buffer->color(_color);
}

bool matrixm::sys::Console::gotoxy(const int& _x, const int& _y)
{
	buffer->gotoxy(_x, _y);
	return true;
}

bool matrixm::sys::Console::gotox(const int& _x)
{
	buffer->gotox(_x);
	return true;
}

bool matrixm::sys::Console::gotoy(const int& _y)
{
	buffer->gotoy(_y);
	return true;
}


matrixm::sys::Console& matrixm::sys::Console::get_instance()
{
	static Console console;
	return console;
}

int matrixm::sys::Console::wherex() const
{
	return wherexy().x;
}

int matrixm::sys::Console::wherey() const
{
	return wherexy().y;
}

matrixm::sys::Vector2i matrixm::sys::Console::wherexy() const
{
	return buffer->wherexy();
}

void matrixm::sys::Console::clear()
{
	buffer->clear();
	buffer->swap();
	buffer->clear();
}

bool matrixm::sys::Console::write(const char& _c)
{
	return buffer->print(_c);
}


bool matrixm::sys::Console::write(const char* _str)
{
	return buffer->print(_str);
}

bool matrixm::sys::Console::write(const std::string& _s)
{
	return buffer->print(_s);
}

void matrixm::sys::Console::show()
{
	buffer->swap();
}


