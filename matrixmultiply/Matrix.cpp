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
matrixm::matrix::Matrix<T>::Matrix(const Matrix<T>& _matrix)
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
void matrixm::matrix::Matrix<T>::copy(const matrixm::matrix::Matrix<T>& _matrix)
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
		std::fill(&matrix_[i][0], &matrix_[i][0] + size_.y, _value);
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

template <class T>
std::string matrixm::matrix::Matrix<T>::type_name() const
{
	return typeid(T).name();
}


#pragma region Linker_Error_fix
//naprawa b³êdu linkera

template matrixm::matrix::Matrix<char>;
template matrixm::matrix::Matrix<short>;
template matrixm::matrix::Matrix<int>;
template matrixm::matrix::Matrix<long>;
template matrixm::matrix::Matrix<long long>;

template matrixm::matrix::Matrix<float>;
template matrixm::matrix::Matrix<double>;
template matrixm::matrix::Matrix<long double>;

template matrixm::matrix::Matrix<matrixm::sys::uchar>;
template matrixm::matrix::Matrix<matrixm::sys::ushort>;
template matrixm::matrix::Matrix<matrixm::sys::uint>;
template matrixm::matrix::Matrix<matrixm::sys::ulong>;
template matrixm::matrix::Matrix<matrixm::sys::ullong>;

#pragma endregion