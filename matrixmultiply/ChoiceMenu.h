#pragma once

#include <string>

#include "Menu.h"

namespace matrixm
{
	namespace menu
	{
		class ChoiceMenu : public Menu
		{
		public:
			ChoiceMenu(const std::string& _ask, Options* parent);
			ChoiceMenu(const std::string& _ask);

		private:
			virtual void select(const int& _key, const int& _min_value, const int& _max_value);
		};
	}
}