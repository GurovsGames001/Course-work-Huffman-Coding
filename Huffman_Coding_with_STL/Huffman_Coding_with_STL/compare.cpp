#include "functions.h"

bool getFileNamesForCompare(std::ifstream& fin1, std::ifstream& fin2); // Получение имён файлов

void compare()
{
	// Открытие файлов
	std::ifstream fin1;
	std::ifstream fin2;

	if (!getFileNamesForCompare(fin1, fin2))
	{
		return;
	}

	// Сравнение файлов
	std::cout << "\nНачинаю сравнение файлов\n";

	bool isEqual = true;

	isEqual = std::equal(std::istream_iterator<char>(fin1), std::istream_iterator<char>(), 
							std::istream_iterator<char>(fin2), std::istream_iterator<char>());

	std::cout << "Сравнение выполнено\n";
	if (isEqual)
	{
		std::cout << "Файлы имеют одинаковые наборы данных\n";
	}
	else
	{
		std::cout << "Файлы имеют разные наборы данных\n";
	}
}

// Получение имён файлов
bool getFileNamesForCompare(std::ifstream& fin1, std::ifstream& fin2)
{
	// Открытие первого файла
	std::cout << "\nДля отмены данной операции введите команду BACK";
	std::cout << "\nВведите название первого файла: ";

	std::string fileName;
	std::getline(std::cin, fileName, '\n');
	if (fileName == "BACK")
	{
		return false;
	}
	fin1.open(fileName);

	while (!fin1.is_open())
	{
		std::cout << "\nERROR: Не удалось открыть данный файл. Попробуйте снова";
		std::cout << "\nВведите название первого файла: ";
		std::getline(std::cin, fileName, '\n');
		if (fileName == "BACK")
		{
			return false;
		}
		fin1.open(fileName);
	}

	// Открытие второго файла
	std::cout << "\nВведите название второго файла: ";
	std::getline(std::cin, fileName, '\n');
	if (fileName == "BACK")
	{
		return false;
	}
	fin2.open(fileName);

	while (!fin2.is_open())
	{
		std::cout << "\nERROR: Не удалось открыть данный файл. Попробуйте снова";
		std::cout << "\nВведите название второго файла: ";
		std::getline(std::cin, fileName, '\n');
		if (fileName == "BACK")
		{
			return false;
		}
		fin2.open(fileName);
	}

	return true;
}