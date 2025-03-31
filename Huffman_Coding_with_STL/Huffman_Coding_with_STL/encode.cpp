#include "functions.h"

void getFrequenciesForCoding(std::array<size_t, SIZE_ARRAY_SYMBOL>& frequencies, std::istream& in); // ��������� ������ ��������
void outputEncodedData(const std::array<std::vector<bool>, SIZE_ARRAY_SYMBOL>& codes, std::istream& in, std::ostream& out); // �������� �������������� ������
bool getFileNamesForCoding(std::ifstream& in, std::ofstream& out); // ��������� ��� ������

void encode()
{
	// �������� �������� � ��������� ������
	std::ifstream fin;
	std::ofstream fout;
	if (!(getFileNamesForCoding(fin, fout)))
	{
		return;
	}

	std::cout << "������� �����������...\n";
	auto startTime = std::chrono::steady_clock::now();

	// ��������� ������ ��������
	std::array<size_t, SIZE_ARRAY_SYMBOL> frequencies = { 0 };
	getFrequenciesForCoding(frequencies, fin);

	// ���������� ������ ��������
	HuffmanTree codingTree;
	codingTree.assembleTree(frequencies);

	// ��������� ������� � ������ ��������
	std::array<std::vector<bool>, SIZE_ARRAY_SYMBOL> codes;
	codingTree.getCodes(codes);

	// ����� ������ ��� �������� �����
	fin.clear();
	fin.seekg(0, fin.beg);

	// ������ �������� � �� ������ � ����
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

	// ����� �������������� ������ � ����
	outputEncodedData(codes, fin, fout);

	// �������� �������� � ��������� ������
	fout.close();
	fin.close();

	auto endTime = std::chrono::steady_clock::now();

	StreamGuard guard(std::cout);
	std::cout << "����������� ������� ���������\n";
	std::cout << "�������������� ������ �������� � ����\n";
	std::cout << "����� �����������: " << std::fixed << std::setprecision(3)
		<< ((std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count()) / 1000.0) << std::endl;
}

// ��������� ������ ��������
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

// �������� �������������� ������
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

// ��������� ��� ������
bool getFileNamesForCoding(std::ifstream& fin, std::ofstream& fout)
{
	// �������� �������� �����
	std::cout << "\n��� ������ ������ �������� ������� ������� BACK";
	std::cout << "\n������� �������� ����� � ��������� �������: ";

	std::string inOutFileName;
	std::getline(std::cin, inOutFileName, '\n'); // input_data.txt
	if (inOutFileName == "BACK")
	{
		return false;
	}
	std::cout << "\n�������� ������� ����...";
	fin.open(inOutFileName);

	while (!fin.is_open())
	{
		std::cout << "\nERROR: �� ������� ������� ������ ����. ���������� �����";
		std::cout << "\n������� �������� ����� � ��������� �������: ";
		std::getline(std::cin, inOutFileName, '\n');
		if (inOutFileName == "BACK")
		{
			return false;
		}
		fin.open(inOutFileName);
	}
	std::cout << "\n������� ���� " << inOutFileName << " ������� ������\n";

	// �������� ��������� �����
	std::cout << "\n������� �������� ����� ��� �������������� ������: ";
	std::getline(std::cin, inOutFileName, '\n');
	if (inOutFileName == "BACK")
	{
		return false;
	}
	std::cout << "\n�������� �������� ����...";
	fout.open(inOutFileName, std::ofstream::binary);
	std::cout << "\n�������� ���� " << inOutFileName << " ������� ������\n";

	return true;
}