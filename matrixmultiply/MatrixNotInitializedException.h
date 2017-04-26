#pragma once

#include "MatrixException.h"
#include "MsgException.h"

namespace matrixm
{
	namespace matrix
	{
		namespace exceptions
		{
			class MatrixNotInitializedException : public MatrixException
			{
			public:
				MatrixNotInitializedException() : MatrixException(MSG_NOT_INITIALIZED_EXCEPTION)
				{}
			};
		}
	}
}
