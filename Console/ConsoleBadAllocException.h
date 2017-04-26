#pragma once

#include "Messagesh.h"
#include "ConsoleException.h"
#include "Exports.h"

namespace console
{
	namespace exception
	{
		class CONSOLE_API ConsoleBadAllocException : ConsoleException
		{
		public:
			ConsoleBadAllocException() : ConsoleException(MSG_CONSOLE_BAD_ALLOC_EXCEPTION)
			{}
		};
	}
}

