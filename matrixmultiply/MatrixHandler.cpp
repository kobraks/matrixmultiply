#include "MatrixHandler.h"

#include "Matrix.h"
#include "MatrixWriter.h"
#include "MatrixReader.h"
#include "Exceptions.h"
#include "Algorithm.h"

#include <fstream>
#include <sstream>

matrixm::matrix::MatrixHandler::MatrixHandler()
{
}


matrixm::matrix::MatrixHandler::~MatrixHandler()
{
	try
	{
		for (auto element : matrix_)
			delete element;
	}
	catch(...)
	{}

}

void matrixm::matrix::MatrixHandler::load()
{
	return;
}

void matrixm::matrix::MatrixHandler::save(const std::string& _file_name, AbstractMatrix* _matrix)
{
	if (!_matrix)
		throw exceptions::MatrixNotInitializedException();

	std::fstream file(_file_name, std::ios::in);
	if (!file.good())
	{
		file.close();
		file.open(_file_name, std::ios::in | std::ios::trunc);
		if (!file.good())
			throw exceptions::MatrixWriteOpenException();
	}

	try
	{
		AbstractMatrixWriter* mwriter = nullptr;

		if (dynamic_cast<Matrixll*>(_matrix))
		{
			mwriter = new MatrixWriterll(file);
			mwriter->write(_matrix);
		}
		else if (dynamic_cast<Matrixld*>(_matrix))
		{

			mwriter = new MatrixWriterld(file);
			mwriter->write(_matrix);
		}
		else
		{
			throw exceptions::MatrixUnknowTypeException();
		}
	}
	catch(exceptions::MatrixUnknowTypeException)
	{
		throw exceptions::MatrixUnknowTypeException();
	}
	catch(...)
	{
		throw exceptions::MatrixBadAllocException();
	}

}

void matrixm::matrix::MatrixHandler::load(const std::string& _file_name)
{
	std::fstream file(_file_name, std::ios::in);
	if (!file.good())
		throw exceptions::MatrixReadNotExistsException();
	std::stringstream stream;

	std::string line;
	while (std::getline(file, line))
		stream << line << std::endl;

	auto type = get_type(stream);
	AbstractMatrixReader* mreader = nullptr;

	try
	{
		if (type == Type::INTEGER)
			mreader = new MatrixReaderll(stream);
		else if (type == Type::FLOATING)
			mreader = new MatrixReaderld(stream);
		else
			throw exceptions::MatrixReadNotNumericTypeException();

		this->matrix_.push_back(mreader->read());

		delete mreader;
	}
	catch(exceptions::MatrixReadNotNumericTypeException)
	{
		throw exceptions::MatrixReadNotNumericTypeException();
	}
	catch (...)
	{
		throw exceptions::MatrixBadAllocException();
	}

}

matrixm::matrix::AbstractMatrix* matrixm::matrix::MatrixHandler::get_matrix(const int& _index)
{
	if (_index > 0 && _index < count())
		return matrix_[_index];
	else
		return nullptr;
}

int matrixm::matrix::MatrixHandler::count() const
{
	return matrix_.size();
}

void matrixm::matrix::MatrixHandler::remove_matrix(const int& _index)
{
	if (_index > 0 && _index < count())
	{
		delete matrix_[_index];
		matrix_.erase(matrix_.begin() + _index);
	}
}

void matrixm::matrix::MatrixHandler::add_matrix(AbstractMatrix* _matrix)
{
	if (_matrix)
		matrix_.push_back(_matrix);
}


matrixm::matrix::MatrixHandler::Type matrixm::matrix::MatrixHandler::get_type(std::istream& _stream)
{
	auto type = Type::UNKNOW;

	std::string line;
	while(std::getline(_stream, line))
	{
		std::string number;
		std::stringstream buffer(line);
		
		while (buffer >> number)
		{
			number = sys::Algorithm::replace(number, ",", ".");

			if (!is_numeric(number))
			{
				type = Type::UNKNOW;
				break;
			}
			else if ((type == Type::INTEGER || type == Type::UNKNOW) && is_floating(number))
			{
				type = Type::FLOATING;
			}
			else if (type != Type::FLOATING && type == Type::UNKNOW)
				type = Type::INTEGER; // INTEGER	
		}

		if (!buffer.eof())
			throw exceptions::MatrixReadNotNumericTypeException();

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
