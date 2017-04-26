#pragma once

#include "ConsoleException.h"
#include "MsgException.h"

namespace matrixm
{
	namespace sys
	{
		namespace console
		{
			namespace exception
			{
				class ConsoleNoHandlerException : public ConsoleException
				{
				public:
					ConsoleNoHandlerException() : ConsoleException(MSG_CONSOLE_NO_HANDLER_EXCEPTION)
					{  }
				};
			}
		}
	}
}