#pragma once

#include <string>
#include <new>
#include <exception>

#include "Exports.h"

namespace console
{
	namespace exception
	{
		class CONSOLE_API ConsoleException : std::exception
		{
		public:

			ConsoleException(const std::string& _message) : message_(_message)
			{
			}

			virtual const char* what() const noexcept
			{
				return message_.c_str();
			}

			~ConsoleException()
			{
			}

		private:
			std::string message_;
		};
	}
}

