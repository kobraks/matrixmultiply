#pragma once
#include <istream>
#include <string>
#include <vector>

#include "Matrix.h"
#include "Vector2.h"
#include "TypeDefs.h"
#include "Converter.h"

namespace matrixm
{
	namespace matrix
	{
		template <int T>
		class Type;

		class MatrixReader
		{
		public:
			MatrixReader(std::istream& _stream);
			MatrixReader(const sys::Vector2ui& _size, std::istream& _stream);
			MatrixReader(const sys::uint& _x, const sys::uint& _y, std::istream& _stream);
			~MatrixReader();
		
			AbstractMatrix* read();

			int index_of_detected_type() const;

		protected:
			enum class Type {UNDEFINED = 0, INTEGER = 1, DOUBLE};
			Type detected_type_;

		private:
			std::vector<std::string> matrix_;
			sys::Vector2ui size_;

			static bool is_numeric(const std::string& s);
			static Type get_type(const std::string& _s);

			template<class T>
			Matrix<T>* create_matrix()
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
				catch(std::bad_alloc)
				{
					throw exceptions::MatrixBadAllocException();
				}
			}
		};

#pragma region Type
//i only need 2 types but its a realy easy to add more

		template<>
		class Type<1>
		{
		public:
			typedef long long type;
		};

		template<>
		class Type<2>
		{
		public:
			typedef double type;
		};

#pragma endregion
	}

}

