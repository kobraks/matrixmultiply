#include <new>
#include <exception>
#include <iostream>
#include <memory>

#include "Program.h"
#include "MsgException.h"
#include "Debuging.h"

int main(int argc, char **argv)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	try
	{
		std::shared_ptr<matrixm::Program> program(new matrixm::Program(argc, argv));

		if (program->execute())
		{
			std::cout << std::endl;
			system("pause");

			return EXIT_SUCCESS;
		}
	}
	catch (std::bad_alloc)
	{
		std::cout << MSG_PROGRAM_ALLOC_EXCEPTION << std::endl;
	}
	catch (std::exception ex)
	{
		std::cout << MSG_PROGRAM_UNKNOW_EXCEPTION << ex.what() << std::endl;
	}
	catch (...)
	{
		std::cout << MSG_PROGRAM_UNKNOW_TYPE_EXCEPTION << std::endl;
	}

	std::cout << std::endl;
	system("pause");
	return EXIT_FAILURE;
}