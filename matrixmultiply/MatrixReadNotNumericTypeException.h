#pragma once

#include "MatrixReadException.h"
#include "MsgException.h"

namespace matrixm
{
	namespace matrix
	{
		namespace exceptions
		{
			class MatrixReadNotNumericTypeException : MatrixReadException
			{
			public:
				MatrixReadNotNumericTypeException() : MatrixReadException(MSG_READ_NOT_NUMERIC_TYPE_EXCEPTION)
				{
				}
			};
		}
	}
}