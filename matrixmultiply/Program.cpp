#include "Program.h"

#include <iostream>

#include "exceptions.h"
#include "Msg.h"
#include "MainMenu.h"
#include "ReadMenu.h"
#include "WriteMenu.h"

#include "MatrixMultiply.h"
#include "Console.h"

matrixm::Program::Program()
{
	state_ = STATE::MAIN_MENU;
	priv_state_ = STATE::NONE;
	menu_ = choice_menu(state_);

	matrix_handler_ = new matrix::MatrixHandler();
}

matrixm::Program::Program(const int& argc, char** argv) : Program()
{
	//TODO interpretowanie argumentow maina, (niekonieczne!).
}


int matrixm::Program::have_argument(const std::string& _argument, const int& _argc, const char** _argv) const
{
	for (int i = 0; i < _argc; i++)
	{
		if (_argument == *_argv)
			return i;
	}

	return -1;
}

std::string matrixm::Program::get_argument_value(const std::string& _argument, const int& _argc, const char** _argv)
{
	int arg = 0;

	if ((arg = have_argument(_argument, _argc, _argv)) != -1)
	{
		return _argv[arg];
	}

	return "";
}


matrixm::Program::~Program()
{
	delete menu_;
	delete matrix_handler_;
}

matrixm::menu::Options* matrixm::Program::choice_menu(STATE _state)
{
	menu::Options* option;

	try
	{
		switch(_state)
		{
		case STATE::MAIN_MENU:
			option = new menu::MainMenu();
			break;

		case STATE::READ_MENU:
			option = new menu::ReadMenu();
			break;

		case STATE::WRITE_MENU:
			option = new menu::WriteMenu();
			break;

		default:
			option = nullptr;
		}
	}
	catch(std::bad_alloc)
	{
		throw menu::exceptions::MenuBadAllocException();
	}

	return option;
}


bool matrixm::Program::execute()
{
	try
	{
		while(true)
		{
			if (menu_)
			{
				menu_->show();
				if (!execute_option(menu_->get_selected()))
					break;
			}
			else break;


			console::Console::clear();
		}
		console::Console::clear();


		return true;
	}
	catch (matrix::exceptions::MatrixException& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	return false;
}

bool matrixm::Program::execute_option(const int& _option)
{
	priv_state_ = state_;

	if (state_ == STATE::MAIN_MENU)
	{
		switch(_option)
		{
		case 1:
			state_ = STATE::READ_MENU;
			break;
		case 2:
			state_ = STATE::WRITE_MENU;
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			state_ = STATE::EXIT;
			break;
		}
	}
	else if (state_ == STATE::READ_MENU)
	{
		std::string name;

		switch(_option)
		{
		case 1:
			//load from the file

			//console::Console::clear();
			//console::Console::print(MSG_LOAD_FILE_ENTER_NAME);
			//console::Console::swap();
			console::Console::clear();
			std::cout << MSG_LOAD_FILE_ENTER_NAME;
			std::cin >> name;

			matrix_handler_->load(name);

			break;

		case 2:
			//load from the console
			break;

		default:
			state_ = STATE::MAIN_MENU;
			break;
		}
	}
	else if (state_ == STATE::WRITE_MENU)
	{
		switch(_option)
		{
		case 1:
			//zapis do pliku
			break;

		case 2:
			//wyswietl w konsoli
			break;

		default:
			state_ = STATE::MAIN_MENU;
			break;
		}
	}

	if (state_ != priv_state_)
	{
		console::Console::swap();

		delete menu_;
		menu_ = nullptr;

		menu_ = choice_menu(state_);
	}


	if (menu_)
		return true;

	return false;
}
