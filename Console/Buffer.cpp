#include "stdafx.h"

#include "Buffer.h"
#include "ConsoleNoHandlerException.h"
#include "ConsoleBadAllocException.h"

#include <iostream>

using namespace console;

Buffer::Buffer(const unsigned& _x, const unsigned& _y)
{
	console_ = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO info;
	if (!GetConsoleScreenBufferInfo(console_, &info))
		throw console::exception::ConsoleNoHandlerException();

	color_ = info.wAttributes;

	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = false;
	cursorInfo.dwSize = 100;

	if (!SetConsoleCursorInfo(console_, &cursorInfo))
		throw console::exception::ConsoleNoHandlerException();

	size_ = Vector2ui(_x, _y);

	try
	{
		buffer1_ = new Sign*[size_.x];
		buffer2_ = new Sign*[size_.x];

		for (uint i = 0; i < size_.x; i++)
		{
			buffer1_[i] = new Sign[size_.y];
			buffer2_[i] = new Sign[size_.y];

			for (uint j = 0; j < size_.y; j++)
			{
				buffer2_[i][j] = buffer1_[i][j] = Sign(' ', color_);
			}
		}

		position_.x = position_.y = 0;
	}
	catch (...)
	{
		try
		{
			for (uint i = 0; i < size_.x; i++)
			{
				delete[] buffer1_[i];
				delete[] buffer2_[i];
			}
		}
		catch (...)
		{
		}


		delete[] buffer1_;
		delete[] buffer2_;

		throw console::exception::ConsoleBadAllocException();
	}
}


Buffer::~Buffer()
{
	try
	{
		for (uint i = 0; i < size_.x; i++)
		{
			delete[] buffer1_[i];
			delete[] buffer2_[i];
		}
	}
	catch (...)
	{
	}


	delete[] buffer1_;
	delete[] buffer2_;
}

void Buffer::swap()
{
	COORD coord;

	std::swap(buffer1_, buffer2_);

	for (uint i = 0; i < size_.x; i++)
	{
		for (uint j = 0; j < size_.y; j++)
		{
			if (buffer1_[i][j] != buffer2_[i][j])
			{
				coord.X = i;
				coord.Y = j;

				if (!SetConsoleTextAttribute(console_, buffer1_[i][j].color))
					throw console::exception::ConsoleNoHandlerException();

				if (!SetConsoleCursorPosition(console_, coord))
					throw console::exception::ConsoleNoHandlerException();
				std::cout << buffer1_[i][j].c;
			}
		}
	}

	coord.X = coord.Y = 0;
	if (!SetConsoleCursorPosition(console_, coord))
		throw console::exception::ConsoleNoHandlerException();
}

void Buffer::clear()
{
	color_ = 7;

	for (uint i = 0; i < size_.x; i++)
	{
		for (uint j = 0; j < size_.y; j++)
			buffer2_[i][j] = Sign(' ', color_);
	}

	position_.x = position_.y = 0;
}

void Buffer::clear_buffers()
{
	color_ = 7;

	for (uint i = 0; i < size_.x; i++)
	{
		for (uint j = 0; j < size_.y; j++)
			buffer1_[i][j] = buffer2_[i][j] = Sign(' ', color_);
	}

	position_.x = position_.y = 0;

	system("cls");
}


void Buffer::gotox(const int& _x)
{
	if (_x >= size_.x)
		position_.x = 0;
	else
		position_.x = _x;
}

void Buffer::gotoy(const int& _y)
{
	if (_y >= size_.y)
		position_.y = 0;
	else
		position_.y = _y;
}

void Buffer::gotoxy(const int& _x, const int& _y)
{
	gotox(_x);
	gotoy(_y);
}

int Buffer::wherex() const
{
	return position_.x;
}

int Buffer::wherey() const
{
	return position_.y;
}

Vector2i Buffer::wherexy() const
{
	return position_;
}

ushort Buffer::color() const
{
	return color_;
}

void Buffer::color(const ushort& _color)
{
	color_ = _color;
}

Vector2i Buffer::size() const
{
	return Vector2i(size_.x, size_.y);
}

bool Buffer::print(const char& _c)
{
	if (position_.x >= size_.x && position_.y < size_.y)
		position_ = Vector2ui(0, ++position_.y);
	else if (position_.y >= size_.y)
		return false;

	buffer2_[position_.x][position_.y] = Sign(_c, color_);
	position_.x++;

	return true;
}

bool Buffer::print(const char* _str)
{
	const char* c = _str;
	while (*c != '\0')
	{
		if (!print(*c))
			return false;

		++c;
	}

	return true;
}

bool Buffer::print(const std::string& _str)
{
	return print(_str.c_str());
}

bool Buffer::println(const char& _c)
{
	if (!print(_c))
		return false;

	position_.y++;

	return true;
}

bool Buffer::println(const char* _str)
{
	if (!print(_str))
		return false;

	position_.y++;
	return true;
}

bool Buffer::println(const std::string& _str)
{
	return println(_str.c_str());
}
