#pragma once

#include <type_traits>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

#include "Vector2.h"
#include "TypeDefs.h"
#include "exceptions.h"

namespace matrixm
{
	namespace matrix
	{
		class MatrixCore
		{
		public:
			enum class Type { INTEGER, FLOATING, UNKNOW };

			MatrixCore();
			MatrixCore(const MatrixCore& _core);
			MatrixCore(const sys::uint& _cols, const sys::uint& _rows);
			explicit MatrixCore(const sys::Vector2ui& _size);

			~MatrixCore();

			bool load_from_file(const std::string& _file_name);
			bool load_from_stream(std::istream& _istream);
			bool write_to_file(const std::string& _file_name, const bool& _force_trunc = false) const;
			std::ostream& write_on_stream(std::ostream& _ostream) const;

			sys::Vector2ui size() const;
			sys::uint cols() const;
			sys::uint rows() const;

			Type get_type() const;

			friend std::ostream& operator<< (std::ostream& _out, const MatrixCore& _core);

			bool fill(const int& _number);
			bool fill(const double& _number);

			template<class T, class = std::enable_if<std::is_arithmetic<T>::value, T>>
			void set(const T& _value, const sys::uint& _col, const sys::uint& _row);
			template<class T, class = std::enable_if<std::is_arithmetic<T>::value, T>>
			void set(const T& _value, const sys::Vector2ui& _index);

			template<class T, class = std::enable_if<std::is_arithmetic<T>::value, T>>
			T get(const sys::uint& _col, const sys::uint& _row) const;
			template<class T, class = std::enable_if<std::is_arithmetic<T>::value, T>>
			T get(const sys::Vector2ui& _index) const;
		protected:
			void create(const sys::uint& _x, const sys::uint& _y);
			void copy(const MatrixCore& _matrix);
			void clear();

			static bool is_numeric(const std::string& _string);

			std::string get_value(const sys::uint& _x, const sys::uint& _y) const;
			void set_value(const std::string& _value, const sys::uint& _x, const sys::uint& _y);

			void set_type(Type _type);
		private:
			std::vector<std::shared_ptr<std::string>> matrix_;
			sys::Vector2ui size_;
			Type type_;

			bool add(const std::string& _value);
			bool fill(const std::string& _number);
			bool out_of_range(const sys::Vector2ui& _index) const;
			static bool is_floating(const std::string& _value);

			template<class T>
			static std::string to_string(const T& _number);
			template<class T>
			static T from_string(const std::string& _string);
		};

#pragma region template_methods
#pragma region public
		template<class T, class = std::enable_if<std::is_arithmetic<T>::value, T>>
		void MatrixCore::set(const T& _value, const sys::uint& _col, const sys::uint& _row)
		{
			if (out_of_range(sys::Vector2ui(_col, _row)))
				throw exceptions::MatrixOufOfRangeExcption();

			std::string value = to_string<T>(_value);
			set_value(value, _col, _row);

			if (is_floating(value)) set_type(Type::FLOATING);
			else set_type(Type::INTEGER);
		}

		template<class T, class = std::enable_if<std::is_arithmetic<T>::value, T>>
		void MatrixCore::set(const T& _value, const sys::Vector2ui& _index)
		{
			set<T>(_value, _index.x, _index.y);
		}

		template<class T, class = std::enable_if<std::is_arithmetic<T>::value, T>>
		T MatrixCore::get(const sys::uint& _col, const sys::uint& _row) const
		{
			if (out_of_range(sys::Vector2ui(_col, _row)))
				throw exceptions::MatrixOufOfRangeExcption();

			return from_string<T>(get_value(_col, _row));
		}

		template<class T, class = std::enable_if<std::is_arithmetic<T>::value, T>>
		T MatrixCore::get(const sys::Vector2ui& _index) const
		{
			return get<T>(_index.x, _index.y);
		}
#pragma endregion

#pragma region private
		template<class T>
		std::string MatrixCore::to_string(const T& _number)
		{
			std::stringstream stream;
			stream << _number;

			return stream.str();
		}

		template<class T>
		T MatrixCore::from_string(const std::string& _string)
		{
			std::stringstream stream(_string);
			T value;
			stream >> value;

			return value;
		}
#pragma endregion

#pragma endregion

#pragma region operators
		inline std::ostream& operator<< (std::ostream& _out, const MatrixCore& _core)
		{
			return _core.write_on_stream(_out);
		}
#pragma endregion
	}
}