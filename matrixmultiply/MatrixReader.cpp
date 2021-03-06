#include "MatrixReader.h"

#include <sstream>
#include <vector>

#include "TypeDefs.h"
#include "Vector2.h"
#include "exceptions.h"
#include "Algorithm.h"
#include <ccType>
#include <algorithm>

matrixm::matrix::MatrixReader::MatrixReader(std::istream& _stream) : size_(0, 0)
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
			number = sys::Algorithm::replace(number, ",", ".");
			
			if (!is_numeric(number))
				throw exceptions::MatrixReadNotNumericTypeException();

			detected_type_ = get_type(number);
			
			x++;
			matrix_.push_back(number);
		}

		if (size_.x == 0)
			size_.x = x;
		else if (size_.x != x)
			throw exceptions::MatrixReadSizeException();

		size_.y++;
	}
}


matrixm::matrix::MatrixReader::MatrixReader(const sys::Vector2ui& _size, std::istream& _stream) : size_(0, 0)
{
	if (!_stream.good())
		throw exceptions::MatrixReadEmptyException();
	
	if (_size == size_)
		return;

	std::string number;

	while(_stream >> number)
	{
		if (!is_numeric(number))
			throw exceptions::MatrixReadNotNumericTypeException();

		detected_type_ = get_type(number);

		matrix_.push_back(number);
		size_.x++;
		
		if (size_.x == _size.x)
		{
			if (size_.y < _size.y)
				size_.y ++;
			else 
				break;
			if (size_ != _size)
				size_.x = 0;
			else break;
		}
	}
}


matrixm::matrix::MatrixReader::MatrixReader(const sys::uint& _x, const sys::uint& _y, std::istream& _stream) 
	: MatrixReader(sys::Vector2ui(_x, _y), _stream)
{}


matrixm::matrix::MatrixReader::~MatrixReader()
{
	matrix_.clear();
	matrix_.resize(0);
}


matrixm::matrix::AbstractMatrix* matrixm::matrix::MatrixReader::read()
{
	switch(detected_type_)
	{
	case Type::INTEGER:
		return create_matrix<matrix::Type<1>::type>();
		break;
	case Type::DOUBLE:
		return create_matrix<matrix::Type<2>::type>();
		break;

	default:
		return nullptr;
	}
}


bool matrixm::matrix::MatrixReader::is_numeric(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(), s.end(), [](char c) {return !std::isdigit(c) && c == '.' ; }) == s.end();
}

matrixm::matrix::MatrixReader::Type matrixm::matrix::MatrixReader::get_type(const std::string& _s)
{
	if (sys::Algorithm::is_an<int>(_s))
		return Type::INTEGER;
	else if (sys::Algorithm::is_an<double>(_s))
		return Type::DOUBLE;
	else
		return Type::UNDEFINED;
}

int matrixm::matrix::MatrixReader::index_of_detected_type() const
{
	return static_cast<int>(detected_type_);
}

template <class T>
matrixm::matrix::Matrix<T>* matrixm::matrix::MatrixReader::create_matrix()
{
	try
	{
		Matrix<T>* matrix = new Matrix<T>(size_);
		sys::uint x = 0;
		sys::uint y = 0;

		for (auto curr = matrix_.begin(); curr != matrix_.end(); ++curr)
		{
			matrix->set(sys::Converter<T>::converts(*curr), x++, y);

			if (x == size_.x)
			{
				y++;
				x = 0;
			}
		}

		return matrix;
	}
	catch (std::bad_alloc)
	{
		throw exceptions::MatrixBadAllocException();
	}
}
