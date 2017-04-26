#pragma once

#include "MatrixReadException.h"
#include "MsgException.h"

namespace matrixm
{
	namespace matrix
	{
		namespace exceptions
		{
			class MatrixReadSizeException : MatrixReadException
			{
			public:
				MatrixReadSizeException() : MatrixReadException(MSG_READ_SIZE_EXCEPTION)
				{
				}
			};
		}
	}
}