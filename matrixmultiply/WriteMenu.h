#pragma once
#include "Menu.h"
#include "Option.h"

#include "Debuging.h"

namespace matrixm
{
	namespace menu
	{
		class WriteMenu : public Menu
		{
		public:
			WriteMenu(Options* _parent);
			WriteMenu();
			virtual ~WriteMenu();

			void show() override;

			virtual void close();

		private:
			bool execute_;
		};
	}
}
