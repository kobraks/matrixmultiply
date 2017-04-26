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
				class ConsoleBadAllocException : public ConsoleException
				{
				public:
					ConsoleBadAllocException() : ConsoleException(MSG_CONSOLE_BAD_ALLOC_EXCEPTION)
					{  }
				};
			}
		}
	}
}