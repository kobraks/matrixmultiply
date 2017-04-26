#pragma once

#include "Matrix.h"

namespace matrixm
{
	namespace matrix
	{
		namespace math
		{
			template<class T, class M, class R>
			class MatrixMath
			{
			public:
				MatrixMath(const Matrix<M>& _matrix, const Matrix<R>& _matrix2);
				virtual ~MatrixMath();

				virtual Matrix<T> execute() = 0;

			protected:
				const Matrix<M>& matrix1_;
				const Matrix<R>& matrix2_;

			};
		}
	}
}

