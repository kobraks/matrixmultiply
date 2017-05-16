#pragma once

#include <string>

#include "Vector2.h"

namespace matrixm
{
	namespace matrix
	{
		class AbstractMatrix
		{
		public:
			virtual std::string type_name() const = 0;
			virtual sys::Vector2ui size() const = 0;

			virtual ~AbstractMatrix() {};
		};
	}
}