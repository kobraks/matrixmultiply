#pragma once

#include "Exports.h"
#include "Typedeffs.h"
#include "Vector2.h"
#include "Buffer.h"

#include <string>

namespace console
{
	class CONSOLE_API Console {
	public:
		Console(Console&) = delete;
		~Console();

		static void gotoxy(const int& _x, const int _y);
		static void gotox(const int& _x);
		static void gotoy(const int& _y);

		static int wherex();
		static int wherey();
		static Vector2i wherexy();

		static bool print(const char& _c);
		static bool print(const char* _str);
		static bool print(const std::string& _str);

		static bool println(const char& _c);
		static bool println(const char* _str);
		static bool println(const std::string& _str);

		static void color(const ushort& _color);
		static ushort color();

		static void clear();

		static void swap();

	private:
		static Console& get_instance();
		Console();

		Buffer* buffer_;
	};
}