#pragma once

#include "MatrixException.h"
#include "MsgException.h"

namespace matrixm
{
	namespace matrix
	{
		namespace exceptions
		{
			class MatrixUnknowTypeException : public MatrixException
			{
			public:
				MatrixUnknowTypeException() : MatrixException(MSG_UNKNOW_TYPE_EXCEPTION)
				{  }
			};
		}
	}
}
