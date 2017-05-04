#pragma once

#include "Debuging.h"
#include "Option.h"

namespace matrixm
{
	namespace menu
	{
		class Options
		{
		public:
			virtual void show() = 0;
			virtual int selected() const = 0;

			virtual Options* parent() = 0;
			virtual Option* get_options() const = 0;
			virtual Option* get_selected() = 0;

			virtual void close() = 0;

			virtual ~Options() {}
		};
	}
}