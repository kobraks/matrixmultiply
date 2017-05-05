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

			virtual void* get(const sys::uint& _x, const sys::uint& _y) = 0;
			virtual void* get(const sys::Vector2ui& _index)
			{
				return get(_index.x, _index.y);
			}

			virtual size_t get_type_size() const = 0;

			virtual ~AbstractMatrix() {};
		};
	}
}