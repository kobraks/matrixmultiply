#include "Matrix.h"

#include <new>
#include "Exceptions.h"

template <class T>
matrixm::matrix::Matrix<T>::Matrix(const sys::Vector2ui& _size) : matrix_(nullptr)
{
	try
	{
		size_ = _size;

		matrix_ = new T*[_size.x];

		for (sys::uint i = 0; i < _size.x; ++i)
			matrix_[i] = new T[_size.y];
	}
	catch (std::bad_alloc)
	{
		clear();
		throw exceptions::MatrixBadAllocException();
	}
}

template <class T>
matrixm::matrix::Matrix<T>::Matrix(const sys::uint& _x, const sys::uint& _y) : Matrix(sys::Vector2ui(_x, _y))
{	
}

template <class T>
matrixm::matrix::Matrix<T>::Matrix(const Matrix& _matrix)
{
	copy(_matrix);
}

template <class T>
matrixm::matrix::Matrix<T>::~Matrix()
{
	clear();
}

template <class T>
void matrixm::matrix::Matrix<T>::clear()
{
	if (!matrix_)
	{
		size_ = sys::Vector2ui(0, 0);
		return;
	}

	try
	{
		for (sys::uint i = 0; i < size().x; ++i)
			delete[] matrix_[i];
	}
	catch(...)
	{ }
	
	delete[] matrix_;

	matrix_ = nullptr;
	size_ = sys::Vector2ui(0, 0);
}

template <class T>
matrixm::matrix::Matrix<T>& matrixm::matrix::Matrix<T>::operator=(const Matrix<T>& _matrix)
{
	clear();

	copy(_matrix);

	return *this;
}

template <class T>
void matrixm::matrix::Matrix<T>::copy(Matrix<T>& _matrix)
{
	size_ = _matrix.size();

	try
	{
		matrix_ = new T*[size_.x];

		for (sys::uint i = 0; i < size_.x; i++)
		{
			matrix_[i] = new T[size_.y];
			std::copy(&_matrix.matrix_[i][0], &_matrix.matrix_[i][0] + _matrix.size().y, &matrix_[i][0]);
		}
	}
	catch (std::bad_alloc)
	{
		clear();
		throw exceptions::MatrixBadAllocException();
	}
}


template <class T>
T& matrixm::matrix::Matrix<T>::get(const sys::Vector2ui& _index)
{
	return get(_index.x, _index.y);
}

template <class T>
T& matrixm::matrix::Matrix<T>::get(const sys::uint& _x, const sys::uint& _y)
{
	if (out_of_range(_x, _y))
		throw exceptions::MatrixOufOfRangeExcption();

	return matrix_[_x][_y];
}

template <class T>
T matrixm::matrix::Matrix<T>::get(const sys::Vector2ui& _index) const
{
	return get(_index.x, _index.y);
}

template <class T>
T matrixm::matrix::Matrix<T>::get(const sys::uint& _x, const sys::uint& _y) const
{
	if (out_of_range(_x, _y))
		throw exceptions::MatrixOufOfRangeExcption();

	return matrix_[_x][_y];
}

template <class T>
void matrixm::matrix::Matrix<T>::set(const T& _value, const sys::Vector2ui& _index)
{
	set(_value, _index.x, _index.y);
}

template <class T>
void matrixm::matrix::Matrix<T>::set(const T& _value, const sys::uint& _x, const sys::uint& _y)
{
	if (out_of_range(_x, _y))
		throw exceptions::MatrixOufOfRangeExcption();

	matrix_[_x][_y] = _value;
}

template <class T>
void matrixm::matrix::Matrix<T>::fill(const T& _value)
{
	for (sys::uint i = 0; i < size_.x; i++)
		std::fill(&matrix_[i][0], &matrix_[i][0] + size_.y);
}

template <class T>
matrixm::sys::Vector2ui matrixm::matrix::Matrix<T>::size() const
{
	return size_;
}

template <class T>
bool matrixm::matrix::Matrix<T>::out_of_range(const sys::uint& _x, const sys::uint& _y) const
{
	return !(_x < size_.x && _y < size_.y);
}

//ta funkcja nie jest nigdzie wywo³ywana ona s³u¿y tyllko do naprawienia linker exception :p
//This funcition is not used anywhere its only for fixing the linker problems
void functionmatrix()
{
	matrixm::sys::Vector2ui size(0, 0);
	matrixm::matrix::Matrix<char> Matrixc(size);
	matrixm::matrix::Matrix<short> Matrixs(size);
	matrixm::matrix::Matrix<int> Matrixi(size);
	matrixm::matrix::Matrix<long> Matrixl(size);
	matrixm::matrix::Matrix<long long> Matrixll(size);

	matrixm::matrix::Matrix<float> Matrixf(size);
	matrixm::matrix::Matrix<double> Matrixd(size);
	matrixm::matrix::Matrix<long double> Matrixld(size);

	matrixm::matrix::Matrix<matrixm::sys::uchar> Matrixuc(size);
	matrixm::matrix::Matrix<matrixm::sys::ushort> Matrixus(size);
	matrixm::matrix::Matrix<matrixm::sys::uint> Matrixui(size);
	matrixm::matrix::Matrix<matrixm::sys::ulong> Matrixul(size);
	matrixm::matrix::Matrix<matrixm::sys::ullong> Matrixull(size);
}