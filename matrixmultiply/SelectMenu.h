#pragma once
#include "Menu.h"
#include "Option.h"

#include "Debuging.h"

namespace matrixm
{
	namespace menu
	{
		class SelectMenu : public Menu
		{
		public:
			SelectMenu(Options* _parent);
			SelectMenu();
			virtual ~SelectMenu();
		};
	}
}