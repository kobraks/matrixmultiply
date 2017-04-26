#pragma once

#include "MatrixReadException.h"
#include "MsgException.h"

namespace matrixm
{
	namespace matrix
	{
		namespace exceptions
		{
			class MatrixReadEmptyException : MatrixReadException
			{
			public:
				MatrixReadEmptyException() : MatrixReadException(MSG_READ_EMPTY_EXCEPTION)
				{
				}
			};
		}
	}
}
