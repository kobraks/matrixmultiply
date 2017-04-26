#include "MatrixHandler.h"

#include "Matrix.h"
#include "MatrixReader.h"
#include "MatrixWriter.h"
#include "Exceptions.h"

#include <fstream>
#include <sstream>

matrixm::matrix::MatrixHandler::MatrixHandler()
{
}


matrixm::matrix::MatrixHandler::~MatrixHandler()
{
	try
	{
		for (auto element : matrixl_)
			delete element;
	}
	catch(...)
	{}

	try
	{
		for (auto element : matrixld_)
			delete element;
	}
	catch(...)
	{ }
}

void matrixm::matrix::MatrixHandler::load()
{
	return;
}

void matrixm::matrix::MatrixHandler::load(const std::string& _file_name)
{
	std::fstream file(_file_name, std::ios::in);
	std::stringstream stream;

	std::string line;
	while (std::getline(file, line))
		stream << line << std::endl;

	auto type = get_type(stream);
	if (type == Type::INTEGER)
	{
		try
		{
			MatrixReaderll* mreader = new MatrixReaderll(stream);
			this->matrixl_.push_back(new Matrixll(mreader->read()));

			delete mreader;
		}
		catch(...)
		{
			throw exceptions::MatrixBadAllocException();
		}
	}
	else if (type == Type::FLOATING)
	{
		try
		{
			MatrixReaderld* mreader = new MatrixReaderld(stream);
			this->matrixld_.push_back(new Matrixld(mreader->read()));

			delete mreader;
		}
		catch (...)
		{
			throw exceptions::MatrixBadAllocException();
		}
	}
	else
	{
		throw exceptions::MatrixUnknowTypeException();
	}
}

matrixm::matrix::Matrixll* matrixm::matrix::MatrixHandler::get_matrixll(int _index)
{
	if (_index > 0 && _index < this->matrixl_.size())
		return matrixl_[_index];
	else return nullptr;
}

matrixm::matrix::Matrixld* matrixm::matrix::MatrixHandler::get_matrixld(int _index)
{
	if (_index > 0 && _index < this->matrixld_.size())
		return matrixld_[_index];
	else return nullptr;
}

std::vector<matrixm::matrix::Matrixll*>::size_type matrixm::matrix::MatrixHandler::sizell() const
{
	return matrixl_.size();
}

std::vector<matrixm::matrix::Matrixld*>::size_type matrixm::matrix::MatrixHandler::sizeld() const
{
	return matrixld_.size();
}

matrixm::matrix::MatrixHandler::Type matrixm::matrix::MatrixHandler::get_type(std::istream& _stream)
{
	auto type = Type::UNKNOW;
	
	std::string line;
	while(std::getline(_stream, line))
	{
		std::string number;
		std::stringstream buf(line);
		
		while (buf >> number)
			if (!is_numeric(number))
			{
				type = Type::UNKNOW;
				break;
			}
			else if (type == Type::INTEGER && is_floating(number))
			{
				type = Type::FLOATING;
			}
			else if (type != Type::FLOATING && type == Type::UNKNOW)
				type = Type::INTEGER; // INTEGER

	}

	_stream.clear();
	_stream.seekg(0, std::ios::beg);

	return type;
}

bool matrixm::matrix::MatrixHandler::is_numeric(const std::string& _s)
{
	try
	{
		std::stoll(_s);
	}
	catch(...)
	{
		return false;
	}
	try
	{
		std::stold(_s);
	}
	catch(...)
	{
		return false;
	}

	return true;
}


bool matrixm::matrix::MatrixHandler::is_floating(const std::string& _s)
{
	if (is_numeric(_s))
	{
		return _s.find('.') != std::string::npos;
	}

	return false;
}
