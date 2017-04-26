#pragma once

#include <string>
#include <sstream>

#include "Debuging.h"

namespace matrixm
{
	namespace sys
	{
		template<class T>
		class Converter
		{
		public:
			static T converts(const std::string& _string)
			{
				std::stringstream stream(_string);
				T resoult;

				stream >> resoult;
				return resoult;
			}

			static std::string convert(const T& _value)
			{
				std::stringstream stream;
				stream << _value;

				return stream.str();
			}
		};
	}
}

