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

				template<class T>
				static AbstractMatrix* create_matrix(const AbstractMatrix* _matrix, const AbstractMatrix* _matrix2);

				template<class T>
				static AbstractMatrix* multiply(const AbstractMatrix* _matrix, const AbstractMatrix* _matrix2);

				template<class T, class M1, class M2>
				static AbstractMatrix* multiply(const AbstractMatrix* _matrix, const AbstractMatrix* _matrix2);

				template<class T, class R>
				static AbstractMatrix* multiply_n(const AbstractMatrix* _matrix, const R& _number);
			};
		}
	}
}
