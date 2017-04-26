#pragma once

#include "Menu.h"
#include "Option.h"

#include "Debuging.h"

namespace matrixm
{
	namespace menu
	{
		class MainMenu : public Menu
		{
		public:
			MainMenu();
			virtual ~MainMenu();

			void show() override;
		};
	}
}

