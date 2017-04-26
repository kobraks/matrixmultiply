#pragma once

#include "MatrixException.h"
#include "MsgException.h"

namespace matrixm
{
	namespace matrix
	{
		namespace exceptions
		{
			class MatrixAdditionException : public MatrixException
			{
			public:
				MatrixAdditionException() : MatrixException(MSG_ADDITION_EXCEPTION)
				{  }
			};
		}
	}
}
