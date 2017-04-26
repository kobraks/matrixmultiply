#include "Matrix.h"

#include "Exceptions.h"

#pragma region constructors

matrixm::matrix::Matrix::Matrix()
{
}

matrixm::matrix::Matrix::Matrix(const Matrix& _matrix) : MatrixCore(static_cast<MatrixCore>(_matrix))
{
}

matrixm::matrix::Matrix::Matrix(const sys::Vector2ui& _size) : MatrixCore(_size)
{
}

matrixm::matrix::Matrix::Matrix(const sys::uint& _x, const sys::uint& _y) : Matrix(sys::Vector2ui(_x, _y))
{
}

#pragma endregion

matrixm::matrix::Matrix::~Matrix()
{
}

matrixm::matrix::MatrixCore::Type matrixm::matrix::Matrix::chose_type(const Matrix& _m1, const Matrix& _m2)
{
	if (_m1.get_type() == Type::FLOATING || _m2.get_type() == Type::FLOATING)
		return Type::FLOATING;
	else if (_m1.get_type() == Type::INTEGER && _m2.get_type() == Type::INTEGER)
		return Type::INTEGER;
	else return Type::UNKNOW;
}

bool matrixm::matrix::Matrix::addition(const Matrix& _matrix)
{
	if (_matrix.size() != size())
		return false;

	set_type(chose_type(_matrix, *this));

	if (_matrix.get_type() == Type::UNKNOW) throw exceptions::MatrixUnknowTypeException();

	if (get_type() == Type::INTEGER)
		addition<int, int>(_matrix);
	else if (get_type() == Type::FLOATING)
	{
		if (_matrix.get_type() == Type::FLOATING)
			addition<double, double>(_matrix);
		else
			addition<double, int>(_matrix);

	}
	else
		throw exceptions::MatrixUnknowTypeException();

	return true;
}

template <class T, class W>
void matrixm::matrix::Matrix::addition(const Matrix& _matrix)
{
	for (sys::uint i = 0; i < size().x; i++)
	{
		for (sys::uint j = 0; j < size().y; j++)
			set<T>(get<T>(i, j) + _matrix.get<W>(i, j), i, j);
	}
}

void matrixm::matrix::Matrix::multiply(const Matrix& _matrix)
{
	if (size() == 1)
	{
		Type type = chose_type(*this, _matrix);
		
		if (type == Type::INTEGER)
		{
			auto v = get<int>(0, 0);
			copy(_matrix);
			this->multiply<int>(v);
		}
		else
		{ }
	}
	else if (size().x == _matrix.size().y || _matrix.size() == 1 && size() != 1)
	{
		Matrix matrix;
		matrix.copy(*this);

		this->create(_matrix.size().x, matrix.size().y);
		set_type(chose_type(_matrix, matrix));

		//wybór wersji algorytmu, aby zwiêkszyæ wiarygodnoœæ wyników
		if (matrix.get_type() == Type::FLOATING)
		{
			if (_matrix.get_type() == Type::INTEGER)
				multiply<double, double, int>(matrix, _matrix);
			else if (_matrix.get_type() == Type::FLOATING)
				multiply<double, double, double>(matrix, _matrix);
			else 
				throw exceptions::MatrixUnknowTypeException();
		}
		else if (matrix.get_type() == Type::INTEGER)
		{
			if (_matrix.get_type() == Type::INTEGER)
				multiply<int, int, int>(matrix, _matrix);
			else if (_matrix.get_type() == Type::FLOATING)
				multiply<double, int, double>(matrix, _matrix);
			else
				throw exceptions::MatrixUnknowTypeException();
		}
		else
			throw exceptions::MatrixUnknowTypeException();
	}
	else throw exceptions::MatrixMultiplyException();
}

template <class T, class R, class W>
void matrixm::matrix::Matrix::multiply(const Matrix& _matrix1, const Matrix& _matrix2)
{
	for (sys::uint i = 0; i < _matrix1.size().y; ++i)
	{
		for (sys::uint j = 0; j < _matrix2.size().x; ++j)
		{
			T sum = 0;

			for (sys::uint k = 0; k < _matrix1.size().x; ++k)
				sum += _matrix1.get<R>(k, i) * _matrix2.get<W>(j, k);

			set<T>(sum, j, i);
		}
	}
}

matrixm::matrix::Matrix& matrixm::matrix::Matrix::operator=(const MatrixCore& _core)
{
	copy(_core);

	return *this;
}

matrixm::matrix::Matrix& matrixm::matrix::Matrix::operator=(const Matrix& _matrix)
{
	*this = *dynamic_cast<MatrixCore*>(const_cast<Matrix*>(&_matrix));
	return *this;
}

