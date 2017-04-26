#pragma once

#include "Exports.h"
#include "ConsoleException.h"
#include "Messagesh.h"

namespace console
{
	namespace exception
	{
		class ConsoleNoHandlerException : ConsoleException
		{
		public:

			ConsoleNoHandlerException() : ConsoleException(MSG_CONSOLE_NO_HANDLER_EXCEPTION)
			{
			}

			~ConsoleNoHandlerException()
			{
			}
		};

	}
}
