#pragma once

#include "Vector2.h"
#include "TypeDefs.h"
#include "Exceptions.h"

#include "Debuging.h"

namespace matrixm
{
	namespace matrix
	{
		template<class T>
		class Matrix
		{
		public:
			Matrix(const sys::uint& _x, const sys::uint& _y);
			explicit Matrix(const sys::Vector2ui& _size);
			Matrix(const Matrix& _matrix);
			virtual ~Matrix();

			T& get(const sys::uint& _x, const sys::uint& _y);
			T& get(const sys::Vector2ui& _index);

			T get(const sys::uint& _x, const sys::uint& _y) const;
			T get(const sys::Vector2ui& _index) const;

			void set(const T& _value, const sys::uint& _x, const sys::uint& _y);
			void set(const T& _value, const sys::Vector2ui& _index);

			void fill(const T& _value);

			sys::Vector2ui size() const;

			Matrix<T>& operator=(const Matrix<T>& _matrix);
		protected:
			bool out_of_range(const sys::uint& _x, const sys::uint& _y) const;

		private:
			T** matrix_;
			sys::Vector2ui size_;
			
			void clear();
			void copy(Matrix<T>& _matrix);
		};

		typedef Matrix<char> Matrixc;
		typedef Matrix<short> Matrixs;
		typedef Matrix<int> Matrixi;
		typedef Matrix<long> Matrixl;
		typedef Matrix<long long> Matrixll;

		typedef Matrix<float> Matrixf;
		typedef Matrix<double> Matrixd;
		typedef Matrix<long double> Matrixld;

		typedef Matrix<sys::uchar> Matrixuc;
		typedef Matrix<sys::ushort> Matrixus;
		typedef Matrix<sys::uint> Matrixui;
		typedef Matrix<sys::ulong> Matrixul;
		typedef Matrix<sys::ullong> Matrixull;
	}
}

