#include "Buffer.h"

#include <algorithm>
#include <iostream>

#include "exceptions.h"

matrixm::sys::Buffer::Buffer(const uint& _rows, const uint& _cols)
{
	console_handle_ = GetStdHandle(STD_OUTPUT_HANDLE);
	
	CONSOLE_SCREEN_BUFFER_INFO info;
	if (!GetConsoleScreenBufferInfo(console_handle_, &info))
		throw console::exception::ConsoleNoHandlerException();

	color_ = info.wAttributes;

	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = false;
	cursorInfo.dwSize = 100;

	if(!SetConsoleCursorInfo(console_handle_, &cursorInfo))
		throw console::exception::ConsoleNoHandlerException();

	size_ = Vector2ui(_rows, _cols);

	try
	{
		buffer_ = new Sign*[size_.x];
		buffer2_ = new Sign*[size_.x];

		for (uint i = 0; i < size_.x; i++)
		{
			buffer_[i] = new Sign[size_.y];
			buffer2_[i] = new Sign[size_.y];

			for (uint j = 0; j < size_.y; j++)
			{
				buffer2_[i][j] = buffer_[i][j] = Sign(' ', color_);
			}
		}

		position_.x = position_.y = 0;
	}
	catch(...)
	{
		try
		{
			for (uint i = 0; i < size_.x; i++)
			{
				delete[] buffer_[i];
				delete[] buffer2_[i];
			}
		}
		catch(...)
		{}


		delete[] buffer_;
		delete[] buffer2_;

		throw console::exception::ConsoleBadAllocException();
	}

}

matrixm::sys::Buffer::Buffer(const Vector2ui& _size) : Buffer(_size.x, _size.y)
{}

matrixm::sys::Buffer::~Buffer()
{
	try
	{
		for (uint i = 0; i < size_.x; i++)
		{
			delete[] buffer_[i];
			delete[] buffer2_[i];
		}
	}
	catch (...)
	{
	}


	delete[] buffer_;
	delete[] buffer2_;
}

void matrixm::sys::Buffer::swap()
{
	COORD coord;
	
	std::swap(buffer_, buffer2_);

	for(uint i = 0; i < size_.x; i++)
	{
		for (uint j = 0; j < size_.y; j++)
		{
			if (buffer_[i][j] != buffer2_[i][j])
			{
				coord.X = i;
				coord.Y = j;

				if(!SetConsoleTextAttribute(console_handle_, buffer_[i][j].color))
					throw console::exception::ConsoleNoHandlerException();

				if(!SetConsoleCursorPosition(console_handle_, coord))
					throw console::exception::ConsoleNoHandlerException();
				std::cout << buffer_[i][j].c;
			}
		}
	}

	coord.X = coord.Y = 0;
	if(!SetConsoleCursorPosition(console_handle_, coord))
		throw console::exception::ConsoleNoHandlerException();
}

void matrixm::sys::Buffer::clear()
{
	color_ = 7;

	for (uint i = 0; i < size_.x; i++)
	{
		for (uint j = 0; j < size_.y; j++)
			buffer2_[i][j] = Sign(' ', color_);
	}

	position_.x = position_.y = 0;
}

void matrixm::sys::Buffer::gotox(const int& _x)
{
	if (_x >= size_.x)
		position_.x = 0;
	else
		position_.x = _x;
}

void matrixm::sys::Buffer::gotoy(const int& _y)
{
	if (_y >= size_.y)
		position_.y = 0;
	else
		position_.y = _y;
}

matrixm::sys::ushort matrixm::sys::Buffer::color() const
{
	return color_;
}

void matrixm::sys::Buffer::color(const ushort& _color)
{
	color_ = _color;
}

matrixm::sys::Vector2ui matrixm::sys::Buffer::size() const
{
	return size_;
}

void matrixm::sys::Buffer::gotoxy(const int& _x, const int& _y)
{
	gotox(_x);
	gotoy(_y);
}

void matrixm::sys::Buffer::gotoxy(const Vector2i& _position)
{
	gotoxy(_position.x, _position.y);
}

int matrixm::sys::Buffer::wherex() const
{
	return position_.x;
}

int matrixm::sys::Buffer::wherey() const
{
	return position_.y;
}

matrixm::sys::Vector2i matrixm::sys::Buffer::wherexy() const
{
	return Vector2i(wherex(), wherey());
}

bool matrixm::sys::Buffer::print(const char& _c)
{
	if (position_.x >= size_.x && position_.y < size_.y)
		position_ = Vector2ui(0, ++position_.y);
	else if (position_.y >= size_.y)
		return false;

	buffer2_[position_.x][position_.y] = Sign(_c, color_);
	position_.x++;

	return true;
}

bool matrixm::sys::Buffer::print(const char* _str)
{
	const char* c = _str;
	while(*c != '\0')
	{
		if (!print(*c))
			return false;

		++c;
	}

	return true;
}

bool matrixm::sys::Buffer::print(const std::string& _str)
{
	return print(_str.c_str());
}

bool matrixm::sys::Buffer::println(const char& _c)
{
	if (!print(_c))
		return false;
	
	position_.y++;

	return true;
}

bool matrixm::sys::Buffer::println(const char* _str)
{
	if (!print(_str))
		return false;

	position_.y++;
	return true;
}

bool matrixm::sys::Buffer::println(const std::string& _str)
{
	return println(_str.c_str());
}



