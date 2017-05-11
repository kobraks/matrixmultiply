#pragma once

#include <exception>
#include <string>

#include "Debuging.h"

namespace matrixm
{
	namespace menu
	{
		namespace exceptions
		{
			class MenuException : public std::exception
			{
			public:
				MenuException(const std::string& _message) : message_(_message)
				{
				}

				const char* what() const throw() override
				{
					return message_.c_str();
				}

			private:
				std::string message_;
			};
		}
	}
}