#include "MatrixMath.h"

#include "exceptions.h"

matrixm::matrix::math::MatrixMath::MatrixMath(const AbstractMatrix* _matrix, const AbstractMatrix* _matrix2)
	: matrix1_(_matrix), matrix2_(_matrix2)
{
	if (!matrix1_ || !matrix2_)
		throw exceptions::MatrixNotInitializedException();

}

matrixm::matrix::math::MatrixMath::~MatrixMath()
{}


