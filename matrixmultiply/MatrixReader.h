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
			Matrix<T>* create_matrix();
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

