#pragma once

#include "MatrixException.h"
#include "MsgException.h"

namespace matrixm
{
	namespace matrix
	{
		namespace exceptions
		{
			class MatrixBadAllocException : public MatrixException
			{
			public:
				MatrixBadAllocException() : MatrixException(MSG_BAD_ALLOC_EXCEPTION)
				{}
			};
		}
	}
}
