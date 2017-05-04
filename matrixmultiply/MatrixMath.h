#pragma once

#include "Matrix.h"

namespace matrixm
{
	namespace matrix
	{
		namespace math
		{
			class MatrixMath
			{
			public:
				MatrixMath(const AbstractMatrix* _matrix, const AbstractMatrix* _matrix2);
				virtual ~MatrixMath();

				virtual AbstractMatrix* execute() = 0;

			protected:
				const AbstractMatrix* matrix1_;
				const AbstractMatrix* matrix2_;

			};
		}
	}
}

