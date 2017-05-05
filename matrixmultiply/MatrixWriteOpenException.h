#pragma once

#include "MsgException.h"
#include "MatrixWriteException.h"

namespace matrixm
{
	namespace matrix
	{
		namespace exceptions
		{
			class MatrixWriteOpenException : public MatrixWriteException
			{
			public:
				MatrixWriteOpenException() : MatrixWriteException(MSG_WRITE_OPEN_EXCEPTION)
				{}
			};
		}
	}
}