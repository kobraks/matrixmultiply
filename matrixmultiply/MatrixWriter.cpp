#include "MatrixWriter.h"

#include "TypeDefs.h"

template <class T>
matrixm::matrix::MatrixWriter<T>::MatrixWriter(std::ostream& _out) : out_(_out)
{
	if (!_out.good())
		throw exceptions::MatrixReadEmptyException();
}

template <class T>
void matrixm::matrix::MatrixWriter<T>::write(const AbstractMatrix* _matrix)
{
	for (sys::uint i = 0; i < _matrix->size().y; i++)
	{
		for (sys::uint j = 0; j < _matrix->size().x; j++)
			out_ << dynamic_cast<Matrix<T>>(_matrix).get(j, i) << " ";

		out_ << std::endl;
	}
}

