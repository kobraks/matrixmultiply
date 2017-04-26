#pragma once

#include "MatrixException.h"
#include "MsgException.h"

namespace matrixm
{
	namespace matrix
	{
		namespace exceptions
		{
			class MatrixMultiplyException : public MatrixException
			{
			public:
				MatrixMultiplyException() : MatrixException(MSG_MULTIPLY_EXCEPTION)
				{}
			};
		}
	}

}