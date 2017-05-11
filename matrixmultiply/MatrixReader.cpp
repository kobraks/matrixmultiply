#include "MatrixReader.h"

#include <sstream>
#include <vector>

#include "TypeDefs.h"
#include "Vector2.h"
#include "exceptions.h"
#include "Algorithm.h"

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
			size_.y ++;
			size_.x = 0;
		}
	}

	if (size_ != _size)
		throw exceptions::MatrixReadSizeException();
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

matrixm::matrix::MatrixReader::Type matrixm::matrix::MatrixReader::get_type(const std::string& _s)
{
	try
	{
		std::stoll(_s);
	}
	catch(...)
	{
		return Type::INTEGER;
	}

	try
	{
		std::stold(_s);
	}
	catch(...)
	{
		return Type::DOUBLE;
	}

	return Type::UNDEFINED;
}

int matrixm::matrix::MatrixReader::index_of_detected_type() const
{
	return static_cast<int>(detected_type_);
}
