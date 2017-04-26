#include "MatrixMath.h"

template <class T, class M, class G>
matrixm::matrix::math::MatrixMath<T, M, G>::MatrixMath(const Matrix<M>& _matrix, const Matrix<G>& _matrix2) 
	: matrix1_(_matrix), matrix2_(_matrix2)
{}

template <class T, class M, class G>
matrixm::matrix::math::MatrixMath<T, M, G>::~MatrixMath()
{}


