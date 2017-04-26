#pragma once

#include <exception>
#include <string>

namespace matrixm
{
	namespace sys
	{
		namespace console
		{
			namespace exception
			{
				class ConsoleException : std::exception
				{
				public:
					ConsoleException(const std::string& _message) : message_(_message)
					{}

					virtual const char* what() const noexcept
					{
						return message_.c_str();
					}

				private:
					std::string message_;
				};
			}
		}
	}
}