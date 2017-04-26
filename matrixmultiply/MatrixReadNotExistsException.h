#pragma once

#include "MatrixReadException.h"
#include "MsgException.h"

namespace matrixm
{
	namespace matrix
	{
		namespace exceptions
		{
			class MatrixReadNotExistsException : MatrixReadException
			{
			public:
				MatrixReadNotExistsException() : MatrixReadException(MSG_READ_DOES_NOT_EXIST_EXCEPTION)
				{
				}
			};
		}
	}
}