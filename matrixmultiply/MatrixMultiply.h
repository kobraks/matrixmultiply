#pragma once

#include "MatrixMath.h"

namespace matrixm
{
	namespace matrix
	{
		namespace math
		{
			class MatrixMultiply : public MatrixMath
			{
			public:
				MatrixMultiply(const AbstractMatrix* _matrix, const AbstractMatrix* _matrix2);
				virtual ~MatrixMultiply();

				virtual AbstractMatrix* execute();

			private:
				static bool can(const AbstractMatrix* _matrix, const AbstractMatrix* _matrix2);
			};
		}
	}
}
