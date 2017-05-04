#pragma once

#include "Menu.h"
#include "Option.h"
#include "typedefs.h"

#include "Debuging.h"

namespace matrixm
{
	namespace menu
	{
		class MainMenu : public Menu
		{
		public:
			MainMenu(Options* _parent);
			MainMenu();
			virtual ~MainMenu();
			virtual void close();

			void show() override;

		private:
			bool execute_;
		};
	}
}

