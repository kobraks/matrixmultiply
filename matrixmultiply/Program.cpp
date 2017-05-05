#include "Program.h"

#include <functional>
#include <iostream>

#include "exceptions.h"
#include "Msg.h"
#include "MainMenu.h"
#include "ReadMenu.h"
#include "WriteMenu.h"

#include "MatrixMultiply.h"
#include "Console.h"

void matrixm::Program::read_file()
{
	console::Console::clear();
	system("cls");
	std::cout << MSG_LOAD_FILE_ENTER_NAME;

	std::string name;
	std::cin >> name;

	try
	{
		matrix_handler_->load(name);
		std::cout << "\n\n" << MSG_LOAD_SUCCESSFULLY << std::endl;

	}
	catch(matrix::exceptions::MatrixException ex)
	{
		std::cout << ex.what();
	}

	system("pause");
	system("cls");
}

void matrixm::Program::read_console()
{
}

void matrixm::Program::write_file()
{
	console::Console::clear();
	system("cls");
	std::cout << MSG_SAVE_FILE_ENTER_NAME;

	std::string name;
	std::cin >> name;
	std::cout << "\n\n" << MSG_SAVE_SECCESSFULLY << std::endl;

	//matrix_handler_->save(name);

	system("pause");
	system("cls");
}

void matrixm::Program::write_console()
{
	
}

void matrixm::Program::read_menu()
{
	priv_state_ = state_;
	state_ = STATE::READ_MENU;
	menu_ = new menu::ReadMenu(menu_);
	auto options = menu_->get_options();
	options[1].set_on_click_action(std::bind(&Program::read_file, this));
	options[2].set_on_click_action(std::bind(&Program::read_console, this));
	options[3].set_on_click_action(std::bind(&Program::back, this));

	console::Console::clear();
	menu_->show();

	auto parent = menu_->parent();
	delete menu_;
	menu_ = parent;
}

void matrixm::Program::back()
{
	std::swap(priv_state_, state_);
	menu_->close();
	console::Console::clear();
}

void matrixm::Program::write_menu()
{
	priv_state_ = state_;
	state_ = STATE::WRITE_MENU;
	menu_ = new menu::WriteMenu(menu_);
	auto options = menu_->get_options();
	options[1].set_on_click_action(std::bind(&Program::write_file, this));
	options[2].set_on_click_action(std::bind(&Program::write_console, this));
	options[3].set_on_click_action(std::bind(&Program::back, this));

	console::Console::clear();
	menu_->show();

	auto parent = menu_->parent();
	delete menu_;
	menu_ = parent;
}

void matrixm::Program::exit()
{
	priv_state_ = state_;
	state_ = STATE::EXIT;

	menu_->close();
}

matrixm::Program::Program()
{
	state_ = STATE::MAIN_MENU;
	priv_state_ = STATE::NONE;

	menu_= new menu::MainMenu();
	auto options = dynamic_cast<menu::MainMenu&>(*menu_).get_options();

	options[1].set_on_click_action(std::bind(&Program::read_menu, this));
	options[2].set_on_click_action(std::bind(&Program::write_menu, this));
	options[5].set_on_click_action(std::bind(&Program::exit, this));
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

bool matrixm::Program::execute()
{
	try
	{
		menu_->show();
		console::Console::clear();

		return true;
	}
	catch (matrix::exceptions::MatrixException& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	return false;
}