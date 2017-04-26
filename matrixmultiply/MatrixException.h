#pragma once

#include <exception>
#include <string>

#include "Debuging.h"

namespace matrixm
{
	namespace matrix
	{
		namespace exceptions
		{
			class MatrixException :
				public std::exception
			{
			public:
				MatrixException()
				{}

				MatrixException(const std::string& _message)
					: message_(_message)
				{
				}

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

