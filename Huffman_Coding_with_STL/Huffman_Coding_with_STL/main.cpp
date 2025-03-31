#include <iostream>
#include <string>
#include "functions.h"
#include "HuffmanTree.h"
#include <Windows.h>

inline void printMenu();
inline void executeCommand(const std::string& command);

int main()
{
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	try
	{
		printMenu();
		bool isExit = false;

		while (!isExit)
		{
			std::cout << "\nВведите команду: ";
			std::string command;
			std::getline(std::cin, command, '\n');
			if (command == "EXIT")
			{
				isExit = true;
			}
			else 
			{
				executeCommand(command);
			}
		}
	}

	catch (...)
	{
		std::cerr << "ERROR: Что-то пошло не так...\n";
		return -1;
	}

	return 0;
}

inline void printMenu()
{
	std::cout << "---------------------------------------------------------------\n";
	std::cout << "  Добро пожаловать в программу кодирования текста по Хаффману  \n";
	std::cout << "---------------------------------------------------------------\n";
	std::cout << "Список команд:\n";
	std::cout << " 1) ENCODE - закодировать текст из файла\n";
	std::cout << " 2) DECODE - раскодировать текст из файла\n";
	std::cout << " 3) COMPARE - сравнить посимвольно два файла\n";
	std::cout << " 4) EXIT - выйти из программы\n";
}

inline void executeCommand(const std::string& command)
{
	if (command == "ENCODE")
	{
		encode();
	}
	else if (command == "DECODE")
	{
		decode();
	}
	else if (command == "COMPARE")
	{
		compare();
	}
	else
	{
		std::cout << "INVALID COMMAND" << std::endl;
	}
	return;
}