#include "MatrixCore.h"

#include "Exceptions.h"

#include <sstream>
#include <algorithm>
#include <fstream>

#pragma region Constructiors


matrixm::matrix::MatrixCore::MatrixCore()
{
	size_ = sys::Vector2ui(0, 0);
	set_type(Type::UNKNOW);
	matrix_.resize(0);
}

matrixm::matrix::MatrixCore::MatrixCore(const sys::Vector2ui& _size) : MatrixCore(_size.x, _size.y)
{
}

matrixm::matrix::MatrixCore::MatrixCore(const sys::uint& _cols, const sys::uint& _rows) : MatrixCore()
{
	create(_cols, _rows);
}

matrixm::matrix::MatrixCore::MatrixCore(const MatrixCore& _core) : MatrixCore()
{
	copy(_core);
}

void matrixm::matrix::MatrixCore::create(const sys::uint& _x, const sys::uint& _y)
{
	if (!matrix_.empty())
		clear();

	size_ = sys::Vector2ui(_x, _y);

	matrix_.resize(_x * _y);
	fill(0);
}

#pragma endregion

bool matrixm::matrix::MatrixCore::is_numeric(const std::string& _string)
{
	try
	{
		std::stod(_string);
		return true;
	}
	catch(std::invalid_argument)
	{}
	catch(std::out_of_range)
	{}
	try
	{
		std::stoi(_string);
		return true;
	}
	catch(std::invalid_argument)
	{}
	catch(std::out_of_range)
	{}
	try
	{
		std::stof(_string);
	}
	catch(std::invalid_argument)
	{}
	catch(std::out_of_range)
	{}

	return false;
}

bool matrixm::matrix::MatrixCore::load_from_file(const std::string& _file_name)
{
	std::fstream file(_file_name, std::ios::in);
	
	if (!file.good() || !load_from_stream(file))
	{
		file.close();
		return false;
	}

	file.close();
	return true;
}

bool matrixm::matrix::MatrixCore::load_from_stream(std::istream& _istream)
{
	if (!_istream.good())
		return false;

	std::string line;
	std::stringstream stream;
	sys::Vector2ui size(0, 0);
	sys::uint i = 0; // iloœæ liczb w jednym wierszu

	while (std::getline(_istream, line))
	{
		stream.str("");
		std::string value;
		stream << line;

		while (stream >> value)
		{
			if (add(value))
				i++;
			else
				return false;
		}

		if (!stream.eof())
			return false;

		if (size.x != 0)
			if (size.x != i)
			{
				clear();
				return false;
			}

		size.x = i;
		i = 0;
		size.y++;
	}
	size_ = size;

	return true;
}

bool matrixm::matrix::MatrixCore::add(const std::string& _value)
{
	if (!is_numeric(_value))
		return false;

	try
	{
		if (is_floating(_value))
			set_type(Type::FLOATING);
		else
			set_type(Type::INTEGER);

		matrix_.push_back(std::make_shared<std::string>(_value));
	}
	catch (std::bad_alloc)
	{
		throw exceptions::MatrixBadAllocException();
	}

	return true;
}



bool matrixm::matrix::MatrixCore::write_to_file(const std::string& _file_name, const bool& _force_trunc) const
{
	std::fstream *file = nullptr;
	bool trunc = _force_trunc;

	try
	{
		if (!trunc)
		{
			file = new std::fstream(_file_name, std::ios::out | std::ios::app);
			if (!file->good())
			{
				file->close();
				delete file;

				trunc = true;
			}
		}
		else if(trunc)
		{
			file = new std::fstream(_file_name, std::ios::out | std::ios::trunc);

			if (!file->good())
			{
				file->close();
				delete file;

				return false;
			}
		}
	}
	catch (...)
	{
		return false;
	}

	write_on_stream(*file);

	file->close();
	delete file;

	return true;
}

std::ostream& matrixm::matrix::MatrixCore::write_on_stream(std::ostream& _ostream) const
{
	if (!_ostream.good()) return _ostream;

	for (sys::uint y = 0; y < size().y; ++y)
	{
		for (sys::uint x = 0; x < size().x; ++x)
			_ostream << get_value(x, y) << " ";

		_ostream << std::endl;
	}

	return _ostream;
}

void matrixm::matrix::MatrixCore::clear()
{
	matrix_.clear();
	matrix_.resize(0);
	size_ = sys::Vector2ui(0, 0);
	set_type(Type::UNKNOW);
}

matrixm::matrix::MatrixCore::~MatrixCore()
{
	clear();
}

matrixm::sys::Vector2ui matrixm::matrix::MatrixCore::size() const
{
	return size_;
}

matrixm::sys::uint matrixm::matrix::MatrixCore::cols() const
{
	return size_.x;
}

matrixm::sys::uint matrixm::matrix::MatrixCore::rows() const
{
	return size_.y;
}

void matrixm::matrix::MatrixCore::copy(const MatrixCore& _matrix)
{
	Type type = _matrix.get_type();
	clear();
	size_ = _matrix.size_;
	set_type(type);

	matrix_ = _matrix.matrix_;
}

matrixm::matrix::MatrixCore::Type matrixm::matrix::MatrixCore::get_type() const
{
	return type_;
}

void matrixm::matrix::MatrixCore::set_type(Type _type)
{
	type_ = _type;
}

std::string matrixm::matrix::MatrixCore::get_value(const sys::uint& _x, const sys::uint& _y) const
{
	if (!out_of_range(sys::Vector2ui(_x, _y)))
		return *matrix_[_x + _y * size().y];
	else
		throw exceptions::MatrixOufOfRangeExcption();
}

void matrixm::matrix::MatrixCore::set_value(const std::string& _value, const sys::uint& _x, const sys::uint& _y)
{
	if (!out_of_range(sys::Vector2ui(_x, _y)))
	{
		matrix_[_x + _y * size().y] = nullptr;
		matrix_[_x + _y * size().y] = std::make_shared<std::string>(_value);
	}
	else
		throw exceptions::MatrixOufOfRangeExcption();
}

bool matrixm::matrix::MatrixCore::fill(const double& _number)
{
	set_type(Type::FLOATING);
	try
	{
		fill(std::to_string(_number));
	}
	catch (...)
	{
		return false;
	}

	return true;
}

bool matrixm::matrix::MatrixCore::fill(const int& _number)
{
	set_type(Type::INTEGER);
	try
	{
		fill(std::to_string(_number));
	}
	catch(...)
	{
		return false;
	}

	return true;
}

bool matrixm::matrix::MatrixCore::fill(const std::string& _number)
{
	try
	{

		std::shared_ptr<std::string> val = std::make_shared<std::string>(_number);

		std::fill(matrix_.begin(), matrix_.end(), val);
	}
	catch(...)
	{
		return false;
	}

	return true;
}

bool matrixm::matrix::MatrixCore::is_floating(const std::string& _value)
{
	if (is_numeric(_value))
		if (_value.find(".") != std::string::npos)
			return true;

	return false;
}

bool matrixm::matrix::MatrixCore::out_of_range(const sys::Vector2ui& _index) const
{
	if (_index.x < size().x && _index.y < size().y)
		return false;
	else
		return true;
}
