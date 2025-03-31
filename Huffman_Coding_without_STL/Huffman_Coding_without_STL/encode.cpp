#include "functions.h"

void getFrequenciesForCoding(size_t* frequencies, std::istream& in); // Получение частот символов
void outputEncodedData(const CodeVector* codes, std::istream& in, std::ostream& out); // Вывод закодированных данных
bool getFileNamesForCoding(std::ifstream& in, std::ofstream& out); // Получение имён файлов

void encode()
{
	// Открытие входного и выходного файлов
	std::ifstream fin;
	std::ofstream fout;
	if (!(getFileNamesForCoding(fin, fout)))
	{
		return;
	}

	std::cout << "Начинаю кодирование...\n";
	auto startTime = std::chrono::steady_clock::now();

	// Получение частот символов
	size_t frequencies[SIZE_ARRAY_SYMBOL] = { 0 };
	getFrequenciesForCoding(frequencies, fin);

	// Построение дерева Хаффмана
	HuffmanTree codingTree;
	codingTree.assembleTree(frequencies, SIZE_ARRAY_SYMBOL);

	// Получение массива с кодами Хаффмана
	CodeVector codes[SIZE_ARRAY_SYMBOL];
	codingTree.getCodes(codes);

	// Сброс потока для входного файла
	fin.clear();
	fin.seekg(0, fin.beg);

	// Запись символов и их частот в файл
	unsigned int nSymbol = codingTree.getNumberSymbol();
	unsigned int numberSymbol = 0;
	size_t sizeSymbol = sizeof(char);
	size_t sizeFrequence = sizeof(size_t); // Объяснить
	fout.write(ID, strlen(ID));
	fout.write(reinterpret_cast<char*>(&nSymbol), sizeof(unsigned int));
	for (size_t& frequence : frequencies)
	{
		if (frequence != 0)
		{
			fout.write(reinterpret_cast<char*>(&numberSymbol), sizeSymbol);
			fout.write(reinterpret_cast<char*>(&frequence), sizeFrequence);
		}
		numberSymbol++;
	}

	// Вывод закодированных данных в файл
	outputEncodedData(codes, fin, fout);

	// Закрытие входного и выходного файлов
	fout.close();
	fin.close();

	auto endTime = std::chrono::steady_clock::now();

	StreamGuard guard(std::cout);
	std::cout << "Кодирование успешно завершено\n";
	std::cout << "Закодированные данные записаны в файл\n";
	std::cout << "Время кодирования: " << std::fixed << std::setprecision(3)
		<< ((std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count()) / 1000.0) << " c" << std::endl;
}

// Получение частот символов
void getFrequenciesForCoding(size_t* frequencies, std::istream& in)
{
	unsigned char symbol = 0;
	while (!in.eof())
	{
		symbol = in.get();
		frequencies[symbol]++;
	}
	frequencies[symbol]--;
}

// Вывод закодированных данных
void outputEncodedData(const CodeVector* codes, std::istream& in, std::ostream& out)
{
	unsigned int countBit = 0;
	unsigned char byte = 0;
	unsigned char symbol = 0;
	while (!in.eof())
	{
		symbol = in.get();
		CodeVector code = codes[symbol];
		for (unsigned int i = 0; i < code.size(); i++)
		{
			byte = byte | code[i] << (7 - countBit);
			countBit++;
			if (countBit == 8)
			{
				countBit = 0;
				out << byte;
				byte = 0;
			}
		}
	}
	if (countBit > 0)
	{
		out << byte;
	}
}

// Получение имён файлов
bool getFileNamesForCoding(std::ifstream& fin, std::ofstream& fout)
{
	// Открытие входного файла
	std::cout << "\nДля отмены данной операции введите команду BACK";
	std::cout << "\nВведите название файла с исходными данными: ";

	std::string inOutFileName;
	std::getline(std::cin, inOutFileName, '\n');
	if (inOutFileName == "BACK")
	{
		return false;
	}
	std::cout << "\nОткрываю входной файл...";
	fin.open(inOutFileName);

	while (!fin.is_open())
	{
		std::cout << "\nERROR: Не удалось открыть данный файл. Попробуйте снова";
		std::cout << "\nВведите название файла с исходными данными: ";
		std::getline(std::cin, inOutFileName, '\n');
		if (inOutFileName == "BACK")
		{
			return false;
		}
		fin.open(inOutFileName);
	}
	std::cout << "\nВходной файл " << inOutFileName << " успешно открыт\n";

	// Открытие выходного файла
	std::cout << "\nВведите название файла для закодированных данных: ";
	std::getline(std::cin, inOutFileName, '\n');
	if (inOutFileName == "BACK")
	{
		return false;
	}
	std::cout << "\nОткрываю выходной файл...";
	fout.open(inOutFileName, std::ofstream::binary);
	std::cout << "\nВыходной файл " << inOutFileName << " успешно открыт\n";

	return true;
}