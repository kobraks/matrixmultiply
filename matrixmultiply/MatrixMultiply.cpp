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

	if (dynamic_cast<Matrixld*>(const_cast<AbstractMatrix*>(matrix1_)) || dynamic_cast<Matrixld*>(const_cast<AbstractMatrix*>(matrix2_)))
	{
		result = multiply<long double>(matrix1_, matrix2_);

	}
	else if (dynamic_cast<Matrixll*>(const_cast<AbstractMatrix*>(matrix1_)) && dynamic_cast<Matrixll*>(const_cast<AbstractMatrix*>(matrix2_)))
	{
		result = multiply<long long>(matrix1_, matrix2_);
	}
	else
		throw exceptions::MatrixUnknowTypeException();


	return result;
}

bool matrixm::matrix::math::MatrixMultiply::can(const AbstractMatrix* _matrix, const AbstractMatrix* _matrix2)
{
	return _matrix->size() == 1 || _matrix2->size() == 1 
			|| _matrix->size().x == _matrix2->size().y 
			|| _matrix->size().y == _matrix2->size().x;
}

template <class T>
matrixm::matrix::AbstractMatrix* matrixm::matrix::math::MatrixMultiply::create_matrix(const AbstractMatrix* _matrix, const AbstractMatrix* _matrix2)
{
	if (_matrix->size() == 1)
		return new Matrix<T>(_matrix2->size());
	else if (_matrix2->size() == 1)
		return new Matrix<T>(_matrix->size());
	else
		return new Matrix<T>(_matrix->size().x, _matrix2->size().y);
}

template <class T>
matrixm::matrix::AbstractMatrix* matrixm::matrix::math::MatrixMultiply::multiply(const AbstractMatrix* _matrix, const AbstractMatrix* _matrix2)
{
	int t1, t2;

	t1 = t2 = 0;

	if (dynamic_cast<Matrixll*>(const_cast<AbstractMatrix*>(_matrix)))
		t1 = 1;
	else if (dynamic_cast<Matrixld*>(const_cast<AbstractMatrix*>(_matrix)))
		t1 = 2;

	if (dynamic_cast<Matrixll*>(const_cast<AbstractMatrix*>(_matrix2)))
		t2 = 1;
	else if (dynamic_cast<Matrixld*>(const_cast<AbstractMatrix*>(_matrix2)))
		t2 = 2;

	if (t1 == 1 && t2 == 1)
		return multiply<T, long long, long long>(_matrix, _matrix2);
	else if (t1 == 1 && t2 == 2)
		return multiply<T, long long, long double>(_matrix, _matrix2);
	else if (t1 == 2 && t2 == 1)
		return multiply<T, long double, long long>(_matrix, _matrix2);
	else if (t1 == 2 && t2 == 2)
		return multiply<T, long double, long double>(_matrix, _matrix2);
	else
		throw exceptions::MatrixUnknowTypeException();
}

template <class T, class R>
matrixm::matrix::AbstractMatrix* matrixm::matrix::math::MatrixMultiply::multiply_n(const AbstractMatrix* _matrix, const R& _number)
{
	Matrix<T>* result = new Matrix<T>(_matrix->size());
	Matrix<T>* matrix = dynamic_cast<Matrix<T>*>(const_cast<AbstractMatrix*>(_matrix));


	for (sys::uint i = 0; i < result->size().y; ++i)
	{
		for (sys::uint j = 0; j < result->size().x; ++j)
		{
			result->set(matrix->get(j, i) * _number, sys::Vector2ui(j, i));
		}
	}

	return result;
}
 
template <class T, class M1, class M2>
matrixm::matrix::AbstractMatrix* matrixm::matrix::math::MatrixMultiply::multiply(const AbstractMatrix* _matrix, const AbstractMatrix* _matrix2)
{
	Matrix<M1>* matrix = dynamic_cast<Matrix<M1>*>(const_cast<AbstractMatrix*>(_matrix));
	Matrix<M1>* matrix2 = dynamic_cast<Matrix<M1>*>(const_cast<AbstractMatrix*>(_matrix2));

	if (_matrix->size() == 1)
	{
		M1 number = matrix->get(0, 0);
		return multiply_n<T, M1>(_matrix2, number);
	}
	else if (_matrix2->size() == 1)
	{
		M2 number = matrix2->get(0, 0);
		return multiply_n<T, M2>(_matrix2, number);
	}
	else
	{
		Matrix<T>* result = dynamic_cast<Matrix<T>*>(create_matrix<T>(_matrix, _matrix2));

		for (sys::uint i = 0; i < _matrix->size().y; ++i)
		{
			for(sys::uint j = 0; j < _matrix2->size().x; ++j)
			{
				T s = 0;

				for (sys::uint k = 0; k < _matrix->size().x; ++k)
					s += matrix->get(k, i) * matrix2->get(j, k);

				result->set(s, j, i);
			}
		}

		return result;
	}

}
