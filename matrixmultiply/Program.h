#pragma once

#include <string>
#include "Options.h"

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
		enum STATE { MAIN_MENU, READ_MENU, WRITE_MENU, EXIT, NONE };
		STATE state_;

		bool execute_option(const int& _option);
		static matrixm::menu::Options *choice_menu(STATE _state);
	private:
		STATE priv_state_;

		matrixm::menu::Options *menu_;

		int have_argument(const std::string& _argument, const int& _argc, const char** argv) const;
		std::string get_argument_value(const std::string& _agument, const int& _argc, const char** _argv);
	};
}
