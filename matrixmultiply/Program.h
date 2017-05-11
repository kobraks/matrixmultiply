#pragma once

#include <string>
#include "Options.h"
#include "Matrix.h"

#include "Debuging.h"

namespace matrixm
{
	class Program
	{
	public:
		Program();
		Program(const int& argc, char** argv);
		bool execute();
		virtual ~Program();

	protected:
		enum STATE { MAIN_MENU, READ_MENU, WRITE_MENU, SELECT_MENU, EXIT, NONE };
		STATE state_;
		STATE priv_state_;

	private:

		matrixm::menu::Options *menu_;

		int have_argument(const std::string& _argument, const int& _argc, const char** argv) const;
		std::string get_argument_value(const std::string& _agument, const int& _argc, const char** _argv);

		int selected_;
		matrix::AbstractMatrix **matrix_;

		//Functions that are useing in a menu.
		void back();

		void read_menu();
		void read_file();
		void read_console();

		void write_menu();
		void write_file();
		void write_console();

		int select_matrix();

		void exit();
		void multiply();
		void addition();
	};
}
