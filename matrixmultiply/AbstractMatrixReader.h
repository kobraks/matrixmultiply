#pragma once

#include "AbstractMatrix.h"

namespace matrixm
{
	namespace matrix
	{
		class AbstractMatrixReader
		{
		public:

			virtual AbstractMatrix* read() = 0;

			virtual ~AbstractMatrixReader()
			{}
		};
	}
}