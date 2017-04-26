#pragma once

#include <ostream>
#include "Matrix.h"

namespace matrixm
{
	namespace matrix
	{
		template<class T>
		class MatrixWriter
		{
		public:
			MatrixWriter(Matrix<T> _matrix, std::ostream& _out);
		};

		typedef MatrixWriter<char> MatrixWriterc;
		typedef MatrixWriter<short> MatrixWriters;
		typedef MatrixWriter<int> MatrixWriteri;
		typedef MatrixWriter<long> MatrixWriterl;
		typedef MatrixWriter<long long> MatrixWriterll;

		typedef MatrixWriter<float> MatrixWriterf;
		typedef MatrixWriter<double> MatrixWriterd;
		typedef MatrixWriter<long double> MatrixWriterld;

		typedef MatrixWriter<sys::uchar> MatrixWriteruc;
		typedef MatrixWriter<sys::ushort> MatrixWriterus;
		typedef MatrixWriter<sys::uint> MatrixWriterui;
		typedef MatrixWriter<sys::ulong> MatrixWriterul;
		typedef MatrixWriter<sys::ullong> MatrixWriterull;
	}
}

