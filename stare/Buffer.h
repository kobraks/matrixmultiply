#pragma once

#include <windows.h>
#include <string>

#include "Vector2.h"
#include "Sign.h"

#include "Debuging.h"

namespace matrixm
{
	namespace sys
	{
		class Buffer
		{
		public:
			Buffer(Buffer&) = delete;
			Buffer(const uint& _rows, const uint& _cols);
			explicit Buffer(const Vector2ui& _size); 
			~Buffer();

			void gotox(const int& _x);
			void gotoy(const int& _y);

			void gotoxy(const int& _x, const int& _y);
			void gotoxy(const Vector2i& _position);

			int wherex() const;
			int wherey() const;
			Vector2i wherexy() const;

			void color(const ushort& _color);
			ushort color() const;

			Vector2ui size() const;

			void clear();
			void swap();

			bool print(const char& _c);
			bool print(const char* _str);
			bool print(const std::string& _str);
		
			bool println(const char& _c);
			bool println(const char* _str);
			bool println(const std::string& _str);
		private:
			Sign **buffer_, **buffer2_;
			HANDLE console_handle_;

			ushort color_;

			Vector2ui size_;
			Vector2ui position_;
		};
	}
}