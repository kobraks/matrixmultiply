#pragma once

#include "MatrixCore.h"
#include "TypeDefs.h"

namespace matrixm
{
	namespace matrix
	{
		class Matrix : public MatrixCore
		{
		public:
			Matrix();
			Matrix(const Matrix& _matrix);
			explicit Matrix(const sys::Vector2ui& _size);
			Matrix(const sys::uint& _x, const sys::uint& _y);

			~Matrix();

			bool addition(const Matrix& _matrix);
			void multiply(const Matrix& _matrix);

			template<class T, class = std::enable_if<std::is_arithmetic<T>::value, T>>
			void multiply(const T& _number);

			Matrix& operator = (const MatrixCore& _core);
			Matrix& operator = (const Matrix& _matrix);
		private:
			template<class T, class R, class W>
			void multiply(const Matrix& _matrix1, const Matrix& _matrix2);

			template<class T, class W>
			void addition(const Matrix& _matrix);

			static Type chose_type(const Matrix& _m1, const Matrix& _m2);
		};

#pragma region template_methods
		template<class T, class = std::enable_if<std::is_arithmetic<T>::value, T>>
		void Matrix::multiply(const T& _number)
		{
			for (uint i = 0; i < size().x; ++i)
				for (uint j = 0; j < size().y; ++j)
				{
					if (get_type() == Type::INTEGER)
					{
						this->set<int>(get<int>(i, j) * _number, i, j);
					}
					else if (get_type() == Type::FLOATING)
					{
						this->set<double>(get<double>(i, j) * _number, i, j);
					}
				}
		}
#pragma endregion

#pragma region operators
		inline Matrix operator* (const Matrix& _matrix1, const Matrix& _matrix2)
		{
			auto resoult(_matrix1);
			resoult.multiply(_matrix2);

			return resoult;
		}

		inline Matrix operator+ (const Matrix& _matrix1, const Matrix& _matrix2)
		{
			auto resoult(_matrix1);
			resoult.addition(_matrix2);

			return resoult;
		}


		template<class T, class = class std::enable_if<std::is_arithmetic<T>::value, T>>
		Matrix operator* (const Matrix& _matrix, const T& _number)
		{
			auto resoult(_matrix);
			resoult.multiply(_number);

			return resoult;
		}

		template<class T, class = class std::enable_if<std::is_arithmetic<T>::value, T>>
		Matrix operator* (const int& _number, const T& _matrix)
		{
			return _matrix * _number;
		}
#pragma endregion
	}
}
