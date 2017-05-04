#pragma once

#include "Matrix.h"

namespace matrixm
{
	namespace matrix
	{
		class AbstractMatrixWriter
		{
		public:
			virtual void write(const AbstractMatrix* _matrix) = 0;

			virtual ~AbstractMatrixWriter()
			{}
		};
	}
}