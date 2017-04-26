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

			void load(const std::string& _file_name_);
			void load();

			Matrixll* get_matrixll(int _index);
			Matrixld* get_matrixld(int _index);

			std::vector<Matrixll*>::size_type sizell() const;
			std::vector<Matrixld*>::size_type sizeld() const;

		private:
			std::vector<Matrixll*> matrixl_;
			std::vector<Matrixld*> matrixld_;

			enum Type { INTEGER, FLOATING, UNKNOW };

			static Type get_type(std::istream& _stream);

			static bool is_numeric(const std::string& _s);
			static bool is_floating(const std::string& _s);
		};
	}
}

