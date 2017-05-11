#include "Program.h"

#include <functional>
#include <iostream>
#include <fstream>
#include <memory>

#include "exceptions.h"
#include "Msg.h"
#include "MainMenu.h"
#include "ReadMenu.h"
#include "WriteMenu.h"
#include "SelectMenu.h"

#include "MatrixMultiply.h"
#include "MatrixReader.h"
#include "MatrixWriter.h"

#include "Console.h"
#include "Algorithm.h"

#define AMOUT_OF_MATRIX 3

int matrixm::Program::select_matrix()
{
	priv_state_ = state_;
	state_ = STATE::SELECT_MENU;
	menu_ = new menu::SelectMenu(menu_);
	auto options = menu_->get_options();

	int selected = 0;

	options[1].set_on_click_action([this, &selected]() { selected = 0; back(); });
	options[2].set_on_click_action([this, &selected]() { selected = 1; back(); });
	options[3].set_on_click_action([this, &selected]() { selected = 2; back(); });
	options[4].set_on_click_action([this, &selected]() { back(); selected = -1; });

	console::Console::clear();
	menu_->show();

	auto parent = menu_->parent();
	delete menu_;
	menu_ = parent;

	return selected;
}

void matrixm::Program::read_file()
{
	if ((selected_ = select_matrix()) < 0) return;

	console::Console::clear();
	system("cls");
	std::cout << MSG_LOAD_FILE_ENTER_NAME;

	std::string name;
	std::cin >> name;

	try
	{
		std::fstream file(name, std::ios::in);
		std::unique_ptr<matrix::MatrixReader> mreader(new matrix::MatrixReader(file));
		matrix_[selected_] = mreader->read();
		file.close();

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
	console::Console::clear();
	system("cls");

	sys::Vector2ui size;

	while (true)
	{
		system("cls");
		std::string line = "";

		std::cout << MSG_SIZE_GET;
		std::getline(std::cin, line);

		int pos = 0;

		if ((pos = line.find('x')) == std::string::npos)
		{
			try
			{
				size.x = std::stoul(line);

			}
			catch (...)
			{
				std::cout << MSG_SIZE_NOT_NUMERIC << std::endl;
				system("pause");

				continue;
			}

			std::cin >> size.y;
			
			if (std::cin.fail())
			{
				std::cout << MSG_SIZE_GET_FALITUDE << std::endl;
				system("pause");

				continue;
				
			}
			break;
		}
		else
		{

			std::string width, height;
			width.insert(0, line, 0 , line.length() - pos);
			height.insert(0, line, pos + 1, line.length() - pos + 1);

			try
			{
				size.x = std::stoul(width);
				size.y = std::stoul(height);
			}
			catch(...)
			{
				std::cout << MSG_SIZE_NOT_NUMERIC << std::endl;
				system("pause");

				continue;
			}
		}

		break;
	}

	try
	{

		std::cout << MSG_LOAD_SUCCESSFULLY << std::endl;
	}
	catch(matrix::exceptions::MatrixException ex)
	{
		std::cout << ex.what();
	}


	system("pause");
	system("cls");
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

	matrix_ = new matrix::AbstractMatrix*[AMOUT_OF_MATRIX];

	for (int i = 0; i < AMOUT_OF_MATRIX; ++i)
		matrix_[i] = nullptr;

	selected_ = 0;
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
	for (int i = 0; i < AMOUT_OF_MATRIX; ++i)
		delete matrix_[i];
	delete[]matrix_;

	delete []menu_;
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