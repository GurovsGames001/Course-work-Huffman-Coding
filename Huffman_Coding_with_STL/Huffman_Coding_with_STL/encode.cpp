#include "functions.h"

void getFrequenciesForCoding(std::array<size_t, SIZE_ARRAY_SYMBOL>& frequencies, std::istream& in); // Получение частот символов
void outputEncodedData(const std::array<std::vector<bool>, SIZE_ARRAY_SYMBOL>& codes, std::istream& in, std::ostream& out); // Создание закодированной строки
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
	std::array<size_t, SIZE_ARRAY_SYMBOL> frequencies = { 0 };
	getFrequenciesForCoding(frequencies, fin);

	// Построение дерева Хаффмана
	HuffmanTree codingTree;
	codingTree.assembleTree(frequencies);

	// Получение массива с кодами Хаффмана
	std::array<std::vector<bool>, SIZE_ARRAY_SYMBOL> codes;
	codingTree.getCodes(codes);

	// Сброс потока для входного файла
	fin.clear();
	fin.seekg(0, fin.beg);

	// Запись символов и их частот в файл
	size_t nSymbol = codingTree.getNumberSymbol();
	size_t numberSymbol = 0;
	size_t sizeSymbol = sizeof(char);
	size_t sizeFrequence = sizeof(size_t);
	fout.write(ID, strlen(ID));
	fout.write(reinterpret_cast<char*>(&nSymbol), sizeFrequence);
	std::for_each(frequencies.begin(), frequencies.end(),
		[&fout, &numberSymbol, &sizeSymbol, &sizeFrequence](size_t& frequence)
		{
			if (frequence != 0)
			{
				fout.write(reinterpret_cast<char*>(&numberSymbol), sizeSymbol);
				fout.write(reinterpret_cast<char*>(&frequence), sizeFrequence);
			}
			numberSymbol++;
		});

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
		<< ((std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count()) / 1000.0) << std::endl;
}

// Получение частот символов
void getFrequenciesForCoding(std::array<size_t, SIZE_ARRAY_SYMBOL>& frequencies, std::istream& in)
{
	in >> std::noskipws;
	std::for_each(std::istream_iterator<char>(in), std::istream_iterator<char>(), 
		[&frequencies](const unsigned char& symbol)
		{
			frequencies[symbol]++;
		});
	in >> std::skipws;
}

// Создание закодированной строки
void outputEncodedData(const std::array<std::vector<bool>, SIZE_ARRAY_SYMBOL>& codes, std::istream& in, std::ostream& out)
{
	size_t countBit = 0;
	unsigned char byte = 0;
	unsigned char symbol = 0;
	while (!in.eof())
	{
		symbol = in.get();
		std::vector<bool> code = codes[symbol];
		std::for_each(code.begin(), code.end(), 
			[&byte, &countBit, &out](const bool bit)
			{
				byte = byte | bit << (7 - countBit);
				countBit++;
				if (countBit == 8)
				{
					countBit = 0;
					out << byte;
					byte = 0;
				}
			});
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
	std::getline(std::cin, inOutFileName, '\n'); // input_data.txt
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