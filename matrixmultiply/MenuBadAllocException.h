#pragma once

#include "MenuException.h"
#include "MsgException.h"

namespace matrixm
{
	namespace menu
	{
		namespace exceptions
		{
			class MenuBadAllocException : public MenuException
			{
			public:
				MenuBadAllocException() : MenuException(MSG_MENU_BAD_ALLOC_EXCEPTION)
				{}
			};
		}
	}
}
