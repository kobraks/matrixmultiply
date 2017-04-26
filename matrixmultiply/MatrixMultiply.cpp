#include "MatrixMultiply.h"

#include "Exceptions.h"

template <class T, class M, class R>
matrixm::matrix::math::MatrixMultiply<T, M, R>::MatrixMultiply(const Matrix<M>& _matrix, const Matrix<R>& _matrix2)
	: MatrixMath<T, M, R>(_matrix, _matrix2)
{
}

template <class T, class M, class R>
matrixm::matrix::math::MatrixMultiply<T, M, R>::~MatrixMultiply()
{}

template <class T, class M, class R>
matrixm::matrix::Matrix<T> matrixm::matrix::math::MatrixMultiply<T, M, R>::execute()
{
	if (!can(matrix1_))
		throw exceptions::MatrixMultiplyException();

	Matrix<T> result();

	return result;
}

template <class T, class M, class R>
bool matrixm::matrix::math::MatrixMultiply<T, M, R>::can(const Matrix<M>& _matrix, const Matrix<R>& _matrix2)
{
	return _matrix.size() == 1 || _matrix2.size() == 1 || _matrix.size().x == _matrix2.size().y;
}
