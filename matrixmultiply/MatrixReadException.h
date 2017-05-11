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
			class MatrixReadException : public MatrixException
			{
				public:
				explicit MatrixReadException(const std::string& _message) : MatrixException(MSG_READ_EXCEPTION + _message)
				{}
			};
		}
	}
}