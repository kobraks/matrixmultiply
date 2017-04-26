#pragma once

#include "MatrixException.h"
#include "MsgException.h"

namespace matrixm
{
	namespace matrix
	{
		namespace exceptions
		{
			class MatrixOufOfRangeExcption : public MatrixException
			{
			public:
				MatrixOufOfRangeExcption() : MatrixException(MSG_OUT_OF_RANGE_EXCEPTION)
				{
				}
			};
		}
	}
}
