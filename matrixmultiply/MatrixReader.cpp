#include "MatrixReader.h"

#include <sstream>
#include <vector>

#include "Converter.h"
#include "TypeDefs.h"
#include "Vector2.h"
#include "exceptions.h"

template <class T>
matrixm::matrix::MatrixReader<T>::MatrixReader(std::istream& _stream) : size_(0, 0)
{
	if (!_stream.good())
		throw exceptions::MatrixReadEmptyException();

	std::string line;

	while(std::getline(_stream, line))
	{
		sys::uint x = 0;
		std::string number;
		std::stringstream sstream(line);

		while(sstream >> number)
		{
			number = replace(number, ",", ".");
			
			if (!is_numeric(number))
				throw exceptions::MatrixReadNotNumericTypeException();
			
			x++;
			matrix_.push_back(sys::Converter<T>::converts(number));
		}

		if (size_.x == 0)
			size_.x = x;
		else if (size_.x != x)
			throw exceptions::MatrixReadSizeException();

		size_.y++;
	}
}

template <class T>
matrixm::matrix::MatrixReader<T>::MatrixReader(const sys::Vector2ui& _size, std::istream& _stream) : size_(0, 0)
{
	if (!_stream.good())
		throw exceptions::MatrixReadEmptyException();
	
	std::string number;

	while(_stream >> number)
	{
		if (!is_numeric(number))
			throw exceptions::MatrixReadNotNumericTypeException();

		matrix_.push_back(sys::Converter<T>::converts(number));

		size_.x++;
		if (size_.x == _size.x)
		{
			size_.y ++;
			size_.x = 0;
		}
	}

	if (size_ != _size)
		throw exceptions::MatrixReadSizeException();
}

template <class T>
matrixm::matrix::MatrixReader<T>::MatrixReader(const sys::uint& _x, const sys::uint& _y, std::istream& _stream) 
	: MatrixReader(sys::Vector2ui(_x, _y), _stream)
{}

template <class T>
matrixm::matrix::MatrixReader<T>::~MatrixReader()
{
	matrix_.clear();
	matrix_.resize(0);
}

template <class T>
matrixm::matrix::Matrix<T> matrixm::matrix::MatrixReader<T>::read()
{
	Matrix<T> matrix(size_);
	sys::uint x = 0;
	sys::uint y = 0;

	for(auto curr = matrix_.begin(); curr != matrix_.end(); ++curr)
	{
		matrix.set(*curr, x++, y);

		if (x == size_.x)
		{
			y++;
			x = 0;
		}
	}

	return matrix;
}

template <class T>
bool matrixm::matrix::MatrixReader<T>::is_numeric(const std::string& s)
{
	try
	{
		std::stoll(s);
		return true;
	}
	catch (...)
	{}

	try
	{
		std::stold(s);
		return true;
	}
	catch (...)
	{}

	return false;
}

template <class T>
std::string matrixm::matrix::MatrixReader<T>::replace(const std::string& _s, const std::string& _to_replace, const std::string& _replace)
{
	std::string result;

	std::string::size_type pos = 0;
	while ((pos = _s.find(_to_replace, pos)) != std::string::npos)
	{
		result.insert(result.length(), _s, 0, pos);
		result += _replace;
		pos += _to_replace.length() - 1;
	}

	return result;
}