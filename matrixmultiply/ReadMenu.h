#pragma once
#include "Menu.h"
#include "Option.h"

#include "Debuging.h"

namespace matrixm
{
	namespace menu
	{
		class ReadMenu : public Menu
		{
		public:
			ReadMenu();
			virtual ~ReadMenu();

			void show() override;
		};
	}
}

