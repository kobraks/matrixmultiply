#include "MatrixMultiply.h"

#include "Exceptions.h"

matrixm::matrix::math::MatrixMultiply::MatrixMultiply(const AbstractMatrix* _matrix, const AbstractMatrix* _matrix2)
	: MatrixMath(_matrix, _matrix2)
{
	
}

matrixm::matrix::math::MatrixMultiply::~MatrixMultiply()
{}

matrixm::matrix::AbstractMatrix* matrixm::matrix::math::MatrixMultiply::execute()
{
	if (!can(matrix1_, matrix2_))
		throw exceptions::MatrixMultiplyException();

	AbstractMatrix* result = nullptr;

	return result;
}

bool matrixm::matrix::math::MatrixMultiply::can(const AbstractMatrix* _matrix, const AbstractMatrix* _matrix2)
{
	return _matrix->size() == 1 || _matrix2->size() == 1 || _matrix->size().x == _matrix2->size().y;
}
