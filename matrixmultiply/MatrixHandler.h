#pragma once

#include <string>
#include <vector>

#include "Matrix.h"

namespace matrixm
{
	namespace matrix
	{
		class MatrixHandler
		{
		public:
			MatrixHandler();
			~MatrixHandler();

			void load(const std::string& _file_name);
			void load();

			void save(const std::string& _file_name, AbstractMatrix* _matrix);
			void show(const AbstractMatrix* _matrix);

			AbstractMatrix* get_matrix(const int& _index);
			void remove_matrix(const int& _index);

			void add_matrix(AbstractMatrix* _matrix);

			int count() const;

		private:
			std::vector<AbstractMatrix*> matrix_;

			enum Type { INTEGER, FLOATING, UNKNOW };

			static Type get_type(std::istream& _stream);

			static bool is_numeric(const std::string& _s);
			static bool is_floating(const std::string& _s);
		};
	}
}

