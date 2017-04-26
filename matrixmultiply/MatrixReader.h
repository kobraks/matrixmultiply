#pragma once
#include <istream>
#include <string>
#include <vector>

#include "Matrix.h"
#include "Vector2.h"
#include "TypeDefs.h"

namespace matrixm
{
	namespace matrix
	{
		template<class T>
		class MatrixReader
		{
		public:
			MatrixReader(std::istream& _stream);
			MatrixReader(const sys::Vector2ui& _size, std::istream& _stream);
			MatrixReader(const sys::uint& _x, const sys::uint& _y, std::istream& _stream);
			~MatrixReader();
		
			Matrix<T> read();

		private:
			std::vector<T> matrix_;
			sys::Vector2ui size_;

			static bool is_numeric(const std::string& s);
			static std::string replace(const std::string& _s, const std::string& _to_replace, const std::string& _replace);
		};
	}
}

//naprawa b��du linkera
#include "MatrixReader.cpp"

namespace matrixm
{
	namespace matrix
	{
		typedef MatrixReader<char> MatrixReaderc;
		typedef MatrixReader<short> MatrixReaders;
		typedef MatrixReader<int> MatrixReaderi;
		typedef MatrixReader<long> MatrixReaderl;
		typedef MatrixReader<long long> MatrixReaderll;

		typedef MatrixReader<float> MatrixReaderf;
		typedef MatrixReader<double> MatrixReaderd;
		typedef MatrixReader<long double> MatrixReaderld;

		typedef MatrixReader<sys::uchar> MatrixReaderuc;
		typedef MatrixReader<sys::ushort> MatrixReaderus;
		typedef MatrixReader<sys::uint> MatrixReaderui;
		typedef MatrixReader<sys::ulong> MatrixReaderul;
		typedef MatrixReader<sys::ullong> MatrixReaderull;
	}
}

