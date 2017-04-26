#pragma once

#include "TypeDefs.h"

#include "Debuging.h"

namespace matrixm
{
	namespace sys
	{
		class Sign
		{
		public:
			Sign() : Sign(' ', 7)
			{}

			explicit Sign(const char& _c) : Sign(_c, 7)
			{}

			Sign(const char& _c, const ushort& _color) : color(_color), c(_c)
			{}

			char c;
			ushort color;

			Sign& operator= (const char& _c)
			{
				c = _c;
				return *this;
			}

			Sign& operator= (const ushort& _color)
			{
				color = _color;
				return *this;
			}

			bool operator==(const Sign& sign) const
			{
				return (c == sign.c && color == sign.color);
			}

			bool operator!=(const Sign& sign) const
			{
				return !(c == sign.c && color == sign.color);
			}
		};
	}
}