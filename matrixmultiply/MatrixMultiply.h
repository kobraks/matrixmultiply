#pragma once

#include "MatrixMath.h"

namespace matrixm
{
	namespace matrix
	{
		namespace math
		{
			template <class T, class M, class R>
			class MatrixMultiply : public MatrixMath<T, M, R>
			{
			public:
				MatrixMultiply(const Matrix<M>& _matrix, const Matrix<R>& _matrix2);
				virtual ~MatrixMultiply();

				virtual Matrix<T> execute();

			private:
				static bool can(const Matrix<M>& _matrix, const Matrix<R>& _matrix2);
			};
		}
	}
}
