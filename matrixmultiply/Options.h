#pragma once

#include "Debuging.h"

namespace matrixm
{
	namespace menu
	{
		class Options
		{
		public:
			virtual void show() = 0;
			virtual int get_selected() const = 0;

			virtual ~Options() {}
		};
	}
}