#pragma once

#include "MsgException.h"
#include "MatrixWriteException.h"

namespace matrixm
{
	namespace matrix
	{
		namespace exceptions
		{
			class MatrixWriteEmptyMatrixException : public MatrixWriteException
			{
			public:
				MatrixWriteEmptyMatrixException() : MatrixWriteException(MSG_WRITE_EMPTY_MATRIX_EXCEPTION)
				{}
			};
		}
	}
}