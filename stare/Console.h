#pragma once

#include <string>

#include "Vector2.h"
#include "Typedefs.h"
#include "Buffer.h"

#include "Debuging.h"

namespace matrixm
{
	namespace sys
	{

		class Console
		{
		public:
			Console(Console&) = delete;
			~Console();

			static Console& get_instance();
			bool gotoxy(const int& _x, const int& _y);
			bool gotox(const int& _x);
			bool gotoy(const int& _y);
			int wherex() const;
			int wherey() const;
			Vector2i wherexy() const;
			void set_color(const ushort& _color);
			void clear();

			bool write(const char& _c);
			bool write(const char* _str);
			bool write(const std::string& _s);

			void show();

		private:
			Console();

			Buffer* buffer;
		};
	}
}
