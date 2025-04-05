#include "functions.h"

void getFrequenciesForDecoding(size_t* frequencies, std::istream& in); // Получение частот символов
bool getFileNamesForDecoding(std::ifstream& in, std::ofstream& out); // Получение имён файлов

void decode()
{
	// Открытие входного и выходного файлов
	std::ifstream fin;
	std::ofstream fout;
	if (!(getFileNamesForDecoding(fin, fout)))
	{
		return;
	}

	std::cout << "Начинаю декодирование...\n";
	auto startTime = std::chrono::steady_clock::now();

	// Считывание частот символов и создание массива с ними
	size_t frequencies[SIZE_ARRAY_SYMBOL] = { 0 };
	getFrequenciesForDecoding(frequencies, fin);

	// Построение дерева Хаффмана
	HuffmanTree decodingTree;
	decodingTree.assembleTree(frequencies, SIZE_ARRAY_SYMBOL);

	// Вывод раскодированных данных в файл
	decodingTree.outputDecodingData(fin, fout);

	// Закрытие входного и выходного файлов
	fout.close();
	fin.close();

	auto endTime = std::chrono::steady_clock::now();

	StreamGuard guard(std::cout);
	std::cout << "Декодирование успешно завершено\n";
	std::cout << "Раскодированные данные записаны в файл\n";
	std::cout << "Время декодирования: " << std::fixed << std::setprecision(3)
		<< ((std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count()) / 1000.0) << " c" << std::endl;
}

// Получение частот символов
void getFrequenciesForDecoding(size_t* frequencies, std::istream& in)
{
	unsigned int nSymbol = 0;
	unsigned char symbol = 0;
	size_t frequence = 0;
	size_t sizeSymbol = sizeof(char);
	size_t sizeFrequence = sizeof(size_t);

	in.read(reinterpret_cast<char*>(&nSymbol), sizeof(unsigned int));
	if ((nSymbol > 256) || (nSymbol < 0))
	{
		throw std::logic_error("ERROR: Что-то пошло не так...");
	}
	for (unsigned int i = 0; i < nSymbol; i++)
	{
		in.read(reinterpret_cast<char*>(&symbol), sizeSymbol);
		in.read(reinterpret_cast<char*>(&frequence), sizeFrequence);
		frequencies[symbol] = frequence;
	}
}

// Получение имён файлов
bool getFileNamesForDecoding(std::ifstream& fin, std::ofstream& fout)
{
	// Открытие входного файла
	bool isFileOpen = false;
	std::string inOutFileName;
	char tempID[21] = "\0";

	std::cout << "\nДля отмены данной операции введите команду BACK";
	while (!isFileOpen)
	{
		std::cout << "\nВведите название файла с закодированными данными: ";
		std::getline(std::cin, inOutFileName, '\n');
		if (inOutFileName == "BACK")
		{
			return false;
		}
		std::cout << "\nОткрываю входной файл...";
		fin.open(inOutFileName, std::ifstream::binary);
		while (!fin.is_open())
		{
			std::cout << "\nERROR: Не удалось открыть данный файл. Попробуйте снова\n";
			std::cout << "\nВведите название файла с закодированными данными: ";
			std::getline(std::cin, inOutFileName, '\n');
			if (inOutFileName == "BACK")
			{
				return false;
			}
			fin.open(inOutFileName, std::ifstream::binary);
		}
		fin.read(tempID, strlen(ID));
		if (strcmp(tempID, ID) != 0)
		{
			std::cout << "\nERROR: Данный файл не является закодированным. Попробуйте снова\n";
			fin.close();
		}
		else
		{
			isFileOpen = true;
		}
	}

	std::cout << "\nВходной файл " << inOutFileName << " успешно открыт\n";

	// Открытие выходного файла
	std::cout << "\nВведите название файла для раскодированных данных: ";
	std::getline(std::cin, inOutFileName, '\n');
	if (inOutFileName == "BACK")
	{
		return false;
	}
	std::cout << "\nОткрываю выходной файл...";
	fout.open(inOutFileName);
	std::cout << "\nВыходной файл " << inOutFileName << " успешно открыт\n";

	return true;
}