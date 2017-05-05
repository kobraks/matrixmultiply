#pragma once

#include <string>

#include "MatrixException.h"
#include "MsgException.h"

namespace matrixm
{
	namespace matrix
	{
		namespace exceptions
		{
			class MatrixWriteException : public MatrixException
			{
			public:
				MatrixWriteException(const std::string _message) : MatrixException(MSG_WRITE_EXCEPTON + _message)
				{}
			};
		}
	}
}