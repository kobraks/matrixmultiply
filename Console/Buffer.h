#pragma once

#include <string>
#include <Windows.h>

#include "Vector2.h"
#include "Typedeffs.h"
#include "Sign.h"

namespace console
{
	class Buffer
	{
	public:
		Buffer(Buffer&) = delete;
		Buffer(const unsigned int& _x, const unsigned int& _y);

		void gotox(const int& _x);
		void gotoy(const int& _y);
		void gotoxy(const int& _x, const int& _y);

		int wherex() const;
		int wherey() const;
		Vector2i wherexy() const;

		ushort color() const;
		void color(const ushort& _color);

		Vector2i size() const;

		void clear();
		void clear_buffers();
		void swap();

		bool print(const char& _c);
		bool print(const char* _str);
		bool print(const std::string& _str);

		bool println(const char& _c);
		bool println(const char* _str);
		bool println(const std::string& _str);

		~Buffer();

	private:
		Sign** buffer1_, **buffer2_;
		HANDLE console_;

		ushort color_;

		Vector2ui size_;
		Vector2i position_;
	};
}

