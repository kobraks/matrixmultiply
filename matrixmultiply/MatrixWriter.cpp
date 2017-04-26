#include "MatrixWriter.h"

#include "TypeDefs.h"

template <class T>
matrixm::matrix::MatrixWriter<T>::MatrixWriter(Matrix<T> _matrix, std::ostream& _out)
{
	if (!_out.good())
		throw exceptions::MatrixReadEmptyException();

	auto size = _matrix.size();

	for (sys::uint i = 0; i < size.y; i++)
	{
		for (sys::uint j = 0; j < size.x; j++)
			_out << _matrix.get(j, i) << " ";

		_out << std::endl;
	}
}
